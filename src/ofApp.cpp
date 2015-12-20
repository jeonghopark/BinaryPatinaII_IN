#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate( 60 );
    ofBackground( 0 );
    
    
    // syphon
    dir.setup();
    client.setup();
    ofAddListener(dir.events.serverAnnounced, this, &ofApp::serverAnnounced);
    ofAddListener(dir.events.serverRetired, this, &ofApp::serverRetired);
    dirIdx = -1;

    staminaVideo.load("Stamina_Video_2.mp4");
    staminaVideoALL = false;
    staminaVideoA = false;
    staminaVideoB = false;
    staminaVideoC = false;
    staminaVideoD = false;
    
    
    mainOffSetXPos = (ofGetWidth() - (baseArch.fassadeCorner[0].x + baseArch.fassadeCorner[1].x)) * 0.5;
    mainOffSetYPos = (ofGetHeight() - (baseArch.fassadeCorner[0].y + baseArch.fassadeCorner[3].y)) * 0.5;
    
    baseArch.mainOffSetXPos = mainOffSetXPos;
    baseArch.mainOffSetYPos = mainOffSetYPos;
    
    fassadeWidth=  baseArch.fassadeCorner[1].x - baseArch.fassadeCorner[0].x;
    fassadeHeight =  baseArch.fassadeCorner[3].y - baseArch.fassadeCorner[0].y;
    
    font.setup("Vera.ttf", 1.0, 1024, true, 8, 1.0);
    font.addFont("VeraMono-Bold.ttf");
    fontVideo.setup("Tungsten-Medium.ttf", 1.0, 1024, true, 8, 1.0);
//    fontVideo.addFont("Tungsten-Medium.otf");

    nBandsToGet = 32 * 2;
    
    fft.fft.stream.setDeviceID(5);
    fft.setVolumeRange(0);
    fft.setup();
    fft.fft.setup(16384 * 0.25);
    fft.setNumFFTBins(nBandsToGet);
    fft.setFFTpercentage(0.9);
    
    midiInput.setup();
    
    mainImgDirectGlitch.allocate(640, 480, OF_IMAGE_COLOR);
    bMainDirectglitch = false;
    qualityMain = OF_IMAGE_QUALITY_WORST;


    webCamHD.listDevices();
    webCamHD.setDeviceID(WEBCAM_ID);
    webCamHD.setup(WEBCAM_WIDTH, WEBCAM_HEIGHT);
    
    leapMotion.open();

    baseArch.inputFont( font );


    glungeWinter.inputBaseArch( baseArch );
    glungeWinter.setup();

    
    liveCamGlitch.inputBaseArch( baseArch );
    liveCamGlitch.inputMidiInput(midiInput);
    liveCamGlitch.inputWebCam( webCamHD );
    liveCamGlitch.setup();
    

    labyrinth.inputBaseArch( baseArch );
    labyrinth.setup();
    labyrinthOldNumParticle = 0;
    labyrinthOldType = 0;
    labyrinthChangeNum = false;
    
    
    calligraphy.inputBaseArch( baseArch );
    calligraphy.inputFFTP( fft );
    calligraphy.setup();

    
    pluto.inputBaseArch( baseArch );
    pluto.setup();
    

    indiaTower.inputMIDI(midiInput);
    indiaTower.inputBaseArch( baseArch );
    indiaTower.inputFFTP( fft );
    indiaTower.setup();
    
    
    
    trierFlyingCam.inputBaseArch( baseArch );
    trierFlyingCam.inputLeapMotion( leapMotion );
    trierFlyingCam.setup();
    
    
    cubicMapFlyingCam.inputBaseArch( baseArch );
    cubicMapFlyingCam.inputLeapMotion( leapMotion );
    cubicMapFlyingCam.setup();
    

    moonCreator.inputBaseArch( baseArch );
    moonCreator.inputFFTP( fft );
    moonCreator.inputBaseArch( baseArch );
    moonCreator.setup();
    
    
    lineVideo.inputBaseArch( baseArch);
    lineVideo.inputMIDI( midiInput );
    lineVideo.setup();
    lineVideo.inputWebCam( webCamHD );

    
    movingObjects.inputBaseArch( baseArch );
    movingObjects.inputFont( font );
    movingObjects.setup();
    
    
    droneAttack.inputBaseArch( baseArch );
    droneAttack.inputFFTP( fft );
    droneAttack.inputFont( font );
    droneAttack.setup();

    
    webLiveCam.inputBaseArch( baseArch );
    webLiveCam.setup();
    
    
    nightVision.inputBaseArch( baseArch );
    nightVision.setup();
    
//    speechVideoSynth.inputMIDI(midiInput);
    speechVideoSynth.inputBaseArch( baseArch );
    speechVideoSynth.setup();
    
    
    fullScreen = false;

    
    
