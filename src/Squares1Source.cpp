#include "Squares1Source.h"








// I did not use this sketch in my project







void Squares1Source::setup(){
	// Give our source a decent name
    name = "Squuares 1 FBO Source";
    phase = 0;
    phase2 = 0;
    numOfSquares = 1;
    alpha1=255;
    alphaSquare=255;
    time = 0;
    ofSetFrameRate(40);
    ofBackground(0);
    ofSetCircleResolution(100);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    //Image Loading - try with array
       firstImage.load("Slit1.jpg");
       firstImage.getPixels();
        //firstImage.resize(ofGetWidth(), ofGetHeight());
        secondImage.load("Slit2.jpg");
        secondImage.getPixels();
        //secondImage.resize(ofGetWidth(), ofGetHeight());
	// Allocate our FBO source, decide how big it should be
    allocate(1200, 1000);
    
}

void Squares1Source::reset(){
    //reset is called optionally. if you leave it empty nothing is happening
}

void Squares1Source::setName(string _name){
    name = _name;
}


// Don't do any drawing here
void Squares1Source::update(){
    phase+=0.0045;
    phase2+=0.005;
    if (ofRandom(10)>9.9) {
        alpha1=250*(ofNoise(noiseSeed)/2);
    }
    time = ofGetFrameRate();
    if (time>1800) {
        alphaSquare=150*(ofNoise(noiseSeed)/2);
    }
    if (time>1900) {
        alphaSquare=50*(ofNoise(noiseSeed)/2);
    }
    if (time>2000) {
        alphaSquare=0;
        alpha1=0;
    }
//      if (ofGetElapsedTimeMillis()>20000) {
//          numOfSquares=5;
//      }
//      if (ofGetElapsedTimeMillis()>40000) {
//            numOfSquares=10;
//        }
//      if (ofGetElapsedTimeMillis()>50000) {
//          numOfSquares=5;
//      }
//      if (ofGetElapsedTimeMillis()>60000) {
//          numOfSquares=3;
//      }
//      if (ofGetElapsedTimeMillis()>70000) {
//             numOfSquares=1;
//         }
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void Squares1Source::draw(){
    ofClear(0); //clear the buffer
    //or pass it dynamic values (ie. ask the fbo how big it is)
    for (int i=0; i<numOfSquares; i++) {
        int phaseDif = 10;
        squares(phase+phaseDif*i, phase2+i, i);
    }
}
//--------------------------------------------------------------
void Squares1Source::squares(float p, float p2, int w){
    ofSetColor(0, 0, 255);
             firstImage.drawSubsection(0, 0, fbo->getWidth(), fbo->getHeight(), (ofNoise(noiseSeed2))*1000, ofRandom(firstImage.getHeight()/2));
//        firstImage.draw(0, 0, fbo->getWidth(),fbo->getHeight());
            ofSetColor(0, alpha1);
            ofDrawRectangle(0, 0, fbo->getHeight(), fbo->getWidth());
    noiseSeed+=0.003;
}
