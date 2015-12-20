//
//  CubicMapFlyingCam.cpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//

#include "CubicMapFlyingCam.hpp"


//--------------------------------------------------------------
CubicMapFlyingCam::CubicMapFlyingCam(){
    
}


//--------------------------------------------------------------
CubicMapFlyingCam::~CubicMapFlyingCam(){
    
}




//--------------------------------------------------------------
void CubicMapFlyingCam::setup(){
 
    
    cam.setNearClip(0.0001f);
    cam.setFarClip(10000.0f);
    cam.toggleControl();
    
    
    buildingsMesh_top = buildingsMesh("vectorTile_16_33975_22294.json");
    roadsPolyline_top = roadsPolyline("vectorTile_16_33975_22294.json");
    
    buildingsMesh_left = buildingsMesh("vectorTile_16_33974_22294.json");
    roadsPolyline_left = roadsPolyline("vectorTile_16_33974_22294.json");
    
    buildingsMesh_right = buildingsMesh("vectorTile_16_33976_22294.json");
    roadsPolyline_right = roadsPolyline("vectorTile_16_33976_22294.json");
    
    buildingsMesh_front = buildingsMesh("vectorTile_16_33975_22295.json");
    roadsPolyline_front = roadsPolyline("vectorTile_16_33975_22295.json");
    
    buildingsMesh_back = buildingsMesh("vectorTile_16_33975_22293.json");
    roadsPolyline_back = roadsPolyline("vectorTile_16_33975_22293.json");
    
    buildingsMesh_bottom = buildingsMesh("vectorTile_16_33975_22296.json");
    roadsPolyline_bottom = roadsPolyline("vectorTile_16_33975_22296.json");
    
    
//    camera = ofEasyCam();
    //    camera.setPosition(_rootNode_33975_22294->getGlobalPosition());
    //    camera.move(0, 0, 300);
    //    camera.setTarget(_rootNode_33975_22294->getGlobalPosition());
    
//    mainLight = ofLight();
    mainLight.setPointLight();
    mainLight.setGlobalPosition(0, 0, 0);
    mainLight.setDiffuseColor(ofColor(255, 255, 255));
    mainLight.setSpecularColor(ofColor(170, 170, 170));
    
    
    returnBase();
    
    
//    building_vboMesh_top.resize(buildingsMesh_top.size());
//    building_vboMesh_left.resize(buildingsMesh_left.size());
//    building_vboMesh_right.resize(buildingsMesh_right.size());
//    
//    for (int i=0; i<buildingsMesh_top.size(); i++) {
//        building_vboMesh_top[i] = buildingsMesh_top[i];
//    }
//    
//    for (int i=0; i<buildingsMesh_left.size(); i++) {
//        building_vboMesh_left[i] = buildingsMesh_left[i];
//    }
//
//    for (int i=0; i<buildingsMesh_right.size(); i++) {
//        building_vboMesh_right[i] = buildingsMesh_right[i];
//    }

    
    Cubic_backGroundColor = ofColor (0, 0);
    
}


//--------------------------------------------------------------
void CubicMapFlyingCam::update(){
 
    
    auto pushed = in.keyPushed;
    auto holded = in.keyHolded;
    auto pulled = in.keyPulled;
    
    if( pushed[GLFW_KEY_LEFT_SHIFT] ) cam.movespeed = 7.0f;
    if( pulled[GLFW_KEY_LEFT_SHIFT] ) cam.movespeed = 1.0f;
    
    if( pushed[GLFW_MOUSE_BUTTON_LEFT] ) paint.push_back( ofPolyline() );
    if( holded[GLFW_MOUSE_BUTTON_LEFT] ) paint.back().addVertex( cam.getPosition() + (cam.getLookAtDir() * 50.0f) );
    
    if( pushed[GLFW_MOUSE_BUTTON_RIGHT] ) cam.toggleControl();
    
    
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

    
    
    roadMovingFactor_top = roadMovingFactor_top + 4;
    roadMoving_top = sin( ofDegToRad(roadMovingFactor_top) ) * 0.5 + 0.5;

    
    
}




