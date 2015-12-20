//
//  SceneSetup.cpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 18/10/15.
//
//

#include "SceneSetup.hpp"


//--------------------------------------------------------------
void SceneSetup::inputBaseArch(BaseArch & _baseArch){
    
    baseArch = & _baseArch;

}


//--------------------------------------------------------------
void SceneSetup::inputFFTP(ProcessFFT & _processFFT){
    
    processFFT = & _processFFT;

}


//--------------------------------------------------------------
void SceneSetup::inputWebCam(ofVideoGrabber & _webCamHD){
    
    webCamHD = & _webCamHD;
    
}


//--------------------------------------------------------------
void SceneSetup::inputFont(ofxFontStash & _f){
    
    font = & _f;
    
}



//--------------------------------------------------------------
void SceneSetup::inputLeapMotion(ofxLeapMotion & _leapMotion){
    
    leapMotion = & _leapMotion;
    
}



//--------------------------------------------------------------
void SceneSetup::inputMIDI(MidiInput & _m){
    
    midi = & _m;
    
}




