//
//  cpp
//  bpii
//
//  Created by JeongHo Park on 6/18/15.
//
//



#include "BaseArch.h"

//--------------------------------------------------------------
BaseArch::BaseArch(){
    
    setupDefault();
    randomNumberGenerator();

}


//--------------------------------------------------------------
BaseArch::~BaseArch(){

}


//--------------------------------------------------------------
void BaseArch::inputFont(ofxFontStash & _f){
    font = & _f;
}

//--------------------------------------------------------------
void BaseArch::setupDefault(){
    
    
//    font.setup("Vera.ttf", 1.0, 1024, true, 8, 1.0);
//    font.addFont("VeraMono-Bold.ttf");

    float _sizeRatio = 1.5; // 1.5 : 1
    
    csv.clear();
    csv.loadFile(ofToDataPath("facadeData.csv"));
    
    fassadeCorner[0] = ofVec2f( ofToFloat(csv.data[0][0]), ofToFloat(csv.data[0][1]) ) * _sizeRatio;
    fassadeCorner[1] = ofVec2f( ofToFloat(csv.data[22][0]), ofToFloat(csv.data[22][1]) ) * _sizeRatio;
    fassadeCorner[2] = ofVec2f( ofToFloat(csv.data[53][0]), ofToFloat(csv.data[53][1]) ) * _sizeRatio;
    fassadeCorner[3] = ofVec2f( ofToFloat(csv.data[31][0]), ofToFloat(csv.data[31][1]) ) * _sizeRatio;


    for (int j=0; j<110; j++) {
        for (int i=0; i<4; i++) {
            float _x = ofToFloat(csv.data[j+54][i*2]) * _sizeRatio;
            float _y = ofToFloat(csv.data[j+54][i*2+1]) * _sizeRatio;
            windowsCorner[j][i] = ofVec2f( _x, _y );
        }
    }

    for (int j=0; j<5; j++) {
        for (int i=0; i<22; i++) {
            int _index = i + j * 22;
            float _x = (windowsCorner[_index][1].x + windowsCorner[_index][0].x) * 0.5;
            float _y = (windowsCorner[_index][3].y + windowsCorner[_index][0].y) * 0.5;
            windowsOriginCenter[i][j] = ofVec2f( _x, _y );
        }
    }

    
    for (int i=1; i<23; i++) {
        float _x = ofToFloat(csv.data[i][0]) * _sizeRatio;
        float _y = abs(windowsCorner[i-1][1].y + ofToFloat(csv.data[i-1][1]) * _sizeRatio ) * 0.5;
        framesCenter[i][0] = ofVec2f( _x, _y );
    }
    
    for (int i=1; i<23; i++) {
        float _x = ofToFloat(csv.data[i+31][0]) * _sizeRatio;
        float _y = abs(windowsCorner[i+88][3].y + ofToFloat(csv.data[i+31][1]) * _sizeRatio) * 0.5;
        framesCenter[i][5] = ofVec2f( _x, _y );
    }
    
    for (int j=1; j<5; j++) {
        for (int i=1; i<22; i++) {
            float _x = abs(windowsCorner[i-1][2].x + windowsCorner[i][3].x) * 0.5;
            float _y = abs(windowsCorner[i-1+22*(j-1)][2].y + windowsCorner[i-1+22*(j)][1].y) * 0.5;
            framesCenter[i][j] = ofVec2f( _x, _y );
        }
    }

    for (int j=1; j<5; j++) {
        float _x = abs(ofToFloat(csv.data[(j-1)+23][0]) * _sizeRatio + windowsCorner[j*22][0].x) * 0.5;
        float _y = ofToFloat(csv.data[j-1+23][1]) * _sizeRatio;
        framesCenter[0][j] = ofVec2f( _x, _y );
    }

    
    for (int j=1; j<5; j++) {
        float _x = abs(ofToFloat(csv.data[(j-1)+27][0]) * _sizeRatio + windowsCorner[(j-1)*22+21][1].x) * 0.5;
        float _y = ofToFloat(csv.data[j-1+23][1]) * _sizeRatio;
        framesCenter[22][j] = ofVec2f( _x, _y );
    }

    framesCenter[0][0] = (windowsCorner[0][0] + fassadeCorner[0]) * 0.5;
    framesCenter[22][0] = (windowsCorner[21][1] + fassadeCorner[1]) * 0.5;
    framesCenter[22][5] = (windowsCorner[109][2] + fassadeCorner[2]) * 0.5;
    framesCenter[0][5] = (windowsCorner[88][3] + fassadeCorner[3]) * 0.5;
    
    
    mainOffSetXPos = (ofGetWidth() - (fassadeCorner[0].x + fassadeCorner[1].x)) * 0.5;
    mainOffSetYPos = (ofGetHeight() - (fassadeCorner[0].y + fassadeCorner[3].y)) * 0.5;

    
    
    oldOn = false;
    
}


