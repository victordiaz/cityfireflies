/*
 *  screen_msgs.h
 *  plaza
 *
 *  Created by Sergio Manuel Galán Nieto on 21/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _MSGS_
#define _MSGS_ 
#include "ofMain.h"
#include "constants.h"

class msgs{
public:
	void drawMsgIntro1();
	void drawMsgIntro2();
	void drawMsgLevel1();
	void setup();
	ofTrueTypeFont font_bottom;


};
#endif