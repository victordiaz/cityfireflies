/*
 *  Particle.cpp
 *  openFrameworks
 *
 *  Created by Stephen Braitsch on 11/6/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Particle.h"

Particle::Particle()
{
	x = ofRandomf();
	y = ofRandomf();
	speedX = ofRandom(0,1);
	speedY = ofRandom(0,1);
	radius =1;
	//color = ofRandom(0, 0xff0000);	
	color.r=205;
	color.g=215;
	color.b=201;
	age = 0;
	dead = false;
	maxAge = ofRandom(0, MAXTIME-MINTIME)+MINTIME;
}

void Particle::update()
{
	age++;
	x += (x>0) ? speedX : speedX*-1;
	y += (y>0) ? speedY : speedY*-1;
	if (age >= maxAge) dead = true;
	//if (y >= 40 +192) dead = true;
	//if (x >= 40+157) dead = true;
}

void Particle::draw()
{
	int alpha=  255-age*(int)((255/MAXTIME)*2);
	alpha<0?alpha=0:alpha=alpha;
	ofSetColor(color.r,color.g, color.b,alpha);
	ofCircle(x, y, radius);
}
