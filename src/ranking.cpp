//
//  ranking.cpp
//  plaza
//
//  Created by Sergio Manuel Galán Nieto on 31/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ranking.h"
#include <iostream>
#include <algorithm>
using namespace std;
void ranking::setup(){
    for(int i=0;  i<ITEMS_RANKING; i ++){
        rankinglist[i]=1000+i;
    }
    myfont.loadFont("visitor1.ttf", 7, false,false,false); 

    
}


bool ranking::draw(){
    char rankingstr[255]; // an array of chars
    if(startTime==0){
        startTime=ofGetElapsedTimef();
    }
    for( int mi=0; mi<ITEMS_RANKING-1 ; mi++){   
        myfont.drawString("TOP 5", 80, 10); //estaba a 52, 25 
        sprintf(rankingstr, "%i - %i seconds", mi+1, rankinglist[mi]);
        myfont.drawString(rankingstr, 50, 30+mi*20); //estaba a 52, 25 
    }
    if(ofGetElapsedTimef()-startTime >5){
        startTime=0;
        return true; // returning true it doesn't get called again until next cycle of the game
    }
    else
        return false; //returning false the screen is still on charge    
}


bool ranking::drawCongrats(int position){
    ofSetHexColor(0xffffff);
    char rankingstr[255]; // an array of chars
    if(startTime==0){
        startTime=ofGetElapsedTimef();
    }
    ofSetHexColor(0xd2007d);
    myfont.drawString("CONGRATS. YOU JOINED TOP 5", 20, 10); 
    ofSetHexColor(0xffffff);
    for( int mi=0; mi<ITEMS_RANKING-1 ; mi++){  
        if(mi==position)    ofSetHexColor(0xd2007d);
        sprintf(rankingstr, "%i - %i seconds", mi+1, rankinglist[mi]);
        myfont.drawString(rankingstr, 50, 30+mi*20); //estaba a 52, 25 
        ofSetHexColor(0xffffff);

    }
    if(ofGetElapsedTimef()-startTime >5){
        startTime=0;
        return true; // returning true it doesn't get called again until next cycle of the game
    }
    else
        return false; //returning false the screen is still on charge    
}


/// returns the position of the new time. It could be number 5  so it doesn't join the top5 list  or any other
int ranking::addTime(int mtime){ //mtime is the new time
    rankinglist[ITEMS_RANKING-1]=mtime;
    sort(rankinglist, rankinglist+sizeof(rankinglist)/sizeof(rankinglist[0])) ;
    
    for( int mi=0; mi<ITEMS_RANKING; mi++){
        if(mtime==rankinglist[mi]){ //go from first element to last element checking if new time is a new record
            return mi;
        }	
    }
    return ITEMS_RANKING-1;
}    



  /**  int mi;
    for( mi=0; mi<ITEMS_RANKING; mi++){
        if (mtime <= rankinglist[mi] ){ //go from first element to last element checking if new time is a new record
            break;
        }
    }
    //now mi is 
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
**/
    
    