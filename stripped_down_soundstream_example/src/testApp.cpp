#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
    
	ofBackground(255,255,255);
    
	// 2 output channels,
	// 0 input channels
	// 22050 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
    
	sampleRate 			= 44100;
	volume				= 1.0f;
    speed               = 1.0f;
	lAudio = new float[256];
	rAudio = new float[256];
    
	bass.load("bass.wav");
	bass.setLooping(true);
    
    guitar.load("guitar.wav");
    guitar.setLooping(true);
    
	ofSoundStreamSetup(2, 0, this, sampleRate, 256, 4);
    
	ofSetFrameRate(30);
    
}


//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}
//--------------------------------------------------------------
void testApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
	float leftScale = 1 - pan;
	float rightScale = pan;
    
    // bass
    for (int i = 0; i < bufferSize; i++){
        // mono
        if(bass.getChannels() == 1) {
            float smp = bass.play(speed);
            lAudio[i] = output[i*nChannels    ] = smp * volume * leftScale;
            rAudio[i] = output[i*nChannels + 1] = smp * volume * rightScale;
        }
        // stereo
        else if (bass.getChannels() == 2) {
            lAudio[i] = output[i*nChannels    ] = bass.play(speed) * volume * leftScale;
            rAudio[i] = output[i*nChannels + 1] = bass.play(speed) * volume * rightScale;
        }
    }

    // guitar
    for (int i = 0; i < bufferSize; i++){
        // mono
        if(guitar.getChannels() == 1) {
            float smp = guitar.play(speed);
            lAudio[i] = output[i*nChannels    ] = smp * volume * leftScale;
            rAudio[i] = output[i*nChannels + 1] = smp * volume * rightScale;
        }
        // stereo
        else if (guitar.getChannels() == 2) {
            lAudio[i] = output[i*nChannels    ] = guitar.play(speed) * volume * leftScale;
            rAudio[i] = output[i*nChannels + 1] = guitar.play(speed) * volume * rightScale;
        }
    }
}

