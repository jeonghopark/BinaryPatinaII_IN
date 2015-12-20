//
//  MoonCreator.cpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//

#include "MoonCreator.hpp"


//--------------------------------------------------------------
MoonCreator::MoonCreator(){
    
    
}



//--------------------------------------------------------------
MoonCreator::~MoonCreator(){
    
    
}


//--------------------------------------------------------------
void MoonCreator::setup(){
    
    
    cam.setNearClip(0.0001f);
    cam.setFarClip(10000.0f);
    cam.toggleControl();

    
    meshMoon.setMode(OF_PRIMITIVE_POINTS);
    
    
    csv.loadFile(ofToDataPath("MoonCreator.csv"));
    
    float _radiusMoon = 700;
    
    mesh.clear();
    
    point3D.resize(csv.data.size());
    lineLengthRandom.resize(csv.data.size());
    
    for (int i=0; i<point3D.size(); i++) {
        
        float _lon = ofToFloat(csv.data[i][0]);
        float _lat = ofToFloat(csv.data[i][1]);
        float _size = ofToFloat(csv.data[i][1]);
        
        ofVec3f _v;
        _v.x = _radiusMoon * cos(ofDegToRad(_lat)) * cos(ofDegToRad(_lon));
        _v.y = _radiusMoon * cos(ofDegToRad(_lat)) * sin(ofDegToRad(_lon));
        _v.z = _radiusMoon *sin(ofDegToRad(_lat));
        
        creatorCoord.push_back(_v);
        creatorSize.push_back(_size * 0.3);
        
        meshMoon.addVertex( _v );
        meshMoon.addColor( ofColor(255) );
        
        ofVec3f _point3D = _v;
        mesh.addVertex(_point3D);
        mesh.addNormal(_point3D);
        
        ofColor _c = ofColor(255);
        mesh.addColor(_c);
        
        point3D[i].point3DRaw = _point3D;
        
        lineLengthRandom[i] = ofRandom(0.5, 1.5);
        
    }
    
    creatorSetting();

    returnBase();
    
    lineFFTFactor = 1;
    
    
    
}



//--------------------------------------------------------------
void MoonCreator::update(){
    
    auto pushed = in.keyPushed;
    auto holded = in.keyHolded;
    auto pulled = in.keyPulled;
    
    if( pushed[GLFW_KEY_LEFT_SHIFT] ) cam.movespeed = 7.0f;
    if( pulled[GLFW_KEY_LEFT_SHIFT] ) cam.movespeed = 1.0f;
    
    if( pushed[GLFW_MOUSE_BUTTON_LEFT] ) paint.push_back( ofPolyline() );
    if( holded[GLFW_MOUSE_BUTTON_LEFT] ) paint.back().addVertex( cam.getPosition() + (cam.getLookAtDir() * 50.0f) );
    
    if( pushed[GLFW_MOUSE_BUTTON_RIGHT] ) cam.toggleControl();
    
    
//    cout << cam.getPosition() << endl;
//    cout << cam.getLookAtDir() << endl;
    

    
}


//--------------------------------------------------------------
void MoonCreator::draw(){
    
//    cam.begin();
//    
////    meshMoon.draw();
//    creatorDraw();
//    
//    drawLines();
//    
//    cam.end();

    
}


//--------------------------------------------------------------
void MoonCreator::creatorSetting(){
    
    for (int i=0; i<point3D.size(); i++) {
        
        point3D[i].radiusCreater = creatorSize[i];
        
        point3D[i].p1 = ofVec3f(0,0,0);
        point3D[i].p2 = mesh.getVertex(i);
        point3D[i].createrMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        
        point3D[i].norm = (point3D[i].p2 - point3D[i].p1).normalize();
        
        point3D[i].u = point3D[i].norm.getCrossed(ofVec3f(1, 0, 0));
        point3D[i].v = point3D[i].norm.getCrossed(point3D[i].u);
        
        for (int t = 0; t <= 360; t+=10) {
            float _rad = ofDegToRad(t);
            ofVec3f pt = point3D[i].p2 + point3D[i].radiusCreater * cos(_rad) * point3D[i].u + point3D[i].radiusCreater * sin(_rad) * point3D[i].v;
            
            ofColor _c = ofColor(255);
            point3D[i].createrMesh.addColor(_c);
            point3D[i].createrMesh.addVertex(pt);
            point3D[i].vboCreator.setMesh(point3D[i].createrMesh, GL_STATIC_DRAW);
        }
        
    }
    
}


//--------------------------------------------------------------
void MoonCreator::drawLines(){

    cam.begin();

    
    ofEnableAlphaBlending();
    
    ofPushStyle();
    
    
    int _fftIndex = processFFT->getSpectrum().size();

    float _fftLength = processFFT->getMidVal();
    cout << _fftLength << endl;
    
    ofSetColor(moonMiddlelinesColor);
    
    
    for (int i=0; i<meshMoon.getNumVertices(); i++) {
        ofPoint _pS = ofPoint(0, 0, 0);
        ofPoint _pE = ofPoint(meshMoon.getVertex(i).x, meshMoon.getVertex(i).y, meshMoon.getVertex(i).z) * lineLengthRandom[i] * _fftLength * lineFFTFactor;
        ofDrawLine(_pS, _pE);
    }
    
    ofPopStyle();
    
    
    ofDisableAlphaBlending();
    
    cam.end();


}




//--------------------------------------------------------------
void MoonCreator::creatorDraw(){
    
    
    cam.begin();

    
    ofEnableAlphaBlending();

    ofPushStyle();
    
    ofSetColor(255);
    
    for (int i=0; i<point3D.size(); i++) {
        point3D[i].vboCreator.draw(GL_LINE_STRIP, 0, 37);
    }
    
    ofPopStyle();
    
    ofDisableAlphaBlending();

    cam.end();
    
}


//--------------------------------------------------------------
void MoonCreator::returnBase(){
    
    ofVec3f _vP = ofVec3f(-1820.91, -1051.97, -179.716);
    cam.setPosition( _vP );
    
    ofVec3f _vL = ofVec3f(0.806166, 0.531315, -0.260386);
    cam.lookAt( _vL );
    
}







