/*
 *  perfectPixelRescale.h
 *
 *  Created by Mar Canet Sola on 6/12/10.
 *  Copyright 2010 lummo. All rights reserved.
 *
 *  http://www.openframeworks.cc/forum/viewtopic.php?f=9&t=3505&view=unread
 *
 */

#ifndef  ___PERFECT_PIXELS_RESCALE__H__
#define  ___PERFECT_PIXELS_RESCALE__H__


#include "ofMain.h"

class perfectPixelsRescale
{
public:
    perfectPixelsRescale();
    ~perfectPixelsRescale();
    void resample(unsigned char* pixels);
    void setSize(int _pixelSizeX, int _pixelSizeY, int _width, int _height);
    void draw(int x, int y, bool alignCenter=true);
	unsigned char* getPixels();
	ofImage getImage();
	int getPixelSizeX();
    int getPixelSizeY();
    int getWidth();
    int getHeight();
private:
	ofImage img;
    int totalPixel;
    int pixelSizeX;
    int pixelSizeY;
    int width;
    int height;
    unsigned char* newPixels;
    int p1;
    int p2;
    int p3;
};

#endif