//--------------------------------------------------------------
void CubicMapFlyingCam::draw(){
    
    
    //    ofEnableLighting();
    

    
    camera.begin();
    
    

    ofEnableDepthTest();
//    ofDisableAlphaBlending();
//    ofDisableArbTex();

    //    mainLight.enable();
    
        
    ofVec3f _offSetPos = ofVec3f(0, 0, 0);
    
    drawBuildingsMesh(buildingsMesh_top, ofVec3f(0, 0, _offSetPos.z), ofVec3f(0, 0, 0));
        drawBuildingsMesh(buildingsMesh_left, ofVec3f(-_offSetPos.x, 0, 0), ofVec3f(0, -90, 0));
        drawBuildingsMesh(buildingsMesh_right, ofVec3f(_offSetPos.x, 0, 0), ofVec3f(0, 90, 0));
    //    drawBuildingsMesh(buildingsMesh_front, ofVec3f(0, _offSetPos.y, 0), ofVec3f(-90, 0, 0));
    //    drawBuildingsMesh(buildingsMesh_back, ofVec3f(0, -_offSetPos.y, 0), ofVec3f(90, 0, 0));
    //    drawBuildingsMesh(buildingsMesh_bottom, ofVec3f(0, 0, -_offSetPos.z), ofVec3f(180, 0, 0));
    
    drawRoadPolyLineMoving(roadsPolyline_top, ofVec3f(0, 0, _offSetPos.z), ofVec3f(0, 0, 0));
        drawRoadPolyLineMoving(roadsPolyline_left, ofVec3f(-_offSetPos.x, 0, 0), ofVec3f(0, -90, 0));
        drawRoadPolyLineMoving(roadsPolyline_right, ofVec3f(_offSetPos.x, 0, 0), ofVec3f(0, 90, 0));
    //    drawRoadPolyLineMoving(roadsPolyline_front, ofVec3f(0, _offSetPos.y, 0), ofVec3f(-90, 0, 0));
    //    drawRoadPolyLineMoving(roadsPolyline_back, ofVec3f(0, -_offSetPos.y, 0), ofVec3f(90, 0, 0));
    //    drawRoadPolyLineMoving(roadsPolyline_bottom, ofVec3f(0, 0, -_offSetPos.z), ofVec3f(180, 0, 0));
    
    
    
    
    
    ofDisableDepthTest();
    
    //    mainLight.disable();
    
    camera.end();
    
    //    ofDisableLighting();

    
}




//--------------------------------------------------------------
void CubicMapFlyingCam::drawBuildingsMesh(vector<ofMesh> _mesh, ofVec3f _position, ofVec3f _rotation){
    
    ofPushMatrix();
    
    ofTranslate( _position );
    
    ofRotateX(_rotation.x);
    ofRotateY(_rotation.y);
    ofRotateZ(_rotation.z);
    
    
    ofPushStyle();
    ofSetColor(255, 80);
    
    //    for (int i=0; i<_mesh.size(); i++) {
    //        _mesh[i].draw();
    //    }
    
    ofPopStyle();
    
    ofPushStyle();
    
    ofEnableDepthTest();
    
    
    
    ofSetColor( buildingColor );
    
    float _height = 20;
    
    for (int i=0; i<_mesh.size(); i++) {
        
        //        ofPushStyle();
        //        ofSetColor(0, 255);
        //        vector<ofVec3f> & _v = _mesh[i].getVertices();
        //        for (int j=0; j<_v.size(); j++) {
        //            ofDrawLine( _v[j] - ofVec3f(0, 0, 0), _v[j] + ofVec3f(0, 0, 10) );
        //        }
        //        ofPopStyle();
        
        ofBeginShape();
        vector<ofVec3f>& _vertices = _mesh[i].getVertices();
        for(int j = 0; j < _vertices.size(); j++) {
            ofVertex(_vertices[j]);
        }
        ofEndShape();
        
        
        ofPushStyle();
        ofSetColor( buildingSideColor );
        vector<ofVec3f>& _verticesSide = _mesh[i].getVertices();
        for(int j = 0; j < _verticesSide.size()-1; j++) {
            ofBeginShape();
            ofVertex(_verticesSide[j]);
            ofVertex(_verticesSide[j+1]);
            ofVec3f _v1Up = _verticesSide[j] + ofVec3f(0, 0, _height);
            ofVec3f _v2Up = _verticesSide[j+1] + ofVec3f(0, 0, _height);
            ofVertex( _v2Up );
            ofVertex( _v1Up );
            ofEndShape();
        }
        ofPopStyle();
        
        
        ofBeginShape();
        vector<ofVec3f>& _verticesUp = _mesh[i].getVertices();
        for(int j = 0; j < _verticesUp.size(); j++) {
            ofVec3f _v = _verticesUp[j] + ofVec3f(0, 0, _height);
            ofVertex(_v);
        }
        ofEndShape();
        
    }
    
    ofDisableDepthTest();
    
    
    ofPopStyle();
    
    ofPopMatrix();
    
}


