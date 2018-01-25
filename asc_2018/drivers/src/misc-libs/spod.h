#ifndef __SICK__SPOD__H__
#define __SICK__SPOD__H__

#include <vector>
#include <math.h>
#include <limits>

#ifndef FLOAT_MAXIMUM_VAL
#define FLOAT_MAXIMUM_VAL std::numeric_limits<float>::max()
#else
#error FLOAT_MAXIMUM_VAL already defined
#endif // FLOAT_MAXIMUM_VAL

#ifndef FLOAT_MINIMUM_VAL
#define FLOAT_MINIMUM_VAL std::numeric_limits<float>::min()
#else
#error FLOAT_MINIMUM_VAL already defined
#endif // FLOAT_MINIMUM_VAL

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

// this scanning algorithm finds the maximum and minimum x/y values
//  - use a circling function to maximize coverage
std::vector<zone__> spodAlgoMaximizeCoverage(const std::vector<v2f>& input, float threshold) {
    // result vector
    std::vector<zone__> results;

    const int STATE_NO_OBJ    = 0;
    const int STATE_IN_OBJ    = 1;
    const int STATE_END_OBJ   = 2;

    int current_state = STATE_NO_OBJ;

    zone__ object_zone;

    float // multiple float declarations
    max_x = FLOAT_MINIMUM_VAL, // can only get larger
    max_y = FLOAT_MINIMUM_VAL, // ...

    min_x = FLOAT_MAXIMUM_VAL, // can only get smaller
    min_y = FLOAT_MAXIMUM_VAL; // ...

    int s = input.size();
    for(int i = 0; i < s-1; i++) {
        float dist = distance(input[i], input[i+1]);

        switch(current_state) {
            case STATE_NO_OBJ: // look for the beginning of an object
                if(dist <= threshold) {

                    if(input[i].x < min_x)
                        min_x = input[i].x;

                    if(input[i].x > max_x)
                        max_x = input[i].x;

                    if(input[i].y < min_y)
                        min_y = input[i].y;

                    if(input[i].y > max_y)
                        max_y = input[i].y;

                    // ----------------------------------------

                    if(input[i+1].x < min_x)
                        min_x = input[i+1].x;

                    if(input[i+1].x > max_x)
                        max_x = input[i+1].x;

                    if(input[i+1].y < min_y)
                        min_y = input[i+1].y;

                    if(input[i+1].y > max_y)
                        max_y = input[i+1].y;

                    current_state = STATE_IN_OBJ;
                }
                break;
            case STATE_IN_OBJ:
                if(dist <= threshold) {

                    if(input[i+1].x < min_x)
                        min_x = input[i+1].x;

                    if(input[i+1].x > max_x)
                        max_x = input[i+1].x;

                    if(input[i+1].y < min_y)
                        min_y = input[i+1].y;

                    if(input[i+1].y > max_y)
                        max_y = input[i+1].y;

                    continue;
                } else {
                    current_state = STATE_END_OBJ;
                }
                break;
            case STATE_END_OBJ:
                // finalize object_zone
                object_zone.x1 = min_x;
                object_zone.y1 = min_y;
                object_zone.x2 = max_x;
                object_zone.y2 = max_y;

                results.push_back(object_zone);

                // reset object zone
                max_x = FLOAT_MINIMUM_VAL;
                max_y = FLOAT_MINIMUM_VAL;
                min_x = FLOAT_MAXIMUM_VAL;
                min_y = FLOAT_MAXIMUM_VAL;

                current_state = STATE_NO_OBJ;
                break;
            default:
                break;

        }
    }
    return results;
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
