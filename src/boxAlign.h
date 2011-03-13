#ifndef _CBOXALIGN_
#define _CBOXALIGN_


#include "ofMain.h"
#include "ofxCvMain.h"


class CBoxAligner {

	public:

		CBoxAligner();
		~CBoxAligner(); 

		void           setup();
		void           setup( int x, int y, float w, float h);

        // moves a handle to mouse position
        float           adjustHandle(float mouseX, float mouseY );

        // returns the id of the handle that is closest to the mouse position
        int            findClosestHandle(float mouseX, float mouseY);

        // returns the  distance of mouse pointer to closest handle
        float          findSelectionDistance(float mouseX, float mouseY);

        // draw handles to screen and sets draw offsets to x,y
        void           draw( int x, int y, float radius = 8.0f );


        float          getTopLeftX(){ return fHandles[0].x; }
        float          getTopLeftY(){ return fHandles[0].y; }
        float          getBottomLeftX(){ return fHandles[3].x; }
        float          getBottomLeftY(){ return fHandles[3].y; }
        float          getTopRightX(){ return fHandles[1].x; }
        float          getTopRightY(){ return fHandles[1].y; }
        float          getBottomRightX(){ return fHandles[2].x; }
        float          getBottomRightY(){ return fHandles[2].y; } 
	
	
	
	float          setTopLeftX(float q){ fHandles[0].x = q; }
	float          setTopLeftY(float q){  fHandles[0].y = q; }
	float          setBottomLeftX(float q){  fHandles[3].x = q; }
	float          setBottomLeftY(float q){  fHandles[3].y = q; }
	float          setTopRightX(float q){  fHandles[1].x = q; }
	float          setTopRightY(float q){  fHandles[1].y = q; }
	float          setBottomRightX(float q){  fHandles[2].x = q; }
	float          setBottomRightY(float q){  fHandles[2].y = q; } 


        ofPoint         fHandles[4];
        ofPoint         fDrawOffset;

        int             imageWidth;
        int             imageHeight;

};

#endif
