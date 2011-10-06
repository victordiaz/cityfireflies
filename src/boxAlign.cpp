#include "boxAlign.h"

CBoxAligner::CBoxAligner()
{

}
//--------------------------------------------------------------
CBoxAligner::~CBoxAligner()
{

}
//--------------------------------------------------------------
void CBoxAligner::setup()
{
    for(int i = 0; i < 4; i++)
    {
        fHandles[i].x = 0.0f;
        fHandles[i].y = 0.0f;
    }

    fDrawOffset.x = 0.0f;
    fDrawOffset.y = 0.0f;
}
//--------------------------------------------------------------
void CBoxAligner::setup( int x, int y, float w, float h)
{

    // sets up the handles to be a box from 0,0 to the width and height of the image
    fHandles[0].x = 0.0f;
    fHandles[0].y = h;

    fHandles[1].x = w;
    fHandles[1].y = h;

    fHandles[2].x = w;
    fHandles[2].y = 0.0f;

    fHandles[3].x = 0.0f;
    fHandles[3].y = 0.0f;

    // this indicates the offset from 0,0 that the image is draw to the screen
    fDrawOffset.x = x;
    fDrawOffset.y = y;

    imageWidth = w;
    imageHeight = h;

}
//--------------------------------------------------------------
float CBoxAligner::adjustHandle(float mouseX, float mouseY)
{

    // find out which handle is closest to mouse and adjust that one
    int iHandle = 	findClosestHandle( mouseX,  mouseY);
    if(iHandle==-1)
        return false;

   	// account for the offset in mouse position based on where the handles are drawn
    fHandles[iHandle].x = mouseX - fDrawOffset.x;
    fHandles[iHandle].y = mouseY - fDrawOffset.y;
    fHandles[iHandle].x = ofMap(fHandles[iHandle].x, 0, 320, 0, imageWidth);
    fHandles[iHandle].y = ofMap(fHandles[iHandle].y, 0, 240, 0, imageHeight);

    return true;
}
//--------------------------------------------------------------
float CBoxAligner::findSelectionDistance(float mouseX, float mouseY)
{
// subtract the draw position so that mouse input makes sense
   mouseX -= fDrawOffset.x;
   mouseY -= fDrawOffset.y;
   mouseX = ofMap(mouseX, 0, 320, 0, imageWidth);
   mouseY = ofMap(mouseY, 0, 240, 0, imageHeight);

   float     closeDist    = sqrt( (fHandles[0].x-mouseX)*(fHandles[0].x-mouseX) + (fHandles[0].y-mouseY)*(fHandles[0].y-mouseY) );

   for( int i = 1; i < 4; i++)
   {
        float d = sqrt( (fHandles[i].x-mouseX)*(fHandles[i].x-mouseX) + (fHandles[i].y-mouseY)*(fHandles[i].y-mouseY) );
        if( d < closeDist )
        {
         closeDist = d;
        }

   }

   return closeDist;
}
//--------------------------------------------------------------
int  CBoxAligner::findClosestHandle(float mouseX, float mouseY)
{

   // subtract the draw position so that mouse input makes sense
   mouseX -= fDrawOffset.x;
   mouseY -= fDrawOffset.y;
   mouseX = ofMap(mouseX, 0, 320, 0, imageWidth);
   mouseY = ofMap(mouseY, 0, 240, 0, imageHeight);

   // start with the first handle
   int       iCloseId      = -1;
   float     fCloseDist    = sqrt( (fHandles[0].x-mouseX)*(fHandles[0].x-mouseX) + (fHandles[0].y-mouseY)*(fHandles[0].y-mouseY) );

   // loop to see which is closest
   for( int i = 0; i < 4; i++)
   {

        float fDist = sqrt( (fHandles[i].x-mouseX)*(fHandles[i].x-mouseX) + (fHandles[i].y-mouseY)*(fHandles[i].y-mouseY) );

        if( fDist <= fCloseDist && fDist < 90 )
        {
         fCloseDist = fDist;
         iCloseId   = i;
        }

   }

   // return id of closest
   return iCloseId;
}
//--------------------------------------------------------------
void CBoxAligner::draw( int x, int y, float radius )
{
		glPushMatrix();

        glTranslatef(fDrawOffset.x,fDrawOffset.y,0.0f);

        ofSetHexColor(0x89ff41);

        ofScale(1, 1, 1);

        // draw box
		glBegin( GL_LINE_STRIP );
		         glVertex2f(fHandles[0].x, fHandles[0].y);
		         glVertex2f(fHandles[1].x, fHandles[1].y);
	             glVertex2f(fHandles[2].x, fHandles[2].y);
		         glVertex2f(fHandles[3].x, fHandles[3].y);
		         glVertex2f(fHandles[0].x, fHandles[0].y);
        glEnd();

		// draw handles
		for( int i = 0; i < 4; i++)
        {
			
             ofRect( fHandles[i].x - radius / 2, fHandles[i].y - radius / 2, radius, radius); 
			
        }

		glPopMatrix();
}
