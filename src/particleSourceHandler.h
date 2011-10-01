/*
 *  particleSourceHandler.h
 *  plaza
 *
 *  Created by Sergio Manuel Galán Nieto on 01/10/11.
 *  Copyright 2011 Uncoded. All rights reserved.
 *
 */
#ifndef _PARTICLE_EMITER_
#define _PARTICLE_EMITER_

#include "ofMain.h"
#include "ParticleEmitter.h"
#include <list>

typedef list<ParticleEmitter *> emitterList;

class ParticleSourceHandler {

private:
	emitterList myEmitters;

public: 
	void addEmitter(int, int);
	void draw();
	void update();
	void removeEmitters(ParticleEmitter);

};
#endif

