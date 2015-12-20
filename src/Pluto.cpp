//
//  Pluto.cpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//

#include "Pluto.hpp"


//--------------------------------------------------------------
Pluto::Pluto(){
    

}


//--------------------------------------------------------------
Pluto::~Pluto(){
    
    
}


//--------------------------------------------------------------
void Pluto::setup(){
    
    loadImages();
    
    speedFactor = 0.4;
    
}


//--------------------------------------------------------------
void Pluto::update(){
    
    yPosMoon = yPosMoon + 1 * speedFactor;
    
    if (yPosMoon > -180) {
        yPosMoon = -180;
        
        xyScaleMoon = xyScaleMoon - 1.3 * speedFactor * speedRatio;
        
//        cout << xyScaleMoon << endl;

        if (xyScaleMoon < 1800) {
            yPosEarth = yPosEarth + 1 * speedFactor * speedRatio;
        }
        
        if (yPosEarth > 400) {
            yPosEarth = 400;
        }
        
        
        if (xyScaleMoon < 0) {
            xyScaleMoon = 0;
        }
        
    }
    
//    cout << yPosMoon << endl;
//    cout << yPosEarth << endl;
//    cout << xyScaleMoon << endl;
//    cout << xyScaleEarth << endl;
    
}


//--------------------------------------------------------------
void Pluto::draw(){
    
    ofEnableAlphaBlending();
    
    ofPushMatrix();
    ofTranslate( 0, -200 );
    moon.draw( ofGetWidth() * 0.5 - xyScaleMoon * 0.5, ofGetHeight() * 0.5 + yPosMoon - xyScaleMoon * 0.5, xyScaleMoon, xyScaleMoon );
    
    ofPopMatrix();
    

    ofPushMatrix();
    earthBlur.draw(ofGetWidth() * 0.5 - xyScaleEarth * 0.5, ofGetHeight() * 0.5 + yPosEarth - xyScaleEarth * 0.5, xyScaleEarth, xyScaleEarth );
    
    ofPopMatrix();

    ofDisableAlphaBlending();
    
}


//--------------------------------------------------------------
void Pluto::loadImages(){

    moon.clear();
    earthBlur.clear();
    
    moon.load("MoonHRfull.png");
    earthBlur.load("earthBlur.png");
    
    xyScaleMoon = moon.getWidth();
    xyScaleEarth = earthBlur.getWidth();
    
    returnValue();
    
}



//--------------------------------------------------------------
void Pluto::returnValue(){
    
    yPosMoon = -moon.getWidth() * 0.5 - 350;
    yPosEarth = -earthBlur.getWidth() * 0.5 - 350;
    xyScaleMoon = 3200;
    xyScaleEarth = 2037;
    
}





