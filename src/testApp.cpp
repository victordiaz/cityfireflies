#include "testApp.h"
#include "constants.h"
#include "ofxSimpleGuiToo.h"

/**
using Poco::Logger;
using Poco::FileChannel;
using Poco::AutoPtr;
using Poco::NumberFormatter;**/
//--------------------------------------------------------------
void testApp::setup(){
    //ofSetDataPathRoot("gamejam/plaza/bin/");
	//ofEnableSmoothing();
    //ofDisableDataPath();

	myfont.loadFont("visitor2.ttf", 12, false,false,false); 
	backCountFont.loadFont("visitor2.ttf", 18, false,false,false);
	fondoImg.loadImage("images/juegofondo.png"); 
	//ofSetBackgroundAuto(true); 

	ofSetFrameRate(30);

    mImageproc.setup();
    my_enemy.setup();
    myRanking.setup();
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
    status_time=TIME_WIN[status_level];
	last_updated=0;
	timmer_pause=0;

	time_intro_msgs=0;
	status_draw_msg1=true; 
	msg_type = 0; 
	
//settings
	//BORN_TIME={1500,1000,700};
	with_explosions=true;
	//mparticles.setup();
	loadSettings(); 
    myMsgs.setup();
    
 /**   
	AutoPtr<FileChannel> pChannel(new FileChannel);
	pChannel->setProperty("path", "../../../data/city_fireflies.log");
	pChannel->setProperty("rotation", "2 M");
	pChannel->setProperty("archive", "timestamp");
	
	Logger::root().setChannel(pChannel);	
	Logger& logger =  Logger::get("TestLogger"); // inherits root channe
	Poco::LocalDateTime now;
	string timestamp = Poco::DateTimeFormatter::format(now, s_dateAndTimeFormat)+" ";
	logger.information(timestamp + "Running");
	mlogger = &logger;
    **/
    //GUI
    saveButton=false;    
    //
    gui.addSlider("Threshold (230 rec)", mImageproc.threshold, 210, 255);	
    gui.addSlider("Darken feedback Img", mImageproc.darken_value, 50, 200);	
    //gui.addSlider("Min Area light", mImageproc.blobMin, 0, 4);	
    gui.addSlider("Max Area light", mImageproc.minPuntos, 0, 10);
    gui.addSlider("Max Area light", mImageproc.maxPuntos, 1, 40);
	//gui.addSlider("Max Area light", mImageproc.blobMax, 1, 30);
    gui.addToggle("explosions", with_explosions);
    gui.addButton("Save Settings \n (including playfield \n borders)",saveButton );
    gui.addFPSCounter();
    ofPushMatrix();
    ofTranslate(300, 200); 
    gui.show();
    ofPopMatrix();
    ofSetLogLevel(OF_LOG_NOTICE); 
    ofLogToFile("city_fireflies.log",true) ;
   // ofLog() << ":data:start::" <<ofGetDay()<<":"<<ofGetMonth()<<":"<< ofGetHours()<<":"<<ofGetHours()<<":"<<ofGetMinutes()<<":"<<ofGetSeconds() <<  "New Game " ;

  //  ofLogToFile("logfile3.txt",true) ;
    
    
    
    
    fullscreen = false; 
    //myOfxFBOTextureCenter.allocate( 192, 157 , GL_RGB);  
    
    myOfxFBOTextureCenter.allocate(192, 157 ,GL_RGB);
    myPerfectPixelsRescale.setSize(5, 5, myOfxFBOTextureCenter.getWidth(), myOfxFBOTextureCenter.getHeight());
    buffer2= (unsigned char* )calloc(sizeof(unsigned char), ofGetWidth()*ofGetHeight()*16);



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
							if (status_first_dead==false && status_game==0 /** && ON_PC==false **/) { //set the game to the level0 status
								status_first_dead=true;
								status_time=TIME_WIN[status_level];
								status_time_init=ofGetElapsedTimef();
								drawing_text_finished_flag=false;	
								//mlogger.information("bicho muerto");
								//Poco::LocalDateTime now;
								gameStartTime = ofGetElapsedTimef();
								//mlogger->information(Poco::DateTimeFormatter::format(now, s_dateAndTimeFormat)+" " + "New user: Starting Game");
                                ofLog() << ":data:start::" <<ofGetDay()<<":"<<ofGetMonth()<<":"<< ofGetHours()<<":"<<ofGetHours()<<":"<<ofGetMinutes()<<":"<<ofGetSeconds() << "New user: Starting Game" ;
							}	
							if(with_explosions) mparticles.addEmitter(i*square_size+6,j*square_size+6);
						}
						mImageproc.matrix[i][j] -= 1; //amountActivity; 

					}				
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
    if(saveButton){
        saveSettings();
        saveButton=false;
    }
    
	myMsgs.update();
	mparticles.update();
	
}

