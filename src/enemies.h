/*
 *  enemies.h
 *  plaza
 *
 *  Created by Sergio Manuel Galán Nieto on 29/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _ENEMIES_
#define _ENEMIES_
#include "ofMain.h"
#include "constants.h"


class enemies {
public:
	//void setExplosionHandler( ParticleSourceHandler *psh);
	//ParticleSourceHandler *explosions;
	
	bool newEnemy(int x,int y, int type);
	//void cleanRegion(int m_x,int m_y, int size, int type);
	int	countEnemies();
	void removeRandomOne();
	enemies();
	void loadImages();
	void draw(int );
	void cleanOne();
	int countDrawings(string );
	int total_drawings[MAX_LEVELS+1];
	bool logic_map [filas][columnas];
	bool war_map [scr_width][scr_height];
	bool newEnemies(int number);
	ofImage* getEnemies();
	int current_iteration; // de 1 a 7
	int malos_en_current_iteration;
	bool cleanRegion(int x, int y);	
	ofImage malos [MAX_LEVELS+1][10][2];
//	ofImage malo2;
	float tipo_dibujo;
	int actualiza_dibujo;
	int counter_enemies;

	void restart();
};



#endif