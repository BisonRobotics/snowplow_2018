#include <objectDection.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <errno.h>
#include <math.h>


using namespace std;

void objectDection::init(void){

    SDL_Init(SDL_INIT_EVERYTHING);

    cout << "Opening LIDAR interface\n";
    //init the LIDAR
	li.init();
	li.setAccessMode(CLIENT);
	li.printReply();

}


float objectDection::distanceToObject(void) {

	glm::vec2 ul(200.0, 200.0);
	glm::vec2 lr(800.0, 1500.0);

	while(shouldQuit() == false) {

    	li.scanData();
		li.generateVectorData();
		vector<glm::vec2>* cartesian = li.getVectorCartesian();

		if(objectCollidesInZone(ul, lr, cartesian)) {
			cout << "object in zone" << endl;
		} else {
		    cout << "no object in the zone" << endl;
		}

	}

	SDL_Delay(100);

	return 0;
}

bool objectDection::shouldQuit(void) {
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

bool objectDection::objectCollidesInZone(glm::vec2 ul, glm::vec2 lr, vector<glm::vec2>* obj_vec) {
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
