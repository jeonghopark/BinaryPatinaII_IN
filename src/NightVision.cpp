//
//  NightVision.cpp
//  BinaryPatinaII
//
//  Created by Jeong-Ho on 19/10/15.
//
//

#include "NightVision.hpp"


// Size : 1056 x 704

//--------------------------------------------------------------
NightVision::NightVision(){
    
    
}


//--------------------------------------------------------------
NightVision::~NightVision(){
    
    
}


//--------------------------------------------------------------
void NightVision::setup(){
    
}


//--------------------------------------------------------------
void NightVision::update(ofxSyphonClient & _s){
    
    syphon = & _s;
    
}



//--------------------------------------------------------------
void NightVision::textureInput(){
    
}


//--------------------------------------------------------------
void NightVision::draw(){
    
    ofEnableAlphaBlending();
    
    ofPushMatrix();
    
    ofPushStyle();
    
    ofSetColor(0, 255, 0);
    
    float _center = baseArch->framesCenter[11][0].x;
    float _h = baseArch->fassadeCorner[3].y - baseArch->fassadeCorner[0].y;
    float _w = _h * 1056.0 / 704.0;
    float _x = baseArch->fassadeCorner[0].x;
    float _y = baseArch->fassadeCorner[0].y;

    float _xShift = abs(_h - _center);
    
    syphon->draw( _x - _xShift, _y, _w + 50, _h + 50 );
    
    ofPopStyle();
    
    ofPopMatrix();
    
    ofDisableAlphaBlending();
    
    
}
