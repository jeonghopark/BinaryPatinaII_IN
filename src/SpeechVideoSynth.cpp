//
//  SpeechVideoSynth.cpp
//  BinaryPatinaII
//
//  Created by Jeong-Ho on 20/10/15.
//
//

#include "SpeechVideoSynth.hpp"



//--------------------------------------------------------------
SpeechVideoSynth::SpeechVideoSynth(){
    
}


//--------------------------------------------------------------
SpeechVideoSynth::~SpeechVideoSynth(){
    
}


//--------------------------------------------------------------
void SpeechVideoSynth::movieLoad(){
    
    
//    C_shell_snowden_start_FIN.load("C_shell_snowden_start_FIN.mp4");
//    CSharp_02_shell_snowden_worldwide_FIN.load("C#_02_shell_snowden worldwide_FIN.mp4");
//    D_02_shell_snowden_everything_FIN.load("D_02 shell_snowden everything FIN.mp4");
//
////    C_shell_snowden_start_FIN_Frame = C_shell_snowden_start_FIN.getTotalNumFrames();
////    CSharp_02_shell_snowden_worldwide_FIN_Frame = CSharp_02_shell_snowden_worldwide_FIN.getTotalNumFrames();
////    D_02_shell_snowden_everything_FIN_Frame = D_02_shell_snowden_everything_FIN.getTotalNumFrames();
//    
//    
//    E_03_thingy_harvested_complete_FIN.load("E_03_thingy_harvested_complete_FIN.mp4");

}


//--------------------------------------------------------------
void SpeechVideoSynth::setup(){
    
    movieLoad();
    
    windowView.allocate(960, 540);
    
    
//    windowView.allocate(speech01_shell.getWidth(), speech01_shell.getHeight());
//
//    float _w = baseArch->framesCenter[1][0].x - baseArch->framesCenter[0][0].x;
//    float _h = baseArch->framesCenter[0][1].y - baseArch->framesCenter[0][0].y;
//    
//    windowsNum = 20;
//    
//    windowMovies.resize(windowsNum);
//    for (int i=0; i<windowsNum; i++){
//        windowMovies[i].allocate(_w, _h);
//    }
    
//    randomWindowsPosition();
    
    indexMovie = 0;
    movie0On = false;
    movie4On = false;
//    E_03_thingy_harvested_complete_FIN.play();

}



//--------------------------------------------------------------
void SpeechVideoSynth::update(){

//    C_shell_snowden_start_FIN.update();
//    CSharp_02_shell_snowden_worldwide_FIN.update();
//    D_02_shell_snowden_everything_FIN.update();
 
    
//        if (midiInput.iacNoteOnCh1[3]) {
//            E_03_thingy_harvested_complete_FIN.update();
//        }
//
//    
//    if ( midiInput.iacNoteOnCh1[3] && !movie4On ) {
//        E_03_thingy_harvested_complete_FIN.play();
//        movie4On = true;
//    } else if (!midiInput.iacNoteOnCh1[3] && movie4On) {
//        E_03_thingy_harvested_complete_FIN.stop();
//        E_03_thingy_harvested_complete_FIN.firstFrame();
//        movie4On = false;
//    }
    
}



//--------------------------------------------------------------
void SpeechVideoSynth::draw(){
    
//    cout << midiInput.iacNoteOnCh1[3] << endl;
//
//    if ( midiInput.iacNoteOnCh1[3]) {
//        cout << "bang" << endl;
//        E_03_thingy_harvested_complete_FIN.draw(0, 0);
//    }

    
//    if ( midi->iacNoteOnCh1[0] && !movie0On ) {
//        C_shell_snowden_start_FIN.play();
//        movie0On = true;
//    } else {
//        C_shell_snowden_start_FIN.stop();
//        C_shell_snowden_start_FIN.firstFrame();
//        movie0On = false;
//    }
//
//    
//    if ( midi->iacNoteOnCh1[1] ) {
//        CSharp_02_shell_snowden_worldwide_FIN.play();
//    } else {
//        CSharp_02_shell_snowden_worldwide_FIN.stop();
//        CSharp_02_shell_snowden_worldwide_FIN.firstFrame();
//    }
//
//    
//    if ( midi->iacNoteOnCh1[2] ) {
//        D_02_shell_snowden_everything_FIN.play();
//    } else {
//        D_02_shell_snowden_everything_FIN.stop();
//        D_02_shell_snowden_everything_FIN.firstFrame();
//    }

//    if ( midi->iacNoteOnCh1[3]) {
//    }
//
    

//    if ( midi->iacNoteOnCh1[3] && !movie4On ) {
//        movie4On = true;
//    } else if (!midi->iacNoteOnCh1[3]) {
//        E_03_thingy_harvested_complete_FIN.stop();
//        E_03_thingy_harvested_complete_FIN.firstFrame();
//        movie4On = false;
//    }

    
//    C_shell_snowden_start_FIN.draw(0, 0);
//
//    CSharp_02_shell_snowden_worldwide_FIN.draw(0, 0);
//
//    D_02_shell_snowden_everything_FIN.draw(0, 0);

    
//    if (movie4On) {
//        E_03_thingy_harvested_complete_FIN.play();
//    }

    
//    E_03_thingy_harvested_complete_FIN.draw(0, 0);
    
    
    
    
}


//--------------------------------------------------------------
void SpeechVideoSynth::movieAllPlay(int _pos){
    
    ofEnableAlphaBlending();
    
    float _mainX = baseArch->framesCenter[11][0].x + baseArch->framesCenter[11][0].x * _pos;
    float _mainY = baseArch->framesCenter[11][0].y;
    float _mainW = baseArch->framesCenter[22][0].x - baseArch->framesCenter[11][0].x;
    float _mainH = baseArch->framesCenter[11][5].y - baseArch->framesCenter[11][0].y;
    
    windowView.draw(_mainX, _mainY, _mainW, _mainH);
    
//    for (int i=0; i<windowsNum; i++){
//        ofVec2f _posROIMovies = baseArch->framesCenter[indexX[i]][indexY[i]] + ofVec2f(baseArch->framesCenter[11][0].x * -_pos, 0);
//        windowMovies[i].draw( _posROIMovies );
//    }
    
    ofDisableAlphaBlending();
    
}


//--------------------------------------------------------------
void SpeechVideoSynth::randomWindowsPosition(){
    
//    indexX.resize(windowsNum);
//    indexY.resize(windowsNum);
//    captureIndexX.resize(windowsNum);
//    captureIndexY.resize(windowsNum);
//    for (int i=0; i<windowMovies.size(); i++){
//        indexX[i] = floor( ofRandom(10) );
//        indexY[i] = floor( ofRandom(5) );
//        captureIndexX[i] = floor( ofRandom(10) );
//        captureIndexY[i] = floor( ofRandom(5) );
//    }
    
}


//--------------------------------------------------------------
void SpeechVideoSynth::keyReleased(int key){
    
//    randomWindowsPosition();
    
}



