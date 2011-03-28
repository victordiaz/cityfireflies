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
	lastTimeMeasure = ofGetElapsedTimef();
	//cout << tileWidth << " " << tileHeight << endl;

	fadeN = 0;
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
	time_intro_msgs=0;
	status_draw_msg1=true;

}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0, 0, 0); 
	mImageproc.update(); 
	
		//si pasa un rato se restan los valores de la matriz
		if (lastTimeMeasure + 0.1 < ofGetElapsedTimef()) {

			//matriz de luz
			for (int i = 0; i < columnas; i++) { 
				for (int j = 0; j < filas; j++) { 

					if (mImageproc.matrix[i][j] > 0) { 
						if(my_enemy.cleanRegion(i,j)==true){
							if (status_first_dead==false && status_game==0 && ON_PC==false) {
								status_first_dead=true;
								status_time=TIME_WIN[status_level];
								status_time_init=ofGetElapsedTimef();
								drawing_text_finished_flag=false;								
							}								
						}
						mImageproc.matrix[i][j] -= 1; //amountActivity; 

					}				
					
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
	
	if(ofGetElapsedTimef()>time_intro_msgs){
		status_draw_msg1=true;
	}
	myMsgs.update();
	
}

//--------------------------------------------------------------
void testApp::draw() { 
	
	ofSetColor(0xffffff); //fondo 
	fondoImg.draw(0, 0); //fondo bonito 
	
	//mask
	ofPushMatrix();
	ofTranslate(topOffset, leftOffset, 0); 
	
	//la camara que sale en el juego 
	mImageproc.drawGameCamera(); 
	ofPopMatrix(); 
	
		
	
	//muestra las imagenes procesadas  
	mImageproc.drawFeedback(); 

	//mask
	ofPushMatrix();
	ofTranslate(topOffset, leftOffset, 0); 
	
	//JUEGO 
	ofPushMatrix();
	ofTranslate(0,32);
	std::ostringstream oss2;
	switch (status_game) {
		case 0: // Waiting to start, nobody is playing and we show random messages inviting people.
			if (status_first_dead==true) {
				status_game=1;
				status_first_dead=false;
			}
			ofSetColor(0xFFFFFF);
			if(status_update==true){ 
				if(my_enemy.countEnemies()<10){ // In this status we don't like to have many evil enemies around
					if (ofRandom(0,10)>6)  //So sometimes I remove
						my_enemy.removeRandomOne();
					else{
						my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0); //and sometimes I make another one. 
					}
				}
				else{
					if (ofRandom(0,10)>3) 
						my_enemy.removeRandomOne();
				}
			}
			my_enemy.draw();
			break;

		case 1: //running This is the gameplay state.		
			if(status_update==true){ 
				status_update=false;
				while(!my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0) ); 
				int contador=my_enemy.countEnemies();
				if(contador>ENEMIES_WIN[status_level]){ //condicion para perder el juego
					status_game=2;
					break;
				}
			}
			if(status_time<=0){ //Cuando termina el tiempo gana;
				status_game=3;
				break;
			}					
			my_enemy.draw();
			if (!drawing_text_finished_flag && status_level==0) {
				drawing_text_finished_flag=myMsgs.initVideo();
			}
			myMsgs.drawButtomMenu(status_time ,status_level );
			break;
			
		case 2: // you loose a level. Have to start again.
			drawing_text_finished_flag=myMsgs.drawFullScreenText("Perdedor");
			if(drawing_text_finished_flag){
				status_game=0;
				my_enemy.restart();
				status_level=0;
				status_time_init=ofGetElapsedTimef();
			}			
			break;
			
		case 3: // you win a level. Go to the next one.
			oss2 << "Level " << status_level+1 <<"/2" ;
			enemy_transition[0].loadImage("images/malo1_40px.png");
			if(status_level>=MAX_LEVELS){ //if you win the level MAXLEVEL you already won the game so it is over.
				status_level=0; //restart the level
				status_game=4;	
			}
			else{
				if(myMsgs.levelVideo(enemy_transition[0], start_img, oss2.str() )){
					my_enemy.restart();
					status_game=4;
					status_level++;
				}
			}
			status_time_init=ofGetElapsedTimef();

			//drawing_text_finished_flag=myMsgs.drawFullScreenText( "You Win! Next Level");
			/**if (drawing_text_finished_flag){ //Cuando se cumple el tiempo
				my_enemy.restart();
				status_game=4;
				status_level>2 ? status_level=0 : status_level++;
				status_time_init=ofGetElapsedTimef();
			}		**/	
		break;

		case 4: //Prepare the game for the next level
			//kind of message----
			if (status_level==0) { //All levels are finished
				drawing_text_finished_flag=myMsgs.drawFullScreenText( "You've won \n Congratulations!");
				if (drawing_text_finished_flag) {
					status_game=0;
					my_enemy.restart();
					drawing_text_finished_flag=false;
				}
			}
			else {//set up next level
				status_game=1;
				my_enemy.restart();
				my_enemy.newEnemies(ENEMIES_BY_LEVEL[status_level]);
			}	
			status_time_init=ofGetElapsedTimef();
			
			break;
			
		default:
			break;
	}
	



	ofPopMatrix();


	ofSetColor(0x000000);
	ofRect(0, 16, screenWidth, 16);
	ofSetColor(0xFFFFFF);
	myfont.drawString("CITY FIREFLIES", 52, 25); 
	//ofPopMatrix(); 


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
} 


