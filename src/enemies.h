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
	bool newEnemy(int x,int y, int type);
	void cleanRegion(int m_x,int m_y, int size, int type);
	int	countEnemies();
	void removeRandomOne();
	enemies();
	void draw();
	void cleanOne();
	bool logic_map [filas][columnas];
	bool war_map [scr_width][scr_height];
	bool newEnemies(int number);
	ofImage* getEnemies();
	int current_iteration; // de 1 a 7
	int malos_en_current_iteration;
	bool cleanRegion(int x, int y);	
	ofImage malo1;
	ofImage malo2;
	float tipo_dibujo;
	int actualiza_dibujo;
	int counter_enemies;
	void restart();
};



#endif