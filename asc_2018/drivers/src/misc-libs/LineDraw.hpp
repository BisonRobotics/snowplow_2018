/*
    Date: Jun 2, 2016

    Big update
        This library now only draws lines 1 pixel wide

---------------------------------------------------------------------------------------------------

    Date: July 9, 2016

    Big Update
        - Library now dynamically chooses between two optimized rendering routines
        - Previously un-optimized routine renders *about* 5 times faster. Other routine
        is relatively unchanged, mostly just variable name changes
        - Lines can now be rendered partially off-screen, though this may result in
        some performace degradation. Future revision(s) will allow user to conditionally
        compile either one way or the other
*/

#ifndef __JJC__LINEDRAW__SDMLBL__HPP__
#define __JJC__LINEDRAW__SDMLBL__HPP__

#include <math.h>
#include <SDL/SDL.h>
#include "LineObj.hpp"

class LineDraw {
public:
        void draw(Line* ln, SDL_Surface* surface, Uint32 color);
        void draw(Line* ln, SDL_Surface* surface); //color supplied by ln
        int SortDelta(int i, int j);
        int ReturnLow(int i, int j);
        int ReturnHigh(int i, int j);
};

void LineDraw::draw(Line* ln, SDL_Surface* surface, Uint32 color) {
    SDL_Rect pixel;

    double deltaY = ln->y1 - ln->y2;
    double deltaX = ln->x1 - ln->x2;

    if(deltaX == 0) { // line is perfectly vertical and so cant be rendered with slope-intercept equation
        pixel.x = ln->x1;
        pixel.w = 1;
        pixel.y = ReturnLow(ln->y1, ln->y2);
        pixel.h = ReturnHigh(ln->y1, ln->y2) - ReturnLow(ln->y1, ln->y2);
        SDL_FillRect(surface, &pixel, color);
    }

    double angle = deltaY / deltaX;
    double yIntercept = ln->y1 - (angle*ln->x1);

    if(angle <= 1 && angle >= -1) { // y = f(x)

        // f(x) = angle*x + yInt

        int lowX =   ReturnLow(ln->x1, ln->x2);
        int highX = ReturnHigh(ln->x1, ln->x2);

        /* perform calculation on lowX <= i <= highX, y = mx + b */
        for(int i = lowX; i <= highX; i++) {
            pixel.h = 1;
            pixel.w = 1;
            pixel.x = i;
            pixel.y = (angle*i) + yIntercept;
            SDL_FillRect(surface, &pixel, color);
        }

    } else { // x = f(y)

        int lowY =   ReturnLow(ln->y1, ln->y2);
        int highY = ReturnHigh(ln->y1, ln->y2);

        /* perform calculation on lowY <= i <= highY */
        for(int i = lowY; i <= highY; i++) {
            pixel.h = 1;
            pixel.w = 1;
            pixel.y = i;
            pixel.x = (i-yIntercept) / angle;
            SDL_FillRect(surface, &pixel, color);
        }

    }

}

void LineDraw::draw(Line* ln, SDL_Surface* surface) {
    draw(ln, surface, ln->color);
}

int LineDraw::SortDelta(int x2, int x1){
    if(x2 > x1){
        return x2 - x1;
    } else if(x1 > x2){
        return x1 - x2;
    } else {
        return 0;
    }
}

int LineDraw::ReturnHigh(int i, int j){
    if(i == j){
        return i;
    } else if(i < j){
        return j;
    } else {
        return i;
    }
}

int LineDraw::ReturnLow(int i, int j){
    if(i == j){
        return j;
    } else if(i < j){
        return i;
    } else {
        return j;
    }
}

#endif // __JJC__LINEDRAW__SDMLBL__HPP__