//--------------------------------------------------------------
void testApp::draw() { 

	//fondoImg.draw(0, 0); //fondo bonito 


	//mask

	ofPushMatrix();
	ofTranslate(topOffset, leftOffset, 0); 
	
	
	//la camara que sale en el juego 
	
	ofSetColor(0,0,0);
	ofRect(68, 0, 52, 16); //rectangulo negro
	
	ofPopMatrix(); 
	
    
	
	//muestra las imagenes procesadas  
	//mImageproc.drawFeedback(); 
    
	//mask
	ofPushMatrix();
	ofTranslate(topOffset, leftOffset, 0); 
    
    
	//JUEGO 
	ofPushMatrix(); 
    
    
    
  //  myOfxFBOTextureCenter.clear();  //*************** 
    
    myOfxFBOTextureCenter.begin(); //*************** 
    ofClear(0,0,0);
	ofSetHexColor(0x000000); 
	ofRect(0, 16, screenWidth, 16);
	
    ofSetHexColor(0xFFFFFF); 
	myfont.drawString("CITYFIREFLIES.COM", 40, 25); //estaba a 52, 25 
    
    mImageproc.drawGameCamera(); 
    mImageproc.drawLitlesquares(); 
    
	ofTranslate(0,32);
	std::ostringstream oss2;
	switch (status_game) {
		case 0: // Waiting to start, nobody is playing and we show random messages inviting people.
			if (status_first_dead==true) {				
				status_game=1;
				my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0);
				my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0);
				status_first_dead=false;
				break;
			}
			ofSetHexColor(0xFFFFFF);
			if(status_update==true){ 
				if (my_enemy.countEnemies()>0 && my_enemy.countEnemies()<10) { // with less than 10 we just make
					my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0);
				}
				else if(my_enemy.countEnemies()<17){ // In this status we don't like to have many evil enemies around so between 10 and 17 we create and remove randomly
					if (ofRandom(0,10)>7)  //So sometimes I remove
						my_enemy.removeRandomOne();
					else{
						my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0); //and sometimes I make another one. 
					}
				}
				else{
					if (ofRandom(0,10)>9)  //with more than 17 we only delete
						my_enemy.removeRandomOne();
				}
			}
			my_enemy.draw(status_level);
			if(status_draw_msg1 && msg_type % 2==0){
				if(myMsgs.idleVideo_es() ){
					time_intro_msgs=ofGetElapsedTimef()+20;
					status_draw_msg1=false; 
					msg_type = msg_type + 1; 
				}
			}
			else if (status_draw_msg1 && msg_type % 2==1)
			{
				if(myMsgs.idleVideo_en() ){
					time_intro_msgs=ofGetElapsedTimef()+30;
					status_draw_msg1=false; 
					msg_type = msg_type + 1; 
				}				
			}		
			
			break;

		case 1: //running: This is the gameplay state.		
			if(status_update==true){ 
				status_update=false;
				while(!my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0) ); 
				int contador=my_enemy.countEnemies();
					if(contador==1){ //¿pq es 1 y no 0 misterios de la vida?
						status_game=3;
						break;
					}
					else if(status_time<=0){
						status_game=2;
						break;
					}					
				//}
			}
			/**if(status_time<=0 && ON_PC){ //Cuando termina el tiempo gana;
				status_game=3;
				break;
			}**/					
			my_enemy.draw(status_level);
			mparticles.draw();
			if (!drawing_text_finished_flag && status_level==0) {
				//drawing_text_finished_flag=myMsgs.initVideo();
				drawing_text_finished_flag=myMsgs.drawFullScreenBlink();
			}
			myMsgs.drawButtomMenu(status_time ,status_level );
			break;
			
		case 2: // you loose a level. Have to start again.
            if(      drawing_text_finished_flag == false)
                drawing_text_finished_flag=myMsgs.looseVideo(); // drawFullScreenText("Perdedor");
            
			if(drawing_text_finished_flag && !drawing_ranking_finished_flag){                
                drawing_ranking_finished_flag=myRanking.draw();                
            }
            if(drawing_text_finished_flag && drawing_ranking_finished_flag){
                
				//Poco::LocalDateTime now;
				float diferencia= ofGetElapsedTimef() - gameStartTime;
				//mlogger->information(Poco::DateTimeFormatter::format(now, s_dateAndTimeFormat) + " " + "End game in level: " + NumberFormatter::format(status_level)+ "enemies:"+ NumberFormatter::format(my_enemy.countEnemies() )+ " length: " + NumberFormatter::format(diferencia) );
                ofLog() << ":data:end:" << my_enemy.countEnemies()<< ":"<< status_level << ":" <<ofGetDay()<<":"<<ofGetMonth()<<":"<< ofGetHours()<<":"<<ofGetHours()<<":"<<ofGetMinutes()<<":"<<ofGetSeconds() << "End game" ;
				status_game=0;
				my_enemy.restart();
				status_level=0;
                drawing_ranking_finished_flag=false;
                drawing_text_finished_flag=false;
                status_time_init=ofGetElapsedTimef();
			}			
			break;
			
		case 3: // you win a level. Go to the next one.
			oss2 << "Level " << status_level+1 << "/2" ;
			enemy_transition[0].loadImage("images/malo1_40px.png");
			if(status_level>=MAX_LEVELS){ //if you win the level MAXLEVEL you already won the game so it is over.
				status_level=0; //restart the level
				status_game=4;	
				//	Poco::LocalDateTime now;
					float diferencia= ofGetElapsedTimef() - gameStartTime;
					//mlogger->information(Poco::DateTimeFormatter::format(now, s_dateAndTimeFormat) + " " + "Win game length: " + NumberFormatter::format(diferencia) );
                ofLog() << ":data:win:" << diferencia<< ":" <<ofGetDay()<<":"<<ofGetMonth()<<":"<< ofGetHours()<<":"<<ofGetHours()<<":"<<ofGetMinutes()<<":"<<ofGetSeconds() << "End game" ;
                    rankingPosition=myRanking.addTime(diferencia);

			}
			else{
				if(myMsgs.levelVideo(enemy_transition[0], start_img, oss2.str() )){
                    cout << "video falso";
					my_enemy.restart();
					status_game=4;
					status_level++;
				}
			}
			status_time_init=ofGetElapsedTimef();


		break;

		case 4: //Prepare the game for the next level
			//kind of message----
			if (status_level==0) { //All levels are finished
                if(drawing_text_finished_flag == false ){
                    drawing_text_finished_flag=myMsgs.finVideo(); //myMsgs.drawFullScreenText( "You've won \n Congratulations!");
                }
                if( drawing_text_finished_flag && ! drawing_ranking_finished_flag ) {
                    if(rankingPosition>4){
                       drawing_ranking_finished_flag=myRanking.draw(); 
                    }else{
                        drawing_ranking_finished_flag=myRanking.drawCongrats(rankingPosition); 
                    }
                }                
				if (drawing_text_finished_flag && drawing_ranking_finished_flag) {
					status_game=0;
					my_enemy.restart();
                    drawing_ranking_finished_flag=false;
                    drawing_text_finished_flag=false;
                    rankingPosition=6;
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


	//ofPopMatrix(); 


	/* 
	if(status_game==1){
		char fpsStr[40]; // an array of chars			
		sprintf(fpsStr, "%i",status_time );
		backCountFont.drawString(fpsStr, 90, 10);
	} 
	*/ 
	

	//informacion de juego
	//ofSetColor(0xFF0000);
	//ofRect(leftOffset + 50, topOffset - 20, 50, 10);



	//unsused areas
/**	ofSetHexColor(0xFFFFFF);
	ofRect(0, 0, bWidth*3 - 1, bHeight*2);
	ofRect(bWidth*3 - 1, 0, bWidth*3 - 2, bHeight);	
	ofRect(screenWidth-bWidth*6, 0, bWidth*3, bHeight);
	ofRect(screenWidth-bWidth*3, 0, bWidth*3, bHeight*2);**/
	ofPopMatrix(); 
	
    ofPushMatrix();
	ofTranslate(topOffset, leftOffset, 0); 
		myOfxFBOTextureCenter.end();

    //ofTranslate(300, 200);  
    
    ofPopMatrix(); 
    
    
    
    
    if (fullscreen) { 
        ofFill(); 
        ofSetColor(0, 0, 0); 
        ofRect(0, 0, ofGetWidth(), ofGetHeight()); 
        ofPixels mpiksels;
        //mpiksels.allocate(192,157,3);  
        
        myOfxFBOTextureCenter.readToPixels(mpiksels);
        
       // myPerfectPixelsRescale.resample( (unsigned char *)myOfxFBOTextureCenter.getPixels(3,buffer2) );  //*************** 
        myPerfectPixelsRescale.resample( (unsigned char *)mpiksels.getPixels() );
        myPerfectPixelsRescale.getImage();  //*************** 
        ofPushMatrix();
        ofRotateX(180);
        ofTranslate(0, -800);
        ofSetColor(255, 255, 255);
        myPerfectPixelsRescale.draw(0, 0);  //*************** 

        ofPopMatrix();

    } else { 
        //mImageproc.drawGameCamera(); 
        ofSetHexColor(0xffffff); 
		fondoImg.draw(0, 0); //fondo bonito 
        ofSetHexColor(0xFFFFFF); 
        myOfxFBOTextureCenter.draw(topOffset, leftOffset, 192, 157);  //*************** 
        mImageproc.drawFeedback(); //esto dibuja las otras cámaras
        gui.draw();
    } 
    


} 


void testApp::loadSettings() { 
	
	
	if( XML.loadFile("mySettings.xml") ){
		//message = "mySettings.xml loaded!"; 
		
		
		mImageproc.boxInputMatrix.setTopLeftX(XML.getValue("CAPTUREREGION:r11:X", 0)); 
		mImageproc.boxInputMatrix.setTopLeftY(XML.getValue("CAPTUREREGION:r11:Y", 0)); 
		
		mImageproc.boxInputMatrix.setBottomLeftX(XML.getValue("CAPTUREREGION:r12:X", 0)); 
		mImageproc.boxInputMatrix.setBottomLeftY(XML.getValue("CAPTUREREGION:r12:Y", mImageproc.imgWidth)); 
		
		mImageproc.boxInputMatrix.setTopRightX(XML.getValue("CAPTUREREGION:r21:X", 0));  
		mImageproc.boxInputMatrix.setTopRightY(XML.getValue("CAPTUREREGION:r21:Y", mImageproc.imgHeight));   
		
		mImageproc.boxInputMatrix.setBottomRightX(XML.getValue("CAPTUREREGION:r22:X", mImageproc.imgWidth)); 
		mImageproc.boxInputMatrix.setBottomRightY(XML.getValue("CAPTUREREGION:r22:Y", mImageproc.imgHeight)); 
		
		mImageproc.threshold = XML.getValue("IMAGESETTINGS:THRESHOLD", 230); 
		mImageproc.thresholdDiff = XML.getValue("IMAGESETTINGS:THRESHOLDDIFF", 102); 
		mImageproc.blobMax = XML.getValue("IMAGESETTINGS:BLOBMAX", 22); 
		mImageproc.blobMin = XML.getValue("IMAGESETTINGS:BLOBMIN", 1); 
		with_explosions = XML.getValue("GAMESETTINGS:EXPLOSION",true);
		BORN_TIME[0]=XML.getValue("GAMESETTINGS:HOW_FAST0", 1500); 
		BORN_TIME[1]=XML.getValue("GAMESETTINGS:HOW_FAST1", 1000); 
		BORN_TIME[2]=XML.getValue("GAMESETTINGS:HOW_FAST2", 700); 
        
        myMsgs.idleVideo_speed=XML.getValue("VIDEO_SETTINGS:IDLE_VIDEO",0.7 ); 
        myMsgs.finVideo_speed=XML.getValue("VIDEO_SETTINGS:FIN_VIDEO",0.7 ); 
        myMsgs.looseVideo_speed=XML.getValue("VIDEO_SETTINGS:LOOSE_VIDEO",0.7 ); 
		
	}else{ 

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
	
	XML.setValue("GAMESETTINGS:EXPLOSION", with_explosions); 
	XML.setValue("GAMESETTINGS:HOW_FAST0", BORN_TIME[0]); 
	XML.setValue("GAMESETTINGS:HOW_FAST1", BORN_TIME[1]); 
	XML.setValue("GAMESETTINGS:HOW_FAST2", BORN_TIME[2]); 
    
    XML.setValue("VIDEO_SETTINGS:IDLE_VIDEO", myMsgs.idleVideo_speed); 
    XML.setValue("VIDEO_SETTINGS:FIN_VIDEO", myMsgs.finVideo_speed); 
    XML.setValue("VIDEO_SETTINGS:LOOSE_VIDEO", myMsgs.looseVideo_speed); 
    
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
				my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0);
				my_enemy.newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0);
				status_time=TIME_WIN[status_level];
				status_time_init=ofGetElapsedTimef();
				drawing_text_finished_flag=false;
				gameStartTime = ofGetElapsedTimef();
			}
			
		break;
			
		case '2': // press 2 to go to the next level
			status_game=2;
			status_time=TIME_WIN[status_level];
			status_time_init=ofGetElapsedTimef();
			//=ofGetElapsedTimef();
			my_enemy.restart();
			drawing_text_finished_flag=false;

			break;
			
		case '3':
			status_game=3; //press 3 to lose the current level and restart the game
			status_time=TIME_WIN[status_level];
			status_time_init=ofGetElapsedTimef();
			//=ofGetElapsedTimef();
			my_enemy.restart();	
			drawing_text_finished_flag=false;

		break;	
			
		case '4':
			status_game=3;
			status_level=2;
			status_time=TIME_WIN[status_level];
			status_time_init=ofGetElapsedTimef();
			//=ofGetElapsedTimef();
			my_enemy.restart();		
			drawing_text_finished_flag=false;

		break;
		
        case '+': gui.nextPage(); break;	
        
        case 'z': my_enemy.cleanOne(); break;
			
		case 'k': 
			saveSettings(); 
			break; 
			
		case 'l':
			loadSettings(); 
			break; 
        
            
		case 'f': 
            fullscreen = true; 
            break; 
			
		case 'w':
            fullscreen = false; 
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
	//my_enemy.cleanOne();

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

