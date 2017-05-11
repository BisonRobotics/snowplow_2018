#ifndef RENDER_API_v1
#define RENDER_API_v1

#include <iostream>
#include "LineDraw.hpp"
#include "LineObj.hpp"
#include <SDL/SDL.h>

#define DEGRAD degrees/57.295779

using namespace std;

namespace _3D_Render_H {

LineDraw drawer;
Line line(0, 0, 0, 0);

//struct containing all data needed for defining single points in 3D space
struct Point {
    float x;
    float y;
    float z;
};

//make cube struct

//accepts an arbitrarily large array of points. performs axis rotation on each point in array
void axis_rotate(char axis, float degrees, Point a[], int pts, bool output){
    float x, y, z;
    for(int i = 0; i < pts; i++){
        x = a[i].x; y = a[i].y; z = a[i].z;
        switch(axis){
            case 88:
            case 120: //x-rotation
                if(output) cout << "x rotation" << endl;
                a[i].y = y*cosf(DEGRAD) - z*sinf(DEGRAD);
                a[i].z = y*sinf(DEGRAD) + z*cosf(DEGRAD);
                break;
            case 89:
            case 121: //y-rotation
                if(output) cout << "y rotation" << endl;
                a[i].x = x*cosf(DEGRAD) + z*sinf(DEGRAD);
                a[i].z = -x*sinf(DEGRAD) + z*cosf(DEGRAD);
                break;
            case 90:
            case 122: //z-rotation
                if(output) cout << "z rotation" << endl;
                a[i].x = x*cosf(DEGRAD) - y*sinf(DEGRAD);
                a[i].y = x*sinf(DEGRAD) + y*cosf(DEGRAD);
                break;
            default:
                cout << "Undefined operation in axis_rotation" << endl;
		break;
        }
    }
}

//maps

//accepts an arbitrarily large array of points, performs axis translation on each point in array
void axis_translate(char axis, float distance, Point a[], int pts, bool output){
    for(int i = 0; i < pts; i++){
        switch(axis){
            case 88:
            case 120:
                if(output) cout << "x rotation" << endl;
                a[i].x += distance;
		break;
	    case 89:
	    case 121:
		if(output) cout << "y rotation" << endl;
		a[i].y += distance;
		break;
	    case 90:
	    case 122:
	        if(output) cout << "z rotation" << endl;
		a[i].z += distance;
		break;
	    default:
		cout << "Undefined operation in axis_translate" << endl;
		break;
       	}
    }
}

//accepts an arbitrarily large array of points and scales them with respect to the origin


//easily fill out Point
void fillPoint(Point* pt, int x, int y, int z){
    pt->x = x;
    pt->y = y;
    pt->z = z;
}

//applies array of points to screen. Does not flip screen, that is left to programmer.
//b[][2] contains all pairs of points which are connected by lines in the virtual space.
void plotLines(SDL_Surface* screen, Point a[], int sizea, int b[][2], int conns, int halfX, int halfY, Uint32 color){
    line.color = color;
    for(int i = 0; i < conns; i++){
        line.x1 = halfX + a[b[i][0]].x;
	line.y1 = halfY - a[b[i][0]].z;
	line.x2 = halfX + a[b[i][1]].x;
	line.y2 = halfY - a[b[i][1]].z;
	drawer.draw(&line, screen, 1);
    }
    SDL_Flip(screen);
}

}

#endif //RENDER_API_v1
