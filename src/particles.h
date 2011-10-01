/*
 *  particles.h
 *  plaza
 *
 *  Created by Sergio Manuel Galán Nieto on 29/09/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _PARTICLES_
#define _PARTICLES_
#include "ofMain.h"
#include "constants.h"
#include <list>

#define RADIUS 1;

class Particle {
private:
	double _x, _y;
	double _x_velocity, _y_velocity;
	int _r, _g, _b;
public:
	Particle(int x, int y, double x_velocity, double y_velocity, int r, int g, int b);
	int x() ;
    int y() ;
    int r() ;
    int g() ;
    int b() ;	
    void move(double );
};
class Source {
	int _x, _y;
	double _rate; // This gives the number of particles that should be created per second.
	double _x_velocity, _y_velocity;
	int _r, _g, _b; 
	int _ncreated; // This is the number of particles that this source has created.
	
public:
    Source(int x, int y, double rate, double x_velocity, double y_velocity, int r, int g, int b);	
	int nCreated();
    double rate();
    Particle* create();
	
    int x();    
	int y();
};


class particleHandler {
	private:
		list<Particle*> *particles;
		list<Source*> *sources;
	public:
	particleHandler();
	void update();
	void create_particles();
	void update_particles();
	void reap_particles();
	void draw_particles() ;
	


};

#endif