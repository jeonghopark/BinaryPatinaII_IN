#include "GlungeWinter.h"

//--------------------------------------------------------------
GlungeWinter::GlungeWinter() {

    grungeTexture.load("free-grunge-textures-backgrounds-12.jpg");

}


//--------------------------------------------------------------
GlungeWinter::~GlungeWinter() {

}


//--------------------------------------------------------------
void GlungeWinter::setup(){

}


//--------------------------------------------------------------
void GlungeWinter::update() {

}



//--------------------------------------------------------------
void GlungeWinter::drawBackTexture() {

    ofEnableAlphaBlending();

    ofPushMatrix();
    
    ofPushStyle();
    
    ofSetColor(255, 30);
    
    float _w = baseArch->fassadeCorner[1].x - baseArch->fassadeCorner[0].x;
    float _h = baseArch->fassadeCorner[3].y - baseArch->fassadeCorner[0].y;
    float _x = baseArch->fassadeCorner[0].x;
    
    grungeTexture.draw(_x, 0, _w, _h);
    
    ofPopStyle();

    ofPopMatrix();
    
    ofDisableAlphaBlending();
    
}



//--------------------------------------------------------------
void GlungeWinter::drawBack() {
    
    ofEnableAlphaBlending();

    ofPushMatrix();
    
    ofPushStyle();
    
    for (int j=0; j<4; j++) {
        for (int i=0; i<15; i++) {
            ofBeginShape();
            ofSetColor( ofColor::fromHsb(ofRandom(255), ofRandom(255), ofRandom(255), 50) );
            
            float _centerX = baseArch->framesCenter[11][1].x;
            float _centerY = (baseArch->windowsCorner[10+22*j][2].y + baseArch->windowsCorner[10+22*(j+1)][0].y) * 0.5;
            
            float _xL = _centerX - i * 40;
            float _xR = _centerX + i * 40;
            float _yU = _centerY - 6;
            float _yD = _centerY + 6;
            
            
            ofVertex( _xL, _yD);
            ofVertex( _xL, _yU);
            ofVertex( _xR, _yU);
            ofVertex( _xR, _yD);
            
            ofEndShape();
        }
    }
    
    
    for (int j=0; j<22-1; j++) {
        for (int i=0; i<10; i++) {
            
            ofBeginShape();
            ofSetColor( ofColor::fromHsb(ofRandom(255), ofRandom(255), ofRandom(255), 50) );
            
            float _centerX = (baseArch->windowsCorner[j][1].x + baseArch->windowsCorner[j+1][0].x) * 0.5;
            float _centerY = baseArch->windowsOriginCenter[10][2].y;
            
            float _xL = _centerX - 6;
            float _xR = _centerX + 6;
            float _yU = _centerY - i * 40;
            float _yD = _centerY + i * 40;
            
            
            ofVertex( _xL, _yD);
            ofVertex( _xL, _yU);
            ofVertex( _xR, _yU);
            ofVertex( _xR, _yD);
            
            ofEndShape();
            
        }
    }

    
    ofPopStyle();
    
    ofPopMatrix();
    
    ofDisableAlphaBlending();
    
}



//--------------------------------------------------------------
void GlungeWinter::drawFrontHorizon() {
    

    ofPushMatrix();

    ofEnableAlphaBlending();
    
    ofPushStyle();
    
//        ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    ofEnableBlendMode( OF_BLENDMODE_MULTIPLY );
    

    
    drawHorizon();
    
    ofDisableBlendMode();
    
    
    ofPopStyle();

    ofDisableAlphaBlending();

    ofPopMatrix();
    

    
}


//--------------------------------------------------------------
void GlungeWinter::drawFrontVertical() {
    
    
    ofPushMatrix();
    
    ofEnableAlphaBlending();
    
    ofPushStyle();
    
    //        ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    ofEnableBlendMode( OF_BLENDMODE_MULTIPLY );
    
    
    drawVertical();
    
    
    ofDisableBlendMode();
    
    
    ofPopStyle();
    
    ofDisableAlphaBlending();
    
    ofPopMatrix();
    
    
    
}



