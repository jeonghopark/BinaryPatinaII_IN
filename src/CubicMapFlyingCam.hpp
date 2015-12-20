//
//  CubicMapFlyingCam.hpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//
#pragma once


#ifndef CubicMapFlyingCam_hpp
#define CubicMapFlyingCam_hpp

#include "ofMain.h"

#include "SceneSetup.hpp"

#include "ofxImmediateModeInput.h"
#include "ofxFirstPersonCamera.h"
#include "FeatureNode.h"
#include "JsonLoader.h"

#include "ofxJSON.h"


class CubicMapFlyingCam : public SceneSetup {
    
public:
    
    CubicMapFlyingCam();
    ~CubicMapFlyingCam();
    
    void setup();
    void update();
    void draw();

    
    ofEasyCam camera;
    ofLight mainLight;
    
    vector< ofMesh > buildingsMesh_top;
    vector< ofMesh > roads_top;
    
    vector< ofMesh > buildingsMesh_left;
    vector< ofMesh > roads_left;
    
    vector< ofMesh > buildingsMesh_right;
    vector< ofMesh > roads_right;
    
    vector< ofMesh > buildingsMesh_front;
    vector< ofMesh > roads_front;
    
    vector< ofMesh > buildingsMesh_back;
    vector< ofMesh > roads_back;
    
    vector< ofMesh > buildingsMesh_bottom;
    vector< ofMesh > roads_bottom;
    
    vector< ofPolyline > buildingsPolyline_top;
    vector< ofPolyline > roadsPolyline_top;
    
    vector< ofPolyline > buildingsPolyline_left;
    vector< ofPolyline > roadsPolyline_left;
    
    vector< ofPolyline > buildingsPolyline_right;
    vector< ofPolyline > roadsPolyline_right;
    
    vector< ofPolyline > buildingsPolyline_front;
    vector< ofPolyline > roadsPolyline_front;
    
    vector< ofPolyline > buildingsPolyline_back;
    vector< ofPolyline > roadsPolyline_back;
    
    vector< ofPolyline > buildingsPolyline_bottom;
    vector< ofPolyline > roadsPolyline_bottom;
    
    
    float roadMoving_top;
    float roadMovingFactor_top;
    
    float roadMoving_left;
    float roadMovingFactor_left;
    
    vector< ofMesh > buildingsMesh(string _fileName );
    vector< ofPolyline > roadsPolyline(string _fileName );
    
    void drawBuildingsMesh(vector< ofMesh > _mesh, ofVec3f _position, ofVec3f _rotation);
    void drawRoadPolyLineMoving(vector< ofPolyline > _polyline, ofVec3f _position, ofVec3f _rotation);

    
    ofxImmediateModeInput in;
    ofxFirstPersonCamera cam;
    vector<ofPolyline> paint;

    ofColor buildingColor;
    ofColor buildingSideColor;
    ofColor roadColor;
    ofColor movingColor;
    
    void returnBase();
    
    ofColor Cubic_backGroundColor;
    
//    vector<ofVboMesh> building_vboMesh_top;
//    vector<ofVboMesh> building_vboMesh_left;
//    vector<ofVboMesh> building_vboMesh_right;
    
};



#endif /* CubicMapFlyingCam_hpp */
