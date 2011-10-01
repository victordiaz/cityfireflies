#ifndef _EMITTER
#define _EMITTER


#include "ofMain.h"
#include "Particle.h"
#include <list>

#define size 64
typedef list<Particle *> particleList;
class ParticleEmitter {

	private:
	particleList particles;
	int centerX;
	int centerY;
	float rotation;
	int current_size;
	public:
	
	void setup(int, int);
	void update();
	void draw();
	bool isEmpty();
	//Particle* p[size];
};

#endif
