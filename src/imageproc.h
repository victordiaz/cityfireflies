/*
 *  imageproc.h
 *  plaza
 *
 *  Created by biquillo on 21/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _IMAGEPROC_
#define _IMAGEPROC_
#include "ofMain.h"
#include "constants.h" 
#include "ofxOpenCv.h"
#include "boxAlign.h" 
#include <math.h> 
#include "ofMath.h" 


class imageproc { 
public:
	imageproc(); 

	void restart(); 
	void update(); 
	void drawGameCamera(); 
	void drawFeedback(); 
	void resetMatrix(); 
	
	void keyPressed  (int key);
	void mouseDragged(int x, int y, int button);
	
	
	#ifdef _USE_LIVE_VIDEO
		ofVideoGrabber 		vidGrabber;
	#else
		ofVideoPlayer 		vidPlayer;
	#endif
	
	
	int camWidth;
	int camHeight;
	
	int imgWidth;
	int imgHeight;
	
	
	ofxCvColorImage		sourceImg;
	
	ofxCvGrayscaleImage 	grayImg;
	ofxCvGrayscaleImage 	grayImgBg;
	ofxCvGrayscaleImage 	grayImgDiff;
	
	ofxCvGrayscaleImage 	grayImgT;
	ofxCvGrayscaleImage 	grayImgW;
	
	//ofxCvGrayscaleImage 	grayBg;
	//ofxCvGrayscaleImage 	grayDiff;
	
	ofxCvContourFinder 	contourFinder;
	
	
	int blobMin;
	int blobMax;
	
	
	int 				threshold;
	int 				thresholdDiff;
	
	bool				bLearnBg;
	
	
	
	ofPoint dstPts[4]; 
	
	
	
	//matrix de alineacion 
	CBoxAligner         boxInputMatrix;
	
	
	
	int numCols;
	int numRows;
	int tileWidth;
	int tileHeight; 
	
	ofTrueTypeFont myfont; 
	
	
	
	float matrix[15][15];
	char tileval[255];
	float amountActivity;

	
	int tileWidthScreen;
	int tileHeightScreen;
	
	
};



#endif 

