/*
 *  imageproc.cpp
 *  plaza
 *
 *  Created by biquillo on 21/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */



#include "imageproc.h" 



//Constructor
void imageproc::setup(){

	myfont.loadFont("visitor1.ttf", 7,false,false,false); 
	
	camWidth = 320;
	camHeight = 240;
	
	imgWidth = 320;
	imgHeight = 240;
	
	
	#ifdef _USE_LIVE_VIDEO
		vidGrabber.setVerbose(true);
		vidGrabber.initGrabber(camWidth, camHeight); 
	#else
		vidPlayer.loadMovie("output.mov");
		vidPlayer.play();
	#endif
	
    sourceImg.allocate(imgWidth,imgHeight); 
	grayImg.allocate(imgWidth,imgHeight); 
	grayImgBg.allocate(imgWidth,imgHeight); 
	grayImgDiff.allocate(imgWidth,imgHeight); 
	grayImgW.allocate(imgWidth,imgHeight); 
	grayImgT.allocate(imgWidth,imgHeight); 
	
	//320, 240
	//matrix
	tileWidth = (int)(grayImg.width / columnas);
	tileHeight = (int)(grayImg.height / filas); 
	
	
	//cout << tileWidth << " " << tileHeight << endl; 

	
	//box para el warping
	boxInputMatrix.setup( 360, 20, imgWidth, imgHeight);
	
	//bg remove
	bLearnBg = false;
	//lastTimeMeasure = ofGetElapsedTimef();
	//lastTimeMeasureFade = ofGetElapsedTimef();
	
	
	
	blobMin = 1;
	blobMax = 22;
	
	threshold = 202	; 
	thresholdDiff = 102; 
	darken_value=100;
	resetMatrix(); 
	
	//cout << "hola2" << endl; 
	
}


void imageproc::restart() { 

} 

void imageproc::update() { 
	
    bool bNewFrame = false;
	
	#ifdef _USE_LIVE_VIDEO
		vidGrabber.grabFrame();
		bNewFrame = vidGrabber.isFrameNew();
	#else
		vidPlayer.idleMovie();
		bNewFrame = vidPlayer.isFrameNew();
	#endif
	
	if (bNewFrame){
		
	#ifdef _USE_LIVE_VIDEO
		sourceImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	#else
		sourceImg.setFromPixels(vidPlayer.getPixels(), 320,240);
	#endif
		
		
		//handlers
        ofPoint dstPts[4] = {
            ofPoint(0, imgHeight, 0),
            ofPoint(imgWidth, imgHeight, 0),
            ofPoint(imgWidth, 0, 0),
            ofPoint(0, 0, 0)
        };
		
		
		//warp
        grayImg = sourceImg;
        grayImgW.warpIntoMe(grayImg, boxInputMatrix.fHandles, dstPts );
		grayImgW.mirror(false, true);
		
		
		if (bLearnBg == true){
			grayImgBg = grayImgW;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBg = false;
		}
		
		
		// take the abs value of the difference between background and incoming and then threshold:
		grayImgDiff.absDiff(grayImgBg, grayImgW);
		grayImgDiff.threshold(thresholdDiff);
		
		
		
		//thresholding
		grayImgT = grayImgW;
		grayImgT.threshold(threshold);
		
		contourFinder.findContours(grayImgT, blobMin, blobMax, 100, false);	// find holes
		
		
		//matriz de luz 
		for (int i = 0; i < columnas; i++) {
			for (int j = 0; j < filas; j++) {
				amountActivity = grayImgT.countNonZeroInRegion(i * tileWidth, j * tileHeight, tileWidth, tileHeight);
				
				if (amountActivity > 1) { 
					if (matrix[i][j] < 15) { 
						matrix[i][j] += 1; //amountActivity; 
					} 
				}
			}
		} 
		
		
		
	} 
		
} 



