#ifndef __OBJECTDECETION__H__
#define __OBJECTDECETION__H__

#include <glm/glm.hpp>
#include <spod.h>
#include <SDL/SDL.h>
#include <LidarInterface.h>


#define BOT_DETECT_WIDTH  1500.0 //mm
#define BOT_DETECT_HEIGHT 1500.0 //mm

#define BOT_WIDTH 686.0   // mm
#define BOT_LENGTH 1143.0 // mm

#define DETECT_THRESHOLD 800.0f // distance between pts to be considered one object (mm)
#define OBJECT_THRESHOLD 1200.0f // distance between objs to be considered together (mm)

#define VALS_PER_MEAS 541 // each is 16-bit unsigned value
#define TIME_PER_SCAN 100 // ms/scan

class objectDection{
private:
    LidarInterface li

public:

    void init(void);
    //is there an object in the zone
    bool objectCollidesInZone(glm::vec2 corner_1, glm::vec2 corner_2, vector<glm::vec2>* obj_loc);

    bool shouldQuit(void);

    //return the distance to the closest object in the zone
    float distanceToObject(void);
};

#endif //____OBJECTDECETION__H__
