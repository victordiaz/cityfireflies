#include "testApp.h"
#include "constants.h"

//--------------------------------------------------------------
void testApp::setup(){

	myfont.loadFont("visitor1.ttf", 7); 
	backCountFont.loadFont("visitor1.ttf", 12);
	fondoImg.loadImage("images/juegofondo.png"); 
	//ofSetBackgroundAuto(true); 

	ofSetFrameRate(30);

	loadSettings(); 
	
	camWidth = 320;
	camHeight = 240;

	imgWidth = 320;
	imgHeight = 240;


	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
	#else
        vidPlayer.loadMovie("output.mov");
        vidPlayer.play();
	#endif

    sourceImg.allocate(320,240);
	grayImg.allocate(320,240);
	grayImgBg.allocate(320,240);
	grayImgDiff.allocate(320,240);
	grayImgW.allocate(320,240);
	grayImgT.allocate(320,240);


	//320, 240
	//matrix
	numCols = 16;
	numRows = 10;
	tileWidth = (int)(grayImg.width / numCols);
	tileHeight = (int)(grayImg.height / numRows);
	lastTimeMeasure = ofGetElapsedTimef();
	//cout << tileWidth << " " << tileHeight << endl;


	//box para el warping
	boxInputMatrix.setup( 360, 20, imgWidth, imgHeight);

	//bg remove
	bLearnBg = false;
	lastTimeMeasure = ofGetElapsedTimef();
	lastTimeMeasureFade = ofGetElapsedTimef();


	threshold = 202;
	thresholdDiff = 102;


	blobMin = 1;
	blobMax = 22;

	fadeN = 0;

	//mask
	leftOffset = 40;
	topOffset = 40;
	screenWidth = 192;
	halfWidth = ofGetWidth()/2;
	screenHeight = 157;
	bHeight = 16;
	bWidth = 12;
	aWidth = bWidth;



	//lights
	lights.resize(20);


	//320, 240
	numCols = 16;
	numRows = 10;
	tileWidth = (int)(grayImg.width / numCols);
	tileHeight = (int)(grayImg.height / numRows);

	tileWidthScreen = (int)(screenWidth / numCols);
	tileHeightScreen = (int)(screenHeight / numRows);

	//cout << tileWidth << " " << tileHeight << endl;


	resetMatrix();

	start_img.loadImage("images/login.png");
	loser_img.loadImage("images/loser.png");
	win_img.loadImage("images/win.png");

	// game status

	status_game=0;
	loser_counter=0;
	status_level=0;
	last_updated=0;
	timmer_pause=0;
	myMsgs.setup();

}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0, 0, 0); 

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


		//matriz de luz automenta
		for (int i = 0; i < numCols; i++) {
			for (int j = 0; j < numRows; j++) {
				amountActivity = grayImgT.countNonZeroInRegion(i * tileWidth, j * tileHeight, tileWidth, tileHeight);

				if (amountActivity > 1) {
					matrix[i][j] += 1; //amountActivity;

				}


				//cout << i << " " << j << " :" << matrix[i][j] << endl;
			}
		}


		//si pasa un rato se restan los valores de la matriz
		if (lastTimeMeasure + 0.1 < ofGetElapsedTimef()) {

			//matriz de luz
			for (int i = 0; i < numCols; i++) {
				for (int j = 0; j < numRows; j++) {

					if (matrix[i][j] > 0) {
///////////////////MI CODIGO AQUI
						my_enemy.cleanRegion(i,j);

						matrix[i][j] -= 1; //amountActivity;

					}

					cout << ofGetElapsedTimef() << endl;

				//cout << i << " " << j << " :" << matrix[i][j] << endl;
				}
			}

			if (fadeN > screenHeight) {
				fadeN = 0;
			} else {
				fadeN += 1;
			}

			lastTimeMeasure = ofGetElapsedTimef();
		}

	//
//		//si pasa un rato se restan los valores de la matriz
//		if (lastTimeMeasureFade + 0.001 < ofGetElapsedTimef()) {
//
//
//			if (fadeN > screenHeight) {
//				fadeN = 0;
//			} else {
//				fadeN += 1;
//			}
//
//			lastTimeMeasureFade = ofGetElapsedTimef();
//		}
//
//



	}
	
	if (ofGetElapsedTimeMillis()-last_updated >= BORN_TIME[status_level]) {
		status_update=true;
		last_updated=ofGetElapsedTimeMillis();
	}
	else{
		status_update=false;
	}
	
	if(status_game==1){
		status_time= TIME_WIN[status_level] - (ofGetElapsedTimef()-status_time_init);
		
	}
	
}

