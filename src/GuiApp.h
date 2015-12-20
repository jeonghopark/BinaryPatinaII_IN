#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class GuiApp : public ofBaseApp {

public:

    void setup();
	void update();
	void draw();

    ofParameter<string> FrameRate;
    ofxButton FullScreen;
    ofxButton webcamOn;
    ofxToggle CanonView;
    ofxButton SyphonSearch;
	ofParameter<bool> OnOff_Windows;
    ofParameter<ofColor> color_Windows;
    ofParameter<bool> OnOff_Frames;
    ofParameter<ofColor> color_Frames;
    ofParameter<bool> OnOff_Lines;
    ofParameter<ofColor> color_Lines;
    ofParameter<bool> OnOff_Numbers;
    ofParameter<ofColor> color_Numbers;
    ofParameter<bool> OnOff_Cross;
    ofParameter<ofColor> color_Cross;
    ofParameter<bool> OnOff_Points;
    ofParameter<ofColor> color_Points;
    ofParameter<bool> OnOff_RandomW;
    ofParameter<ofColor> color_RandomW;

    ofxFloatSlider xPos;
    ofxFloatSlider yPos;
    ofxFloatSlider xScale;
    ofxFloatSlider yScale;
    
    
    ofParameter<bool> OnOff_GlungeWinter;
    ofxToggle verticalOnOff;
    ofxColorSlider VerticalColor;
    ofxToggle horizonOnOff;
    ofxColorSlider HorizonColor;
    
    ofParameter<bool> OnOff_LiveCamGlitch;
    ofxButton ResetShader;
    
    ofParameter<bool> OnOff_Labyrinth;
    ofxToggle LineType;
    ofxButton UpdateRandom;
    ofxIntSlider NumParticles;
    ofxFloatSlider Speed;
    ofxFloatSlider ParticleSize;
    ofxColorSlider ParticleColor;
    ofxColorSlider PathColor;
    ofxColorSlider ConnectionColor;


    ofParameter<bool> OnOff_Calligraphy;
    ofxFloatSlider fftSize;
    
    ofParameter<bool> OnOff_Pluto;
    ofxButton Return;
    ofxFloatSlider SpeedRatioMoon;

    
    ofParameter<bool> OnOff_IndiaTower;
    ofxColorSlider BezielColor;
    
    
    ofParameter<bool> OnOff_TrierFlyingCam;
    ofxColorSlider TrierBuildColor;
    ofxColorSlider TrierRoadColor;
    ofxColorSlider TrierMovingColor;

    ofParameter<bool> OnOff_CubicMapFlyingCam;
    ofxColorSlider BuildColor;
    ofxColorSlider BuildSideColor;
    ofxColorSlider RoadColor;
    ofxColorSlider MovingColor;
    ofxToggle BuildOnOff;
    ofxToggle BuildSideOnOff;
    ofxToggle RoadOnOff;
    ofxToggle MovingOnOff;
    
    
    
    ofParameter<bool> OnOff_MoonCreator;
    ofxColorSlider moonStraightLine;
    
    

    ofParameter<bool> OnOff_LineVideo;
    ofxFloatSlider ControlRandom;
    
    
    ofParameter<bool> OnOff_MovingObject;
    ofxColorSlider ColorText;
    ofxColorSlider ColorRect;
    ofxColorSlider ColorRandomText;
    ofxToggle RandomTextOnOff;


    ofParameter<bool> OnOff_DroneAttack;
    ofxButton LoadImage;
    ofxToggle DrawEarth;
    ofxToggle DrawAttack;
    ofxButton DrawEarthTexture;
    ofxFloatSlider DroneSpeedFactor;
    ofxColorSlider EarthColor;
    ofxColorSlider AttackColor;
    
    

    ofParameter<bool> OnOff_WebLiveCam;
    ofxButton LoadMovies;
    ofxButton RandomPosition;
    ofxIntSlider IndexMovie;
    

    ofParameter<bool> OnOff_NightVision;

    ofParameter<bool> OnOFf_SpeechVideo;
    ofxButton LoadSpeechVideos;
    ofxIntSlider IndexSpeechMovie;
    

    ofxButton plutoGlitch;
    
    
    
    
    ofxPanel main;
    ofxPanel glungeWinter;
    ofxPanel liveCamGlitch;
    ofxPanel labyrinth;
    ofxPanel calligraphy;
    ofxPanel pluto;
    ofxPanel indiaTower;
    ofxPanel trierFlyingCam;
    ofxPanel cubicMapFlyingCam;
    ofxPanel moonCreator;
    ofxPanel lineVideo;
    ofxPanel movingObject;
    ofxPanel droneAttack;
    ofxPanel webLiveCam;
    ofxPanel nightVision;
    ofxPanel speechVideo;
    ofxPanel glitchMain;
    
    ofParameter<bool> audioInputOnOff;
    
};




