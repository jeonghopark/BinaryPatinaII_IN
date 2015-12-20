//
//  Windows.cpp
//  Abstract
//
//  Created by jeonghopark on 13/10/15.
//
//

#include "LineVideo.h"

//--------------------------------------------------------------
LineVideo::LineVideo(){
    
}


//--------------------------------------------------------------
LineVideo::~LineVideo(){
    
}


//--------------------------------------------------------------
void LineVideo::setup(){
    
    float _h = baseArch->fassadeCorner[3].y - baseArch->fassadeCorner[0].y;
    for (int i=0; i<startLineColors.size(); i++) {
        controlPosY[i] = ofRandom(_h);
    }

    colorImg.allocate(480, 360);
    
    //    halfCam.allocate( 480, 360, OF_IMAGE_COLOR );
    
    startLineColors.resize( 120 );
    controlPosY.resize( 120 );

}


//--------------------------------------------------------------
void LineVideo::update(){
    
    float _x = ofMap( midi->indiaControl.x, 0, 127, -400, 400 );
    float _y = ofMap( midi->indiaControl.y, 0, 127, -500, 500 );
    kasoPadInput = ofVec2f( _x, _y );
    if (webCamHD->isFrameNew()){
        colorImg.setFromPixels( webCamHD->getPixels() );
        colorImg.setROI(180,0,120,360);
        halfCam.setFromPixels( colorImg.getRoiPixels() );
        
        for (int i=0; i<startLineColors.size(); i++) {
            startLineColors[i] = halfCam.getColor(i * 120 * 3 * 3 + 359 * 3);
        }
    }
    
}


//--------------------------------------------------------------
void LineVideo::draw(){
    
    float _h = baseArch->fassadeCorner[3].y - baseArch->fassadeCorner[0].y;
    float _w = _h * 120.0 / 360.0;
    float _x = baseArch->fassadeCorner[0].x;
    float _y = baseArch->fassadeCorner[0].y;
    halfCam.draw( _x, _y, _w, _h );

}


//--------------------------------------------------------------
void LineVideo::drawStartPoints(){
    
    float _h = baseArch->fassadeCorner[3].y - baseArch->fassadeCorner[0].y;
    float _w = _h * 120.0 / 360.0;
    float _x = baseArch->fassadeCorner[0].x;

    for (int i=0; i<startLineColors.size(); i++) {
    
        ofPushStyle();
        
        ofSetColor( startLineColors[i] );

        float _y = i * _h / 120.0;
        
        ofDrawCircle( _x + _w, _y, 2 );
        
        ofPopStyle();
        
    }

}


//--------------------------------------------------------------
void LineVideo::drawLines(){

    ofPushStyle();
    
    float _h = baseArch->fassadeCorner[3].y - baseArch->fassadeCorner[0].y;
    float _w = _h * 120.0 / 360.0;
    float _x = baseArch->fassadeCorner[0].x;
    float _rightX = baseArch->fassadeCorner[1].x;
    
    ofNoFill();
    
    for (int i=0; i<startLineColors.size(); i++) {
        
        ofPushStyle();
        
        ofSetColor( startLineColors[i] );
        
        float _y = i * _h / 120.0;
        float _controlY = controlPosY[i] + ofRandom(100, 300) * controlPointRandom;
        
//        ofDrawBezier(_x + _w, _y,
//                     _x + _w + 100, _controlY,
//                     _rightX - _x - _w - 100, _controlY,
//                     _rightX - _x - _w, _y);

        ofDrawBezier(_x + _w, _y,
                     _x + _w + 100 + kasoPadInput.x, _controlY + kasoPadInput.y,
                     _rightX - _x - _w - 100 + kasoPadInput.x, _controlY + kasoPadInput.y,
                     _rightX - _x - _w, _y);

        
        ofPopStyle();
        
    }

    ofPopStyle();


}


//--------------------------------------------------------------
void LineVideo::drawColorNumber(){
    
    ofPushStyle();
    
    float _h = baseArch->fassadeCorner[3].y - baseArch->fassadeCorner[0].y;
    float _w = _h * 120.0 / 360.0;
    float _x = baseArch->fassadeCorner[0].x;
    float _rightX = baseArch->fassadeCorner[1].x;
    
    
    for (int i=0; i<startLineColors.size(); i++) {
        
        ofPushStyle();
        
        ofSetColor( startLineColors[i] );
        
        float _y = i * _h / 120.0;
        
        ofDrawBitmapString( ofToString(startLineColors[i]), _rightX - _x - _w, _y);
        
        ofPopStyle();
        
    }
    
    ofPopStyle();
    
}



//--------------------------------------------------------------
void LineVideo::drawWindows(){
    
}




