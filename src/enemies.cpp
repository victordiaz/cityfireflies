/*
 *  enemies.c
 *  plaza
 *
 *  Created by Sergio Manuel Galán Nieto on 29/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "enemies.h"
#include <math.h>
#include "ofMath.h"
//Constructor
enemies::enemies(){
	for (int x=0; x<columnas; x++) {
		for(int y=0;y<filas;y++){
			logic_map[x][y]=false;
		}
	}
	for (int x=0; x<scr_width; x++) {
			for (int y=0; y<scr_height;y++){
				war_map[x][y]=false;
			}
		}
	current_iteration=0; // de 1 a 7
	malos_en_current_iteration=0;

	malo1.loadImage("images/malo1.png");
	malo2.loadImage("images/malo2.png");
	tipo_dibujo=0;
	actualiza_dibujo=0;
}


void enemies::restart(){
	tipo_dibujo=0;
	actualiza_dibujo=0;
	
	for (int x=0; x<columnas; x++) {
		for(int y=0;y<filas;y++){
			logic_map[x][y]=false;
		}
	}
	for (int x=0; x<scr_width; x++) {
		for (int y=0; y<scr_height;y++){
			war_map[x][y]=false;
		}
	}
	counter_enemies=0;
	current_iteration=0; // de 1 a 7
	malos_en_current_iteration=0;

}
//Create an enemy at possition m_x, m_y
// if the enmy was created, returns true, if not because all the screen  is full or because that part is already full, returns false
bool enemies::newEnemy(int m_x,int m_y, int type){

	if (counter_enemies<= filas*columnas)
		counter_enemies++;
	else{
		return false;	
	}
	if(logic_map[m_x][m_y]==false)
	{	
		logic_map[m_x][m_y]=true;
		return true;
	}
	else return false;

	return false;
}


void enemies::removeRandomOne(){
	if(counter_enemies<=0) return;
	while(true){
	for (int x=(int)ofRandom(0,columnas); x<columnas; x++) {
		for(int y=(int)ofRandom(0,filas);y<filas;y++){
			if(logic_map[x][y]==true){ 
				logic_map[x][y]=false;
				counter_enemies--;
				return;
			}
		}
	}
	}

}



//no funcionando (crea enemigos siguendo un patron circular) 
bool enemies::newEnemies(int total){
	int counter=0;
	int max_tries=0;
	while(true){
		if(newEnemy(ofRandom(0,columnas),ofRandom(0,filas),0)==true){
			counter++;
			if(counter>=total)
				break;
		}
		max_tries++;
		if(max_tries>=250)
			return false;
	}
	return true;
}



//How the enemies move:

/**bool enemies::updatePosition(){
	for (int x=0; x<=columnas; x+=1) {
		for(int y=0;y<filas;y+=1){
			if(logic_map[x][y]==true)
				counter_enemies++;
		}
	}

}**/
//
//void enemies::cleanRegion(int m_x,int m_y, int size, int type){
	//for (int x=m_x; x<m_x+size; x++) {
//		for (int y=m_y; y<m_y+size;y++){
//			war_map[m_x][m_y]=false;
//		}
//	}
//	return;
//}


//Funcion para borrar enemigos
bool enemies::cleanRegion(int x, int y){
	if (logic_map[x][y]==true) {
		cout << "lalalalallalala" << endl; 
		logic_map[x][y]=false;
		counter_enemies--;
		return true;
	}
	else{
		return false;
	}
}



int enemies::countEnemies(){
	return counter_enemies;
}

//This function reads the logic_map variable and draw an enemy where there is supposed to be one.
void enemies::draw() {
	for (int x=0; x<columnas; x+=1) {
		for(int y=0;y<filas;y+=1){
			if(logic_map[x][y]==true){
				ofSetColor(255,255,255);
				if(ofGetFrameNum()%30==0){
					tipo_dibujo=ofRandomf();
					//actualiza_dibujo=0;
				}
				//actualiza_dibujo++;
				if(tipo_dibujo>=0){
					malo1.draw(x*square_size, y*square_size);
				}
				else {
					malo2.draw(x*square_size, y*square_size);
				}
			}
			else {
				//ofSetColor(200,0,0);
				//ofRect(x*square_size,y*square_size,x+square_size,y+square_size);
			}

		}
	}
}



