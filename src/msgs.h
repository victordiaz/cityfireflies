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
#include "ofxFBOTexture.h"
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
	bool levelVideo( ofImage status1_img, ofImage status2_img, string levelText );
	bool drawPlayingImg();
	
	msgs();
	ofTrueTypeFont font_bottom;
	ofTrueTypeFont font_full_screen;
	
	void update();
	int window_size_ani;
	ofImage walking1;
	ofImage walking2;
	ofImage img_play1_es;
	ofVideoPlayer walkingVid;
	ofVideoPlayer finMovie;
	ofVideoPlayer tryMovie;
	ofVideoPlayer idleMovie_en;
	ofVideoPlayer idleMovie_es;
	GameSprite sprites;
	int position;
	long counter;
	bool must_draw_half;
	bool must_draw_sec;
	bool must_draw_milis;
	bool must_draw_ocho;
	bool draw_flag;
	float frameTime;
	int status_animation;
	bool drawCoolExplosion();
	string currentMovie;
	bool initVideo();
	bool looseVideo();
	bool finVideo();
	bool idleVideo_es();
	bool idleVideo_en();	
	
private:	
	int timmer_pause;
	int scroll_control;
	ofxFBOTexture myFBO;
	int x_exp, y_exp;
	int explotionCounter;
	struct screenSquare {
		int x;
		int y;
		int color;
	};
	struct screenSquare myScreen[54];
	int x1,y1; //used to draw the transition. 
	int malpha;
	int position_init_msg;
};
#endif