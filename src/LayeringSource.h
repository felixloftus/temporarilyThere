#pragma once

#include "ofMain.h"
#include "FboSource.h"

class LayeringSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        vector<ofImage> images;
        ofMesh mesh, mesh2, mesh3, mesh4, mesh5;
        float intensityThreshold;
    float phase;
    float noiseSeed;
    int w,h;
    int time;
    float changeX,changeY, changeX2, changeY2;
    float alpha;
    int startTime;
};