//    backFBO.allocate(1920, 1080);
//    backGlitch.setup(& backFBO);
//    
//    frontFBO.allocate(1920, 1080);
//    frontGlitch.setup(& frontFBO);

    mainFBO.allocate(1920, 1080);
    mainGlitch.setup(& mainFBO);

    
    ofSetEscapeQuitsApp(false);


    
    C_shell_snowden_start_FIN.load("C_shell_snowden_start_FIN.mp4");
    CSharp_02_shell_snowden_worldwide_FIN.load("C#_02_shell_snowden worldwide_FIN.mp4");
    D_02_shell_snowden_everything_FIN.load("D_02 shell_snowden everything FIN.mp4");
    E_03_thingy_harvested_complete_FIN.load("E_03_thingy_harvested_complete_FIN.mp4");
    F_03_thingy_harvested_FIN.load("F_03_thingy_harvested_FIN.mp4");
    FSharp_09_stringer_ericschmidt_FIN.load("F#_09_stringer_ericschmidt_FIN.mp4");
    G_13_oddity_We_kill_people_FIN.load("G_13_oddity_We kill people FIN.mp4");
    GSharp_Bowie_Mind_Control.load("G#_Bowie_Mind Control.mp4");
    A_Bowie_payyourbills.load("A_Bowie_payyourbills.mp4");
    ASharp_Bowie_thenetworks.load("A#_Bowie_thenetworks.mp4");
    B_Bowie_conquer_the_world.load("B_Bowie_conquer the world.mp4");

    movieAllOnOff = true;
    
    for (int i=0; i<11; i++) {
        moviesOn[i] = false;
    }
    

    randomText = false;
    
    Cubic_backGroundColor = ofColor(0,0);
    
    
}


// syphon
//--------------------------------------------------------------
void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

//--------------------------------------------------------------
void ofApp::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

//--------------------------------------------------------------
void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}



