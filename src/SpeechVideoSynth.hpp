//
//  SpeechVideoSynth.hpp
//  BinaryPatinaII
//
//  Created by Jeong-Ho on 20/10/15.
//
//

#pragma once


#ifndef SpeechVideoSynth_hpp
#define SpeechVideoSynth_hpp

#include "ofMain.h"

#include "SceneSetup.hpp"


#include "MidiInput.hpp"
#include "ofxOpenCv.h"

class SpeechVideoSynth : public SceneSetup {
    
public:
    
    SpeechVideoSynth();
    ~SpeechVideoSynth();
    
    void setup();
    void update();
    void draw();
    
    void randomWindowsPosition();
    
    void movieLoad();
    void keyReleased(int key);
    
    void movieAllPlay(int _pos);
    
    MidiInput midiInput;
    
    ofVideoPlayer C_shell_snowden_start_FIN;
    ofVideoPlayer CSharp_02_shell_snowden_worldwide_FIN;
    ofVideoPlayer D_02_shell_snowden_everything_FIN;
    
    ofVideoPlayer E_03_thingy_harvested_complete_FIN;

    
    ofxCvColorImage windowView;
    vector<ofxCvColorImage> windowMovies;
    vector<int> indexX;
    vector<int> indexY;
    vector<int> captureIndexX;
    vector<int> captureIndexY;
    
    int windowsNum;
    
    int indexMovie;
    int indexMovieOldNum;
    bool movie0On;
    bool movie4On;
    
    int C_shell_snowden_start_FIN_Frame;
    int CSharp_02_shell_snowden_worldwide_FIN_Frame;
    int D_02_shell_snowden_everything_FIN_Frame;
    
    
    int E_03_thingy_harvested_complete_FIN_Frame;
    

    
    
};


#endif /* SpeechVideoSynth_hpp */




