//LineObj implementation file
//contains definitions of the LineObj

#ifndef __JJC__LINEOBJ__SDMLBL__HPP__
#define __JJC__LINEOBJ__SDMLBL__HPP__

#include <SDL/SDL.h>

struct Line {
    int x1;
    int y1;
    int x2;
    int y2;
    Uint32 color;
    Line(Uint32 _color, int startx = 0, int starty = 0, int endx = 0, int endy = 0);
    Line(void);
};

Line::Line(Uint32 _color, int startx, int starty, int endx, int endy) {
    color = _color;
    x1 = startx;
    y1 = starty;
    x2 = endx;
    y2 = endy;
}

Line::Line(void){
	;
}

#endif // __JJC__LINEOBJ__SDMLBL__HPP__
