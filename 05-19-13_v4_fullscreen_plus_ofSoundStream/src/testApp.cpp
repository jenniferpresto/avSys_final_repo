/*
 One-Man Air-Band
 
 Jennifer G. Presto
 AVSys Final Project
 May 19, 2013
 
 Created for AVSys, a class in the MFA program in Design and Technology at Parsons
 
 Play in an awesome air band, even if you're by yourself!
 
 PS3Eye cam-specific settings from basic example
 that comes with addon, available here:
 https://github.com/paulobarcelos/ofxMacamPs3Eye
 
 ofSoundStream code adapted from code by
 by Pierre Proske, available here:
 http://forum.openframeworks.cc/index.php/topic,3502.0.html
 
 ofxCenteredTrueTypeFont subclass
 created by armadillu, available here:
 https://github.com/armadillu/ofxCenteredTrueTypeFont
 */

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
//    ofSetFullscreen(true);
    ofSetVerticalSync(true);
	ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
    ofSetColor(255, 255, 255);
	
	camWidth = 640;     // if change this, change both vector sizes in testApp.h
	camHeight = 480;    // if change this, change both vector sizes in testApp.h
	
	ps3eye.listDevices();
	
	ps3eye.setDesiredFrameRate(60);
	ps3eye.initGrabber(camWidth,camHeight);
	
	ps3eye.setAutoGainAndShutter(false); // otherwise we can't set gain or shutter
	ps3eye.setGain(0.5);
	ps3eye.setShutter(1.0);
	ps3eye.setGamma(0.5);
	ps3eye.setBrightness(0.6);
	ps3eye.setContrast(1.0);
    //	ps3eye.setHue(0.0);
	
	ps3eye.setFlicker(1);
    
    // images used in creating loops
    background.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    grayImageForAlpha.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
    displayCutOut.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    
    // images to be displayed in loops
    displayImage.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    
    // threshold for background subtractions
    threshold = 400;
    
    // sound setup:
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
    
	drums.load("drums.wav");
	drums.setLooping(true);
    
    drumsPerc.load("drumsPerc.wav");
    drumsPerc.setLooping(true);
    
    drumsPercBass.load("drumsPercBass.wav");
    drumsPercBass.setLooping(true);
    
    drumsPercBassGuitar.load("drumsPercBassGuitar.wav");
    drumsPercBassGuitar.setLooping(true);
    
	ofSoundStreamSetup(2, 0, this, sampleRate, 256, 4);
    
    // variables for interface
    appState = 0;
    helvetica.loadFont("helvetica.otf", 24);
    recording = false;
    timeStartRecording = 0;
    
    titlePage.loadImage("titlePage.png");
    drumsButton.loadImage("drumsButton.png");
    percussionButton.loadImage("percussionButton.png");
    bassButton.loadImage("bassButton.png");
    guitarButton.loadImage("guitarButton.png");
    audienceButton.loadImage("audienceButton.png");
    
    
}