//--------------------------------------------------------------
void testApp::draw() { 
	
	
	
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetColor(0xffffff);
	
	
	
	fondoImg.draw(0, 0); 

	//mask
	ofPushMatrix();
	ofTranslate(topOffset, leftOffset, 0);


	//background
	ofFill();
	ofSetColor(0x000000);
	ofRect(0, 0, screenWidth, screenHeight);


	ofSetColor(0xFFFFFF);
	grayImgW.draw(0, 0, screenWidth, screenHeight);




	ofPushMatrix();
	ofTranslate(0,32);
	switch (status_game) {
		case 0: // Waiting to start
			ofSetColor(0xFFFFFF);
			//start_img.draw(0,0);
			if(status_update==true){ 
				cout << "update";
				if(my_enemy.countEnemies()<10){
					if (ofRandom(0,10)>6) 
						my_enemy.removeRandomOne();
					else{
						my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0); //creo bichos
					}
				}
				else{
					if (ofRandom(0,10)>3) 
						my_enemy.removeRandomOne();
				}
			}
			my_enemy.draw();
			myMsgs.drawMsgIntro1();
			
			break;
		case 1: //running		
			if(status_update==true){ 
				status_update=false;
				while(!my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0)); //be carefull with this line; if the screen is full can fall into an infinite loop
				int contador=my_enemy.countEnemies();
				printf("contador %i \n", contador);
				if(contador>ENEMIES_WIN[0]){
					status_game=2;
					break;
				}
			}
			if(status_time<=0){
				status_game=3;
				break;
			}
			
			my_enemy.draw();
			break;
			
		case 2: // lose
			cout << "I lose";
			
			loser_img.draw(0,0);
			if(timmer_pause==0){ //first time we start the timmer
				timmer_pause=ofGetElapsedTimef();	
			}
			else if(ofGetElapsedTimef() - timmer_pause >=SCREEN_CHANGE_TIME){
				status_game=0;
				my_enemy.restart();
				status_level=0;
				timmer_pause=0;
				status_time_init=ofGetElapsedTimef();
			}
			
			break;
			
		case 3: // win
			win_img.draw(0,0);
			if(timmer_pause==0){ //first time we start the timmer
				timmer_pause=ofGetElapsedTimef();	
			}
			else if(ofGetElapsedTimef() - timmer_pause >=SCREEN_CHANGE_TIME){
				my_enemy.restart();
				status_game=1;
				status_level>2 ? status_level=0 : status_level++;
				timmer_pause=0;
				status_time_init=ofGetElapsedTimef();
			}
			
			
			break;
			break;
		default:
			break;
	}
	



	ofPopMatrix();


	ofSetColor(0x000000);
	ofRect(0, 16, screenWidth, 16);
	ofSetColor(0xFFFFFF);
	myfont.drawString("CITY FIREFLIES", 52, 25);

	if(status_game==1){
		char fpsStr[40]; // an array of chars			
		sprintf(fpsStr, "%i",status_time );
		backCountFont.drawString(fpsStr, 90, 10);
	}


	//informacion de juego
	//ofSetColor(0xFF0000);
	//ofRect(leftOffset + 50, topOffset - 20, 50, 10);



	//unsused areas
	ofSetColor(0xFFFFFF);
	ofRect(0, 0, bWidth*3 - 1, bHeight*2);
	ofRect(bWidth*3 - 1, 0, bWidth*3 - 2, bHeight);
	ofRect(screenWidth-bWidth*6, 0, bWidth*3, bHeight);
	ofRect(screenWidth-bWidth*3, 0, bWidth*3, bHeight*2);
	ofPopMatrix();

	//
	ofSetColor(0xFFFFFF);
	grayImg.draw(360,20);
	grayImgW.draw(700,20);
	contourFinder.draw(700,20);

	//grayImgT.draw(360,280);
	grayImgDiff.draw(700, 375); 

	//contourFinder.draw(360,280);

	//grayDiff.draw(360,280);


	//blobs
	ofPushMatrix();
	glTranslated(700, 20, 0);

	for (int i = 0; i < contourFinder.nBlobs; i++) {
        contourFinder.blobs[i].draw(0,0);
		ofCircle(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y, 20);



		//printf("%f ", contourFinder.blobs[i].area);
    }



	ofPopMatrix();



	ofNoFill();
	//ofSetColor(200, 200, 200);


	//matriz de luz
	ofPushMatrix();
	//ofTranslate(700, 20);
	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
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


				ofSetColor(200, 200, 200);
				ofFill();
				ofPushMatrix();
				glTranslated(leftOffset, topOffset + 32, 0);
				ofRect(i * square_size, j * square_size, square_size, square_size);
				ofPopMatrix();


			}
			//cout << j * tileHeight << endl;
		}
	}
	ofPopMatrix();

	ofNoFill();




	//warp handles
    ofFill();
    boxInputMatrix.draw(360, 20);

	
	// report:
	ofSetColor(0x222222); 
	char reportStr[1024];
	sprintf(reportStr, "bg subtraction and blob detection\npress ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i, fps: %f \nnum blob min size %i max size %i", threshold, contourFinder.nBlobs, ofGetFrameRate(), blobMin, blobMax);
	ofDrawBitmapString(reportStr, 370, 570); 
	

}

