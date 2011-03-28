/*
// Class GameSprite stores ofImages and iterates threw them in the update()-function  in a defined framerate.
// by Ivo Havranek, feb 2010
*/

#ifndef GAME_SPRITE
#define GAME_SPRITE

#include "ofImage.h"
#include <string>
#include <iostream>
using namespace std;

#define DEBUG_SPRITE
#define FRAME_RATE 10

class GameSprite: public ofBaseDraws, public ofBaseUpdates {

	public:
		GameSprite();
		GameSprite(string imgpath, string filename = "");
		~GameSprite();
		void load(string imgpath, string filename = ""); // loads images by filepath + filename + increasing number (must start at 1)
		void setup(); // animation starts at frame 0
		int getActualFrame() const;
		int getFrameNum() const;

		// ofBaseDraws
		void draw(float x,float y);
		void draw(float x,float y,float w, float h);
		float getWidth();
		float getHeight();

		// ofBaseUpdates
		void update();

	private:	
		vector<ofImage> frames;
		int actualFrame;
		int frameNum;
		float frameTime;
		
};

#endif