//--------------------------------------------------------------
void testApp::update(){
	
    
	ps3eye.update();
	
	// Blink the led everytime there is a new frame
	if(ps3eye.isFrameNew()){
		ps3eye.setLed(true);
	}
	else ps3eye.setLed(false);
    
    
    // when press spacebar, capture the background
    if(ofGetKeyPressed(' ')){
        if(ps3eye.isFrameNew()){
            background.setFromPixels(ps3eye.getPixelsRef());
            backgroundPixels = background.getPixels();          // pixels from bg image
            
            // fill array of bgPixel vectors with the RGB values of each background pixel
            for(int i=0; i < camWidth; i++){
                for(int j=0; j < camHeight; j++){
                    bgPixels[j*camWidth + i].set(backgroundPixels[(j*camWidth + i)*3], backgroundPixels[(j*camWidth + i)*3 + 1], backgroundPixels[(j*camWidth + i)*3 + 2]);
                }
            }
        }
    }
    
    
    // when press various keys, record from camera (each frame adds an image to the appropriate vector)
    if(ofGetKeyPressed('a')){
        makeLoop(images);
    }
    if(ofGetKeyPressed('b')){
        makeLoop(images2);
    }
    if(ofGetKeyPressed('c')){
        makeLoop(images3);
    }
    if(ofGetKeyPressed('d')){
        makeLoop(images4);
    }
    if(ofGetKeyPressed('e')){
        makeLoop(images5);
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    background.draw(0, 0, 1024, 768);
    cout << appState << "  recording? " << recording << "   " << mouseX << " " << mouseY << endl;
    
    if (images.size() > 0){
        int whichImage = ofGetFrameNum() % images.size();
        displayImage.setFromPixels(images[whichImage].getPixelsRef());
        displayImage.draw(0, 0, 1024, 768);
    }
    
    if (images2.size() > 0){
        int whichImage = ofGetFrameNum() % images2.size();
        displayImage.setFromPixels(images2[whichImage].getPixelsRef());
        displayImage.draw(0, 0, 1024, 768);
    }
    
    if (images3.size() > 0){
        int whichImage = ofGetFrameNum() % images3.size();
        displayImage.setFromPixels(images3[whichImage].getPixelsRef());
        displayImage.draw(0, 0, 1024, 768);
    }
    
    if (images4.size() > 0){
        int whichImage = ofGetFrameNum() % images4.size();
        displayImage.setFromPixels(images4[whichImage].getPixelsRef());
        displayImage.draw(0, 0, 1024, 768);
    }
    
    if (images5.size() > 0){
        int whichImage = ofGetFrameNum() % images5.size();
        displayImage.setFromPixels(images5[whichImage].getPixelsRef());
        displayImage.draw(0, 0, 1024, 768);
    }
    
    if (appState != 5){
        ps3eye.draw(10,10, 320, 240);
    }
    // beginning of app
    if(appState == 0){
        titlePage.draw(0, 0);
    }
    
    // background set; nothing recorded
    // record drums
    if(appState == 1){
        drumsButton.draw(10, 384);
        ofSetColor(75, 75, 75);
        percussionButton.draw(10, 465);
        bassButton.draw(10, 546);
        guitarButton.draw(10, 627);
        audienceButton.draw(10, 708);
        ofSetColor(255, 255, 255);
    }
    
    // drums already recorded and looping
    // record percussion
    if(appState == 2){
        
    }
    
    // drums and percussion already recorded and looping
    // record bass
    if(appState == 3){
        
    }
    
    // drums, percussion, and bass already recorded and looping
    // record guitar
    if(appState == 4){
        
    }
    
    // drums, percussion, bass, and guitar already recorded and looping
    // record audience
    if(appState == 5){
        
    }
	
	ofDrawBitmapString("Ps3Eye FPS: "+ ofToString(ps3eye.getRealFrameRate()), 20,15);
    if(recording && ofGetElapsedTimeMillis()-timeStartRecording < 5000){
        countdown();
    }
}

//--------------------------------------------------------------
void testApp::makeLoop (vector<ofImage> & loopingClip){
    if(ps3eye.isFrameNew()){
        unsigned char * grayPixels = grayImageForAlpha.getPixels();     // will be alpha channel
        unsigned char * colorPixels = ps3eye.getPixels();               // pixels from camera
        unsigned char * colorAlphaPixels = displayCutOut.getPixels();   // camera plus alpha
        
        // compare against the background to determine the alpha for the image
        for (int i = 0; i < camWidth; i++){
            for (int j = 0; j < camHeight; j++){
                // convert RGB values of each pixel into a vector
                // background pixels already converted when spacebar pressed
                // now do it for image being recorded
                rgbPixels[j*camWidth+i].set(colorPixels[(j*camWidth + i) * 3], colorPixels[(j*camWidth + i) * 3 + 1], colorPixels[(j*camWidth + i) * 3 + 2]);
                
                // compare bgPixels to rgbPixels to create a black-and-white alpha mask
                grayPixels[j*camWidth + i] = bgPixels[j*camWidth + i].squareDistance(rgbPixels[j*camWidth + i]) > threshold ? 255 : 0;
                
            }
        }
        
        // apply the alpha mask when creating new cut-out color image
        for (int i = 0; i < camWidth; i++){
            for (int j = 0; j < camHeight; j++){
                colorAlphaPixels[(j*camWidth + i) * 4] = colorPixels[(j*camWidth + i) * 3];
                colorAlphaPixels[(j*camWidth + i) * 4 + 1] = colorPixels[(j*camWidth + i) * 3 + 1];
                colorAlphaPixels[(j*camWidth + i) * 4 + 2] = colorPixels[(j*camWidth + i) * 3 + 2];
                colorAlphaPixels[(j*camWidth + i) * 4 + 3] = grayPixels[j*camWidth + i];
            }
        }
        
        displayCutOut.update();
        
        ofImage temp;
        temp.setUseTexture(false); // store only in RAM
        temp.setFromPixels(displayCutOut.getPixelsRef());
        loopingClip.push_back(temp);
    }
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if(key==' '){
        appState = 1;
        images.clear();
        images2.clear();
        images3.clear();
        images4.clear();
        images5.clear();
    }
	
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(appState == 1 && x > 10 && x < 330 && y > 384 && y < 434){
        recording = true;
        timeStartRecording = ofGetElapsedTimeMillis();
    }
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
//--------------------------------------------------------------
void testApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
	float leftScale = 1 - pan;
	float rightScale = pan;
    
    // drums only
    if(appState == 2){
        for (int i = 0; i < bufferSize; i++){
            // mono
            if(drums.getChannels() == 1) {
                float smp = drums.play(speed);
                lAudio[i] = output[i*nChannels    ] = smp * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = smp * volume * rightScale;
            }
            // stereo
            else if (drums.getChannels() == 2) {
                lAudio[i] = output[i*nChannels    ] = drums.play(speed) * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = drums.play(speed) * volume * rightScale;
            }
        }
    }
    
    // drums plus percussion
    if(appState == 3){
        for (int i = 0; i < bufferSize; i++){
            // mono
            if(drumsPerc.getChannels() == 1) {
                float smp = drumsPerc.play(speed);
                lAudio[i] = output[i*nChannels    ] = smp * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = smp * volume * rightScale;
            }
            // stereo
            else if (drumsPerc.getChannels() == 2) {
                lAudio[i] = output[i*nChannels    ] = drumsPerc.play(speed) * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = drumsPerc.play(speed) * volume * rightScale;
            }
        }
    }
    
    // drums, percussion, and bass
    if(appState == 4){
        for (int i = 0; i < bufferSize; i++){
            // mono
            if(drumsPercBass.getChannels() == 1) {
                float smp = drumsPerc.play(speed);
                lAudio[i] = output[i*nChannels    ] = smp * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = smp * volume * rightScale;
            }
            // stereo
            else if (drumsPercBass.getChannels() == 2) {
                lAudio[i] = output[i*nChannels    ] = drumsPercBass.play(speed) * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = drumsPercBass.play(speed) * volume * rightScale;
            }
        }
    }
    
    // drums, percussion, bass, and guitar
    if(appState == 5){
        for (int i = 0; i < bufferSize; i++){
            // mono
            if(drumsPercBassGuitar.getChannels() == 1) {
                float smp = drumsPercBassGuitar.play(speed);
                lAudio[i] = output[i*nChannels    ] = smp * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = smp * volume * rightScale;
            }
            // stereo
            else if (drumsPercBassGuitar.getChannels() == 2) {
                lAudio[i] = output[i*nChannels    ] = drumsPercBassGuitar.play(speed) * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = drumsPercBassGuitar.play(speed) * volume * rightScale;
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::countdown (){
    helvetica.drawStringCentered("Beginning recording in", ofGetWidth() * 0.5, 30);
    helvetica.drawStringCentered(ofToString((int)(timeStartRecording+5000-ofGetElapsedTimeMillis())/1000 + 1), ofGetWidth() * 0.5, 60);
}

//--------------------------------------------------------------
void testApp::drawRecordingMeter (){
    
}