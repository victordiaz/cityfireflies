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
#include "Poco/String.h"
#include "Poco/Format.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/NumberFormatter.h"

using Poco::NumberFormatter;
using Poco::Path;
using Poco::format;
using Poco::File;
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
	loadImages();
	// malo1.loadImage("images/malo1.png");
	// malo2.loadImage("images/malo2.png");
	tipo_dibujo=0;
	actualiza_dibujo=0;
}

/**void enemies::setExplosionHandler( ParticleSourceHandler *psh){
	explosions = psh;
}**/

void enemies::loadImages(){	
	std::string s;
	
	for (int level=0; level<= MAX_LEVELS; level++){
		total_drawings[level] = countDrawings(NumberFormatter::format(level) );
		total_drawings[level] = (int) total_drawings[level]/2;
		for (int n=0; n<total_drawings[level]; n++) {
			s=format( "images/malos/%d/malo_%d_a.png", level,n);
			malos[level][n][0].loadImage(s);
			s=format( "images/malos/%d/malo_%d_b.png", level,n);
			cout << s << "\n";
			malos[level][n][1].loadImage(s);	
		}
	}
//	malos[0][0].loadImage("images/malos/malo1.png");
//	malos[0][1].loadImage("images/malos/malo2.png");
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

	if (counter_enemies>= filas*columnas)
		return true;	
	
	if(logic_map[m_x][m_y]==false)
	{	
		logic_map[m_x][m_y]=true;
		counter_enemies++;
		return true;
	}


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


//Funcion para borrar enemigos
bool enemies::cleanRegion(int x, int y){
	if (logic_map[x][y]==true) {
		logic_map[x][y]=false;
	//	explosions->addEmitter(x*square_size,y*square_size);
		counter_enemies--;
		return true;
	}
	else{
		return false;
	}
}

void enemies::cleanOne(){
	int max_tries=0;
	while(true){
		if(cleanRegion(ofRandom(0,columnas),ofRandom(0,filas))==false){
			max_tries++;
			if(max_tries>=100)
				return;
		}
		else {
			return;
		}

	}
	return;
	
}


int enemies::countEnemies(){
	return counter_enemies;
}


int enemies::countDrawings(std::string mdir){
	
	Poco::Path path(Path::current() + "../../../data/images/malos/"+mdir , Path::PATH_UNIX);
	cout << path.toString();
	cout << "\n";
	//cout << path.toString();
	File tmpDir(path);
	
	std::vector<std::string> files;
	tmpDir.list(files);
	std::vector<std::string>::iterator it = files.begin();
	int total_drawings1=0;
	for (; it != files.end(); ++it)
	{
		total_drawings1++;
	}
	cout << total_drawings1;
	return total_drawings1;
	
	//tmpDir.remove(true);
	
}

//This function reads the logic_map variable and draw an enemy where there is supposed to be one.
void enemies::draw(int current_level) {

	
	ofSetColor(255,255,255,200);
	for (int x=0; x<columnas; x+=1) {
		for(int y=0;y<filas;y+=1){
			if(logic_map[x][y]==true){ //draw the enemy

				if(ofGetFrameNum()%30==0){
					tipo_dibujo=ofRandomf();
					//actualiza_dibujo=0;
				}
				//actualiza_dibujo++;
				//ofSetColor(255, 255, 255);
				//ofsetColor (255,255,255); 
				ofPushStyle(); 
				ofSetColor(255, 255, 255, ofMap(counter_enemies, 0, maxMalos, 225, 92)); 
				//ofSetColor(255, 255, 255, 25); 
				int number_drawing_symbol=(x+y) % total_drawings[current_level];
				if(tipo_dibujo >= 0) { 
					malos[current_level][number_drawing_symbol][0].draw(x*square_size, y*square_size);
				}
				else {
					malos[current_level][number_drawing_symbol][1].draw(x*square_size, y*square_size);
				} 
				ofPopStyle(); 
			}
			else { //don't draw the eneny

			}

			
		}
	}
}



