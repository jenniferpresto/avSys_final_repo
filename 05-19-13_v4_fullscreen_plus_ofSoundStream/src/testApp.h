/*
 One-Man Air-Band
 
 Jennifer G. Presto
 AVSys Final Project
 May 19, 2013
 
 Created for AVSys, a class in the MFA program in Design and Technology at Parsons
 
 PS3Eye cam-specific settings from basic example that comes with addon, available here:
 https://github.com/paulobarcelos/ofxMacamPs3Eye
 
 ofSoundStream code adapted from code by
 by Pierre Proske, available here: http://forum.openframeworks.cc/index.php/topic,3502.0.html
 
 
 */

#pragma once

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"
#include "Sample.h"


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

        // variables for the camera
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

        // looping images (each vector is essentially a short movie clip)
        vector<ofImage> images;
        vector<ofImage> images2;
        vector<ofImage> images3;
        vector<ofImage> images4;
        vector<ofImage> images5;

        // sound variables
        void audioRequested 	(float * input, int bufferSize, int nChannels);
        
        float 	pan;
        int		sampleRate;
        float 	volume;
        float   speed;
        
        float 	* lAudio;
        float   * rAudio;
        
        Sample drums;
        Sample drumsPerc;
        Sample drumsPercBass;
        Sample drumsPercBassGuitar;
    
    //variables for interface itself
    int appState;
    ofImage drumsButton;
    ofImage percussionButton;
    ofImage bassButton;
    ofImage guitarButton;
    ofImage audienceButton;
    
};
