//
//  NightVision.hpp
//  BinaryPatinaII
//
//  Created by Jeong-Ho on 19/10/15.
//
//

#ifndef NightVision_hpp
#define NightVision_hpp

#include "ofMain.h"
#include "SceneSetup.hpp"

#include "ofxSyphon.h"

#include "ofxOpenCv.h"


class NightVision : public SceneSetup{
    
    public :
    
    NightVision();
    ~NightVision();
    
    void setup();
    void update(ofxSyphonClient & _s);
    void textureInput();
    void draw();
    
    ofxSyphonClient * syphon;
    
    ofxCvGrayscaleImage nightVisionView;
    ofxCvColorImage colorView;
    
    ofPixels nightvisionPixels;
    
    
};

#endif /* NightVision_hpp */
