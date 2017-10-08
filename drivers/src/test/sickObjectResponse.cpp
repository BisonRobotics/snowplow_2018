#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <errno.h>
#include <math.h>

#include <SDL/SDL.h>
#include <LidarInterface.h>
#include <Colors_v2.h>
#include <spod.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <RoboteQ.h>
#include <glm/glm.hpp>

#define RQI_WHEEL_VEL 200.0
#define BOT_DETECT_WIDTH  1500.0
#define BOT_DETECT_HEIGHT 1500.0

#define BOT_WIDTH 686.0   // mm 
#define BOT_LENGTH 1143.0 // mm

// inverse of scale used to fit data on screen
#define SCALE_F 30.0f

using namespace std;

void paintTargetOnScreen(SDL_Surface* screen, uint32_t color, uint32_t plow_color);
void paintDetectZone(SDL_Surface* screen, uint32_t color, const glm::vec2& upperLeft, const glm::vec2& lowerRight);
void paintDetectZone(SDL_Surface* screen, uint32_t color, float width, float height);
void plotScaledData(SDL_Surface* screen, uint32_t color, const vector<glm::vec2>& pts, int ptSize);
bool objectCollidesInZone(glm::vec2 corner_1, glm::vec2 corner_2, vector<glm::vec2>* obj_loc);

// called once per loop
bool shouldQuit(void);

int main(int argc, char* argv[]) {

	if(argc < 2) {
		cerr << "Not enough input arguments\n";
		cerr << "Usage: " << argv[0] << " <RoboteQ mount location>\n";
		return 1; // error
	}

	// setup screen to render objects to
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen = SDL_SetVideoMode(640, 640, 32, SDL_HWACCEL | SDL_DOUBLEBUF);

	// setup color support objects
	ColorPallette cp_std(screen);
	ColorPallette cp_gfx(screen);
	cp_gfx.convertColorsToGfxMode();

	// setup roboteq interface
	cout << "Opening serial port " << argv[1] << endl;
	RoboteQInterface rqi(argv[1]); // no error checking here so dont be dumb

	cout << "Opening LIDAR interface\n";
	// setup lidar interface
	LidarInterface li;
	li.init();
	li.setAccessMode(CLIENT);
	li.printReply();

	rqi.setWatchdogTimer(0); // disable wdt
	rqi.wheelVelocity(RQI_WHEEL_VEL, Bot_LEFT);
	rqi.wheelVelocity(RQI_WHEEL_VEL, Bot_RIGHT);

	glm::vec2 ul(200.0, 200.0);
	glm::vec2 lr(800.0, 1500.0);

	while(shouldQuit() == false) {
		// setup screen for overlaying data
		SDL_FillRect(screen, NULL, NULL);
		//paintDetectZone(screen, cp_gfx.grey, BOT_DETECT_WIDTH, BOT_DETECT_HEIGHT);
		//paintDetectZone(screen, cp_gfx.grey, ul, lr);
		paintTargetOnScreen(screen, cp_std.white, cp_std.blue);

		li.scanData();
		li.generateVectorData();
		vector<glm::vec2>* cartesian = li.getVectorCartesian();

		if(objectCollidesInZone(ul, lr, cartesian)) {
			rqi.wheelHalt();
			paintDetectZone(screen, cp_gfx.yellow, ul, lr);
		} else {
			rqi.wheelVelocity(RQI_WHEEL_VEL, Bot_LEFT);
			rqi.wheelVelocity(RQI_WHEEL_VEL, Bot_RIGHT);
			paintDetectZone(screen, cp_gfx.green, ul, lr);
		}

		plotScaledData(screen, cp_std.red, *cartesian, 2);

		//SDL_Delay(100);
		SDL_Flip(screen);
	}

	rqi.wheelHalt();

	//rqi.wheelVelocity(0, Bot_RIGHT);
	//rqi.wheelVelocity(0, Bot_LEFT);
	SDL_Delay(100);

	return 0;
}

bool shouldQuit(void) {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				return true;
				break;
			default:
				break;
		}
	}
	return false;
}

void paintTargetOnScreen(SDL_Surface* screen, uint32_t color, uint32_t plow_color) {
	SDL_Rect r;
	
	// plot scale model of snowplow
	r.w = BOT_WIDTH / SCALE_F;
	r.h = BOT_LENGTH / SCALE_F;
	r.x = screen->w / 2 - (r.w / 2);
	r.y = screen->h / 2;
	SDL_FillRect(screen, &r, plow_color);

	r.x = 0;
	r.y = screen->h / 2;
	r.h = 1;
	r.w = screen->w;

	SDL_FillRect(screen, &r, color);

	r.x = screen->w / 2;
	r.y = 0;
	r.w = 1;
	r.h = screen->h / 2;

	SDL_FillRect(screen, &r, color);


    for(int i = screen->h / 2; i < screen->h; i++) {
        r.x = i;
        r.y = i;
        r.w = 1;
        r.h = 1;

        SDL_FillRect(screen, &r, color);

        r.x = screen->w - r.x;

        SDL_FillRect(screen, &r, color);
    }
}

void paintDetectZone(SDL_Surface* screen, uint32_t color, const glm::vec2& upperLeft, const glm::vec2& lowerRight) {
	glm::vec2 ul = upperLeft  / SCALE_F;
	glm::vec2 lr = lowerRight / SCALE_F;
	
	int min_x, min_y, max_x, max_y;
	int half_x = screen->w / 2;
	int half_y = screen->h / 2;

	min_x = (ul.x < lr.x ? ul.x : lr.x);
	min_y = (ul.y < lr.y ? ul.y : lr.y);
	max_x = (ul.x > lr.x ? ul.x : lr.x);
	max_y = (ul.y > lr.y ? ul.y : lr.y);

	min_x += half_x;
	max_x += half_x;
	min_y += half_y;
	max_y += half_y;

	min_y = screen->h - min_y;
	max_y = screen->h - max_y;

	rectangleColor(screen, min_x, min_y, max_x, max_y, color);
}

void paintDetectZone(SDL_Surface* screen, uint32_t color, float width, float height) {
	glm::vec2 upperLeft(-(width/2.0), height);
	glm::vec2 lowerRight((width/2.0), 0.0);

	paintDetectZone(screen, color, upperLeft, lowerRight);
}

void plotScaledData(SDL_Surface* screen, uint32_t color, const vector<glm::vec2>& pts, int ptSize) {
	float offset = ptSize / 2;

	int half_screen_w = screen->w / 2;
	int half_screen_h = screen->h / 2;

	int s = pts.size();
	for(int i = 0; i < s; i++) {
		SDL_Rect r;
		r.h = ptSize;
		r.w = ptSize;
		r.x = pts[i].x / SCALE_F + half_screen_w;
		r.y = pts[i].y / SCALE_F + half_screen_h;

		r.y = screen->h - r.y;
		SDL_FillRect(screen, &r, color);
	}
}

bool objectCollidesInZone(glm::vec2 ul, glm::vec2 lr, vector<glm::vec2>* obj_vec) {
	float min_x, min_y, max_x, max_y;

	min_x = (ul.x < lr.x ? ul.x : lr.x);
	min_y = (ul.y < lr.y ? ul.y : lr.y);
	max_x = (ul.x > lr.x ? ul.x : lr.x);
	max_y = (ul.y > lr.y ? ul.y : lr.y);

	for(int i = 0; i < obj_vec->size(); i++) {
		glm::vec2 obj = obj_vec->at(i);
		if(obj.x >= min_x && obj.x <= max_x) {
			if(obj.y >= min_y && obj.y <= max_y)
				return true;
		}
	}	
	return false;
}

