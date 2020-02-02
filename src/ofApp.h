#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "VideoSource.h"
#include "SceneManager.h"
//#include "Squares1Source.h"
#include "Squares2Source.h"
#include "LayeringSource.h"
#include "BarsSource.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
		void keyReleased(int key);
	
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);

		ofxPiMapper piMapper;

		// By using a custom source that is derived from FboSource
		// you will be able to see the source listed in sources editor
//        Squares1Source * squares1Source;
        Squares2Source * squares2Source;
        LayeringSource * layeringSource;
        BarsSource * barsSource;
        ofImage dummyObjects;

        SceneManager sceneManager;
};
