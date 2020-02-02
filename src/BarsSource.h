#pragma once

#include "ofMain.h"
#include "FboSource.h"

class BarsSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        vector<ofImage> images;
        float phase;
        float phase2;
        float noiseSeed;
        float rotation;
        float noiseX;
    int time;
    float alphaSquare;
    int startTime;
};
