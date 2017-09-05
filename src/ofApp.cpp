#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	
	ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(100, 100, 20);	
	shrek.load("shrek.png");

	soundStream.printDeviceList();
	//if you want to set a different device id
	soundStream.setDeviceID(2); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.

	// 0 output channels,
	// 1 input channels
	// 48000 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	int sampleRate = 48000;
	int bufferSize = 256;
	int outChannels = 0;
	int inChannels = 1;
	
	left.assign(bufferSize, 0.0);

	smoothedVol = 0.0;
	scaledVol = 0.0;

        soundStream.setup(this, outChannels, inChannels, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){

	//lets scale the vol up to a 0-0.5 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.15, 0.55, true);

	// don't allow output if vol is at a minimum (remove background noise)
	if (scaledVol > 0.0 && scaledVol <= .153)
		scaledVol = 0.0;
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetColor(225);
        // set up a matrix for drawing debug strings
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(250, 170, 0);
		ofSetColor(225);
                // ofDrawBitmapString("Scaled average vol (0-55): " + ofToString(scaledVol * 100.0, 0), 4, 18);
		ofPopMatrix();
	ofPopStyle();
	
	shrek.draw(ofGetWidth()/4 + 100, ofGetHeight()/4-70, scaledVol * 1500.0f, scaledVol * 1500.0f);
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){	
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		left[i]	= input[i];
		curVol += left[i] * left[i];
                numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	if( key == 's' ){
		soundStream.start();
	}
	
	if( key == 'e' ){
		soundStream.stop();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

