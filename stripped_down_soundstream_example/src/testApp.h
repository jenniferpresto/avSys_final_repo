// Extremely stripped-down app using ofSoundStream to play wav files.
// Adapted from much cooler example created by Pierre Proske
// Downloaded from oF forums here:
// http://forum.openframeworks.cc/index.php/topic,3502.0.html

#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Sample.h"

class testApp : public ofBaseApp{
    
public:
    
    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    void audioRequested 	(float * input, int bufferSize, int nChannels);
    
    float 	pan;
    int		sampleRate;
    float 	volume;
    float   speed;
    
    float 	* lAudio;
    float   * rAudio;
    
    Sample bass;
    Sample guitar;
};

#endif
