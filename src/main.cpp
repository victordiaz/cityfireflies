#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    ofAppGlutWindow window;
    #ifdef WINDOWS	
        window.setGlutDisplayString("rgba double samples>=4 depth"); //esto puede que pete en windows
    #endif  
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW); 		// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}