//--------------------------------------------------------------
void BaseArch::guideFrames(ofColor _c){
    
    ofPushMatrix();
    ofPushStyle();
    
    ofSetColor(_c);
    
    float _xRS = fassadeCorner[0].x;
    float _yRS = fassadeCorner[0].y;
    float _wRS = windowsCorner[0][0].x - fassadeCorner[0].x;
    float _hRS = fassadeCorner[3].y;
    ofDrawRectangle( _xRS, _yRS, _wRS, _hRS );
    
    for (int i=0; i<21; i++) {
        float _x = windowsCorner[i][1].x;
        float _y = fassadeCorner[0].y;
        float _w = windowsCorner[i+1][0].x - windowsCorner[i][1].x;
        float _h = fassadeCorner[3].y;
        ofDrawRectangle( _x, _y, _w, _h );
    }
    
    float _xRE = windowsCorner[21][1].x;
    float _yRE = fassadeCorner[0].y;
    float _wRE = fassadeCorner[1].x - windowsCorner[21][1].x;
    float _hRE = fassadeCorner[3].y;
    ofDrawRectangle( _xRE, _yRE, _wRE, _hRE );
    
    
    float _xCS = fassadeCorner[0].x;
    float _yCS = windowsCorner[0][0].y;
    float _wCS = fassadeCorner[1].x - fassadeCorner[0].x;
    float _hCS = fassadeCorner[0].y - windowsCorner[0][0].y;
    ofDrawRectangle( _xCS, _yCS, _wCS, _hCS );
    
    for (int i=0; i<4; i++) {
        float _x = fassadeCorner[0].x;
        float _y = windowsCorner[i*22][3].y;
        float _w = fassadeCorner[1].x - fassadeCorner[0].x;
        float _h = windowsCorner[(i+1)*22][0].y - windowsCorner[i*22][3].y;
        ofDrawRectangle( _x, _y, _w, _h );
    }
    
    float _xCE = fassadeCorner[0].x;
    float _yCE = windowsCorner[88][3].y;
    float _wCE = fassadeCorner[1].x - fassadeCorner[0].x;
    float _hCE = fassadeCorner[3].y - windowsCorner[88][3].y;
    ofDrawRectangle( _xCE, _yCE, _wCE, _hCE );
    
    
    ofPopStyle();
    ofPopMatrix();
    
}


//--------------------------------------------------------------
void BaseArch::guideLines(ofColor _c){
    
    ofEnableAlphaBlending();
    
    ofPushMatrix();
    
    ofPushStyle();
    
    ofSetColor(_c);
    
    for (int i=0; i<22-1; i++) {
        for (int j=0; j<5; j++) {
            ofDrawLine( windowsOriginCenter[i][j].x, windowsOriginCenter[i][j].y, windowsOriginCenter[i+1][j].x, windowsOriginCenter[i+1][j].y );
        }
    }

    for (int i=0; i<22; i++) {
        for (int j=0; j<5-1; j++) {
            ofDrawLine( windowsOriginCenter[i][j].x, windowsOriginCenter[i][j].y, windowsOriginCenter[i][j+1].x, windowsOriginCenter[i][j+1].y );
        }
    }

    
    ofSetColor(_c);

    
    for (int i=0; i<23-1; i++) {
        for (int j=0; j<6; j++) {
            ofDrawLine( framesCenter[i][j].x, framesCenter[i][j].y, framesCenter[i+1][j].x, framesCenter[i+1][j].y );
        }
    }
    
    for (int i=0; i<23; i++) {
        for (int j=0; j<6-1; j++) {
            ofDrawLine( framesCenter[i][j].x, framesCenter[i][j].y, framesCenter[i][j+1].x, framesCenter[i][j+1].y );
        }
    }

    
    ofPopStyle();
    
    ofPopMatrix();
    
    ofDisableAlphaBlending();

    
}


