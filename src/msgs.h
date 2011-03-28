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
#include "GameSprite.h"

class msgs{
public:
	bool drawMsgIntro1();
	void drawMsgIntro2();
	void drawMsgLevel1();
	void setup();
	void drawButtomMenu(int time, int level );
	bool drawFullScreenText(string text);
	bool drawFullScreenTextTransparent(string text);
	bool drawFullScreenTextScroll(string texto,int tiempo);
	msgs();
	ofTrueTypeFont font_bottom;
	ofTrueTypeFont font_full_screen;
	
	void update();
	int window_size_ani;
	ofImage walking1;
	ofImage walking2;
	ofVideoPlayer walkingVid;
	GameSprite sprites;
	int position;
	bool must_draw;
	float frameTime;
	int status_animation;

private:	
	int timmer_pause;
	int scroll_control;
};
#endif