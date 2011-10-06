#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofTrueTypeFont.h"

#include "enemies.h"
#include "constants.h" 
#include "imageproc.h" 
#include "msgs.h"
#include "ofxXmlSettings.h"
#include "particleSourceHandler.h"
#include <sstream>
#include "ofxSimpleGuiToo.h"
#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/FileChannel.h>
#include <Poco/LocalDateTime.h>
#include <Poco/DateTimeFormatter.h>

#define MX 10;
#define MY 10;


using Poco::Logger;



class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void resetMatrix();
		void loadSettings(); 
		void saveSettings(); 

		ofxXmlSettings XML;
	
		int tileWidth;
		int tileHeight;

	
		ofTrueTypeFont myfont;
		ofTrueTypeFont backCountFont;
		char tileval[255];
		float amountActivity;
		float lastTimeMeasure;
		float lastTimeMeasureFade;

		ofImage fondoImg; 


		int tileWidthScreen;
		int tileHeightScreen;

		int fadeN;	
		imageproc mImageproc; 
		ParticleSourceHandler mparticles;
		Logger *mlogger;
		float gameStartTime;
		

	//GAME PARAMETERS
	int BORN_TIME[3];
	bool status_update;
	int last_updated;
	int status_game; // 0 waiting to run, 1 running,2 win or loose
	int status_time;
	int status_draw_msg1;
	enemies my_enemy;
	int status_level;
	bool status_first_dead; // we 
	//Imagenes
	ofImage start_img;
	ofImage loser_img;
	ofImage win_img;
	ofImage enemy_transition[2];
	int loser_counter;	
	int status_time_init;
	int timmer_pause;

	msgs myMsgs; 
	int time_intro_msgs; 
	bool drawing_text_finished_flag; 
	int msg_type; 
	bool with_explosions;
	//bool draw_text_finish;
    bool	saveButton;

};

#endif
