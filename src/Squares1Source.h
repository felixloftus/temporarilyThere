#pragma once

#include "ofMain.h"
#include "FboSource.h"







// I did not use this sketch in my project








class Squares1Source : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        void squares(float phase, float phase2, int width);
        float phase;
        float phase2;
        ofImage firstImage, secondImage;
        float noiseSeed, noiseSeed2;
        int numOfSquares;
        float alpha1, alphaSquare;
    int time;
        
};
