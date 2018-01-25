/*
    Nothing in this file flips the screen

    TODO: fix rectFillRot()

*/

#ifndef __JJC__SDL__PRIMITIVES__HPP__
#define __JJC__SDL__PRIMITIVES__HPP__

#include <SDL/SDL.h>
#include <iostream>
#include <math.h>
#include "3D_Render.h"

#include "LineObj.hpp"
#include "LineDraw.hpp"

#define PI 3.1415926535

namespace sdlDrawPrim {

// TODO: put macros for various colors here

LineDraw myDraw;

/* round shapes */

// draws an empty circle. does not overrwrite anything inside the circle
void circle(SDL_Surface* screen, int xCenter, int yCenter, double radius, unsigned int color) {
    SDL_Rect myRect;
    double perPointIndex = 1 / (radius*2*PI);

    for(double i = 0; i <= 2*PI; i = i + perPointIndex) {
        myRect.h = 1;
        myRect.w = 1;
        myRect.x = radius*cosf(i) + xCenter;
        myRect.y = radius*sinf(i) + yCenter;
        SDL_FillRect(screen, &myRect, color);
    }
}

// renders a circle of a single solid color
void fillCircle(SDL_Surface* screen, int xCenter, int yCenter, double radius, unsigned int color) {
    SDL_Rect myRect;
    double perPointIndex = 1 / (radius*2*PI);

    for(double i = PI; i <= 2*PI; i = i + perPointIndex) { // travel around half of the circle
        myRect.x = radius*cosf(i) + xCenter;
        myRect.y = radius*sinf(i) + yCenter;
        //myRect.h = 2 * (myRect.y - yCenter);
        myRect.h = 2 * (yCenter - myRect.y);
        myRect.w = 1;
        SDL_FillRect(screen, &myRect, color);
    }
}

// render circle and then lines going through
void target(SDL_Surface* screen, int xCenter, int yCenter, double radius, unsigned int color) {
    sdlDrawPrim::circle(screen, xCenter, yCenter, radius, color);

    SDL_Rect myRect;

    // vertical line
    myRect.w = 1;
    myRect.h = 2 * radius;
    myRect.x = xCenter;
    myRect.y = yCenter - radius;
    SDL_FillRect(screen, &myRect, color);

    // horizontal line
    myRect.w = 2 * radius;
    myRect.h = 1;
    myRect.x = xCenter - radius;
    myRect.y = yCenter;
    SDL_FillRect(screen, &myRect, color);

}

/* various types of rectangles */

// renders empty rectangle
void rectEmpty(SDL_Surface* screen, int centerX, int centerY, int height, int width, unsigned int color) {

    SDL_Rect myRect;

    // top and bottom
    myRect.w = width;
    myRect.h = 1;
    myRect.x = centerX - (width/2);
    myRect.y = centerY - (height/2);
    SDL_FillRect(screen, &myRect, color);
    //myRect.x += width;
    myRect.y += height;
    SDL_FillRect(screen, &myRect, color);

    // sides
    myRect.h = height;
    myRect.y -= height;
    myRect.w = 1;
    SDL_FillRect(screen, &myRect, color);
    myRect.x += width;
    SDL_FillRect(screen, &myRect, color);

    return;
}

// renders four LineObj's in shape of rectangle
void rectEmptyRot(SDL_Surface* screen, int centerX, int centerY, int height, int width, double degrees, unsigned int color) {

    _3D_Render_H::Point pts[4];

    // upper left
    pts[0].x = centerX - (width/2);
    pts[0].y = centerY - (height/2);

    // upper right
    pts[1].x = centerX + (width/2);
    pts[1].y = centerY - (height/2);

    // lower left
    pts[2].x = centerX - (width/2);
    pts[2].y = centerY + (height/2);

    // lower right
    pts[3].x = centerX + (width/2);
    pts[3].y = centerY + (height/2);

    for(int i = 0; i < 4; i++) {
        pts[i].x -= centerX;
        pts[i].y -= centerY;

        float x = pts[i].x;
        float y = pts[i].y;
        pts[i].x = x*cos(DEGRAD) - y*sin(DEGRAD);
        pts[i].y = x*sin(DEGRAD) + y*cos(DEGRAD);

        pts[i].x += centerX;
        pts[i].y += centerY;
    }

    Line myLine(0, 0, 0, 0);
    myLine.color = color;

    myLine.x1 = pts[0].x;
    myLine.y1 = pts[0].y;
    myLine.x2 = pts[1].x;
    myLine.y2 = pts[1].y;
    myDraw.draw(&myLine, screen);
    myLine.x1 = pts[3].x;
    myLine.y1 = pts[3].y;
    myDraw.draw(&myLine, screen);
    myLine.x2 = pts[2].x;
    myLine.y2 = pts[2].y;
    myDraw.draw(&myLine, screen);
    myLine.x1 = pts[0].x;
    myLine.y1 = pts[0].y;
    myDraw.draw(&myLine, screen);

    return;
}

// renders standard SDL_Rect but offset from centerX/Y
void rectFill(SDL_Surface* screen, int centerX, int centerY, int height, int width, unsigned int color) {

    SDL_Rect myRect;

    myRect.x = centerX - (width/2);
    myRect.y = centerY - (height/2);
    myRect.h = height;
    myRect.w = width;
    SDL_FillRect(screen, &myRect, color);

    return;
}

// a relatively long operation. renders filled rectangle at given angle of rotation. uses SDL coordinate frame
void rectFillRot(SDL_Surface* screen, int centerX, int centerY, int height, int width, double degrees, unsigned int color) {

    int smallSide = myDraw.ReturnLow(height, width);

    for(double i = 0; i <= smallSide; i += 1) { // iterate inwards, rendering consecutively smaller and smaller hollow rectangles
        rectEmptyRot(screen, centerX, centerY, height-i, width-i, degrees, color);
    }

    return;
}

}


#endif // __JJC__SDL_PRIMITIVES__HPP__
