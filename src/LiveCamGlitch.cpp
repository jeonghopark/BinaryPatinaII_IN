//
//  LiveCamGlitch.cpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 14/10/15.
//
//

#include "LiveCamGlitch.hpp"


//--------------------------------------------------------------
LiveCamGlitch::LiveCamGlitch(){

}


//--------------------------------------------------------------
LiveCamGlitch::~LiveCamGlitch(){
    
}


//--------------------------------------------------------------
void LiveCamGlitch::inputMidiInput(MidiInput & _midiInput){
    midiInput = & _midiInput;
}



//--------------------------------------------------------------
void LiveCamGlitch::setup(){
    
    quality = OF_IMAGE_QUALITY_WORST;
    
    videoW = 640;  // 1920, 1280
    videoH = 480;   // 1080, 720
    
    liveVideoFbo.clear();
    liveVideoFbo.allocate(videoW, videoH);
    
    windowView.allocate(videoW, videoH);
    captureCam.allocate(videoW * 0.5, videoH);
    
    float _w = baseArch->fassadeCorner[1].x - baseArch->fassadeCorner[0].x;
    float _h = baseArch->fassadeCorner[2].y - baseArch->fassadeCorner[0].y;
    imgDirectGlitch.allocate(videoW, videoH, OF_IMAGE_COLOR);
    
    glitchEffect.loadShader();
    glitchEffect.setup(&liveVideoFbo);
    
    bDirectglitch = false;
    
}






//--------------------------------------------------------------
void LiveCamGlitch::update(){
    
    if (webCamHD->isFrameNew()){

        windowView.setFromPixels(webCamHD->getPixels());
        windowView.setROI(videoW * 0.5, 0, videoW * 0.5, videoH);
        captureCam.setFromPixels( windowView.getRoiPixels() );

        liveVideoFbo.begin();
        ofColor(0,255);
        captureCam.draw(0, 0);
        liveVideoFbo.end();
        
    }
    
    
    
    
//    glitchEffect.setFx(OFXPOSTGLITCH_CONVERGENCE, midiInput->drumPad[0]);
//    glitchEffect.setFx(OFXPOSTGLITCH_GLOW, midiInput->drumPad[1]);
//    glitchEffect.setFx(OFXPOSTGLITCH_SHAKER, midiInput->drumPad[2]);
//    glitchEffect.setFx(OFXPOSTGLITCH_CUTSLIDER, midiInput->drumPad[3]);
//    glitchEffect.setFx(OFXPOSTGLITCH_TWIST, midiInput->drumPad[4]);
//    glitchEffect.setFx(OFXPOSTGLITCH_NOISE, midiInput->drumPad[5]);
//    glitchEffect.setFx(OFXPOSTGLITCH_SLITSCAN, midiInput->drumPad[6]);
//    glitchEffect.setFx(OFXPOSTGLITCH_SWELL, midiInput->drumPad[7]);

}



//--------------------------------------------------------------
void LiveCamGlitch::glitchUpdate(ofPixels _p) {
    
    string compressedFilename = "compressed.jpg";
    
    unsigned char * _c = _p.getData();
    
    float coin = ofRandom(100);
    if (coin > 95) {
        _c = _p.getData() + (int)ofRandom(100);
    }
    
    imgDirectGlitch.setImageType(OF_IMAGE_COLOR);
    
    float _w = baseArch->fassadeCorner[1].x - baseArch->fassadeCorner[0].x;
    float _h = baseArch->fassadeCorner[2].y - baseArch->fassadeCorner[0].y;
    imgDirectGlitch.setFromPixels(_c, videoW * 0.5, videoH, OF_IMAGE_COLOR);
    
    imgDirectGlitch.save(compressedFilename, quality);
    
    ofBuffer file = ofBufferFromFile(compressedFilename);
    int fileSize = file.size();
    char * buffer = file.getData();
    
    int whichByte = (int) ofRandom(fileSize);
    int whichBit = ofRandom(8);
    
    char bitMask;
    if ( whichBit >4 ) {
        bitMask = 1 << whichBit;
    } else {
        bitMask = 7 << whichBit;
    }
    
    buffer[whichByte] |= bitMask;
    
    ofBufferToFile(compressedFilename, file);
    imgDirectGlitch.load(compressedFilename);
    
    //    float coin = ofRandom(100);
    //    if (coin > 95) {
    //        reset();
    //    }
 
}



