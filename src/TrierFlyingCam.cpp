//
//  TrierFlyingCam.cpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//

#include "TrierFlyingCam.hpp"

//--------------------------------------------------------------
TrierFlyingCam::TrierFlyingCam(){
    

}


//--------------------------------------------------------------
TrierFlyingCam::~TrierFlyingCam(){
    
    
}


//--------------------------------------------------------------
void TrierFlyingCam::setup(){
    
    cam.setNearClip(0.0001f);
    cam.setFarClip(10000.0f);
    cam.toggleControl();

    
    jsonDataSetup();
    
    mainLight = ofLight();
    mainLight.setPointLight();
    mainLight.setGlobalPosition(-100, 0, 500);
    mainLight.setDiffuseColor(ofColor(35, 35, 35));
    mainLight.setSpecularColor(ofColor(170, 170, 170));

    returnBase();
    
}


//--------------------------------------------------------------
void TrierFlyingCam::jsonDataSetup(){
    
    FeatureNode* _rootNode_33975_22294;
    
    JsonLoader _jsonLoader_33975_22294 = JsonLoader("OSMJSON.json");
    _rootNode_33975_22294 = _jsonLoader_33975_22294.loadNodeGraph();
    
    ofxJSONElement _jsonMain;
    _jsonMain = _jsonLoader_33975_22294.jsonRoot;
    
    ofxJSONElement _jsonBuildings;
    _jsonBuildings = _jsonMain["features"];
    
    
    for (int i=0; i<_jsonBuildings.size(); i++) {
        
        string _way = _jsonBuildings[i]["id"].asString();
        
        if (_way.at(0) == 'w') {
            ofxJSONElement _jsonBuilding;
            _jsonBuilding = _jsonBuildings[i]["geometry"]["coordinates"][0];
            
            ofMesh _m;
            _m.setMode(OF_PRIMITIVE_LINE_LOOP);
            
            ofPolyline _pl;
            _pl.setClosed(false);
            _pl.begin();
            
            string _polygon = _jsonBuildings[i]["geometry"]["type"].asString();
            
            if (_polygon == "Polygon") {
                
                for (int j=0; j<_jsonBuilding.size(); j++) {
                    
                    ofxJSONElement _coordinateBuilding;
                    _coordinateBuilding = _jsonBuilding[j];
                    
                    
                    ofVec2f _v;
                    _v.x = _jsonLoader_33975_22294.lon2x(_coordinateBuilding[0].asFloat()) - 740603;
                    _v.y = _jsonLoader_33975_22294.lat2y(_coordinateBuilding[1].asFloat()) - 6.40447e+06;
                    
                    
                    _m.addVertex(_v);
                    _m.addColor( ofColor(255) );
                    
                    _pl.addVertex( _v );
                    
                }
                
                
                buildings_33975_22294.push_back( _m );
                
                _pl.end();
                buildingsPolyline_33975_22294.push_back(_pl);
            }
            
        }
        
        
    }
    
    
    
    ofxJSONElement _jsonRoads;
    _jsonRoads = _jsonMain["features"];
    
    for (int i=0; i<_jsonRoads.size(); i++) {
        ofxJSONElement _jsonRoad;
        
        
        string _way = _jsonRoads[i]["id"].asString();
        
        if (_way.at(0) == 'w') {
            
            ofMesh _m;
            _m.setMode(OF_PRIMITIVE_LINE_STRIP);
            
            ofPolyline _pl;
            
            string _LineString = _jsonRoads[i]["geometry"]["type"].asString();
            
            if (_LineString == "LineString") {
                
                _jsonRoad = _jsonRoads[i]["geometry"]["coordinates"];
                
                for (int j=0; j<_jsonRoad.size(); j++) {
                    
                    ofxJSONElement _coordinateRoad;
                    _coordinateRoad = _jsonRoad[j];
                    
                    ofVec2f _v;
                    _v.x = _jsonLoader_33975_22294.lon2x(_jsonRoad[j][0].asFloat()) - 740603;
                    _v.y = _jsonLoader_33975_22294.lat2y(_jsonRoad[j][1].asFloat()) - 6.40447e+06;
                    
                    _m.addVertex(_v);
                    _m.addColor( ofColor(255) );
                    
                    _pl.addVertex(_v);
                    
                    
                }
                
                roads_33975_22294.push_back( _m );
                roadsPolyline_33975_22294.push_back( _pl );
                
                
            } else {
                
                //                _jsonRoad = _jsonRoads[i]["geometry"]["coordinates"][0];
                //
                //                for (int j=0; j<_jsonRoad.size(); j++) {
                //
                //                    ofxJSONElement _coordinateRoad;
                //                    _coordinateRoad = _jsonRoad[j];
                //
                //                    ofVec2f _v;
                //                    _v.x = _jsonLoader_33975_22294.lon2x(_jsonRoad[j][0].asFloat()) - 740603;
                //                    _v.y = _jsonLoader_33975_22294.lat2y(_jsonRoad[j][1].asFloat()) - 6.40447e+06;
                //
                //                    _m.addVertex(_v);
                //                    _m.addColor( ofColor(255) );
                //
                //                    _pl.addVertex(_v);
                //
                //                }
                //
                //                roads_33975_22294.push_back( _m );
                //                roadsPolyline_33975_22294.push_back( _pl );
                
            }
            
        }
        
    }
    
    
    
    _rootNode_33975_22294->setPosition(0, 0, 0);
    _rootNode_33975_22294->printPosition("");
    
//    camera = ofEasyCam();
//    camera.setPosition(_rootNode_33975_22294->getGlobalPosition());
//    camera.move(0, 0, 300);
//    camera.setTarget(_rootNode_33975_22294->getGlobalPosition());

}




