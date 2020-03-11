ofxErrorEvent
=====================================
ofxErrorEvent is provide easy error handling for OpenGL.

Introduction
------------
ofxErrorEvent is provide easy error handling for OpenGL.  
below code is example source code.
````
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
````

License
-------
MIT License

Installation
------------
this folder into the `openFrameworks/addons/` folder.

Dependencies
------------
have no dependencies.

Compatibility
------------
* of_v0.11.0_vs2017_release
* Windows10

Known issues
------------
known problem is none.

Version history
------------


### Version 0.1 (2020/03/11):
first release

