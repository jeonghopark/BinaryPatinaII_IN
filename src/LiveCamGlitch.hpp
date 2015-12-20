//
//  LiveCamGlitch.hpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 14/10/15.
//
//

#pragma once

#ifndef LiveCamGlitch_hpp
#define LiveCamGlitch_hpp

#include "ofMain.h"
#include "SceneSetup.hpp"

#include "ofxOpenCv.h"
#include "ofxPostGlitch.h"

#include "MidiInput.hpp"

class LiveCamGlitch : public SceneSetup {
    
    public :
    
    LiveCamGlitch();
    ~LiveCamGlitch();
    
    
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    void inputMidiInput(MidiInput &);
    
    MidiInput * midiInput;
    
    ofxPostGlitch glitchEffect;
    ofFbo liveVideoFbo;

    void glitchUpdate(ofPixels _p);
    
    bool bDirectglitch;
    ofImage imgDirectGlitch;
    ofImageQualityType quality;

    
    ofxCvColorImage windowView;
    ofxCvColorImage captureCam;
    
    float videoW, videoH;
    
    
};


#endif /* LiveCamGlitch_hpp */