//--------------------------------------------------------------
void ofApp::update(){
    
    if (staminaVideoALL || staminaVideoA || staminaVideoB || staminaVideoC || staminaVideoD) {
        staminaVideo.update();
    }
    
    
    gui->OnOff_GlungeWinter = sceneSelect[0];
    gui->OnOff_LiveCamGlitch = sceneSelect[1];
    gui->OnOff_Labyrinth = sceneSelect[2];
    gui->OnOff_Calligraphy = sceneSelect[3];
    gui->OnOff_Pluto = sceneSelect[4];
    gui->OnOff_IndiaTower= sceneSelect[5];
    gui->OnOff_TrierFlyingCam= sceneSelect[6];
    gui->OnOff_CubicMapFlyingCam= sceneSelect[7];
    gui->OnOff_MoonCreator= sceneSelect[8];
    gui->OnOff_LineVideo= sceneSelect[9];
    gui->OnOff_MovingObject= sceneSelect[10];
    gui->OnOff_DroneAttack= sceneSelect[11];
    gui->OnOff_WebLiveCam= sceneSelect[12];
    
    gui->OnOff_Windows = BaseArchSelect[0];
    gui->OnOff_Frames = BaseArchSelect[1];
    gui->OnOff_Lines = BaseArchSelect[2];
    gui->OnOff_Points = BaseArchSelect[3];
    gui->OnOff_Cross = BaseArchSelect[4];
    gui->OnOff_Numbers = BaseArchSelect[5];
    
    if (gui->FullScreen) {
        ofSetFullscreen(true);
        ofSetWindowPosition(0, 0);
        ofSetWindowShape(1920, 1080);
    }
    
    
    
    webCamHD.update();
//    midiInput.update();
//    midiInput.drumPadOutput();
    
    if (gui->webcamOn) {
        webCamHD.close();
        webCamHD.setDeviceID(WEBCAM_ID);
        webCamHD.setup(WEBCAM_WIDTH, WEBCAM_HEIGHT);
    }
    
    if (gui->OnOff_LiveCamGlitch) {
        liveCamGlitch.update();
        
        if (gui->ResetShader) {
            webCamHD.close();
            webCamHD.setDeviceID(WEBCAM_ID);
            webCamHD.setup(WEBCAM_WIDTH, WEBCAM_HEIGHT);
            liveCamGlitch.inputBaseArch( baseArch );
            liveCamGlitch.inputMidiInput(midiInput);
            liveCamGlitch.inputWebCam( webCamHD );
            liveCamGlitch.glitchEffect.loadShader();
            liveCamGlitch.setup();
            liveCamGlitch.update();
            liveCamGlitch.draw();
        }

    }
    
    
    if (gui->OnOff_Labyrinth) {
        labyrinth.update();
        labyrinth.numParticles = gui->NumParticles;
        labyrinth.LineType = gui->LineType;
        labyrinth.speedFactor = gui->Speed;
        labyrinth.particlesizeFactor = gui->ParticleSize;
        labyrinth.particleC = gui->ParticleColor;
        labyrinth.pathC = gui->PathColor;
        labyrinth.connectionLineC = gui->ConnectionColor;
        
        if (((labyrinthOldNumParticle != gui->NumParticles) && !labyrinthChangeNum )||
            ((labyrinthOldType != gui->LineType) && !labyrinthChangeNum )){
            labyrinth.initParticles();
            labyrinthOldNumParticle = gui->NumParticles;
            labyrinthOldType = gui->LineType;
            labyrinthChangeNum = true;
        } else {
            labyrinthChangeNum = false;
        }
        
        if (gui->UpdateRandom) labyrinth.initParticles();
    }
    
    
    if (gui->OnOff_Calligraphy) {
        fft.update();
        calligraphy.update();
        calligraphy.fftValue = gui->fftSize;
    }

    if (gui->Return) {
        pluto.returnValue();
    }
    
    if (gui->OnOff_Pluto) {
        pluto.update();
        pluto.speedRatio = gui->SpeedRatioMoon;
    }


    if (gui->OnOff_IndiaTower) {
        fft.update();
        indiaTower.update();
        indiaTower.bezielcolor = gui->BezielColor;
    }
    
    
    if (gui->OnOff_TrierFlyingCam) {
        trierFlyingCam.update();
        trierFlyingCam.buildingColor = gui->TrierBuildColor;
        trierFlyingCam.roadColor = gui->TrierRoadColor;
        trierFlyingCam.movingColor = gui->TrierMovingColor;
    }

    if (gui->OnOff_CubicMapFlyingCam) {
        cubicMapFlyingCam.update();
        cubicMapFlyingCam.buildingColor = gui->BuildColor;
        cubicMapFlyingCam.buildingSideColor = gui->BuildSideColor;
        cubicMapFlyingCam.roadColor = gui->RoadColor;
        cubicMapFlyingCam.movingColor = gui->MovingColor;
    }
    
    if (gui->OnOff_MoonCreator) {
        fft.update();
        moonCreator.update();
    }

    if (gui->OnOff_LineVideo) {
        lineVideo.update();
        lineVideo.controlPointRandom = gui->ControlRandom;
    }

    if (gui->OnOff_MovingObject) {
        movingObjects.update();
        movingObjects.colorRect = gui->ColorRect;
        movingObjects.colorText = gui->ColorText;
    }

    
    if (gui->OnOff_DroneAttack) {
        droneAttack.update();
        droneAttack.speedFactor = gui->DroneSpeedFactor;
        droneAttack.colorAttack = gui->AttackColor;
        droneAttack.colorEarth = gui->EarthColor;
        if (gui->LoadImage) {
            droneAttack.loadImage();
        }
    }
    

    if (gui->OnOff_WebLiveCam) {
        webLiveCam.update();
        webLiveCam.indexMovie = gui->IndexMovie;
        if (gui->LoadMovies) {
            webLiveCam.movieLoad();
        }
        if (gui->RandomPosition) {
            webLiveCam.randomWindowsPosition();
        }
    }
    
    

    if (gui->CanonView) {
        if (gui->OnOff_NightVision) {
            nightVision.update(client);
        }
    }
    
    
    // syphon
    if (gui->SyphonSearch) {
        if (dir.size() > 0) {
            dirIdx++;
            if(dirIdx > dir.size() - 1)
                dirIdx = 0;
            
            client.set(dir.getDescription(dirIdx));
            string serverName = client.getServerName();
            string appName = client.getApplicationName();
            
            if(serverName == ""){
                serverName = "null";
            }
            if(appName == ""){
                appName = "null";
            }
        }
    }
    
    
    
    if (gui->OnOFf_SpeechVideo) {
//        speechVideoSynth.update();
//        speechVideoSynth.indexMovie = gui->IndexSpeechMovie;
    }

    
    speechMovieUpdate(C_shell_snowden_start_FIN, 0);
    speechMovieUpdate(CSharp_02_shell_snowden_worldwide_FIN, 1);
    speechMovieUpdate(D_02_shell_snowden_everything_FIN, 2);
    speechMovieUpdate(E_03_thingy_harvested_complete_FIN, 3);
    speechMovieUpdate(F_03_thingy_harvested_FIN, 4);
    speechMovieUpdate(FSharp_09_stringer_ericschmidt_FIN, 5);
    speechMovieUpdate(G_13_oddity_We_kill_people_FIN, 6);
    speechMovieUpdate(GSharp_Bowie_Mind_Control, 7);
    speechMovieUpdate(A_Bowie_payyourbills, 8);
    speechMovieUpdate(ASharp_Bowie_thenetworks, 9);
    speechMovieUpdate(B_Bowie_conquer_the_world, 10);


    
    // draw FBO
    mainFBO.begin();

    ofClear(0, 0, 0, 0);
    ofPushMatrix();

    ofEnableAlphaBlending();
    
    ofTranslate( mainOffSetXPos, mainOffSetYPos );
    
    if (gui->OnOff_Pluto) {
        pluto.draw();
    }

    ofDisableAlphaBlending();

    ofEnableAlphaBlending();

    if (gui->OnOff_LiveCamGlitch) {
        liveCamGlitch.draw();
    }
    

    ofDisableAlphaBlending();
    
    ofEnableAlphaBlending();

    if (staminaVideoALL) {
        staminaVideo.draw(0, -170, 1920, 1080);
    }
    
    ofDisableAlphaBlending();
    
    
    // Speech Video
    
    ofEnableAlphaBlending();
    
    ofPushMatrix();
    ofTranslate( (baseArch.windowsCorner[0][1].x - baseArch.windowsCorner[0][0].x) * 0.25 + 19, 0);

    if (movieAllOnOff) {
     
        
        float _windowW = baseArch.windowsCorner[0][1].x - baseArch.windowsCorner[0][0].x;
        float _windowH = baseArch.windowsCorner[0][0].y - baseArch.windowsCorner[0][3].y;
        float _fassadeCenterX = (baseArch.fassadeCorner[1].x - baseArch.fassadeCorner[0].x) * 0.5;
        
        if (gui->OnOFf_SpeechVideo) {
            
            if (midiInput.iacNoteOnCh1[0]) {
                float _vW = C_shell_snowden_start_FIN.getWidth();
                float _vH = C_shell_snowden_start_FIN.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                C_shell_snowden_start_FIN.draw(0 - _windowW * 3, 0, _w, _h);

                
                ofPushStyle();
                ofSetColor(0);
                ofDrawRectangle(_fassadeCenterX, 0, _w * 0.5, _h);
                ofPopStyle();
                
            
                ofPushMatrix();
                ofTranslate(-19, 0);
                string _title1[6] = {"E", "D", "W", "A", "R", "D"};
                for (int i=0; i<6; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][0].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][0].y - _windowH * 0.5;
                    fontVideo.draw(_title1[i], 100, _x, _y - 30);
                }
                string _title2[7] = {"S", "N", "O", "W", "D", "E", "N"};
                for (int i=0; i<7; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][1].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][1].y - _windowH * 0.5;
                    fontVideo.draw(_title2[i], 100, _x, _y - 30);
                }
                ofPopMatrix();

