#ifndef __SICK__SPOD__H__
#define __SICK__SPOD__H__

#include <vector>
#include <math.h>

struct zone__ {
    float x1, y1;
    float x2, y2;
};

struct v2f {
    float x, y;
};

float distance(v2f v1, v2f v2) {
    float xd = v1.x - v2.x;
    float yd = v1.y - v2.y;

    float d_sq = xd*xd + yd*yd;
    return sqrt(d_sq);
}

float distance(float x1, float y1, float x2, float y2) {
    float dx = x1-x2;
    float dy = y1-y2;

    float d_sq = dx*dx + dy*dy;
    return sqrt(d_sq);
}

std::vector<zone__> spodAlgo(const std::vector<v2f>& input, float threshold) {
    // no point reserving memory for the full input vector
    std::vector<zone__> results;

    const int STATE_NO_OBJ    = 0;
    const int STATE_IN_OBJ    = 1;
    const int STATE_END_OBJ   = 2;

    int current_state = STATE_NO_OBJ;

    zone__ object_zone;

    int s = input.size();
    for(int i = 0; i < s-1; i++) {
        float dist = distance(input[i], input[i+1]);

        switch(current_state) {
            case STATE_NO_OBJ: // look for the beginning of an object
                if(dist <= threshold) {
                    object_zone.x1 = input[i].x;
                    object_zone.y1 = input[i].y;
                    current_state = STATE_IN_OBJ;
                }
                break;
            case STATE_IN_OBJ:
                if(dist <= threshold) {
                    continue;
                } else {
                    object_zone.x2 = input[i].x;
                    object_zone.y2 = input[i].y;
                    current_state = STATE_END_OBJ;
                }
                break;
            case STATE_END_OBJ:
                results.push_back(object_zone);
                current_state = STATE_NO_OBJ;
                break;
            default:
                break;

        }
    }
    return results;
}

std::vector<zone__> spodReduceObjs(const std::vector<zone__>& input, float threshold) {

    std::vector<zone__> results;
    zone__ obj_zone;

    const int STATE_NO_CONNECT    = 0;
    const int STATE_IN_CONNECT    = 1;
    const int STATE_END_CONNECT   = 2;

    int current_state = STATE_NO_CONNECT;

    int s = input.size();
    for(int i = 0; i < s-1; i++) {
        float dist = distance(input[i].x2, input[i].y2, input[i+1].x1, input[i+1].y1);

        switch(current_state) {
            case STATE_NO_CONNECT:
                if(dist < threshold) {
                    obj_zone.x1 = input[i].x1;
                    obj_zone.y1 = input[i].y1;
                    current_state = STATE_IN_CONNECT;
                }
                break;
            case STATE_IN_CONNECT:
                if(dist < threshold) {
                    continue;
                } else {
                    obj_zone.x2 = input[i].x2;
                    obj_zone.y2 = input[i].y2;
                    current_state = STATE_END_CONNECT;
                }
            case STATE_END_CONNECT:
                results.push_back(obj_zone);
                current_state = STATE_NO_CONNECT;
                break;
            default:
                break;
        }

    }

    return results;
}

#endif // __SICK__SPOD__H__