//--------------------------------------------------------------
void BaseArch::guidePoints(ofColor _c){
    
    int _size = 3;
    
    ofEnableAlphaBlending();

    
    ofPushMatrix();
    
    ofPushStyle();

    ofSetColor(_c);
    
    for (int i=0; i<110; i++) {
        for (int j=0; j<4; j++) {
            float _xS = windowsCorner[i][j].x;
            float _yS = windowsCorner[i][j].y;
            ofDrawCircle( _xS, _yS, _size );
        }
    }

    ofSetColor(_c, 120);

    for (int i=0; i<23; i++) {
        for (int j=0; j<6; j++) {
            float _xS = framesCenter[i][j].x;
            float _yS = framesCenter[i][j].y;
            ofDrawCircle( _xS, _yS, _size );
        }
    }

    ofSetColor(_c);

    for (int i=0; i<4; i++) {
        ofDrawCircle( fassadeCorner[i], _size );
    }
    
    ofPopStyle();
    
    ofPopMatrix();
    
    ofDisableAlphaBlending();

    
}


//--------------------------------------------------------------
void BaseArch::guideCrossPoints(ofColor _c, float _size){
    
    ofEnableAlphaBlending();

    
    ofPushMatrix();
    
    ofPushStyle();
    
    ofSetColor(_c);
    
    for (int i=0; i<110; i++) {
        for (int j=0; j<4; j++) {
            float _xS = windowsCorner[i][j].x;
            float _yS = windowsCorner[i][j].y;
            ofDrawLine( _xS - _size, _yS, _xS + _size, _yS );
            ofDrawLine( _xS, _yS - _size, _xS, _yS + _size );
        }
    }
    
    ofSetColor(_c, 120);
    
    for (int i=0; i<23; i++) {
        for (int j=0; j<6; j++) {
            float _xS = framesCenter[i][j].x;
            float _yS = framesCenter[i][j].y;
            ofDrawLine( _xS - _size, _yS, _xS + _size, _yS );
            ofDrawLine( _xS, _yS - _size, _xS, _yS + _size );
        }
    }
    
    
    for (int i=0; i<4; i++) {
        float _xS = fassadeCorner[i].x;
        float _yS = fassadeCorner[i].y;
        ofDrawLine( _xS - _size, _yS, _xS + _size, _yS );
        ofDrawLine( _xS, _yS - _size, _xS, _yS + _size );
    }
    
    ofPopStyle();
    
    ofPopMatrix();
    
    
    ofDisableAlphaBlending();

    
}


//--------------------------------------------------------------
void BaseArch::drawEdgeCover(ofColor _c){
    
    ofEnableAlphaBlending();

    
    ofPushStyle();
    
    ofSetColor(_c);
    
    ofBeginShape();
    ofVertex(-mainOffSetXPos, -mainOffSetYPos);
    ofVertex(ofGetWidth()-mainOffSetXPos, -mainOffSetYPos);
    ofVertex(fassadeCorner[0].x, fassadeCorner[0].y);
    ofVertex(fassadeCorner[3].x, fassadeCorner[3].y);
    ofEndShape();
    
    ofBeginShape();
    ofVertex(ofGetWidth()-mainOffSetXPos, -mainOffSetYPos);
    ofVertex(ofGetWidth()-mainOffSetXPos, ofGetHeight()-mainOffSetYPos);
    ofVertex(fassadeCorner[1].x, fassadeCorner[1].y);
    ofVertex(fassadeCorner[0].x, fassadeCorner[0].y);
    ofEndShape();

    ofBeginShape();
    ofVertex(ofGetWidth()-mainOffSetXPos, ofGetHeight()-mainOffSetYPos);
    ofVertex(-mainOffSetXPos, ofGetHeight()-mainOffSetYPos);
    ofVertex(fassadeCorner[2].x, fassadeCorner[2].y);
    ofVertex(fassadeCorner[1].x, fassadeCorner[1].y);
    ofEndShape();

    ofBeginShape();
    ofVertex(-mainOffSetXPos, ofGetHeight()-mainOffSetYPos);
    ofVertex(-mainOffSetXPos, -mainOffSetYPos);
    ofVertex(fassadeCorner[3].x, fassadeCorner[3].y);
    ofVertex(fassadeCorner[2].x, fassadeCorner[2].y);
    ofEndShape();
    
    ofPopStyle();
    
    ofDisableAlphaBlending();

    
}



//--------------------------------------------------------------
void BaseArch::drawPointNumber( ofColor _c ){
    
    ofEnableAlphaBlending();

    ofPushMatrix();
    

    ofPushStyle();
    
    
    ofSetColor(_c);
    
//    for (int i=0; i<110; i++) {
//        for (int j=0; j<5; j++) {
//            
//            float _xS = windowsCorner[i][j].x;
//            float _yS = windowsCorner[i][j].y;
//            
//            ofDrawBitmapString(ofToString(windowsCornerNumber[i][j],0), _xS, _yS);
//            
//        }
//    }
    
    ofSetColor(_c);
    
    for (int i=0; i<23; i++) {
        for (int j=0; j<6; j++) {
            float _xS = framesCenter[i][j].x;
            float _yS = framesCenter[i][j].y;
            string _s = ofToHex(&windowsCornerNumber[i+j]);
            string _sS = ofToString(windowsCornerNumber[i+j], 4);
            font->draw(ofToString(windowsCornerNumber[i+j]), 14, _xS, _yS + 6);
        }
    }
    
    
//    for (int i=0; i<4; i++) {
//        float _xS = fassadeCorner[i].x;
//        float _yS = fassadeCorner[i].y;
//
//        ofDrawBitmapString(ofToString(windowsCornerNumber[i],0), _xS, _yS);
//
//    }
    
    
    ofPopStyle();


    ofPopMatrix();
    
    ofDisableAlphaBlending();

    
}


