#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void reverseColor(unsigned char* pixels);
        void noiseColor(unsigned char* pixels);
        void modifyPixels(unsigned char* pixels);
    
    ofVideoGrabber video;
    int w, h;
    unsigned char* changedPixels;
    ofTexture videoTexture;
    int state = 0;
};
