//
//  TrierFlyingCam.hpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//

#pragma once


#ifndef TrierFlyingCam_hpp
#define TrierFlyingCam_hpp

#include "ofMain.h"

#include "SceneSetup.hpp"

#include "ofxImmediateModeInput.h"
#include "ofxFirstPersonCamera.h"
#include "FeatureNode.h"
#include "JsonLoader.h"

#include "ofxJSON.h"


class TrierFlyingCam : public SceneSetup{
    
public :
    
    TrierFlyingCam();
    ~TrierFlyingCam();
    
    void setup();
    void update();
    void draw();

    void jsonDataSetup();
    
    ofEasyCam camera;
    ofLight mainLight;
    
    vector< ofMesh > buildings_33975_22294;
    vector< ofMesh > roads_33975_22294;
    
    vector< ofPolyline > buildingsPolyline_33975_22294;
    vector< ofPolyline > roadsPolyline_33975_22294;
    
    float roadMoving_33975_22294;
    float roadMovingFactor_33975_22294;

    
    double y2lat(double y) { return ofRadToDeg(2 * atan(exp(ofDegToRad(y))) - PI / 2); }
    double x2lon(double x) { return ofRadToDeg(x / R_EARTH); }
    double lat2y(double lat) { return R_EARTH * log(tan(PI / 4 + ofDegToRad(lat) / 2)); }
    double lon2x(double lon) { return ofDegToRad(lon) * R_EARTH; }

    // Flying
    ofxImmediateModeInput in;
    ofxFirstPersonCamera cam;
    vector<ofPolyline> paint;

    
    ofColor roadColor;
    ofColor buildingColor;
    ofColor movingColor;
    
    
    void returnBase();
    
    

    
};


#endif /* TrierFlyingCam_hpp */