void testApp::loadSettings() { 
	
	
	if( XML.loadFile("mySettings.xml") ){
		//message = "mySettings.xml loaded!"; 
		
		cout << "qq" << endl; 
		mImageproc.boxInputMatrix.setTopLeftX(XML.getValue("CAPTUREREGION:r11:X", 0)); 
		mImageproc.boxInputMatrix.setTopLeftY(XML.getValue("CAPTUREREGION:r11:Y", 0)); 
		
		mImageproc.boxInputMatrix.setBottomLeftX(XML.getValue("CAPTUREREGION:r12:X", 0)); 
		mImageproc.boxInputMatrix.setBottomLeftY(XML.getValue("CAPTUREREGION:r12:Y", mImageproc.imgWidth)); 
		
		mImageproc.boxInputMatrix.setTopRightX(XML.getValue("CAPTUREREGION:r21:X", 0));  
		mImageproc.boxInputMatrix.setTopRightY(XML.getValue("CAPTUREREGION:r21:Y", mImageproc.imgHeight));   
		
		mImageproc.boxInputMatrix.setBottomRightX(XML.getValue("CAPTUREREGION:r22:X", mImageproc.imgWidth)); 
		mImageproc.boxInputMatrix.setBottomRightY(XML.getValue("CAPTUREREGION:r22:Y", mImageproc.imgHeight)); 
		
		mImageproc.threshold = XML.getValue("IMAGESETTINGS:THRESHOLD", 202); 
		mImageproc.thresholdDiff = XML.getValue("IMAGESETTINGS:THRESHOLDDIFF", 102); 
		mImageproc.blobMax = XML.getValue("IMAGESETTINGS:BLOBMAX", 1); 
		mImageproc.blobMin = XML.getValue("IMAGESETTINGS:BLOBMIN", 22); 
		
	}else{ 
		cout << "qq1" << endl; 
		//message = "unable to load mySettings.xml check data/ folder";
	}
	

	
	
} 

void testApp::saveSettings() { 
	
	XML.clear();
	XML.setValue("CAPTUREREGION:r11:X", mImageproc.boxInputMatrix.getTopLeftX()); 
	XML.setValue("CAPTUREREGION:r11:Y", mImageproc.boxInputMatrix.getTopLeftY()); 
	
	XML.setValue("CAPTUREREGION:r12:X", mImageproc.boxInputMatrix.getBottomLeftX()); 
	XML.setValue("CAPTUREREGION:r12:Y", mImageproc.boxInputMatrix.getBottomLeftY()); 
	
	XML.setValue("CAPTUREREGION:r21:X", mImageproc.boxInputMatrix.getTopRightX()); 
	XML.setValue("CAPTUREREGION:r21:Y", mImageproc.boxInputMatrix.getTopRightY()); 
	
	XML.setValue("CAPTUREREGION:r22:X", mImageproc.boxInputMatrix.getBottomRightX()); 
	XML.setValue("CAPTUREREGION:r22:Y", mImageproc.boxInputMatrix.getBottomRightY()); 
	
	XML.setValue("IMAGESETTINGS:THRESHOLD", mImageproc.threshold); 
	XML.setValue("IMAGESETTINGS:THRESHOLDDIFF", mImageproc.thresholdDiff); 
	XML.setValue("IMAGESETTINGS:BLOBMAX", mImageproc.blobMax); 
	XML.setValue("IMAGESETTINGS:BLOBMIN", mImageproc.blobMin); 
	
	XML.saveFile("mySettings.xml"); 
	
} 



//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	mImageproc.keyPressed(key); //le paso a image proc lo que se ha pulsado 
	
	switch (key) { 
	
		case 'c':
			//my_enemy.cleanRegion(ofRandom(0,columnas),ofRandom(0,filas),20,0);
			break;
		case 's':
			if(status_game==0 ) //press s to start when waiting in main screen
			{	status_game=1;
				status_time=TIME_WIN[status_level];
				status_time_init=ofGetElapsedTimef();
				drawing_text_finished_flag=false;
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

	mImageproc.mouseDragged(x, y, button); 
  
	
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

