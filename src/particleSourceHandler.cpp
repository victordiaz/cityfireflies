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
	/**for (emitterList::iterator em= myEmitters.begin();  em!= myEmitters.end(); em++){
		(*em)->update();
		if ((*em)->isEmpty()) {
			delete *em;
			myEmitters.remove((*em));
		}
	}**/
    

    for(emitterList::iterator itr=  myEmitters.begin(); itr != myEmitters.end();){
        (*itr)->update();
        if ((*itr)->isEmpty()) {
			delete *itr;
            itr=myEmitters.erase(itr);
		} 
        else
            ++itr;
    }
    
}


 