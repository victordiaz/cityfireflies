#include "GameSprite.h"

GameSprite::GameSprite() {
	setup();
}
GameSprite::GameSprite(string imgpath, string filename) {
	this->load(imgpath, filename);
	setup();
}
GameSprite::~GameSprite() {	
	frames.clear();
}
void GameSprite::load(string imgpath, string filename) {
	int i = 1; // i = 1 because the user usually starts like "1.jpg" instead of "0.jpg"
	while (true) { 
		stringstream intToString;
		intToString << i;
		string srcpath = imgpath + filename + intToString.str() + ".png";
		ofImage tmpImg;
		if (tmpImg.loadImage(srcpath)) {
			frames.push_back(tmpImg);
#ifdef DEBUG_SPRITE
			cout << "Loaded frame " << srcpath << "\n";
#endif
			i ++;
		}
		else 
			break;
	}
	frameNum = frames.size();
}

int GameSprite::getActualFrame() const{
	return actualFrame;
}

int GameSprite::getFrameNum() const {
	return frameNum;
}

void GameSprite::setup() {
	actualFrame = 0;
	frameTime = ofGetElapsedTimef();
}

void GameSprite::draw(float x, float y) {
	try {
		frames.at(actualFrame).draw(x,y);
	}
	catch(...) {
		cerr << "Frame " << actualFrame << " not found\n";
	}
}

void GameSprite::draw(float x,float y,float w, float h) {
	try {
		frames.at(actualFrame).draw(x,y,w,h);
	}
	catch(...) {
		cerr << "Frame " << actualFrame << " not found\n";
	}
}

void GameSprite::update() {
	if (ofGetElapsedTimef() > frameTime) {
		actualFrame ++;
		if (actualFrame > frames.size() - 1)
			actualFrame = 0;

		frameTime += 1.0 / FRAME_RATE;
	}
}

float GameSprite::getWidth() {
	return frames.at(actualFrame).getWidth();
}
float GameSprite::getHeight() {
	return frames.at(actualFrame).getHeight();
}