//--------------------------------------------------------------
void imageproc::drawGameCamera() {
	
	//imagen de la camara en el juego 
	ofSetHexColor(0xFFFFFF);
	grayImgW.draw(0, 32, screenWidth, 125); 
    ofPushStyle();
    ofEnableAlphaBlending();
	ofSetColor(0, 0, 0,darken_value); //We tint the image in black a little to avoid too much bright on the screen
	ofRect(0, 32, screenWidth, 125);
    ofPopStyle();
	
} 


//--------------------------------------------------------------
void imageproc::drawFeedback() {  
	
	
	
	//feedback del procesado 
	ofSetHexColor(0xFFFFFF);
	grayImg.draw(360,20);
	grayImgW.draw(700,20);
	contourFinder.draw(700,20);
	grayImgDiff.draw(700, 375); 
	
	
	//blobs
	ofPushMatrix();
	glTranslated(700, 20, 0);
	
	for (int i = 0; i < contourFinder.nBlobs; i++) {
        contourFinder.blobs[i].draw(0,0);
        cout << "blobs size: "<< contourFinder.blobs[i].area << "\n";
		ofCircle(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y, 20);
    }
	ofPopMatrix();
	
	
	//matriz de luz
	ofPushMatrix(); 
	for (int i = 0; i < columnas; i++) { 
		for (int j = 0; j < filas; j++) {
			//ofSetColor(200, 200, 200, 255);
			ofFill();
			ofSetColor(100, 100, ofMap(matrix[i][j], 100, 800, 100, 255, false), 200);
			ofEnableAlphaBlending();
			ofRect(700 + i * tileWidth,  20 + j * tileHeight, tileWidth, tileHeight);
			sprintf(tileval, "%d", (int)matrix[i][j]);
			ofSetColor(0, 0, 255, 255);
			myfont.drawString(tileval, 710 + i * tileWidth, 30 + j * tileHeight);
			
			if(matrix[i][j] > 1) {
				int qi = i;
				int qj = j;
				
				ofPushStyle(); 
				energy = ofMap(matrix[i][j], 0, 7, 0, 255, true); 
				ofSetColor(55, 205, 242, energy);  
				ofFill();
				ofPushMatrix(); 
				//TODO 
				glTranslated(40, 40 + 32, 0); 
				ofRect(i * square_size, j * square_size, square_size, square_size); 
				ofPopMatrix(); 
				ofPopStyle(); 
			
			}
		} 
	}
	ofPopMatrix(); 
	
	
	
	//sprintf(t, "Adjust threshold using U and I keys"); 
	sprintf(tD, "threshold:  %d", threshold); 


	ofPushStyle(); 
	ofSetColor(255, 255, 255); 
	//myfont.drawString(t, 200, 500); 
	//myfont.drawString(tD, 200, 320); 
	ofPopStyle(); 

	
	//warp handles
    ofFill();
    boxInputMatrix.draw(360, 20);
	
	
	
} 



//--------------------------------------------------------------
void imageproc::resetMatrix() { 
	
	
	//matriz de luz reset
	for (int i = 0; i < columnas; i++) {
		for (int j = 0; j < filas; j++) {
			matrix[i][j] = 0; //amountActivity; 
		}
	} 
	
	
	
}  


	
	
	//--------------------------------------------------------------
	void imageproc::keyPressed  (int key){
		
		switch (key){
			case ' ':
				bLearnBg = true;
				
				
			#ifdef _USE_LIVE_VIDEO
				
			#else
				resetMatrix();
				vidPlayer.setPosition(0);
			#endif
				
				
				break;
			case 'u':
				threshold++;
				if (threshold > 255) threshold = 255;
				break;
			case 'i':
				threshold--;
				if (threshold < 0) threshold = 0;
				break; 
				
			case 'o':
				thresholdDiff++;
				if (threshold > 255) threshold = 255;
				break;
			case 'p':
				thresholdDiff--;
				if (threshold < 0) threshold = 0;
				break; 
				
				
		
		}  
		
		
	} 
	

	//--------------------------------------------------------------
	void imageproc::mouseDragged(int x, int y, int button) {
		
		
		boxInputMatrix.adjustHandle(x, y);
        //boxInputMatrix.adjustHandle(x, y);
		
		
	}
	