//--------------------------------------------------------------
void TrierFlyingCam::update(){
    
    auto pushed = in.keyPushed;
    auto holded = in.keyHolded;
    auto pulled = in.keyPulled;
    
    if( pushed[GLFW_KEY_LEFT_SHIFT] ) cam.movespeed = 7.0f;
    if( pulled[GLFW_KEY_LEFT_SHIFT] ) cam.movespeed = 1.0f;
    
    if( pushed[GLFW_MOUSE_BUTTON_LEFT] ) paint.push_back( ofPolyline() );
    if( holded[GLFW_MOUSE_BUTTON_LEFT] ) paint.back().addVertex( cam.getPosition() + (cam.getLookAtDir() * 50.0f) );
    
    if( pushed[GLFW_MOUSE_BUTTON_RIGHT] ) cam.toggleControl();
    
    
    roadMovingFactor_33975_22294 = roadMovingFactor_33975_22294 + 1;
    roadMoving_33975_22294 = sin( ofDegToRad(roadMovingFactor_33975_22294) ) * 0.5 + 0.5;
    

    simpleHands = leapMotion->getSimpleHands();

    if( leapMotion->isFrameNew() && simpleHands.size() ){
        ofPoint _p;
        if (!leapMotionPause) {
            _p = ofPoint( simpleHands[0].yaw * -8, simpleHands[0].pitch * 10 - 2 );
        } else {
            _p = ofPoint( 0, 0 );
        }
        cam.nodeRotateLeapMotion( _p );
        
    }
    
    
    camera.lookAt(cam.getLookAtDir());
    camera.setGlobalPosition(cam.getGlobalPosition());
    camera.setGlobalOrientation(cam.getGlobalOrientation());
    
//    cout << cam.getLookAtDir() << endl;
//    cout << cam.getPosition() << endl;
//    cout << cam.getGlobalOrientation() << endl;
//    cout << cam.getModelViewProjectionMatrix() << endl;
    
}


//--------------------------------------------------------------
void TrierFlyingCam::draw(){
    
    
    //    ofEnableLighting();
    
    
    cam.begin();
    
    
    ofEnableAlphaBlending();
    
    //    mainLight.enable();
    
    
    //    for (int i=0; i<buildingsPolyline_33975_22294.size(); i++) {
    //        buildingsPolyline_33975_22294[i].draw();
    //    }
    
    //    ofPushStyle();
    //    ofSetColor(255, 160);
    //
    //    for (int i=0; i<buildings_33975_22294.size(); i++) {
    //        vector<ofVec3f> & _v = buildings_33975_22294[i].getVertices();
    //        for (int j=0; j<_v.size(); j++) {
    //            ofDrawLine( _v[j] - ofVec3f(0, 0, 0), _v[j] + ofVec3f(0, 0, 100) );
    //        }
    //    }
    //    ofPopStyle();
    
    
    ofPushStyle();
    ofSetColor(roadColor);
    for (int i=0; i<roadsPolyline_33975_22294.size(); i++) {
        roadsPolyline_33975_22294[i].draw();
    }
    ofPopStyle();
    

    ofPushStyle();
    ofSetColor(movingColor);
    for (int i=0; i<roadsPolyline_33975_22294.size(); i++) {
        ofDrawCircle(roadsPolyline_33975_22294[i].getPointAtPercent( roadMoving_33975_22294 ) , 2);
    }
    ofPopStyle();
    
    
    ofPushStyle();
    ofSetColor(buildingColor);
    for (int i=0; i<buildingsPolyline_33975_22294.size(); i++) {
        
        buildingsPolyline_33975_22294[i].draw();
        
        //                ofBeginShape();
        //                vector<ofVec3f>& vertices = buildingsPolyline_33975_22294[i].getVertices();
        //                for(int j = 0; j < vertices.size(); j++) {
        //                    ofVertex(vertices[j]);
        //                }
        //                ofEndShape();
        //
        //                ofBeginShape();
        //                vector<ofVec3f>& verticesUp = buildingsPolyline_33975_22294[i].getVertices();
        //                for(int j = 0; j < verticesUp.size(); j++) {
        //                    ofVec3f _v = verticesUp[j] + ofVec3f(0, 0, 100);
        //                    ofVertex(_v);
        //                }
        //                ofEndShape();
        
    }
    ofPopStyle();
    
    
    ofDisableAlphaBlending();
    
    //    mainLight.disable();
    
    cam.end();
    
    //    ofDisableLighting();
    
}



//--------------------------------------------------------------
void TrierFlyingCam::returnBase(){
    
    ofVec3f _vP = ofVec3f(-1000, -1000, 1000);
    cam.setPosition( _vP );

    ofVec3f _vL = ofVec3f(-1, 0, 0);
    cam.lookAt( _vL );
    
}



