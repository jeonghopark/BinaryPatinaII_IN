//
//  Calligraphy.h
//  MusicFFT_score
//
//  Created by JeongHo Park on 09/07/15.
//
//

#pragma once

#ifndef __MusicFFT_score__Calligraphy__
#define __MusicFFT_score__Calligraphy__

#include "ofMain.h"
#include "SceneSetup.hpp"

class Calligraphy: public SceneSetup {
    
    vector<float> captureFFTSmoothed;
    vector<int> captureFFTIndex;
    
    vector<Calligraphy> calligraphies;
    vector<ofVec2f> calliPos;

    
public :

    Calligraphy();
    ~Calligraphy();
    
    void setup();
    void update();
    
    void inputFftSmoothed(vector<float> );
    void draw();
    void drawElement(float _xPos, float _yPos, int _h, float _size);
        
    int calliSize;
    
    int calliYShift;
    bool bClliXPosChange;
    int calliIndex;
    
    float fftValue;

    
    
};


#endif /* defined(__MusicFFT_score__Calligraphy__) */
