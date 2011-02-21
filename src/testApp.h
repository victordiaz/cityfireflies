#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofTrueTypeFont.h"

#include "ofxOpenCv.h"
#include "boxAlign.h"
#include "enemies.h"
#include "constants.h"
#include "msgs.h"
#include "ofxXmlSettings.h"
//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file

#define MX 10;
#define MY 10;


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

        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif


		int camWidth;
		int camHeight;

		int imgWidth;
		int imgHeight;


        ofxCvColorImage		sourceImg;

        ofxCvGrayscaleImage 	grayImg;
		ofxCvGrayscaleImage 	grayImgBg;
		ofxCvGrayscaleImage 	grayImgDiff;

		ofxCvGrayscaleImage 	grayImgT;
		ofxCvGrayscaleImage 	grayImgW;

		//ofxCvGrayscaleImage 	grayBg;
		//ofxCvGrayscaleImage 	grayDiff;

        ofxCvContourFinder 	contourFinder;

		ofxXmlSettings XML;
	
	
		ofPoint dstPts[4]; 


		CBoxAligner         boxInputMatrix;
		CBoxAligner         boxInputReference;
		CBoxAligner         boxOutput;




		int numCols;
		int numRows;
		int tileWidth;
		int tileHeight;


		ofTrueTypeFont myfont;
		ofTrueTypeFont backCountFont;
		float matrix[15][15];
		char tileval[255];
		float amountActivity;
		float lastTimeMeasure;
		float lastTimeMeasureFade;

	ofImage fondoImg; 



		//mask
		int leftOffset;
		int topOffset;

		int screenWidth;
		int halfWidth;
		int screenHeight;
		int bHeight;
		int bWidth;
		int aWidth;

		int tileWidthScreen;
		int tileHeightScreen;

		int fadeN;

		int blobMin;
		int blobMax;


		int 				threshold;
		int 				thresholdDiff;

		bool				bLearnBg;



		vector<ofPoint> lights;


	//GAME PARAMETERS
	bool status_update;
	int last_updated;
	int status_game; // 0 waiting to run, 1 running,2 win or loose
	int status_time;
	enemies my_enemy;
	int status_level;
	//Imagenes
	ofImage start_img;
	ofImage loser_img;
	ofImage win_img;
	int loser_counter;	
	int status_time_init;
	int timmer_pause;
	msgs myMsgs;
};

#endif
