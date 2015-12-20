// http://www.json-generator.com

//
//  MovingObjects.cpp
//  FrameMoving
//
//  Created by jeonghopark on 04/10/15.
//
//

#include "MovingObjects.h"


//--------------------------------------------------------------
MovingObjects::MovingObjects(){
 
    
}


//--------------------------------------------------------------
MovingObjects::~MovingObjects(){
    
    
}


//--------------------------------------------------------------
void MovingObjects::setup(){
    
    
    hFrames.resize(12);
    for (int i=0; i<12; i++) {
        ofPolyline _p;
        for (int j=0; j<23; j++) {
            ofVec2f _v;
            float _x = baseArch->framesCenter[j][i/2].x;
            float _y = baseArch->framesCenter[j][i/2].y + (i%2 * 7 - 7);
            _v = ofVec2f(_x, _y);
            _p.addVertex(_v);
        }
        hFrames[i] = _p;
    }
    
    hMovingXPos.resize(12);
    hMoving.resize(12);
    hMovingFactor.resize(12);
    
    for (int i=0; i<12; i++) {
        hMovingFactor[i] = ofRandom(0.5, 1.5);
    }
    
    

    hCenterFrames.resize(6);
    for (int i=0; i<6; i++) {
        ofPolyline _p;
        for (int j=0; j<23; j++) {
            ofVec2f _v;
            float _x = baseArch->framesCenter[j][i].x;
            float _y = baseArch->framesCenter[j][i].y;
            _v = ofVec2f(_x, _y);
            _p.addVertex(_v);
        }
        hCenterFrames[i] = _p;
    }

    
    
    ofxJSONElement _main;
    _main.open("generated_guid.json");
    guidID.resize(_main.size());
    
    for (int i=0; i<_main.size(); i++) {
        GuidID _gID;
        _gID.hTextMoving = 0;
        _gID.hTextMovingXPos = 0;
        _gID.hTextMovingYPos = 0;
        _gID.hTextMovingFactor = ofRandom(2, 4) * 0.001;
        _gID.quid_string = _main[i]["guid"].asString();
        guidID[i] = _gID;
    }
    for (int i=0; i<72; i++){
        guidIDNumber[i] = floor(ofRandom(42));
    }
    
    
    colorRect = ofColor(255);
    colorText = ofColor(255);
    
}



//--------------------------------------------------------------
void MovingObjects::update(){
    
    for (int i=0; i<12; i++) {
        hMoving[i] = hMoving[i] + hMovingFactor[i];
        hMovingXPos[i] = sin(ofDegToRad(hMoving[i]));
    }

    
    for (int i=0; i<72; i++) {
        guidID[i].hTextMoving = guidID[i].hTextMoving + guidID[i].hTextMovingFactor;
        
        if (guidID[i].hTextMoving > 1) {
            guidID[i].hTextMoving = 0;
        }
        if (guidID[i].hTextMoving < 0) {
            guidID[i].hTextMoving = 1;
        }

    }


}



//--------------------------------------------------------------
void MovingObjects::draw(ofColor _c){

    drawRectangles();
    
    drawText();
    
}




//--------------------------------------------------------------
void MovingObjects::drawRectangles(){

    
    ofEnableAlphaBlending();
    
    ofPushMatrix();
    
    ofPushStyle();
    
    ofSetColor(colorRect);
    
    for (int i=0; i<12; i++) {
        ofRectMode(OF_CENTER);
        ofDrawRectangle( hFrames[i].getPointAtPercent((hMovingXPos[i]+1) * 0.5), 7, 7 );
    }

    ofPopStyle();

    ofPopMatrix();
    
    ofDisableAlphaBlending();
    

}


//--------------------------------------------------------------
void MovingObjects::drawText(){

    
    ofEnableAlphaBlending();

    ofPushMatrix();
    
    ofPushStyle();
    
    ofSetColor(colorText);
    
    for (int j=0; j<12; j++) {
        for (int i=0; i<6; i++) {
            int _index = i + j * 6;
            string _s = guidID[guidIDNumber[_index]].quid_string;
            ofPoint _xy = hCenterFrames[i].getPointAtPercent((guidID[_index].hTextMoving)) + ofPoint(j * 30, 4) * ofPoint( 1.5, 1 );
            if ( abs(_xy.x - ofGetWidth() * 0.5) < 50 ) {
                guidIDNumber[_index] = floor(ofRandom(guidID.size()));
            }
            ofDrawBitmapString( _s, _xy );
        }
    }
    
    ofPopStyle();
    
    ofPopMatrix();

    ofDisableAlphaBlending();

    
}


//--------------------------------------------------------------
void MovingObjects::drawRandomText(){

    ofEnableAlphaBlending();
    
    ofPushMatrix();
    
    ofPushStyle();
    
    ofSetColor(colorRandomText);
    
    for (int j=0; j<180; j+=2) {
        for (int i=0; i<50; i+=2) {
            font->draw( ofToString(ofRandom(10),2), 30, j * 10, i * 20 );
        }
    }
    
    ofPopStyle();
    
    ofPopMatrix();
    
    ofDisableAlphaBlending();
    
}