//                string _title3[11] = {"E", "x", "-", " ", "N", "S", "A"};
//                for (int i=0; i<11; i++) {
//                    float _x = baseArch.windowsOriginCenter[11 + i][2].x - _windowW * 0.5;
//                    float _y = baseArch.windowsOriginCenter[11 + i][2].y - _windowH * 0.5;
//                    font.draw(_title3[i], 100, _x, _y - 30);
//                }
//                string _title4[11] = {"W", "h", "i", "s", "t", "l", "e", "b", "l", "o", "w"};
//                for (int i=0; i<11; i++) {
//                    float _x = baseArch.windowsOriginCenter[21 - i][3].x - _windowW * 0.5;
//                    float _y = baseArch.windowsOriginCenter[21 - i][3].y - _windowH * 0.5;
//                    font.draw(_title3[i], 100, _x, _y - 30);
//                }
                
                
                
            }
            
            if (midiInput.iacNoteOnCh1[1]) {
                float _vW = CSharp_02_shell_snowden_worldwide_FIN.getWidth();
                float _vH = CSharp_02_shell_snowden_worldwide_FIN.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                CSharp_02_shell_snowden_worldwide_FIN.draw(0 - _windowW * 3, 0, _w, _h);
                
                ofPushStyle();
                ofSetColor(0);
                ofDrawRectangle(_fassadeCenterX, 0, _w * 0.5, _h);
                ofPopStyle();

            }
            
            if (midiInput.iacNoteOnCh1[2]) {
                float _vW = D_02_shell_snowden_everything_FIN.getWidth();
                float _vH = D_02_shell_snowden_everything_FIN.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                D_02_shell_snowden_everything_FIN.draw(0 - _windowW * 3, 0, _w, _h);
                
                ofPushStyle();
                ofSetColor(0);
                ofDrawRectangle(_fassadeCenterX, 0, _w * 0.5, _h);
                ofPopStyle();

            }
            
            
            
            
            if (midiInput.iacNoteOnCh1[3]) {
                float _vW = E_03_thingy_harvested_complete_FIN.getWidth();
                float _vH = E_03_thingy_harvested_complete_FIN.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                E_03_thingy_harvested_complete_FIN.draw(0 - _windowW * 2, 0, _w, _h);
                
                
                ofPushStyle();
                ofSetColor(0);
                ofDrawRectangle(_fassadeCenterX, 0, _w * 0.5, _h);
                ofPopStyle();
                
                ofPushMatrix();
                ofTranslate(-19, 0);
                string _title1[8] = {"S", "H", "O", "S", "H", "A", "N", "A"};
                for (int i=0; i<8; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][0].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][0].y - _windowH * 0.5;
                    fontVideo.draw(_title1[i], 100, _x, _y - 30);
                }
                string _title2[7] = {"Z", "U", "B", "O", "F", "F", ","};
                for (int i=0; i<7; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][1].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][1].y - _windowH * 0.5;
                    fontVideo.draw(_title2[i], 100, _x, _y - 30);
                }
                string _title3[8] = {"H", "A", "R", "V", "A", "R", "D"};
                for (int i=0; i<8; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][2].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][2].y - _windowH * 0.5;
                    fontVideo.draw(_title3[i], 100, _x, _y - 30);
                }
                ofPopMatrix();
                
