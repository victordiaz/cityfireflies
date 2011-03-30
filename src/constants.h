/*
 *  constants.h
 *  plaza
 *
 *  Created by Sergio Manuel Galán Nieto on 29/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef CONSTANTS
#define CONSTANTS
const bool ON_PC=false;
const int MAX_LEVELS=2;
const int scr_width=192;
const int scr_height=157;
const int TIME_WIN[3]={20,20,100}; //Tiempo por niveles (el nivel 0 en realidad no funciona)
const int ENEMIES_WIN[3]={12,40,144};
const int ENEMIES_BY_LEVEL[3]={10,20,80};
const int square_size=12;
const int filas=9;
const int columnas=16; 
const int maxMalos = 144; 
const int BORN_TIME[3]={1500,1000,500};
const int SCREEN_CHANGE_TIME=5; 
const int LONG_COLA_ANIMATION=20;
//mask
const int leftOffset = 40;
const int topOffset = 40;
const int screenWidth = 192;
//const int halfWidth = ofGetWidth()/2; 
const int screenHeight = 157;
const int bHeight = 16;
const int bWidth = 12;
const int aWidth = bWidth; 

#endif