void testApp::resetMatrix() {


	//matriz de luz reset
	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
			matrix[i][j] = 0; //amountActivity;


		}
	}




} 


void testApp::loadSettings() { 
	
	if( XML.loadFile("mySettings.xml") ){
		//message = "mySettings.xml loaded!";
	}else{
		//message = "unable to load mySettings.xml check data/ folder";
	}
	
	
	boxInputMatrix.setTopLeftX(XML.getValue("CAPTUREREGION:11:X", 0)); 
	boxInputMatrix.setTopLeftY(XML.getValue("CAPTUREREGION:11:Y", 0)); 
	
	boxInputMatrix.setBottomLeftX(XML.getValue("CAPTUREREGION:12:X", 0)); 
	boxInputMatrix.setBottomLeftY(XML.getValue("CAPTUREREGION:12:Y", imgWidth)); 
	
	boxInputMatrix.setTopRightX(XML.getValue("CAPTUREREGION:21:X", 0));  
	boxInputMatrix.setTopRightY(XML.getValue("CAPTUREREGION:21:Y", imgHeight));   
	
	boxInputMatrix.setBottomRightX(XML.getValue("CAPTUREREGION:22:X", imgWidth)); 
	boxInputMatrix.setBottomRightY(XML.getValue("CAPTUREREGION:22:Y", imgHeight)); 
	
	
	
	
} 

void testApp::saveSettings() { 
	
	XML.setValue("CAPTUREREGION:11:X", boxInputMatrix.getTopLeftX()); 
	XML.setValue("CAPTUREREGION:11:Y", boxInputMatrix.getTopLeftY()); 
	
	XML.setValue("CAPTUREREGION:12:X", boxInputMatrix.getBottomLeftX()); 
	XML.setValue("CAPTUREREGION:12:Y", boxInputMatrix.getBottomLeftY()); 
	
	XML.setValue("CAPTUREREGION:21:X", boxInputMatrix.getTopRightX()); 
	XML.setValue("CAPTUREREGION:21:Y", boxInputMatrix.getTopRightY()); 
	
	XML.setValue("CAPTUREREGION:22:X", boxInputMatrix.getBottomRightX()); 
	XML.setValue("CAPTUREREGION:22:Y", boxInputMatrix.getBottomRightY()); 
	XML.saveFile("mySettings.xml"); 
	
} 



//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	switch (key){
		case ' ':
			bLearnBg = true;


			#ifdef _USE_LIVE_VIDEO

			#else
				resetMatrix();
				vidPlayer.setPosition(0);
			#endif


			break;
		case '+':
			thresholdDiff++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			thresholdDiff--;
			if (threshold < 0) threshold = 0;
			break;

		case 'c':
			//my_enemy.cleanRegion(ofRandom(0,columnas),ofRandom(0,filas),20,0);
			break;
		case 's':
			if(status_game==0 ) //press s to start when waiting in main screen
			{	status_game=1;
				status_time=TIME_WIN[status_level];
				status_time_init=ofGetElapsedTimef();
				//=ofGetElapsedTimef();
				
			}
			if(status_game==2 || status_game==3)  // press s to start when waiting in winner screen
			{	status_game=0;
				status_time=TIME_WIN[status_level];
				status_time_init=ofGetElapsedTimef();
				//=ofGetElapsedTimef();
				my_enemy.restart();
			}
			
		case 'k': 
			saveSettings(); 
			break; 
			
		case 'l':
			loadSettings(); 
			break;


	}  


} 



//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {

	//blobMin = x;
	//blobMax = y;

} 

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {


    boxInputMatrix.adjustHandle(x, y);
        //boxInputMatrix.adjustHandle(x, y);


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

