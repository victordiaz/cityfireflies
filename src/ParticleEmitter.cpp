#include "ParticleEmitter.h"


//--------------------------------------------------------------
void ParticleEmitter::setup(int x1,int y1){
	centerX = x1;
	centerY = y1;
	rotation = 0;
	current_size=size;
	for (int i=0; i<size; i++) 
		particles.push_back(new Particle());
}

//--------------------------------------------------------------
void ParticleEmitter::update(){
	
	for (particleList::iterator pp= particles.begin();  pp!= particles.end(); pp++){
		(*pp)->update();
		if ((*pp)->dead==true) {
			delete *pp;
			particles.remove((*pp));
			
			//p[i] = new Particle();
		} 
	}
	rotation+=.05;
}

bool ParticleEmitter::isEmpty(){
	return particles.empty();
}
								
//--------------------------------------------------------------
void ParticleEmitter::draw(){
	ofPushMatrix();		
	ofTranslate(centerX, centerY);
	ofRotate(rotation);
	for (particleList::iterator pp= particles.begin();  pp!= particles.end(); pp++){
		(*pp)->draw();
	}
	ofPopMatrix();
}
