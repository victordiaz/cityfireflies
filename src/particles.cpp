/*
 *  particles.cpp
 *  plaza
 *
 *  Created by Sergio Manuel Galán Nieto on 29/09/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "particles.h"

	

Source::Source(int x, int y, double rate, double x_velocity, double y_velocity, int r, int g, int b) {
		_x = x;
		_y = y;
		_rate = rate;
		_x_velocity = x_velocity;
		_y_velocity = y_velocity;
		_r = r;
		_g = g;
		_b = b;
		
		_ncreated = 0;
    }
	
    int Source::nCreated() { return _ncreated; }
    double Source::rate() { return _rate; }
    Particle* Source::create() {
		_ncreated += 1;
		return new Particle(_x, _y, _x_velocity, _y_velocity, _r, _g, _b);
    }
	
    int Source::x() { return _x; }
    int Source::y() { return _y; }



Particle::Particle(int x, int y, double x_velocity, double y_velocity, int r, int g, int b) {
		_x = x;
		_y = y;
		_x_velocity = x_velocity;
		_y_velocity = y_velocity;
		_r = r;
		_g = g;
		_b = b;
    }
	
    int Particle::x() { return (int)floor(_x); }
    int Particle::y() { return (int)floor(_y); }
    int Particle::r() { return _r; }
    int Particle::g() { return _g; }
    int Particle::b() { return _b; }
	
    void Particle::move(double time_delta) {
		_x += time_delta * _x_velocity;
		_y += time_delta * _y_velocity;
    }


particleHandler::particleHandler(){
	//list<Particle> particles;
	//list<Source> sources;
}

	void particleHandler::update(){
		create_particles();
		update_particles();
		reap_particles();
	}
	
	void particleHandler::create_particles() {
		for (list<Source*>::iterator si = sources->begin(); si != sources->end(); si++) {
			Source* s = *si;
			int ndesired = (int)floor(s->rate() * ofGetElapsedTimef());
			for (int i = s->nCreated(); i < ndesired; i++)
				particles->push_back(s->create());
		}
	}
	
	void particleHandler::update_particles() {
		double delta = 100;
		for (list<Particle*>::iterator pi = particles->begin(); pi != particles->end(); pi++) {
			Particle* p = *pi;
			p->move(delta);
		}
	}
	
	void particleHandler::reap_particles() {
		for (list<Particle*>::iterator pi = particles->begin(); pi != particles->end(); pi++) {
			Particle* p = *pi;
			int x = p->x();
			int y = p->y();
			if (x < 0 || x >= ofGetWidth() || y < 0 || y >= ofGetHeight()) {
				delete p;
				pi = particles->erase(pi);
				if (pi == particles->end()) break;
			}
		}
	}
	
void particleHandler::draw_particles() {
		for (list<Particle*>::iterator pi = particles->begin(); pi != particles->end(); pi++) {
			Particle* p = *pi;
			
			ofSetColor(p->r(), p->g(), p->b());
			ofFill();
			ofCircle(p->x(), p->y(), 4 );	
		}	
}

