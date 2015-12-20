//
//  KinectView.cpp
//  NightVisionKinect
//
//  Created by jeonghopark on 14/10/15.
//
//

#include "KinectView.hpp"


//--------------------------------------------------------------
KinectView::KinectView(){
    
}


//--------------------------------------------------------------
KinectView::~KinectView(){
    
}


//--------------------------------------------------------------
void KinectView::setup(){
 
    // enable depth->video image calibration
    kinect.setRegistration(true);
    
    //	kinect.init();
    kinect.init(true); // shows infrared instead of RGB video image
    //kinect.init(false, false); // disable video image (faster fps)
    
    kinect.open();		// opens first available kinect
    //kinect.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
    //kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
#ifdef USE_TWO_KINECTS
    kinect2.init();
    kinect2.open();
#endif
    
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
    
    nearThreshold = 230;
    farThreshold = 70;
    bThreshWithOpenCV = true;
    
    ofSetFrameRate(60);
    
    // zero the tilt on startup
    angle = 45;
    kinect.setCameraTiltAngle(angle);
    
    // start from the front
    bDrawPointCloud = false;
    
    
    contrastKinect.allocate(400, 300);

}



//--------------------------------------------------------------
void KinectView::update(){
    
    
    kinect.update();
    
    // there is a new frame and we are connected
    if(kinect.isFrameNew()) {
        
        contrastKinect.setFromPixels(kinect.getPixels());

//        contrastKinect.brightnessContrast(ofMap(mouseX, 0, ofGetWidth(), 0, 1), ofMap(mouseY, 0, ofGetHeight(), 0, 1));
        
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(kinect.getDepthPixels());
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        } else {
            
            // or we do it ourselves - show people how they can work with the pixels
            ofPixels & pix = grayImage.getPixels();
            int numPixels = pix.size();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
        }
        
        // update the cv images
        grayImage.flagImageChanged();
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
    }
    
#ifdef USE_TWO_KINECTS
    kinect2.update();
#endif

    
    
}


//--------------------------------------------------------------
void KinectView::draw(){
    
    
    if(bDrawPointCloud) {

        easyCam.begin();
        drawPointCloud();
        easyCam.end();
        
    } else {
        // draw from the live kinect
        ofSetColor(0, 255, 0);
        //		kinect.drawDepth(10, 10, 400, 300);
        //		kinect.draw(0, 0, 400, 300);
        
        //		grayImage.draw(10, 320, 400, 300);
        //		contourFinder.draw(10, 320, 400, 300);
        
#ifdef USE_TWO_KINECTS
        kinect2.draw(420, 320, 400, 300);
#endif
        
        
    }
    
    
    
    
    //	// draw instructions
    //	ofSetColor(255, 255, 255);
    //	stringstream reportStream;
    //
    //    if(kinect.hasAccelControl()) {
    //        reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
    //        << ofToString(kinect.getMksAccel().y, 2) << " / "
    //        << ofToString(kinect.getMksAccel().z, 2) << endl;
    //    } else {
    //        reportStream << "Note: this is a newer Xbox Kinect or Kinect For Windows device," << endl
    //		<< "motor / led / accel controls are not currently supported" << endl << endl;
    //    }
    //
    //	reportStream << "press p to switch between images and point cloud, rotate the point cloud with the mouse" << endl
    //	<< "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
    //	<< "set near threshold " << nearThreshold << " (press: + -)" << endl
    //	<< "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs
    //	<< ", fps: " << ofGetFrameRate() << endl
    //	<< "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl;
    //
    //    if(kinect.hasCamTiltControl()) {
    //    	reportStream << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl
    //        << "press 1-5 & 0 to change the led mode" << endl;
    //    }
    //    
    //	ofDrawBitmapString(reportStream.str(), 20, 652);
 
    

}



//--------------------------------------------------------------
void KinectView::drawNightVision(){
    
    ofPushStyle();
    ofSetColor(0, 255, 0);
    
    float _x = baseArch->framesCenter[0][0].x;
    float _y = baseArch->framesCenter[0][0].y;
//    float _h = baseArch->framesCenter[0][5].y - baseArch->framesCenter[0][0].y;
    float _w = baseArch->framesCenter[22][0].x - baseArch->framesCenter[0][1].x;
//    float _w = _h * 400.0 / 300.0;
    float _h = _w * 300.0 / 400.0;

//        contrastKinect.invert();
    contrastKinect.draw( _x, _y, _w, _h );
    
    ofPopStyle();
    
}


//--------------------------------------------------------------
void KinectView::exit(){
    
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
    
#ifdef USE_TWO_KINECTS
    kinect2.close();
#endif

    
}


//--------------------------------------------------------------
void KinectView::drawPointCloud(){

    int w = 640;
    int h = 480;
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    int step = 2;
    for(int y = 0; y < h; y += step) {
        for(int x = 0; x < w; x += step) {
            if(kinect.getDistanceAt(x, y) > 0) {
                mesh.addColor(kinect.getColorAt(x,y));
                mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
            }
        }
    }
    glPointSize(3);
    ofPushMatrix();
    // the projected points are 'upside down' and 'backwards'
    ofScale(1, -1, -1);
    ofTranslate(0, 0, -1000); // center the points a bit
    ofEnableDepthTest();
    mesh.drawVertices();
    ofDisableDepthTest();
    ofPopMatrix();

    
}

