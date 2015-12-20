//
//  MoonCreator.hpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//
#pragma once


#ifndef MoonCreator_hpp
#define MoonCreator_hpp

#include "ofMain.h"

#include "SceneSetup.hpp"

#include "ofxImmediateModeInput.h"
#include "ofxFirstPersonCamera.h"

#include "ofxCsv.h"

using namespace wng;

typedef struct{
    
    ofVec3f degree3D;
    
    ofVec3f point3DRaw;
    
    ofVec3f p1;
    ofVec3f p2;
    
    ofVec3f norm;
    
    ofVec3f u; //x axis unit vector
    ofVec3f v;
    
    ofMesh createrMesh;
    float radiusCreater;
    ofVbo vboCreator;
    
    float theta;
    float phi;
    float radius;
    
    
} Point3D;



class MoonCreator : public SceneSetup{
    
public:
    
    MoonCreator();
    ~MoonCreator();
    
    
    void setup();
    void update();
    void draw();
    
    ofxCsv csv;
    
    vector< ofVec3f > creatorCoord;
    vector< float > creatorSize;
    
    ofMesh meshMoon;
    ofMesh mesh;
    
    vector<Point3D> point3D;
    
    ofEasyCam camera;
    
    void creatorSetting();

    void creatorDraw();
    void drawLines();
    
    vector<float> lineLengthRandom;
    
    
    ofxImmediateModeInput in;
    ofxFirstPersonCamera cam;
    vector<ofPolyline> paint;

    void returnBase();
    float lineFFTFactor;
    
    ofColor moonMiddlelinesColor;
    
};


#endif /* MoonCreator_hpp */
