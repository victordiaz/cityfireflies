/*
 *  particleSourceHandler.cpp
 *  plaza
 *
 *  Created by Sergio Manuel Galán Nieto on 01/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "particleSourceHandler.h"

void ParticleSourceHandler::addEmitter(int x1, int x2 ){
	ParticleEmitter *pe= new ParticleEmitter();
	pe->setup(x1,x2);
	myEmitters.push_back(pe);	
}

void ParticleSourceHandler::draw(){
	for (emitterList::iterator em= myEmitters.begin();  em!= myEmitters.end(); em++){
		(*em)->draw();
	}
}

void ParticleSourceHandler::update(){
	for (emitterList::iterator em= myEmitters.begin();  em!= myEmitters.end(); em++){
		(*em)->update();
		if ((*em)->isEmpty()) {
			myEmitters.remove((*em));
		}
	}
}


void ParticleSourceHandler::removeEmitters(ParticleEmitter pe){

	
}
 