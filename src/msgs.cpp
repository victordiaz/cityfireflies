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
	walking1.loadImage("images/walking1.png");
	walking1.loadImage("images/walking2.png");
	walkingVid.loadMovie("images/walking1.swf");
	position=192;
}

void msgs::setup(){
	font_bottom.loadFont("visitor1.ttf", 7);
	font_full_screen.loadFont("visitor1.ttf",25);
//walkingVid.play();
	sprites.setup();
	sprites.load("images/walking");
	frameTime=ofGetElapsedTimef();
	must_draw=false;
	status_animation=0;
	timmer_pause=0;


};

void msgs::update(){
	sprites.update();
	
	if (ofGetElapsedTimef() > frameTime) {
		must_draw=true;		
		frameTime += 1.0 / FRAME_RATE;
	}
	else{
		must_draw=false;
	}
}


bool msgs::drawMsgIntro1(){
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
		sprites.draw(position,92);

		if(must_draw){
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
		sprites.draw(position,92);
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
		
};
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
		font_full_screen.drawString(texto, 192-scroll_control, 50);
		if(must_draw) scroll_control+=10;
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

void msgs::drawButtomMenu(int time, int level ){
	ofSetColor(0,0,0);
	ofRect(0, 108, 192, 17); 
	std::ostringstream oss;
	oss << "Level " << level << "  Time " << time;
	ofSetColor(255,255,255);

	font_bottom.drawString(oss.str(), 100, 115);

	
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