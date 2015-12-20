//
//  IndiaTower.hpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//

#pragma once

#ifndef IndiaTower_hpp
#define IndiaTower_hpp

#include "ofMain.h"
#include "SceneSetup.hpp"

class IndiaTower : public SceneSetup {
    
    public :
    
    IndiaTower();
    ~IndiaTower();
    
    void setup();
    void update();
    void draw();
    
    void drawingRectColumn();
    void drawingNumber();
    void drawingBeziel();

    ofTrueTypeFont spectrumNumbers;

    vector<ofVec2f> bezielStart;
    vector<ofVec2f> bezielEnd;

    
    ofVec2f kasoPadInput;
    
    ofColor bezielcolor;
    
};


#endif /* IndiaTower_hpp */