//--------------------------------------------------------------
void BaseArch::drawWindows( ofColor _c ){

    ofEnableAlphaBlending();

    
    ofPushMatrix();
    ofPushStyle();
    
    
    ofSetColor(_c);
    
    float _w = windowsCorner[0][1].x - windowsCorner[0][0].x;
    float _h = windowsCorner[0][0].y - windowsCorner[0][3].y;
    

    for (int i=0; i<22; i++) {
        for (int j=0; j<5; j++) {
            float _x = windowsOriginCenter[i][j].x - _w * 0.5;
            float _y = windowsOriginCenter[i][j].y - _h * 0.5;

            ofDrawRectangle( _x, _y, _w, _h );
        }
    }
    
    
    ofPopStyle();
    ofPopMatrix();
    
    ofDisableAlphaBlending();

    
}


//--------------------------------------------------------------
void BaseArch::drawRandomWindows( ofColor _c ){
    
    
    int _windowsVerticalOn[4];
    int _windowsHorizomOn[2];
    for (int i=0; i<4; i++) {
        _windowsVerticalOn[i] = (int)ofRandom(21);
    }
    for (int i=0; i<2; i++) {
        _windowsHorizomOn[i] = (int)ofRandom(4);
    }
    
    ofEnableAlphaBlending();
    
    
    ofPushMatrix();
    ofPushStyle();
    
    
    ofSetColor(_c);
    
    float _w = windowsCorner[0][1].x - windowsCorner[0][0].x;
    float _h = windowsCorner[0][0].y - windowsCorner[0][3].y;
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<2; j++) {
            
            int _i = _windowsVerticalOn[i];
            int _j = _windowsHorizomOn[j];
            
            float _x = windowsOriginCenter[_i][_j].x - _w * 0.5;
            float _y = windowsOriginCenter[_i][_j].y - _h * 0.5;
            
            ofDrawRectangle( _x, _y, _w, _h );

        }
    }
    
    
    ofPopStyle();
    ofPopMatrix();
    
    ofDisableAlphaBlending();
    
    
}



//--------------------------------------------------------------
void BaseArch::drawWindowNumber( ofColor _c ){
    
    
    int _windowsVerticalOn[4];
    int _windowsHorizomOn[2];
    int _windowsNumbers[26];

    for (int i=0; i<4; i++) {
        _windowsVerticalOn[i] = floor(ofRandom(22));
    }
    for (int i=0; i<2; i++) {
        _windowsHorizomOn[i] = floor(ofRandom(5));
    }
    for (int i=0; i<8; i++) {
        _windowsNumbers[i] = (int)ofRandom(26);
    }
    
    ofEnableAlphaBlending();
    
    
    ofPushMatrix();
    ofPushStyle();
    
    
    ofSetColor(_c);
    
    float _w = windowsCorner[0][1].x - windowsCorner[0][0].x;
    float _h = windowsCorner[0][0].y - windowsCorner[0][3].y;
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<2; j++) {
            
            int _i = _windowsVerticalOn[i];
            int _j = _windowsHorizomOn[j];
            
            float _x = windowsOriginCenter[_i][_j].x - _w * 0.5;
            float _y = windowsOriginCenter[_i][_j].y - _h * 0.5;
            
            int _index = i + j * 4;
            string _s = alphabet[_windowsNumbers[_index]];
            font->draw(_s, 100, _x, _y - 30 );
        }
    }
    
    
    ofPopStyle();
    ofPopMatrix();
    
    ofDisableAlphaBlending();
    
    
}


//--------------------------------------------------------------
void BaseArch::randomNumberGenerator(){
    
    windowsCornerNumber.resize(440);
    for (int j=0; j<440; j++) {
            float _r = ofRandom(440);
            windowsCornerNumber[j] = _r;
    }

    
}



//--------------------------------------------------------------
void BaseArch::keyInteraction(int key){

    if (key == ' ') {
        randomNumberGenerator();
    }
        
}





