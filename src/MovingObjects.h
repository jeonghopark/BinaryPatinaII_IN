//
//  MovingObjects.hpp
//  FrameMoving
//
//  Created by jeonghopark on 04/10/15.
//
//
#pragma once

#ifndef MovingObjects_hpp
#define MovingObjects_hpp

#include "ofMain.h"
#include "SceneSetup.hpp"

#include "ofxJSON.h"


struct GuidID{
    
    float hTextMoving;
    float hTextMovingFactor;
    float hTextMovingXPos;
    float hTextMovingYPos;
    
    string quid_string;
};


class MovingObjects : public SceneSetup{
    
    public:
    
    MovingObjects();
    ~MovingObjects();
        
    void setup();
    void update();
    void draw(ofColor _c = ofColor(255));
    
    void drawRectangles();
    void drawText();
    
    void drawRandomText();
    
    vector< ofPolyline > hFrames;
    vector< ofPolyline > vFrames;
    vector< ofPolyline > hCenterFrames;
    
    vector< float > hMoving;
    vector< float > hMovingFactor;
    vector< float > hMovingXPos;

    vector< GuidID > guidID;
    int guidIDNumber[72];
    
    float mainOffSetXPos, mainOffSetYPos;
    
    ofColor colorRect;
    ofColor colorText;
    ofColor colorRandomText;
    
    
};




#endif /* MovingObjects_hpp */
