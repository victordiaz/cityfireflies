/*
 *  screen_msgs.cpp
 *  plaza
 *
 *  Created by Sergio Manuel Galán Nieto on 21/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "msgs.h"


msgs::msgs(){
	window_size_ani=0;
	//walking1.loadImage("images/walking1.png");
	//walking1.loadImage("images/walking2.png");
	position=192;
    idleVideo_speed=finVideo_speed=looseVideo_speed=0.7;
}

void msgs::setup(){
	img_play1_es.loadImage("images/play1_es.png");
	//img_play1_en.loadImage("images/play1_en.png");

	font_bottom.loadFont("visitor1.ttf", 7,false,false);
	font_full_screen.loadFont("visitor1.ttf",16,false,false,false);
	font_big.loadFont("visitor1.ttf",42,false,false,false);

	
	//sprites.setup();
	//sprites.load("images/walking");
	frameTime=ofGetElapsedTimef();
	must_draw_milis=false;
	must_draw_half=false;
	must_draw_sec=false;
	must_draw_ocho=false;

	counter=0;
	status_animation=0;
	timmer_pause=0;
	draw_flag=false;
	
	
	//myFBO.allocate(192, 125, false);
	x1=y1=explotionCounter=0;
	x_exp=y_exp=0;
	for(int i=0; i<LONG_COLA_ANIMATION; i++){
		myScreen[i].x=0;
		myScreen[i].y=0;
		myScreen[i].color=0x000000;
	}
    
    walkingVid.setLoopState(OF_LOOP_NONE); 
	malpha=0;
	currentMovie="";
	position_init_msg=0;
	finMovie.loadMovie("images/fin_ok.gif");
	finMovie.setLoopState(OF_LOOP_NONE);
    finMovie.play(); finMovie.stop();
    
	tryMovie.loadMovie("images/tryAgain.gif");
	tryMovie.setLoopState(OF_LOOP_NONE);
	tryMovie.play(); tryMovie.stop();
    
	idleMovie_es.loadMovie("images/movil_es.gif");
	idleMovie_es.setLoopState(OF_LOOP_NONE);
	
	idleMovie_en.loadMovie("images/movil_en.gif");
	idleMovie_en.setLoopState(OF_LOOP_NONE);
	
	tryMovie.setSpeed(looseVideo_speed);	
	finMovie.setSpeed(finVideo_speed);	
	idleMovie_es.setSpeed(idleVideo_speed);	
	idleMovie_en.setSpeed(idleVideo_speed);

	
	
	blinkCounter=0;
}

void msgs::update(){
//	sprites.update();
	
	if (ofGetElapsedTimef() > frameTime) {
		must_draw_milis=true;
		counter++;
		counter%5==0?must_draw_half=true:must_draw_half=false;
		counter%10==0?must_draw_sec=true:must_draw_sec=false;
		counter%6==0?must_draw_ocho=true:must_draw_ocho=false;

		//frameTime += 1.0 / FRAME_RATE;
	}
	else{
		must_draw_milis=false;
	}
	walkingVid.idleMovie();	
	finMovie.idleMovie();
	tryMovie.idleMovie();
	idleMovie_es.idleMovie();
	idleMovie_en.idleMovie();
}

//esta funcion se usa
bool msgs::levelVideo( ofImage status1_img, ofImage status2_img, string levelText ){
	string levelMovie="images/level_animation.gif";
	if (currentMovie!=levelMovie) {
		walkingVid.loadMovie(levelMovie);
        walkingVid.setLoopState(OF_LOOP_NONE); 
		currentMovie=levelMovie;
	}
	walkingVid.play(); 
	ofSetHexColor(0xFFFFFF);

	if(walkingVid.getIsMovieDone()){
		//return 	drawCoolExplosion();
		malpha-=20;
		ofSetColor(255, 255, 255,malpha);
		walkingVid.draw(0,0);	
		font_full_screen.drawString(levelText, 70, 92);
		status1_img.draw(5, 40);

		if (malpha<10){
			walkingVid.stop();
			walkingVid.setPosition(0);
			return true;
		}
		
	}
	else{
		malpha<235?malpha+=20:malpha=255;
		ofSetColor(255, 255, 255,malpha);
		walkingVid.draw(0,0);	
		status1_img.draw(5, 40);
		font_full_screen.drawString(levelText, 70, 92);		
	}
	return false;
}


bool msgs::finVideo(){

	finMovie.play(); 
	ofSetHexColor(0xFFFFFF);
	if(finMovie.getIsMovieDone()){
		finMovie.stop();
		finMovie.setPosition(0);
		return true;
	}	
	else{		
		finMovie.draw(0,0);	
	}
	return false;	
}

bool msgs::looseVideo(){	
	tryMovie.play(); 
	ofSetHexColor(0xFFFFFF);
	if(tryMovie.getIsMovieDone()){
		tryMovie.stop();
		tryMovie.setPosition(0);
		return true;
	}
	
	else{		
		ofSetColor(255, 255, 255);
		tryMovie.draw(0,0);	
	}
	return false;	
}

bool msgs::idleVideo_es(){	
	idleMovie_es.play(); 
	ofSetHexColor(0xFFFFFF);
	if(idleMovie_es.getIsMovieDone()){
		position_init_msg!=41?position_init_msg+=4:position_init_msg=0;
		idleMovie_es.draw(0,81+position_init_msg);	
		if (position_init_msg>35)
		{
			position_init_msg=0;
			idleMovie_es.stop();
			idleMovie_es.setPosition(0);
			return true;
		}
		
	}
	else{		
		position_init_msg<40?position_init_msg+=4:position_init_msg=41;
		ofSetColor(255, 255, 255);
		idleMovie_es.draw(0,125-position_init_msg);	
	}
	return false;
}

bool msgs::idleVideo_en(){	
	idleMovie_en.play(); 
	ofSetHexColor(0xFFFFFF);
	if(idleMovie_en.getIsMovieDone()){
		position_init_msg!=41?position_init_msg+=4:position_init_msg=0;
		idleMovie_en.draw(0,81+position_init_msg);	
		if (position_init_msg>35)
		{
			position_init_msg=0;
			idleMovie_en.stop();
			idleMovie_en.setPosition(0);
			return true;
		}
		
	}
	else{		
		position_init_msg<40?position_init_msg+=4:position_init_msg=41;
		ofSetColor(255, 255, 255);
		idleMovie_en.draw(0,125-position_init_msg);	
	}
	return false;
}


bool msgs::initVideo(){
	string levelMovie="images/proteje_plaza.gif";
	if (currentMovie!=levelMovie) {
		walkingVid.loadMovie(levelMovie);
		currentMovie=levelMovie;
	}	

	walkingVid.play(); 
	ofSetHexColor(0xFFFFFF);
	if(walkingVid.getIsMovieDone()){
		position_init_msg!=41?position_init_msg+=4:position_init_msg=0;
		walkingVid.draw(0,67+position_init_msg);	
		if (position_init_msg>35)
		{
			position_init_msg=0;
			walkingVid.stop();
			walkingVid.setPosition(0);
			return true;
		}
		
	}
	else{		
		position_init_msg<40?position_init_msg+=4:position_init_msg=41;
		ofSetColor(255, 255, 255);
		walkingVid.draw(0,107-position_init_msg);	
	}
	return false;
}
//bool msgs::

bool msgs::drawCoolExplosion(){
	int colourArray[6]={0xD2007D,0x30F030,0xCCD7C9,0x322830,0xC21010,0x02CCCC};
	
	//int y1=round(ofRandom(0, 14));
	//int x1=round(ofRandom(0,23));
	
	//It goes line by line top left to buttom right


	//ofSetColor(colourArray[ofRandom(0, 4)]);
	
	x1++;
	if(x1>9){
		x1=0;
		y1++;
	}
	if(y1>=6 && x1>=9){
		return true;
	}
	
	explotionCounter++;
	if (explotionCounter>LONG_COLA_ANIMATION){
		explotionCounter=0;
	}
	
	myScreen[explotionCounter].x=x1;
	myScreen[explotionCounter].y=y1;
	myScreen[explotionCounter].color=colourArray[rand() % 6];

	ofFill();
	for(int i=0;i<LONG_COLA_ANIMATION;i++){
		ofRect(myScreen[i].x*20, myScreen[i].y*20, 20, 20);
		ofSetColor(myScreen[i].color);
	}
	
	
	/**myFBO.begin();
		ofFill();
		int color= colourArray[rand() % 6];
		ofSetColor(color);
		ofRect(x_exp*20, y_exp*20, 20, 20);
	myFBO.end();
	
	myFBO.draw(40,72);**/
	
	
	return false;
	
}
/**bool msgs::drawMsgIntro1(){
	if(status_animation==0){
		ofSetColor(0,0,0);
		ofRect(0, 125-window_size_ani, 192, window_size_ani); // I draw the bottom rectangle two points below.
		window_size_ani+=2;
		status_animation=(window_size_ani<50) ? 0:1; 
	}	
	else if(status_animation==1){
		ofSetColor(0,0,0);
		ofRect(0, 125-window_size_ani, 192, window_size_ani);
		ofSetColor(255,255,255);

		font_bottom.drawString("Enciende la pantalla de tu teléfono \n  y apunta hacia los bichos", 0, 80);
		//walking1.draw(190-4*counter,92);
//		sprites.draw(position,92);

		if(must_draw_half){
			cout << position << "\n";
			position=position-4;
			if (position<20) {
				status_animation=2;	
				position=192;
			}		
		}
	}
	else if(status_animation==2){
		ofSetColor(0,0,0);
		ofRect(0, 125-window_size_ani, 192, window_size_ani);
//		sprites.draw(position,92);
		status_animation=3;

	}	
	
	else if(status_animation==3){
		ofSetColor(0,0,0);
		ofRect(0, 125-window_size_ani, 192, window_size_ani); // I draw the bottom rectangle two points below.
		window_size_ani-=2;
		status_animation=(window_size_ani>=0) ? 3:4; 
		
	}
	else if(status_animation==4){
		cout << "end animation \n";
		status_animation=0;
		return true; //animation has finished
	}
	
	//this means that the animation hasn't finished
	return false;
		
}; **/
/**
void msgs::drawFullScreenText(string texto){
	ofSetColor(0,0,0);
	ofRect(0, 0, 192, 125); 
	ofSetColor(255,255,255);

	font_full_screen.drawString(texto, 10, 50); 
	
}**/
//returns true when it has finished painting the screen.
bool msgs::drawFullScreenText(string texto){
	ofSetColor(0,0,0);
	ofRect(0, 0, 192, 125); 
	ofSetColor(255,255,255);	
	font_full_screen.drawString(texto, 10, 50);
	
	if(timmer_pause==0){ //first time we start the timmer
		timmer_pause=ofGetElapsedTimef();	
	}
	else if(ofGetElapsedTimef() - timmer_pause >=SCREEN_CHANGE_TIME){
		timmer_pause=0;
		return true;
	}
	return false;
	
}
//return false while running true when finish.
bool msgs::drawPlayingImg(){
	ofSetColor(255,255,255);
	//ofRect(0, 0, 192, 125); 
	//ofSetColor(255,255,255);	
	//font_full_screen.drawString(texto, 10, 50);
	if(must_draw_sec==true && must_draw_milis==true){ 
		draw_flag=!draw_flag;
	}
	//if(draw_flag==false) 	
	ofSetColor(0,0,0,50);
	ofFill();
	ofRect(0, 0, 192, 108);
	ofSetHexColor(0xffffff);

	img_play1_es.draw(0,0);
	
	if(timmer_pause==0){ //first time we start the timmer
		timmer_pause=ofGetElapsedTimef();	
	}
	else if(ofGetElapsedTimef() - timmer_pause >=SCREEN_CHANGE_TIME){
		timmer_pause=0;
		return true;
	}
	return false;
	
}


