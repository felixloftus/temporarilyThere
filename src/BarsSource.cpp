#include "BarsSource.h"
// =====================================================
void BarsSource::setup(){
    // The scene starts with a slight reveal of the image used, before collapsing into more chaotic movement of strips of light. The strips then start rotating. They eventually disappear as the alpha dims
    
    name = "Bars FBO Source";
    allocate(1200, 1200);
    
    // Initialising Variables
    ofClear(0);
    rotation = 0;
    noiseX = 10;
    phase = 0;
    noiseSeed = 0;
    time = 0;
    alphaSquare=0;
 
    //Creating Vector of Images from Directory
    // glass=0 paint=1 rust=2 metal=1 motors=3
    // using motors for this sketch
    string path = "photos2";
    ofDirectory dir(path);
    dir.allowExt("jpg");
    dir.listDir();
    for(int i = 0; i < dir.size(); i++){
        ofLogNotice(dir.getPath(i));
        ofImage img;
        img.load(dir.getPath(i));
        images.push_back(img);
        images[i].getPixels();
        images[i].resize(fbo->getWidth(), fbo->getHeight());
    }
}
// =====================================================
void BarsSource::reset(){
        startTime = ofGetFrameNum();
}
// =====================================================
void BarsSource::setName(string _name){
    name = _name;
}
// =====================================================
void BarsSource::update(){
    // buffer cleared
    ofClear(0);
    // clock for sketch
    time=ofGetFrameNum()- startTime ;
    // Push phases for rotations
    phase+=0.05;
    phase2+=0.5;
    if (time>1200) {
        phase+=0.0005;
        rotation=cos(phase2)/sin(phase)*360;
    }
    if (time>26*30) {
        rotation=-cos(phase2)/sin(phase)*360;;
    }
    if(time>30*30){
        alphaSquare+=2;
    }
    
}
// =====================================================
void BarsSource::draw(){
        ofClear(0);
        ofBackground(0);
    if(ofRandom(10)>9.9){
        ofSetColor(0, 0, 255);
        ofDrawRectangle(0, 0, fbo->getWidth(), fbo->getHeight());
    }
    
    // initial 'scan' of cube
    // this would go through a few iterations if the projection was longer
    if (time<90) {
        ofSetColor(255, 255, 255,ofRandom(230, 255));
        images[3].drawSubsection(0, 0, phase*550, fbo->getHeight()/2, 0, 0);
        if (time>30) {
            images[3].drawSubsection(fbo->getWidth(), fbo->getHeight()/2, -((phase-(0.05*30)))*550, fbo->getHeight()/2, fbo->getWidth(), fbo->getHeight()/2);
        }

    }
    if (time>90&&time<180) {
        ofSetColor(255, 255, 255,ofRandom(200, 255));
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(fbo->getWidth()/2,fbo->getHeight()/2);
        ofDrawRectangle(-ofRandom(fbo->getWidth()/3), -ofRandom(fbo->getHeight()/2), ofRandom(fbo->getWidth()/3), ofRandom(fbo->getHeight()/2));
        ofPopMatrix();

    }
    //  Bars made up of strips of the image flash across screen - to light up cube
    if (time>180) {

        ofPushMatrix();
        float translationX =fbo->getWidth()*sin(ofRadToDeg(phase2));
        ofTranslate(translationX, fbo->getHeight()/2.5);
        ofRotateDeg(rotation);
         ofBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(255,255,255);
          for (int i=0; i<10; i++) {
                int imgWidth = 8+(ofNoise(noiseSeed)*5);
                int imgHeight = ofGetHeight()/1.75*sin(ofRadToDeg(phase));
              float varNoise = ofNoise(noiseSeed);
              float varNoiseM =ofMap(varNoise, 0, 1, -fbo->getWidth()/2, fbo->getWidth()/2);
              images[3].drawSubsection(noiseX+(i*4), varNoiseM, imgWidth, imgHeight, imgHeight, varNoiseM);

         }
        if (ofRandom(10)>9.5) {
            ofSetColor(255);
            ofDrawRectangle(-ofRandom(fbo->getWidth()/2), -ofRandom(fbo->getHeight()/2,fbo->getHeight()), ofRandom(fbo->getWidth()/2),fbo->getWidth()), ofRandom(fbo->getHeight()/2,fbo->getHeight());
        }
        ofPopMatrix();
        }
    // fade out with black rectangle
    if(time>30*30){
        ofSetColor(0,alphaSquare);
        ofRotateDeg(0);
        ofDrawRectangle(0, 0, fbo->getWidth(), fbo->getHeight());
    }
        noiseSeed+=0.001;
}

