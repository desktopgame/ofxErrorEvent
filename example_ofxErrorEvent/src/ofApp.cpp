#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	auto hdr = ofxErrorEvent::Handler::setup(nullptr);
	// method 1.
	// use callback function.
	// can using lambda.
	auto& listeners = hdr->startUpdateCallbackList();
	listeners.emplace_back([](ofxErrorEvent::EventArgs e) -> void {
		ofLog() << "method 1:" << e.toString();
	});
	hdr->endUpdateCallbackList();
	// method 2.
	// use openFrameworks `ofEvent` in direct.
	// can using only member function pointer.
	ofAddListener(hdr->getEvent(), this, &ofApp::onError);
	// this is bug!
	// this statement as trigger, launch event from ofxErrorEvent.
	glGenBuffers(-1, 0);
	glDeleteBuffers(-1, 0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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


void ofApp::onError(ofxErrorEvent::EventArgs& e) {
	ofLog() << "method 2:" << e.toString();
}
