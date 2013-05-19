#pragma once

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"

//#define CAMWIDTH 320
//#define CAMHEIGHT 240

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
    
    // camera variables
    ofxMacamPs3Eye ps3eye;
    int camWidth;
    int camHeight;
    
    // images for creating the loops
    ofImage background;
    unsigned char * backgroundPixels;
    ofVec3f bgPixels[320*240];   // this will store each bg pixel as a vector for comparison
    ofVec3f rgbPixels[320*240];  // this will store each live pixel as a vector for comparison
    ofImage grayImageForAlpha;              // will hold become alpha mask for each image
    ofImage displayCutOut;                  // will include the alpha; created at time images are added to vector
    ofImage displayImage;                   // image that actually gets drawn
    
    
    // vectors that hold the images for each loop
    vector<ofImage> images;     // first looping image
    vector<ofImage> images2;    // second looping image
    vector<ofImage> images3;    // third looping image
    vector<ofImage> images4;    // fourth looping image
    
    //threshold of comparison
    float threshold;
    
    // fake (delightful!) background for testing
    ofImage tulips;
        
    // music variables
    ofSoundPlayer drums;
    ofSoundPlayer conga;
    ofSoundPlayer bass;
    ofSoundPlayer guitar;
    
};