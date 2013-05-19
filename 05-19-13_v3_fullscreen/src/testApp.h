#pragma once

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"

class testApp : public ofBaseApp{
	
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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
        // function for creating looping series of images
        void makeLoop(vector<ofImage> & loopingClip);

    
		ofxMacamPs3Eye ps3eye;
	
		int 				camWidth;
		int 				camHeight;
    
        // images for creating the loops
        ofImage background;
        unsigned char * backgroundPixels;
        ofVec3f bgPixels[640*480];   // this will store each bg pixel as a vector for comparison
        ofVec3f rgbPixels[640*480];  // this will store each live pixel as a vector for comparison
        ofImage grayImageForAlpha;              // will hold become alpha mask for each image
        ofImage displayCutOut;                  // will include the alpha; created at time images are added to vector
        ofImage displayImage;                   // image that actually gets drawn

        float threshold;        // for comparison of images

    vector<ofImage> images;
    vector<ofImage> images2;
    vector<ofImage> images3;
    vector<ofImage> images4;
    vector<ofImage> images5;
    
};