bool msgs::drawFullScreenTextTransparent(string texto){
	ofSetColor(255,255,255);	
	font_full_screen.drawString(texto, 10, 50);
	
	if(timmer_pause==0){ //first time we start the timmer
		timmer_pause=ofGetElapsedTimef();	
	}
	else if(ofGetElapsedTimef() - timmer_pause >=SCREEN_CHANGE_TIME){
		timmer_pause=0;
		return true; //return true when it has finished
	}
	return false;
	
}

bool msgs::drawFullScreenTextScroll(string texto,int tiempo){
	ofSetColor(255,255,255);
	ofPushMatrix();
	ofTranslate(10,0);
		font_full_screen.drawString(texto, 192-scroll_control, 118);
		if(must_draw_milis) scroll_control+=10;
	ofPopMatrix();
	if(timmer_pause==0){ //first time we start the timmer
		timmer_pause=ofGetElapsedTimef();	
	}
	else if(ofGetElapsedTimef() - timmer_pause >=tiempo){
		timmer_pause=0;
		scroll_control=0;
		return true;	
	}
	return false;
}

bool msgs::drawFullScreenBlink(){
	
	if(must_draw_ocho==true && must_draw_milis==true){ 
		draw_flag=!draw_flag;
		must_draw_ocho=false;
		blinkCounter++;
		//cout << "mierda";
	}
	ofSetHexColor(0xd2007d);
	if(draw_flag==true){
		font_big.drawString("Play!", 24, 60);
	}
	if(blinkCounter>=6){
		blinkCounter=0;
		return true;
	}
	return false;
}




