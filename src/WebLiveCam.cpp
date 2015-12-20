//
//  WebLiveCam.cpp
//  BinaryPatinaII
//
//  Created by jeonghopark on 15/10/15.
//
//

#include "WebLiveCam.hpp"


//--------------------------------------------------------------
WebLiveCam::WebLiveCam(){
    
}


//--------------------------------------------------------------
WebLiveCam::~WebLiveCam(){
    
}

//--------------------------------------------------------------
void WebLiveCam::movieLoad(){
    
    webCam01.load("Asakusa Traffic Cam - japan - 1151 - 1410 - 2015.mp4");
    webCam02.load("NYSDOT Traffic Cam - newyork - 1156 - 1410 - 2015.mp4");
    webCam03.load("Street Cams and Market Square-Finland-1142_1410_2015.mp4");
    
    webCam01.setSpeed(3);
    webCam02.setSpeed(3);
    webCam03.setSpeed(3);


}


//--------------------------------------------------------------
void WebLiveCam::setup(){
    
    webCam01.load("Asakusa Traffic Cam - japan - 1151 - 1410 - 2015.mp4");
    webCam02.load("NYSDOT Traffic Cam - newyork - 1156 - 1410 - 2015.mp4");
    webCam03.load("Street Cams and Market Square-Finland-1142_1410_2015.mp4");
    
    webCam01.setSpeed(3);
    webCam02.setSpeed(3);
    webCam03.setSpeed(3);
    
    windowView.allocate(webCam01.getWidth(), webCam01.getHeight());
    
    float _w = baseArch->framesCenter[1][0].x - baseArch->framesCenter[0][0].x;
    float _h = baseArch->framesCenter[0][1].y - baseArch->framesCenter[0][0].y;
    
    windowsNum = 20;
    
    windowMovies.resize(windowsNum);
    for (int i=0; i<windowsNum; i++){
        windowMovies[i].allocate(_w, _h);
    }
    
    randomWindowsPosition();
    
    indexMovie = 0;
    indexMovieOldNum = 0;
    movieOn = false;
    
}



//--------------------------------------------------------------
void WebLiveCam::update(){

    if ((indexMovie == 0)&&!movieOn) {
        webCam01.play();
        webCam02.stop();
        webCam03.stop();
        indexMovieOldNum = indexMovie;
        movieOn = true;
    } else if ((indexMovie == 1)&&!movieOn) {
        webCam01.stop();
        webCam02.play();
        webCam03.stop();
        indexMovieOldNum = indexMovie;
        movieOn = true;
    } else if ((indexMovie == 2)&&!movieOn) {
        webCam01.stop();
        webCam02.stop();
        webCam03.play();
        indexMovieOldNum = indexMovie;
        movieOn = true;
    }
    
    if (indexMovie != indexMovieOldNum) {
        movieOn = false;
    }

    
    
    
    switch (indexMovie) {

        case 0:
            webCam01.update();
            if (webCam01.isFrameNew()) {
                
                windowView.setFromPixels(webCam01.getPixels());
                
                float _w = baseArch->framesCenter[1][0].x - baseArch->framesCenter[0][0].x;
                float _h = baseArch->framesCenter[0][1].y - baseArch->framesCenter[0][0].y;
                
                for (int i=0; i<windowsNum; i++){
                    float _x = captureIndexX[i] * _w;
                    float _y = captureIndexY[i] * _h;
                    windowView.setROI(_x, _y, _w, _h);
                    windowMovies[i].setFromPixels( windowView.getRoiPixels() );
                }
                
            }

            break;

        case 1:
            webCam02.update();
            if (webCam02.isFrameNew()) {
                
                windowView.setFromPixels(webCam02.getPixels());
                
                float _w = baseArch->framesCenter[1][0].x - baseArch->framesCenter[0][0].x;
                float _h = baseArch->framesCenter[0][1].y - baseArch->framesCenter[0][0].y;
                
                for (int i=0; i<windowsNum; i++){
                    float _x = captureIndexX[i] * _w;
                    float _y = captureIndexY[i] * _h;
                    windowView.setROI(_x, _y, _w, _h);
                    windowMovies[i].setFromPixels( windowView.getRoiPixels() );
                }
                
            }
            
            break;

            
        case 2:
            webCam03.update();
            if (webCam03.isFrameNew()) {
                
                windowView.setFromPixels(webCam03.getPixels());
                
                float _w = baseArch->framesCenter[1][0].x - baseArch->framesCenter[0][0].x;
                float _h = baseArch->framesCenter[0][1].y - baseArch->framesCenter[0][0].y;
                
                for (int i=0; i<windowsNum; i++){
                    float _x = captureIndexX[i] * _w;
                    float _y = captureIndexY[i] * _h;
                    windowView.setROI(_x, _y, _w, _h);
                    windowMovies[i].setFromPixels( windowView.getRoiPixels() );
                }
                
            }
            
            break;

            
        default:
            break;
            
    }

    
}



//--------------------------------------------------------------
void WebLiveCam::draw(){
    
    
    switch (indexMovie%2) {

        case 0:
            movieAllPlay( 0 );
            break;

        case 1:
            movieAllPlay( -1 );
            break;
            
        default:
            break;
    
    }
    

}


//--------------------------------------------------------------
void WebLiveCam::movieAllPlay(int _pos){

    ofEnableAlphaBlending();
    
    float _mainX = baseArch->framesCenter[11][0].x + baseArch->framesCenter[11][0].x * _pos;
    float _mainY = baseArch->framesCenter[11][0].y;
    float _mainW = baseArch->framesCenter[22][0].x - baseArch->framesCenter[11][0].x;
    float _mainH = baseArch->framesCenter[11][5].y - baseArch->framesCenter[11][0].y;
    
    windowView.draw(_mainX, _mainY, _mainW, _mainH);

    for (int i=0; i<windowsNum; i++){
        ofVec2f _posROIMovies = baseArch->framesCenter[indexX[i]][indexY[i]] + ofVec2f(baseArch->framesCenter[11][0].x * -_pos, 0);
        windowMovies[i].draw( _posROIMovies );
    }

    ofDisableAlphaBlending();
    
}


//--------------------------------------------------------------
void WebLiveCam::randomWindowsPosition(){
    
    indexX.resize(windowsNum);
    indexY.resize(windowsNum);
    captureIndexX.resize(windowsNum);
    captureIndexY.resize(windowsNum);
    for (int i=0; i<windowMovies.size(); i++){
        indexX[i] = floor( ofRandom(10) );
        indexY[i] = floor( ofRandom(5) );
        captureIndexX[i] = floor( ofRandom(10) );
        captureIndexY[i] = floor( ofRandom(5) );
    }

}


//--------------------------------------------------------------
void WebLiveCam::keyReleased(int key){
    
    randomWindowsPosition();
    
}