//                ofPushMatrix();
//                ofTranslate(baseArch.windowsOriginCenter[11][0].x, baseArch.windowsOriginCenter[11][0].y - 30);
//                string _title1 = string("Shoshana");
//                font.draw(_title1, 100, 0, 20);
//                string _title2 = string("Zuboff");
//                font.draw(_title2, 100, 0, 120);
//                string _title3 = string("Harvard");
//                font.draw(_title3, 70, 0, 220);
//                string _title4 = string("Business School");
//                font.draw(_title4, 70, 0, 290);
//                ofPopMatrix();

            }
            

            if (midiInput.iacNoteOnCh1[4]) {

                float _vW = F_03_thingy_harvested_FIN.getWidth();
                float _vH = F_03_thingy_harvested_FIN.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                F_03_thingy_harvested_FIN.draw(0 - _windowW * 2, 0, _w, _h);

                ofPushStyle();
                ofSetColor(0);
                ofDrawRectangle(_fassadeCenterX, 0, _w * 0.5, _h);
                ofPopStyle();
            }
            
            
            if (midiInput.iacNoteOnCh1[5]) {
                float _vW = FSharp_09_stringer_ericschmidt_FIN.getWidth();
                float _vH = FSharp_09_stringer_ericschmidt_FIN.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                FSharp_09_stringer_ericschmidt_FIN.draw(0 - _windowW, 0, _w, _h);
                
                ofPushStyle();
                ofSetColor(0);
                ofDrawRectangle(_fassadeCenterX, 0, _w * 0.5, _h);
                ofPopStyle();
                
                ofPushMatrix();
                ofTranslate(-19, 0);
                string _title1[4] = {"E", "R", "I", "C"};
                for (int i=0; i<4; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][0].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][0].y - _windowH * 0.5;
                    fontVideo.draw(_title1[i], 100, _x, _y - 30);
                }
                string _title2[8] = {"S", "C", "H", "M", "I", "D", "T", ","};
                for (int i=0; i<8; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][1].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][1].y - _windowH * 0.5;
                    fontVideo.draw(_title2[i], 100, _x, _y - 30);
                }
                string _title3[7] = {"G", "O", "O", "G", "L", "E"};
                for (int i=0; i<7; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][2].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][2].y - _windowH * 0.5;
                    fontVideo.draw(_title3[i], 100, _x, _y - 30);
                }
                ofPopMatrix();


            }
            
            
            if (midiInput.iacNoteOnCh1[6]) {
                float _vW = G_13_oddity_We_kill_people_FIN.getWidth();
                float _vH = G_13_oddity_We_kill_people_FIN.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                G_13_oddity_We_kill_people_FIN.draw(0 - _windowW * 3, 0, _w, _h);
                

                ofPushStyle();
                ofSetColor(0);
                ofDrawRectangle(_fassadeCenterX, 0, _w * 0.5, _h);
                ofPopStyle();
                
                ofPushMatrix();
                ofTranslate(-19, 0);
                string _title1[7] = {"M", "I", "C", "H", "A", "E", "L"};
                for (int i=0; i<7; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][0].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][0].y - _windowH * 0.5;
                    fontVideo.draw(_title1[i], 100, _x, _y - 30);
                }
                string _title2[7] = {"H", "A", "Y", "D", "E", "N", ","};
                for (int i=0; i<7; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][1].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][1].y - _windowH * 0.5;
                    fontVideo.draw(_title2[i], 100, _x, _y - 30);
                }
                string _title3[6] = {"E", "X", "-", "N", "S", "A"};
                for (int i=0; i<6; i++) {
                    float _x = baseArch.windowsOriginCenter[11 + i][2].x - _windowW * 0.5;
                    float _y = baseArch.windowsOriginCenter[11 + i][2].y - _windowH * 0.5;
                    fontVideo.draw(_title3[i], 100, _x, _y - 30);
                }
                ofPopMatrix();

            }
            
            
            ofPushMatrix();
            ofTranslate(_windowW * 3, 0);

            if (midiInput.iacNoteOnCh1[7]) {
                float _vW = GSharp_Bowie_Mind_Control.getWidth();
                float _vH = GSharp_Bowie_Mind_Control.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                GSharp_Bowie_Mind_Control.draw(0, 0, _w, _h);
            }
            
            if (midiInput.iacNoteOnCh1[8]) {
                float _vW = A_Bowie_payyourbills.getWidth();
                float _vH = A_Bowie_payyourbills.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                A_Bowie_payyourbills.draw(0, 0, _w, _h);
            }
            
            if (midiInput.iacNoteOnCh1[9]) {
                float _vW = ASharp_Bowie_thenetworks.getWidth();
                float _vH = ASharp_Bowie_thenetworks.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                ASharp_Bowie_thenetworks.draw(0, 0, _w, _h);
            }
            
            if (midiInput.iacNoteOnCh1[10]) {
                float _vW = B_Bowie_conquer_the_world.getWidth();
                float _vH = B_Bowie_conquer_the_world.getHeight();
                
                float _h =  fassadeHeight;
                float _w = _vW * _h / _vH;
                B_Bowie_conquer_the_world.draw(0, 0, _w, _h);
            }
            
            ofPopMatrix();
            
            
        }

    }

    ofPopMatrix();
    
    ofDisableAlphaBlending();

    
    
    
    
    
    if (gui->CanonView) {
        if (gui->OnOff_NightVision) {
            nightVision.draw();
        }
    }

    
    if (gui->OnOff_WebLiveCam) {
        webLiveCam.draw();
    }
    
    

    
    
    if (gui->OnOff_LineVideo) {
        lineVideo.draw();
        lineVideo.drawStartPoints();
        lineVideo.drawLines();
        lineVideo.drawColorNumber();
    }
    
    if (gui->OnOff_TrierFlyingCam) {
        trierFlyingCam.draw();
    }
    
    if (gui->OnOff_CubicMapFlyingCam) {
        ofEnableAlphaBlending();
        ofSetColor( Cubic_backGroundColor );
        ofDrawRectangle(0, 0, 1920, 1080);
        ofDisableAlphaBlending();
        cubicMapFlyingCam.draw();
    }
    
    
    if (gui->OnOff_MoonCreator) {
        moonCreator.creatorDraw();
        moonCreator.drawLines();
        moonCreator.moonMiddlelinesColor = gui->moonStraightLine;
    }
    
    
    if (gui->OnOff_DroneAttack) {
        if (gui->DrawEarthTexture) {
            droneAttack.drawEarthTexture();
        }
        if (gui->DrawEarth) {
            droneAttack.drawEarth();
        }
        if (gui->DrawAttack) {
            droneAttack.drawAttackPosition();
        }
    }
    
    
    if (gui->OnOff_Calligraphy) {
        calligraphy.draw();
    }
    
    
    if (gui->OnOff_GlungeWinter) {
        glungeWinter.verticalColor = gui->VerticalColor;
        glungeWinter.horizonColor = gui->HorizonColor;
        glungeWinter.drawBackTexture();
        glungeWinter.drawBack();
    }
    
    
    if (gui->OnOff_Labyrinth) {
        labyrinth.draw();
    }
    
    

    
    drawBaseArch();

    
    if ( (gui->OnOff_Windows) || midiInput.drumPad[0] ) {
        ofColor _c = gui->color_Windows;
        baseArch.drawWindows( _c );
    }
    
    if (gui->OnOff_GlungeWinter) {
        if (gui->verticalOnOff) {
            glungeWinter.drawFrontVertical();
        }
        if (gui->horizonOnOff) {
            glungeWinter.drawFrontHorizon();
        }
    }
    
    
    if (gui->OnOff_IndiaTower) {
        indiaTower.drawingRectColumn();
        indiaTower.drawingNumber();
        indiaTower.drawingBeziel();
    }
    
    if (gui->OnOff_MovingObject) {
        movingObjects.draw();
        if (gui->RandomTextOnOff) {
            movingObjects.colorRandomText = gui->ColorRandomText;
        }
        if (randomText) {
            movingObjects.drawRandomText();
        }
    }

    ofPopMatrix();
    mainFBO.end();
    
    

    
    
}



