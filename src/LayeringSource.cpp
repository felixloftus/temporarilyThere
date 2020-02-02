#include "LayeringSource.h"

void LayeringSource::setup(){
    // Layering source is made up of layers of sections of images. The pixels of the images are first 'scanned' to get their lightness. If the pixels lightness passes a set threshold then the pixel is added to the mesh. After trying multiple techniques to layer photos I settled on using meshes but only using the x and y axis.
    // Reason for using ofMesh: I attempted this by creating a function that added x,y coordinates for each calculation to a vector. I would then call the function in LayeringSource::draw() and draw circles at the x,y co-ordinates. However, drawing the circles was computationally expensive and it seemed wrong to create a complex function for something that ofMesh does.
    // https://openframeworks.cc/ofBook/chapters/generativemesh.html ofBook Mesh
    //https://openframeworks.cc/ofBook/chapters/image_processing_computer_vision.html ofBook
    // potential to leave this sketch out of pop-up
    name = "Layering FBO Source";
    // Allocate our FBO source, decide how big it should be
    allocate(1200, 1200);
//    ofClear(0,250);
    // Initialising Variables
    phase=0;
    changeX=2;
    changeY=-2;
    changeX2=3;
    changeY2=-3;
    noiseSeed=0;
    alpha = 0;
    // load images in vector
    // glass=0 paint=1 rust=2 metal=1 motors=3
    // resize images for computational performance
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
        images[i].resize(fbo->getWidth()/6, fbo->getHeight()/6);
    }
    // Setup up w and h for scanning through images
    w = fbo->getWidth()/6;
    h = fbo->getHeight()/6;
    
        // create meshes - mesh 4 with use lines rather than points
        mesh.setMode(OF_PRIMITIVE_POINTS);
           mesh.enableColors();
           mesh2.setMode(OF_PRIMITIVE_POINTS);
           mesh2.enableColors();
           mesh3.setMode(OF_PRIMITIVE_POINTS);
           mesh3.enableColors();
           mesh4.setMode(OF_PRIMITIVE_LINES);
           mesh4.enableIndices();
           mesh4.enableColors();
    
    // create threshold to test each pixel against
    // initialise to 100
    intensityThreshold = 100;
    
    // create a for loop to check each pixels lightness for an image
    // If pixel is above threshold add to a mesh
    // Process taken from ofBook - Image Processing
    // meshes have no z index
    for (int x=0; x<w; x++) {
           for (int y=0; y<h; y++) {
               // perform calculations with 'paint'
               ofColor c = images[1].getColor(x, y);
               float intensity = c.getLightness();
               if (intensity >= intensityThreshold) {
                   ofVec3f pos(x*2, y*6, 0.0);
                   mesh.addVertex(pos);
                   mesh.addColor(c);
               }
               ofColor c2 = images[2].getColor(x, y);
               float intensity2 = c2.getLightness();
               if (intensity2 >= intensityThreshold) {
                   ofVec3f pos(x*2, y*6, 0.0);
                   mesh2.addVertex(pos);
//                   c2.invert();
                   mesh2.addColor(c2);
               }
               ofColor c3 = images[0].getColor(x, y);
               float intensity3 = c3.getLightness();
               if (intensity3 >= intensityThreshold) {
                   ofVec3f pos(x*2, y*6, 0.0);
                   mesh3.addVertex(pos);
                   mesh3.addColor(c3);
               }
               ofColor c4 = images[3].getColor(x, y);
               float intensity4 = c4.getLightness();
               if (intensity4 >= intensityThreshold) {
                   ofVec3f pos(x*3, y*6, 0.0);
                  c4.invert();
                   mesh4.addVertex(pos);
                   mesh4.addColor(c4);
               }
           }
    }
//        float connectionDistance = 10;
//        int numVerts = mesh4.getNumVertices();
//        for (int a=0; a<numVerts; ++a) {
//            ofVec3f verta = mesh4.getVertex(a);
//            for (int b=a+1; b<numVerts; ++b) {
//                ofVec3f vertb = mesh4.getVertex(b);
//                float distance = verta.distance(vertb);
//                if (distance <= connectionDistance) {
//                    // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
//                    // connected to form a line
//                    mesh4.addIndex(a);
//                    mesh4.addIndex(b);
//                }
//            }
//        }
}

void LayeringSource::reset(){
    startTime = ofGetFrameNum();
    ofClear(0,1);
}

void LayeringSource::setName(string _name){
    name = _name;
}

void LayeringSource::update(){
    // Push Phase for Time
    phase++;
    // clock for sketch
    time = ofGetFrameNum()-startTime;
    if (time<30*11) {

        changeX=changeX+(ofRandom(-15,15));
    if(time%6==0){
        changeY=changeX-(ofNoise(noiseSeed+0.2))*20;
    }
    if(time%12==0){
        changeX2=changeX+(ofRandom(-40,40));
    }
    if(time%14==0){
        changeY2=changeX+ofRandom(-20,20);
    }
}
    if (time>30*11) {
        if(time%8==0){
        float noiseVal=ofMap(ofNoise(noiseSeed), 0, 1, -2, 2);
        changeX=changeX+noiseVal;
        }
        changeY=changeX/10+(ofNoise(noiseSeed+0.2))*20;
    }
    if(time>28*30){
        if(ofRandom(10)>9){
            alpha+=5;
        }
    }
    
}

