//
//  ranking.h
//  plaza
//
//  Created by Sergio Manuel Galán Nieto on 31/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#ifndef _RANKING_
#define _RANKING_
#include "ofTrueTypeFont.h"
#include "ofMain.h"
#include "constants.h"
/****
 Behavior:
 The game ends with the players winning the last level. Before the message they see a ranking with all the better times.
 In case their time is in the ranking it appears highlighted with a message
 If their time is not one of the bests, they get a different message.
 
 
 things to do on this ranking: 
 -- Receive a new time
 -Compare with previous time
 --Draw the ranking screen 
 
 
 **/

const int ITEMS_RANKING = 6;

class ranking{
    

    
private:
    int rankinglist[ITEMS_RANKING];     //this is the ranking list
    int mustHighlight; 
    ofTrueTypeFont myfont;
    float startTime;
    
public:
    ranking(): startTime(0){}
    int addTime(int);
    void setup();
    bool draw();
    bool drawCongrats(int);
//    ranking();
    

};

#endif