//--------------------------------------------------------------
void ofApp::speechMovieUpdate(ofVideoPlayer _p, int _i){
    
    

    // Speech
    if (midiInput.iacNoteOnCh1[_i]) {
        _p.update();
    }
    if ( midiInput.iacNoteOnCh1[_i] && !moviesOn[_i] ) {
        _p.play();
        moviesOn[_i] = true;
    } else if (!midiInput.iacNoteOnCh1[_i] && moviesOn[_i]) {
        _p.stop();
        _p.firstFrame();
        moviesOn[_i] = false;
    }


}





//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofPushMatrix();
    
    ofTranslate( gui->xPos, gui->yPos );
    ofScale( gui->xScale, gui->yScale );
    
    ofTranslate( mainOffSetXPos, mainOffSetYPos);
    
//    mainFBO.draw(0, 0);
    
    ofEnableAlphaBlending();

    ofPushMatrix();
    ofTranslate( -mainOffSetXPos, -mainOffSetYPos );
    mainGlitch.generateFx();
    mainFBO.draw(0, 0);
    ofPopMatrix();
    
    ofDisableAlphaBlending();


    ofEnableAlphaBlending();
    baseArch.drawEdgeCover( ofColor(0, 255) );
    ofDisableAlphaBlending();
    
    
    ofEnableAlphaBlending();
    
    if (bMainDirectglitch) {
        float _w = baseArch.fassadeCorner[1].x - baseArch.fassadeCorner[0].x;
        float _h = baseArch.fassadeCorner[2].y - baseArch.fassadeCorner[0].y;
        float _x = baseArch.fassadeCorner[0].x;
        float _y = baseArch.fassadeCorner[0].y;
        
        ofPixels _p;
        _p.allocate(640, 480, 3);
        mainFBO.readToPixels(_p);
        mainGlitchPixel(_p);
        mainImgDirectGlitch.draw(_x, _y, _w, _h);
    }
    
    ofDisableAlphaBlending();

    
    ofPopMatrix();

}


//--------------------------------------------------------------
void ofApp::drawBaseArch(){
    
    ofEnableAlphaBlending();
    
    ofPushStyle();
        
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    if ( (gui->OnOff_Frames) || midiInput.drumPad[1] )
    {
        ofColor _c = gui->color_Frames;
        baseArch.guideFrames( _c );
    }
    
    if ( (gui->OnOff_Lines) || midiInput.drumPad[2] )
    {
        ofColor _c = gui->color_Lines;
        baseArch.guideLines( _c );
    }
    
    if ( (gui->OnOff_Points) || midiInput.drumPad[3] )
    {
        ofColor _c = gui->color_Points;
        baseArch.guidePoints( _c );
    }
    
    if ( (gui->OnOff_Cross) || midiInput.drumPad[4] )
    {
        ofColor _c = gui->color_Cross;
        baseArch.guideCrossPoints( _c );
    }
    
    if ( (gui->OnOff_Numbers) || midiInput.drumPad[5] )
    {
        ofColor _c = gui->color_Numbers;
        baseArch.drawPointNumber( _c );
    }
    
    if ( (gui->OnOff_RandomW) || ( midiInput.drumPad[6] )) {
        ofColor _c = gui->color_RandomW;
        baseArch.drawRandomWindows( _c );
    }
 
    if ( (gui->OnOff_RandomW) || ( midiInput.drumPad[7] )) {
        ofColor _c = gui->color_RandomW;
        baseArch.drawWindowNumber( _c );
    }
    
    
//    ofDisableBlendMode();
    
    
    ofPopStyle();
    
    ofDisableAlphaBlending();
    

}



