#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <math.h>
#include <SDL/SDL.h>
#include <LidarInterface.h>

#ifndef SCALE_F
#define SCALE_F 1.0
#endif // SCALE_F

using namespace std;

void putTarget(SDL_Surface* screen);

int main(int argc, char* argv[]) {
    LidarInterface li;
    li.init(); // initialize SICK sensor communication

    li.setAccessMode(USER::CLIENT);
    li.printReply();

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(640, 640, 32, SDL_HWACCEL | SDL_DOUBLEBUF);
    int halfX = screen->w / 2;
    int halfY = screen->h / 2;

    uint32_t red = SDL_MapRGB(screen->format, 255, 0, 0);

    float factor = 3.14159265 / 360.00;

    //putTarget(screen);

    for(int ij = 0; ij < 2000; ij++) {
        li.scanData();
        vector<float> reply = li.getResults();

        SDL_FillRect(screen, NULL, NULL);
        putTarget(screen);

        for(int i = 0; i < reply.size(); i++) {
            SDL_Rect r;
            r.w = 1; r.h = 1;
            r.x = halfX + (reply[i] / SCALE_F) * cos(float(i-90) * factor);
            r.y = screen->h - (halfY + (reply[i] / SCALE_F) * sin(float(i-90) * factor));
            SDL_FillRect(screen, &r, red);
        }

        reply.clear();
        SDL_Flip(screen);

        li.getDeviceState();
        li.printReply();

    }

    //SDL_Delay(10000);

    return 0;
}

void putTarget(SDL_Surface* screen) {
    uint32_t white = SDL_MapRGB(screen->format, 255, 255, 255);

    SDL_Rect r;
    r.h = 1;
    r.w = screen->w;
    r.x = 0;
    r.y = screen->h / 2;

    SDL_FillRect(screen, &r, white);

    r.h = screen->h / 2;
    r.w = 1;
    r.x = screen->w / 2;
    r.y = 0;

    SDL_FillRect(screen, &r, white);

    for(int i = screen->h / 2; i < screen->h; i++) {
        r.x = i;
        r.y = i;
        r.w = 1;
        r.h = 1;

        SDL_FillRect(screen, &r, white);

        r.x = screen->w - r.x;

        SDL_FillRect(screen, &r, white);
    }

}

