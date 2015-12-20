//
//  WebLiveCam.hpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//
#pragma once


#ifndef WebLiveCam_hpp
#define WebLiveCam_hpp

#include "ofMain.h"

#include "SceneSetup.hpp"

#include "ofxOpenCv.h"

class WebLiveCam : public SceneSetup {
    
public:
    
    WebLiveCam();
    ~WebLiveCam();
    
    void setup();
    void update();
    void draw();
    
    void randomWindowsPosition();
    
    void movieLoad();
    void keyReleased(int key);

    void movieAllPlay(int _pos);
    
    ofVideoPlayer webCam01;
    ofVideoPlayer webCam02;
    ofVideoPlayer webCam03;

    ofxCvColorImage windowView;
    vector<ofxCvColorImage> windowMovies;
    vector<int> indexX;
    vector<int> indexY;
    vector<int> captureIndexX;
    vector<int> captureIndexY;
    
    int windowsNum;
    
    int indexMovie;
    bool movieOn;
    int indexMovieOldNum;

};




#endif /* WebLiveCam_hpp */




