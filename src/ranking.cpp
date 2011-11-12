//
//  ranking.cpp
//  plaza
//
//  Created by Sergio Manuel Galán Nieto on 31/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
/*
#include "ranking.h"

void ranking::setup(){
    for(int i=0; int i<ITEMS_RANKING; i ++){
        rankinglist[i]=1000;
    }
    
}


void ranking::draw(){
    
    
}

int ranking::addTime(int mtime){
    int mi;
    for( mi=0; mi<ITEMS_RANKING; mi++){
        if (mtime <= rankinglist[mi] ); //go from first element to last element checking if new time is a new record
    }
    
    if(mi==5){
        return -1; // the new time is not         
    }
    else{
        for( int ji=ITEMS_RANKING-1; ji < mi ;ji--){
            rankinglist[ji]=rankinglist[ji-1]; //shifts all values to give some space to the new element           
        }
        rankinglist[mi]=mtime;        
    }
    mustHighlight=mi;
    return mi;

}*/