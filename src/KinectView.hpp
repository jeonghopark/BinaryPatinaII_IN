//
//  KinectView.hpp
//  NightVisionKinect
//
//  Created by jeonghopark on 14/10/15.
//
//

#pragma once

#ifndef KinectView_hpp
#define KinectView_hpp

#include "ofMain.h"

#include "SceneSetup.hpp"

#include "ofxOpenCv.h"
#include "ofxKinect.h"

class KinectView : public SceneSetup {
    
    public :
    
    KinectView();
    ~KinectView();
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void drawNightVision();
    void drawPointCloud();
    
    ofxKinect kinect;

#ifdef USE_TWO_KINECTS
    ofxKinect kinect2;
#endif
    
    ofxCvColorImage colorImg;
    
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayThreshNear;
    ofxCvGrayscaleImage grayThreshFar;
    
    ofxCvContourFinder contourFinder;

    
    bool bThreshWithOpenCV;
    bool bDrawPointCloud;
    
    int nearThreshold;
    int farThreshold;
    
    int angle;
    
    ofEasyCam easyCam;
    
    ofxCvGrayscaleImage contrastKinect;

};


#endif /* KinectView_hpp */