//--------------------------------------------------------------
void ofApp::mainGlitchPixel(ofPixels _p) {
    
    string compressedFilename = "compressed.jpg";
    
    _p.setImageType(OF_IMAGE_COLOR);
    unsigned char * _c = _p.getData();
    
    float coin = ofRandom(100);
    if (coin > 95) {
        _c = _p.getData() + (int)ofRandom(100);
    }
    
    mainImgDirectGlitch.setImageType(OF_IMAGE_COLOR);
    mainImgDirectGlitch.setFromPixels(_c, (int)ofRandom(10, 640), (int)ofRandom(10, 480), OF_IMAGE_COLOR);
    mainImgDirectGlitch.save(compressedFilename, qualityMain);
    
    ofBuffer fileGlitchBuffer = ofBufferFromFile(compressedFilename);
    int fileSize = fileGlitchBuffer.size();
    char * buffer = fileGlitchBuffer.getData();
    
    int whichByte = (int) ofRandom(fileSize);
    int whichBit = ofRandom(16);
    
    char bitMask;
    if ( whichBit > 4 ) {
        bitMask = 1 << whichBit;
    } else {
        bitMask = 7 << whichBit;
    }
    
    buffer[whichByte] |= bitMask;
    
    ofBufferToFile(compressedFilename, fileGlitchBuffer);
    mainImgDirectGlitch.load(compressedFilename);
    
    //    float coin = ofRandom(100);
    //    if (coin > 95) {
    //        reset();
    //    }
    
}






//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 49) mainGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
    if (key == 50) mainGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
    if (key == 51) mainGlitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
    if (key == 52) mainGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
    if (key == 53) mainGlitch.setFx(OFXPOSTGLITCH_TWIST			, true);
//    if (key == '6') backGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
    if (key == 54) mainGlitch.setFx(OFXPOSTGLITCH_NOISE			, true);
    if (key == 55) mainGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
    if (key == 56) mainGlitch.setFx(OFXPOSTGLITCH_SWELL			, true);
    if (key == 57) mainGlitch.setFx(OFXPOSTGLITCH_INVERT			, true);
    
    if (key == 48) mainGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
    if (key == 223) mainGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
    if (key == 112) mainGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
    if (key == 111) mainGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
    if (key == 105) mainGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
    if (key == 117) mainGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
    if (key == 252) mainGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);
    
    if (key == 43) bMainDirectglitch = true;
    
    
    liveCamGlitch.keyPressed(key);


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (key == 127 || key == 49) mainGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
    if (key == 127 || key == 50) mainGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
    if (key == 127 || key == 51) mainGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
    if (key == 127 || key == 52) mainGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
    if (key == 127 || key == 53) mainGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
//    if (key == '6') backGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
    if (key == 127 || key == 54) mainGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
    if (key == 127 || key == 55) mainGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
    if (key == 127 || key == 56) mainGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
    if (key == 127 || key == 57) mainGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);
    
    if (key == 127 || key == 48) mainGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
    if (key == 127 || key == 223) mainGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
    if (key == 127 || key == 112) mainGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
    if (key == 127 || key == 111) mainGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
    if (key == 127 || key == 105) mainGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
    if (key == 127 || key == 117) mainGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
    if (key == 127 || key == 252) mainGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);

    if (key == 127 || key == 43) bMainDirectglitch = false;


    
    labyrinth.initParticles();
    liveCamGlitch.keyReleased(key);
    baseArch.keyInteraction(key);
    labyrinth.keyReleased(key);
    webLiveCam.keyReleased(key);

    if (key == 248) {
        baseArch.setupDefault();
    }
    
    if (key == 'x' ) {
        C_shell_snowden_start_FIN.stop();
        CSharp_02_shell_snowden_worldwide_FIN.stop();
        D_02_shell_snowden_everything_FIN.stop();
        E_03_thingy_harvested_complete_FIN.stop();
        F_03_thingy_harvested_FIN.stop();
        FSharp_09_stringer_ericschmidt_FIN.stop();
        G_13_oddity_We_kill_people_FIN.stop();
        GSharp_Bowie_Mind_Control.stop();
        A_Bowie_payyourbills.stop();
        ASharp_Bowie_thenetworks.stop();
        B_Bowie_conquer_the_world.stop();
    }
    
    if ( key == 'v' ) {
        movieAllOnOff = !movieAllOnOff;
    }
    
    
//    if (key == ' ') {
//        indiaTower.setup();
//        pluto.loadImages();
//        webLiveCam.movieLoad();
//    }
    