//--------------------------------------------------------------
void CubicMapFlyingCam::drawRoadPolyLineMoving(vector< ofPolyline > _ofPolyline, ofVec3f _position, ofVec3f _rotation){
    
    ofPushMatrix();
    
    ofTranslate( _position );
    
    ofRotateX(_rotation.x);
    ofRotateY(_rotation.y);
    ofRotateZ(_rotation.z);
    
    
    
    ofPushStyle();
    ofSetColor(roadColor);
    
    ofSetLineWidth(1);
    for (int i=0; i<_ofPolyline.size(); i++) {
        _ofPolyline[i].draw();
    }
    
    ofSetColor(movingColor);
    for (int i=0; i<_ofPolyline.size(); i++) {
        ofDrawCircle(_ofPolyline[i].getPointAtPercent( roadMoving_top ) , 2);
    }
    
    
    ofPopStyle();
    
    
    ofPopMatrix();
    
}



//--------------------------------------------------------------
vector< ofMesh > CubicMapFlyingCam::buildingsMesh(string _fileName){
    
    vector< ofMesh > _return;
    
    FeatureNode * _rootNode;
    
    JsonLoader _jsonLoader = JsonLoader(_fileName);
    _rootNode = _jsonLoader.loadNodeGraph();
    
    ofxJSONElement _jsonMain;
    _jsonMain = _jsonLoader.jsonRoot;
    
    ofxJSONElement _jsonBuildings;
    _jsonBuildings = _jsonMain["buildings"]["features"];
    
    
    for (int i=0; i<_jsonBuildings.size(); i++) {
        ofxJSONElement _jsonBuilding;
        _jsonBuilding = _jsonBuildings[i]["geometry"]["coordinates"][0];
        
        ofMesh _m;
        _m.setMode(OF_PRIMITIVE_LINE_LOOP);
        
        for (int j=0; j<_jsonBuilding.size(); j++) {
            
            ofxJSONElement _coordinateBuilding;
            _coordinateBuilding = _jsonBuilding[j];
            
            ofVec2f _v;
            _v.x = _jsonLoader.lon2x(_coordinateBuilding[0].asFloat()) - _rootNode->getX();
            _v.y = _jsonLoader.lat2y(_coordinateBuilding[1].asFloat()) - _rootNode->getY();
            
            _m.addVertex(_v);
            _m.addColor( ofColor(255) );
            
        }
        
        _return.push_back( _m );
        
    }
    
    _rootNode->setPosition(0, 0, 0);
    //    _rootNode->printPosition("");
    
    return _return;
    
}


//--------------------------------------------------------------
vector< ofPolyline > CubicMapFlyingCam::roadsPolyline(string _fileName){
    
    vector< ofPolyline > _return;
    
    FeatureNode * _rootNode;
    
    JsonLoader _jsonLoader = JsonLoader(_fileName);
    _rootNode = _jsonLoader.loadNodeGraph();
    
    ofxJSONElement _jsonMain;
    _jsonMain = _jsonLoader.jsonRoot;
    
    ofxJSONElement _jsonRoads;
    _jsonRoads = _jsonMain["roads"]["features"];
    
    
    for (int i=0; i<_jsonRoads.size(); i++) {
        ofxJSONElement _jsonRoad;
        
        
        string _multiString = _jsonRoads[i]["geometry"]["type"].asString();
        
        ofPolyline _pl;
        
        if (_multiString != "MultiLineString") {
            
            _jsonRoad = _jsonRoads[i]["geometry"]["coordinates"];
            
            for (int j=0; j<_jsonRoad.size(); j++) {
                
                ofxJSONElement _coordinateRoad;
                _coordinateRoad = _jsonRoad[j];
                
                ofVec2f _v;
                _v.x = _jsonLoader.lon2x(_jsonRoad[j][0].asFloat()) - _rootNode->getX();
                _v.y = _jsonLoader.lat2y(_jsonRoad[j][1].asFloat()) - _rootNode->getY();
                
                _pl.addVertex(_v);
                
            }
            
            _return.push_back( _pl );
            
            
        } else {
            
            _jsonRoad = _jsonRoads[i]["geometry"]["coordinates"][0];
            
            for (int j=0; j<_jsonRoad.size(); j++) {
                
                ofxJSONElement _coordinateRoad;
                _coordinateRoad = _jsonRoad[j];
                
                ofVec2f _v;
                _v.x = _jsonLoader.lon2x(_jsonRoad[j][0].asFloat()) - _rootNode->getX();
                _v.y = _jsonLoader.lat2y(_jsonRoad[j][1].asFloat()) - _rootNode->getY();
                
                _pl.addVertex(_v);
                
            }
            
            _return.push_back( _pl );
            
        }
        
    }
    
    
    _rootNode->setPosition(0, 0, 0);
    //    _rootNode->printPosition("");
    
    return _return;
    
}



//--------------------------------------------------------------
void CubicMapFlyingCam::returnBase(){
    
    ofVec3f _vP = ofVec3f(-400, -400, 400);
    cam.setPosition( _vP );
    
    ofVec3f _vL = ofVec3f(-1, 0, 0);
    cam.lookAt( _vL );
    
}


