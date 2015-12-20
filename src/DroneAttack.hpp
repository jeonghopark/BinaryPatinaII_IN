//
//  DroneAttack.hpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//
#pragma once


#ifndef DroneAttack_hpp
#define DroneAttack_hpp

#include "ofMain.h"

#include "SceneSetup.hpp"

#include "ofxImmediateModeInput.h"
#include "ofxFirstPersonCamera.h"

#include "ofxJSON.h"

struct DronData{
    
    ofVec3f coord;
    float deathMax;
    
};

class DroneAttack : public SceneSetup {
    
public:
    
    DroneAttack();
    ~DroneAttack();
    
    void setup();
    void update();
    
    void jsonDataSetup();
    
    void drawEarthTexture();
    void drawAttackPosition();
    void drawEarth();
    
    void loadImage();
    
    vector<DronData> dronData;
    
    vector<ofPolyline> oceanLineCoord;

    ofxImmediateModeInput in;
    ofxFirstPersonCamera cam;
    vector<ofPolyline> paint;
    
    
    ofSpherePrimitive earth;
    
    ofImage earthImages;
    
    ofColor colorEarth;
    ofColor colorAttack;

    float speedFactor;
    
    void returnBase();
    
};

#endif /* DroneAttack_hpp */
