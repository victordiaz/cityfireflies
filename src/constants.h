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

//#define WINDOWS
const bool ON_PC=false;
const int MAX_LEVELS=2;
const int scr_width=192;
const int scr_height=157;

const int TIME_WIN[3]={80,120,120}; //Tiempo por niveles 80 120 120

//const int ENEMIES_WIN[3]={12,40,144};
const int ENEMIES_BY_LEVEL[3]={10,20,70};
const int square_size=12;
const int filas=9;
const int columnas=16; 
const int maxMalos = 144; 
//int BORN_TIME[3];//={1500,1000,700};
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