//--------------------------------------------------------------
void LiveCamGlitch::draw(){
    
    ofEnableAlphaBlending();

    float _w = baseArch->fassadeCorner[1].x - baseArch->fassadeCorner[0].x;
    float _h = _w * videoW * 0.5 / videoH;
    webCamHD->draw( baseArch->fassadeCorner[0].x, baseArch->fassadeCorner[0].y, _w, _h);
    glitchEffect.generateFx();
    
    float _center = baseArch->framesCenter[11][0].x;
    liveVideoFbo.draw( _center, 0, _w, _h );  // 640 : 960

    ofDisableAlphaBlending();

    
    
    ofEnableAlphaBlending();
    
    if (bDirectglitch) {
        float _w = baseArch->fassadeCorner[1].x - baseArch->fassadeCorner[0].x;
        float _h = baseArch->fassadeCorner[2].y - baseArch->fassadeCorner[0].y;
        float _x = baseArch->fassadeCorner[0].x;
        float _y = baseArch->fassadeCorner[0].y;
        
        ofPixels _p;
        liveVideoFbo.readToPixels(_p);
        glitchUpdate(_p);

        imgDirectGlitch.draw(_x, _y, _w * 0.5, _h);
    }
    
    ofDisableAlphaBlending();

}


//--------------------------------------------------------------
void LiveCamGlitch::keyPressed(int key){

    cout << key << endl;
    
    if (key == 33) glitchEffect.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
    if (key == 34) glitchEffect.setFx(OFXPOSTGLITCH_GLOW			, true);
    if (key == 167) glitchEffect.setFx(OFXPOSTGLITCH_SHAKER			, true);
    if (key == 36) glitchEffect.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
    if (key == 37) glitchEffect.setFx(OFXPOSTGLITCH_TWIST			, true);
    if (key == 38) glitchEffect.setFx(OFXPOSTGLITCH_NOISE			, true);
    if (key == 47) glitchEffect.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
    if (key == 40) glitchEffect.setFx(OFXPOSTGLITCH_SWELL			, true);
    if (key == 41) glitchEffect.setFx(OFXPOSTGLITCH_INVERT			, true);
    
    if (key == 61) glitchEffect.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
    if (key == 63) glitchEffect.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
    if (key == 220) glitchEffect.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
    if (key == 80) glitchEffect.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
    if (key == 79) glitchEffect.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
    if (key == 73) glitchEffect.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
    if (key == 85) glitchEffect.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);

    if (key == 42) bDirectglitch = true;

}

//--------------------------------------------------------------
void LiveCamGlitch::keyReleased(int key){

    if (key == 2305 || key == 33) glitchEffect.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
    if (key == 2305 || key == 34) glitchEffect.setFx(OFXPOSTGLITCH_GLOW			, false);
    if (key == 2305 || key == 167) glitchEffect.setFx(OFXPOSTGLITCH_SHAKER			, false);
    if (key == 2305 || key == 36) glitchEffect.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
    if (key == 2305 || key == 37) glitchEffect.setFx(OFXPOSTGLITCH_TWIST			, false);
    if (key == 2305 || key == 38) glitchEffect.setFx(OFXPOSTGLITCH_NOISE			, false);
    if (key == 2305 || key == 47) glitchEffect.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
    if (key == 2305 || key == 40) glitchEffect.setFx(OFXPOSTGLITCH_SWELL			, false);
    if (key == 2305 || key == 41) glitchEffect.setFx(OFXPOSTGLITCH_INVERT			, false);
    
    if (key == 2305 || key == 61) glitchEffect.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
    if (key == 2305 || key == 63) glitchEffect.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
    if (key == 2305 || key == 220) glitchEffect.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
    if (key == 2305 || key == 80) glitchEffect.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
    if (key == 2305 || key == 79) glitchEffect.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
    if (key == 2305 || key == 73) glitchEffect.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
    if (key == 2305 || key == 85) glitchEffect.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
    
    if (key == 2305 || key == 42) bDirectglitch = false;

    //    if (key == ' ') baseArch->keyInteraction(' ');
    
}




