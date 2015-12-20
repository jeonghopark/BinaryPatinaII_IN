//
//  MidiInput.hpp
//  exampleInput_MIDIClass
//
//  Created by jeonghopark on 27/09/15.
//
//

#ifndef MidiInput_hpp
#define MidiInput_hpp

#pragma once

#include "ofMain.h"

#include "ofxMidi.h"

class MidiInput : public ofxMidiListener {

public:
    
    ofxMidiIn midiIn;
    ofxMidiIn midiInDrumPad;
    ofxMidiIn midiInKaosPad;
    ofxMidiIn midiInPadKontrol;
    ofxMidiIn midiInIACControl;
    ofxMidiMessage midiMessage;
    
    
    void setup();
    void update();
    void draw();
    void exit();

//    void drumPadOutput();
//    
//    void padKONTROL();
//   
//    void kaosPad();
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    void drumPadMessage(ofxMidiMessage& msg);
    void kaosPadMessage(ofxMidiMessage& msg);
    void iacMessage(ofxMidiMessage& msg);

    void keyboardMessage(ofxMidiMessage& msg);

    
    stringstream text;
    
    
    int barIndex;
    
    int tempoDenominator;
    float ticksPerBar;
    int tempoNumerator;
    int ticksPerqNote;
    int ticks32thNotePerBar;
    int ticksPer32thNote;
    int tempoTicks;
    int ticksfor32thNote;
    int num32thNotes;
    int tempoqNotes;
    int tempoBars;
    bool isPlaying;
    
    
    bool _oldOn;
    
    bool sceneSelect[13];
    int sceneIndex[13];
    bool drumPad[8];
    
    ofVec2f indiaControl;
    
    bool iacNoteOnCh1[11];
    bool oldNote[11];
    
    
};

#endif /* MidiInput_hpp */
