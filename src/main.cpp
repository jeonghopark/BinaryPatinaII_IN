#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"


//========================================================================
int main( ){
    
    
    ofGLFWWindowSettings settings;
    
    settings.width = 1800;
    settings.height = 1200;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    
    settings.width = 1920;  // 1920 : 1280
    settings.height = 1080;  // 1080 :  720
    settings.resizable = true;
    settings.setPosition( ofVec2f(0, 0 ));
    settings.windowMode = OF_WINDOW;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    shared_ptr<GuiApp> guiApp(new GuiApp);
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->gui = guiApp;
    
    ofRunApp(mainWindow, mainApp);
    ofRunApp(guiWindow, guiApp);
    ofRunMainLoop();
    
}
