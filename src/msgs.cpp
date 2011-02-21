/*
 *  screen_msgs.cpp
 *  plaza
 *
 *  Created by Sergio Manuel Galán Nieto on 21/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "msgs.h"



void msgs::setup(){
	font_bottom.loadFont("visitor1.ttf", 7);
	
};
void msgs::drawMsgIntro1(){
	ofSetColor(0,0,0);
	ofRect(0, 110, 192, 15); // I draw the bottom rectangle two points below.
	ofSetColor(255,255,255);

	font_bottom.drawString("Enciende la pantalla de tu teléfono y apuntala hacia los enemigos", 1, 120);
	
};
// franja inferior empieza en 108 y ocupa 17 pixels
// a tamaño 7 caben 32 caracteres.