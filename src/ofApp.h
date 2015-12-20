#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxPostGlitch.h"

#include "GuiApp.h"

#include "BaseArch.h"

#include "ofxLeapMotion2.h"

#include "ofxFontStash.h"

#include "ofxProcessFFT.h"
#include "MidiInput.hpp"

#include "GlungeWinter.h"
#include "LiveCamGlitch.hpp"
#include "Labyrinth.hpp"
#include "Calligraphy.h"
#include "Pluto.hpp"
#include "IndiaTower.hpp"
#include "TrierFlyingCam.hpp"
#include "CubicMapFlyingCam.hpp"
#include "MoonCreator.hpp"
#include "LineVideo.h"
#include "MovingObjects.h"
#include "DroneAttack.hpp"
#include "WebLiveCam.hpp"
#include "NightVision.hpp"
#include "SpeechVideoSynth.hpp"

#define WEBCAM_WIDTH 640
#define WEBCAM_HEIGHT 480
#define WEBCAM_ID 1


class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    shared_ptr<GuiApp> gui;

    ofxFontStash font;
    ofxFontStash fontVideo;
    MidiInput midiInput;
    ofVideoGrabber webCamHD;

    ofxLeapMotion leapMotion;
    
    BaseArch baseArch;
    
    GlungeWinter glungeWinter;
    LiveCamGlitch liveCamGlitch;
    Labyrinth labyrinth;
    ProcessFFT fft;
    Calligraphy calligraphy;
    Pluto pluto;
    IndiaTower indiaTower;
    TrierFlyingCam trierFlyingCam;
    CubicMapFlyingCam cubicMapFlyingCam;
    MoonCreator moonCreator;
    LineVideo lineVideo;
    MovingObjects movingObjects;
    DroneAttack droneAttack;
    WebLiveCam webLiveCam;

    NightVision nightVision;    
    SpeechVideoSynth speechVideoSynth;

    
    int nBandsToGet;

    float mainOffSetXPos, mainOffSetYPos;
    
    vector<float> captureFFTSmoothed;
    vector<int> captureFFTIndex;


    void drawBaseArch();
    
    int labyrinthOldNumParticle;
    int labyrinthOldType;
    bool labyrinthChangeNum;

    
    int speechVideoOldNum;

    
    bool fullScreen;
    
    
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
    ofxSyphonServerDirectory dir;
    ofxSyphonClient client;
    int dirIdx;

    
    ofFbo			backFBO;
    ofFbo			frontFBO;
    ofxPostGlitch	backGlitch;
    ofxPostGlitch	frontGlitch;
    
    ofFbo			mainFBO;
    ofxPostGlitch	mainGlitch;
    
    bool bMainDirectglitch;
    ofImage mainImgDirectGlitch;
    ofImageQualityType qualityMain;
    void mainGlitchPixel(ofPixels _p);

    bool scene01;
    
    bool sceneSelect[13];
    bool BaseArchSelect[6];
    
    
    float fassadeWidth;
    float fassadeHeight;
    
    
    ofVideoPlayer C_shell_snowden_start_FIN;
    ofVideoPlayer CSharp_02_shell_snowden_worldwide_FIN;
    ofVideoPlayer D_02_shell_snowden_everything_FIN;
    ofVideoPlayer E_03_thingy_harvested_complete_FIN;
    ofVideoPlayer F_03_thingy_harvested_FIN;
    ofVideoPlayer FSharp_09_stringer_ericschmidt_FIN;
    ofVideoPlayer G_13_oddity_We_kill_people_FIN;  
    ofVideoPlayer GSharp_Bowie_Mind_Control;
    ofVideoPlayer A_Bowie_payyourbills;
    ofVideoPlayer ASharp_Bowie_thenetworks;
    ofVideoPlayer B_Bowie_conquer_the_world;
    
    
    bool moviesOn[11];
    bool movieAllOnOff;
    
    void speechMovieUpdate(ofVideoPlayer _p, int _i);
    
    
    ofVideoPlayer staminaVideo;
    bool staminaVideoALL;
    bool staminaVideoA;
    bool staminaVideoB;
    bool staminaVideoC;
    bool staminaVideoD;
    
    bool randomText;
    
    
    ofColor Cubic_backGroundColor;
    
};



