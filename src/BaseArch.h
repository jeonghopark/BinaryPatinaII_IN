//
//  BaseArch.h
//  bpii
//
//  Created by JeongHo Park on 6/18/15.
//
//
#pragma once

#ifndef __bpii__BaseArch__
#define __bpii__BaseArch__

#include "ofMain.h"
#include "ofxFontStash.h"

#include "ofxCsv.h"

using namespace wng;

class BaseArch {
    
public:
    
    BaseArch();
    ~BaseArch();
    
    ofVec2f windowsOriginCenter[8][8];
    ofVec2f windowsCorner[64][4];
    ofVec2f framesCenter[9][9];
    ofVec2f fassadeCorner[4];
    
    vector<float> windowsCornerNumber;
    
    void setupDefault();
    
    void randomNumberGenerator();
    
    ofxFontStash * font;
    void inputFont(ofxFontStash & _f);
    
    
    void keyInteraction(int key);
    
    ofxCsv csv;
    
    float mainOffSetXPos, mainOffSetYPos;
    
    void guideFrames(ofColor _c = ofColor(0, 150, 0, 180));
    void guideLines(ofColor _c = ofColor(0, 255, 0, 180));
    void guidePoints(ofColor _c = ofColor(0, 220, 0, 180));
    void drawEdgeCover(ofColor _c = ofColor(255, 30));
    void guideCrossPoints(ofColor _c = ofColor(0, 220, 0, 180), float _size = 6);
    void drawPointNumber( ofColor _c = ofColor(255, 255) );
    void drawWindows( ofColor _c = ofColor(255, 0) );
    void drawRandomWindows( ofColor _c = ofColor(255, 0) );
    void drawWindowNumber( ofColor _c = ofColor(255, 0) );
    
    bool oldOn;

    string alphabet[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    
};

#endif /* defined(__bpii__BaseArch__) */