//--------------------------------------------------------------
void GlungeWinter::drawVertical(){
    
    ofPushStyle();
    
    
    for (int i=0; i<15; i++) {
        ofBeginShape();
//        ofSetColor( ofColor::fromHsb(15, 183, 120, 50) );
  
        ofSetColor( verticalColor );

        
        float _centerX = baseArch->framesCenter[11][0].x;
        float _centerY = (baseArch->windowsCorner[10][0].y + baseArch->fassadeCorner[0].y) * 0.5;
        
        float _xL = _centerX - i * 40;
        float _xR = _centerX + i * 40;
        float _yU = _centerY - 9;
        float _yD = _centerY + 9;
        
        
        ofVertex( _xL, _yD);
        ofVertex( _xL, _yU);
        ofVertex( _xR, _yU);
        ofVertex( _xR, _yD);
        
        ofEndShape();
    }
    
    ofPopStyle();
    
    
    ofPushStyle();
    
    for (int j=0; j<4; j++) {
        for (int i=0; i<15; i++) {
            ofBeginShape();
//            ofSetColor( ofColor::fromHsb(15, 183, 120, 50) );
            
            ofSetColor( verticalColor );

            
            float _centerX = baseArch->framesCenter[11][1].x;
            float _centerY = (baseArch->windowsCorner[10+22*j][2].y + baseArch->windowsCorner[10+22*(j+1)][0].y) * 0.5;
            
            float _xL = _centerX - i * 40;
            float _xR = _centerX + i * 40;
            float _yU = _centerY - 6;
            float _yD = _centerY + 6;
            
            
            ofVertex( _xL, _yD);
            ofVertex( _xL, _yU);
            ofVertex( _xR, _yU);
            ofVertex( _xR, _yD);
            
            ofEndShape();
        }
    }
    
    
    ofPopStyle();
    
    
    
    ofPushStyle();
    
    for (int i=0; i<15; i++) {
        ofBeginShape();
        //            ofSetColor( ofColor::fromHsb(15, 183, 120, 50) );
        
        ofSetColor( verticalColor );
        
        float _centerX = baseArch->framesCenter[11][0].x;
        float _centerY = (baseArch->windowsCorner[10+22*4][3].y + baseArch->fassadeCorner[2].y) * 0.5;
        
        float _xL = _centerX - i * 40;
        float _xR = _centerX + i * 40;
        float _yU = _centerY - 6;
        float _yD = _centerY + 6;
        
        
        ofVertex( _xL, _yD);
        ofVertex( _xL, _yU);
        ofVertex( _xR, _yU);
        ofVertex( _xR, _yD);
        
        ofEndShape();
    }
    
    ofPopStyle();

}

//--------------------------------------------------------------
void GlungeWinter::drawHorizon(){
    
    
    ofPushStyle();
    

    for (int i=0; i<10; i++) {
        
        ofBeginShape();
//        ofSetColor( ofColor::fromHsb(15, 183, 120, 50) );
        
        ofSetColor( horizonColor );
        
        float _centerX = (baseArch->fassadeCorner[0].x + baseArch->windowsCorner[0][0].x) * 0.5;
        float _centerY = baseArch->windowsOriginCenter[10][2].y;
        
        float _xL = _centerX - 6;
        float _xR = _centerX + 6;
        float _yU = _centerY - i * 40;
        float _yD = _centerY + i * 40;
        
        
        ofVertex( _xL, _yD);
        ofVertex( _xL, _yU);
        ofVertex( _xR, _yU);
        ofVertex( _xR, _yD);
        
        ofEndShape();
        
    }

    
    for (int j=0; j<22-1; j++) {
        for (int i=0; i<10; i++) {

            ofBeginShape();
            //        ofSetColor( ofColor::fromHsb(15, 183, 120, 50) );
            
            ofSetColor( horizonColor );
            
            float _centerX = (baseArch->windowsCorner[j][1].x + baseArch->windowsCorner[j+1][0].x) * 0.5;
            float _centerY = baseArch->windowsOriginCenter[10][2].y;
            
            float _xL = _centerX - 6;
            float _xR = _centerX + 6;
            float _yU = _centerY - i * 40;
            float _yD = _centerY + i * 40;
            
            
            ofVertex( _xL, _yD);
            ofVertex( _xL, _yU);
            ofVertex( _xR, _yU);
            ofVertex( _xR, _yD);
            
            ofEndShape();
            
        }
    }
    
    
    for (int i=0; i<10; i++) {
        
        ofBeginShape();
        //        ofSetColor( ofColor::fromHsb(15, 183, 120, 50) );
        
        ofSetColor( horizonColor );
        
        float _centerX = (baseArch->fassadeCorner[1].x + baseArch->windowsCorner[21][1].x) * 0.5;
        float _centerY = baseArch->windowsOriginCenter[10][2].y;
        
        float _xL = _centerX - 6;
        float _xR = _centerX + 6;
        float _yU = _centerY - i * 40;
        float _yD = _centerY + i * 40;
        
        
        ofVertex( _xL, _yD);
        ofVertex( _xL, _yU);
        ofVertex( _xR, _yU);
        ofVertex( _xR, _yD);
        
        ofEndShape();
        
    }

    
    ofPopStyle();
    
    
}