//    if (key == 'f') {
//        fullScreen = !fullScreen;
//        ofSetFullscreen(fullScreen);
//    }
    

    if (key == 362) {
        trierFlyingCam.returnBase();
        cubicMapFlyingCam.returnBase();
        moonCreator.returnBase();
        droneAttack.returnBase();
    }

    
    cout << key << endl;
    
    if (key == 161) sceneSelect[0] = !sceneSelect[0];
    if (key == 8220) sceneSelect[1] = !sceneSelect[1];
    if (key == 182) sceneSelect[2] = !sceneSelect[2];
    if (key == 162) sceneSelect[3] = !sceneSelect[3];
    if (key == 91) sceneSelect[4] = !sceneSelect[4];
    if (key == 93) sceneSelect[5] = !sceneSelect[5];
    if (key == 124) sceneSelect[6] = !sceneSelect[6];
    if (key == 123) sceneSelect[7] = !sceneSelect[7];
    if (key == 125) sceneSelect[8] = !sceneSelect[8];
    if (key == 8800) sceneSelect[9] = !sceneSelect[9];
    if (key == 171) sceneSelect[10] = !sceneSelect[10];
    if (key == 8721) sceneSelect[11] = !sceneSelect[11];
    if (key == 8364) sceneSelect[12] = !sceneSelect[12];

    
    if (key == 229) BaseArchSelect[0] = !BaseArchSelect[0];
    if (key == 8218) BaseArchSelect[1] = !BaseArchSelect[1];
    if (key == 8706) BaseArchSelect[2] = !BaseArchSelect[2];
    if (key == 402) BaseArchSelect[3] = !BaseArchSelect[3];
    if (key == 169) BaseArchSelect[4] = !BaseArchSelect[4];
    if (key == 170) BaseArchSelect[5] = !BaseArchSelect[5];
    
    
    if (key == 'j') {
        staminaVideoALL = !staminaVideoALL;
        if(staminaVideoALL) {
            staminaVideo.setFrame(0);
            staminaVideo.play();
        } else {
            staminaVideo.stop();
        }
    }

    if (key == 'k') {
        staminaVideoA = !staminaVideoA;
        if(staminaVideoA) {
            staminaVideo.setFrame(2275);
            staminaVideo.play();
        } else {
            staminaVideo.stop();
        }
    }

    if (key == 'l') {
        staminaVideoB = !staminaVideoB;
        if(staminaVideoB) {
            staminaVideo.setFrame(2350);
            staminaVideo.play();
        } else {
            staminaVideo.stop();
        }
    }

    if (key == 246) {
        staminaVideoC = !staminaVideoC;
        if(staminaVideoC) {
            staminaVideo.setFrame(2525);
            staminaVideo.play();
        } else {
            staminaVideo.stop();
        }
    }

    if (key == 228) {
        staminaVideoD = !staminaVideoD;
        if(staminaVideoD) {
            staminaVideo.setFrame(2775);
            staminaVideo.play();
        } else {
            staminaVideo.stop();
        }
    }

    
    if (key == 35) {
        staminaVideoD = !staminaVideoD;
        if(staminaVideoD) {
            staminaVideo.setFrame((int)ofRandom(2000));
            staminaVideo.play();
        } else {
            staminaVideo.stop();
        }
    }

    
    
    if (key == ' ') {
    
        gui->VerticalColor = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->HorizonColor = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->VerticalColor = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->HorizonColor = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        
        gui->color_Windows = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->color_Frames = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->color_Lines = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->color_Numbers = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->color_Cross = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->color_Points = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->color_RandomW = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        
        gui->BuildColor = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->BuildSideColor = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->MovingColor = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        

    }
    

    if (key == 'n') {
        gui->color_Windows = ofColor( 255, 0, 0 );
        gui->color_Frames = ofColor( 255, 0, 0 );
        gui->color_Lines = ofColor( 255, 0, 0 );
        gui->color_Numbers = ofColor( 255, 0, 0 );
        gui->color_Cross = ofColor( 255, 0, 0 );
        gui->color_Points = ofColor( 255, 0, 0 );
        gui->color_RandomW = ofColor( 255, 0, 0 );
        
        gui->BuildColor = ofColor( 255 );
        gui->BuildSideColor = ofColor( 180 );
        gui->MovingColor = ofColor( 255 );

    }
    
    if (key == 'b') {
        Cubic_backGroundColor = ofColor(255, 255);
        gui->BuildColor = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->BuildSideColor = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
        gui->MovingColor = ofColor( ofRandom(255), ofRandom(255), ofRandom(255));
    }
    
    
    if (key == '.') {
        Cubic_backGroundColor = ofColor(0, 0);
    }

    
    if (key == 'm') {
        randomText = !randomText;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
    mainOffSetXPos = (ofGetWidth() - (baseArch.fassadeCorner[0].x + baseArch.fassadeCorner[1].x)) * 0.5;
    mainOffSetYPos = (ofGetHeight() - (baseArch.fassadeCorner[0].y + baseArch.fassadeCorner[3].y)) * 0.5;
    baseArch.mainOffSetXPos = mainOffSetXPos;
    baseArch.mainOffSetYPos = mainOffSetYPos;
    
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}