void msgs::drawButtomMenu(int time, int level ){
	ofPushMatrix();
	ofTranslate(0, 108, 0);
	ofSetColor(0,0,0);
	ofRect(0, 0, 192, 17); 
	ofFill();
	ofSetColor(255,255,255);

	std::ostringstream oss;
	oss << "Level " << level; // << "  Time " << time;
	font_bottom.drawString(oss.str(), 135, 10);

	//if(level!=0){
		ofSetHexColor(0x30F030);
		
		ofNoFill();
		ofRect(10, 3, 70, 9);
		ofFill();
		ofSetHexColor(0xD2007D);
		int porcentaje=(int) (70*time)/TIME_WIN[level];
		ofRect(10,4, porcentaje, 8);
		ofSetHexColor(0xffffff);
		char fpsStr[255]; // an array of chars		
		sprintf(fpsStr, " %i", time);
		//std::ostringstream oss2;
		//oss2 << time;
		font_bottom.drawString(fpsStr , 30, 10);	
	//}
	ofPopMatrix();

}




// franja inferior empieza en 108 y ocupa 17 pixels
// a tamaño 7 caben 32 caracteres.

/***
 void msgs::drawMsgDuringGame(){
 ofSetColor(0,0,0);
 ofRect(0, 110, 192, 15); // I draw the bottom rectangle two points below.
 ofSetColor(255,255,255);
 
 font_bottom.drawString("Enciende la pantalla de tu teléfono y apuntala hacia los enemigos", 1, 120);
 
 };
 ***/