//==========================================================
void LayeringSource::draw(){
    ofClear(160,1);
    // chunk 1
    if (time<30*20) {
        float wave=sin(phase/15);
        float waveMapped = ofMap(wave, -1, 1, 0.4, 1);
        ofSetColor(250*waveMapped);
        ofPushMatrix();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofTranslate(fbo->getWidth()/2, fbo->getWidth()/2);
        ofScale(waveMapped);
        ofDrawRectangle(0, 0, fbo->getWidth(), fbo->getWidth());
        ofPopMatrix();

         for(int i=0; i<20;i++){
                ofPushMatrix();
                ofTranslate(i*changeX, 0);
                mesh.draw();
                mesh2.draw();
                ofPopMatrix();
            }
         for(int i=0; i<20;i++){
                ofPushMatrix();
                ofTranslate(fbo->getWidth()/3, changeY);
                mesh3.draw();
                ofRotateXRad(changeX/200);
                mesh4.draw();
                ofPopMatrix();
            }
         for(int i=0; i<20;i++){
                ofPushMatrix();
                ofTranslate((2*fbo->getWidth()/3), 0);
                mesh3.draw();
//                ofRotateXRad(changeX/200);
                mesh.draw();
                ofPopMatrix();
            }
    }
    
    // chunk 2
    if (time>30*25) {
        float wave=sin(phase/10);
        float waveMapped = ofMap(wave, -1, 1, 0.4, 1);
        ofSetColor(1*waveMapped);
        ofPushMatrix();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofTranslate(fbo->getWidth()/2, fbo->getWidth()/2);
        ofScale(waveMapped);
        ofDrawRectangle(ofRandom(fbo->getWidth()/8.5,-fbo->getWidth()/8.5), ofRandom(fbo->getWidth()/8.5,-fbo->getWidth()/7.5), fbo->getWidth()/8.5, fbo->getWidth()/8.5);
        ofPopMatrix();
        if (wave>0) {
        
         for(int i=0; i<20;i++){
                ofPushMatrix();
                mesh.draw();
                ofRotateXRad(changeX/200);
                mesh2.draw();
                ofPopMatrix();
            }
        }
        if (wave<0) {
        
         for(int i=0; i<20;i++){
                ofPushMatrix();
                ofTranslate(fbo->getWidth()/3, (i*10));
                mesh3.draw();
                ofRotateXRad(changeX/200);
                mesh2.draw();
                ofPopMatrix();
            }
        }
        if (wave<0.5||wave<-0.5) {
        
         for(int i=0; i<10;i++){
                ofPushMatrix();
                ofTranslate(2*fbo->getWidth()/3,i);
                mesh3.draw();
                ofRotateXRad(changeX/200);
                mesh.draw();
                ofPopMatrix();
            }
        }
        }
    //chunk 3
        if (time>30*30) {
            float wave=sin(phase/10);
            float waveMapped = ofMap(wave, -1, 1, 0.4, 1);
            ofSetColor(200*waveMapped);
            ofPushMatrix();
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofTranslate(fbo->getWidth()/2, fbo->getWidth()/2);
            ofScale(waveMapped);
            ofDrawRectangle(0, 0, fbo->getWidth(), fbo->getWidth());
            ofPopMatrix();

            for(int i=0; i<15;i++){
                ofPushMatrix();
                ofTranslate(i*changeX2, i);
                mesh.draw();
    //            ofRotateXRad(changeX/200);
                mesh3.draw();
                ofPopMatrix();
            }
                for(int i=0; i<15;i++){
                    ofPushMatrix();
                    ofTranslate(i, i*changeY);
    //                ofRotateXRad(changeY/20);
                    mesh2.draw();
                    ofPopMatrix();
                }

            // Chunk two - from 1/3 fbo->getWidth
                for(int i=0; i<15;i++){
                    ofPushMatrix();
        //            ofRotateDeg(90);
                    ofTranslate(i+fbo->getWidth()/3+(i*10), 0);
                    ofRotateXRad(-changeX/200);
                    mesh.draw();
        //            mesh3.draw();
                    ofPopMatrix();
                }
                for(int i=0; i<15;i++){
                    ofPushMatrix();
                    ofTranslate(i+fbo->getWidth()/3, i*changeX);
                    mesh2.draw();
    //                ofRotateXRad(changeY2/20);
    //                mesh4.draw();
                    ofPopMatrix();
                }
            // Chunk 3 - from 2/3 fbo->getWidth
                for(int i=0; i<15;i++){
                    ofPushMatrix();
        //            ofRotateDeg(90);
                    ofTranslate(2*fbo->getWidth()/3, i);
    //                ofRotateXRad(changeX/200);
                    ofPopMatrix();
                }
                for(int i=0; i<15;i++){
                    ofPushMatrix();
                    ofTranslate(2*fbo->getWidth()/3, i*changeX);
                    mesh.draw();
    //                mesh2.draw();
    //                ofRotateXRad(-changeY/20);
                    mesh3.draw();

    //                mesh4.draw();
                    ofPopMatrix();
                }
            }
        noiseSeed+=0.001;
    ofSetColor(0, alpha);
    
}

