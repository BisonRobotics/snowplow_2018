#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <math.h>
#include <SDL/SDL.h>
#include <LidarInterface.h>

#ifndef SCALE_F
#define SCALE_F 10.0
#endif // SCALE_F

using namespace std;

int main(int argc, char* argv[]) {
    LidarInterface li;
    li.init(); // initialize SICK sensor communication

    cout << "SICK sensor communication initialized" << endl;

    li.setAccessMode(USER::CLIENT);
    li.scanData();
    vector<float> reply = li.getResults();

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(640, 640, 32, SDL_HWACCEL | SDL_DOUBLEBUF);
    int halfX = screen->w / 2;
    int halfY = screen->h / 2;

    uint32_t red = SDL_MapRGB(screen->format, 255, 0, 0);

    for(int i = 0; i < reply.size(); i++) {
        SDL_Rect r;
        r.w = 1; r.h = 1;
        r.x = halfX + (reply[i] / SCALE_F) * cos(float(i) / 2);
        r.y = halfY + (reply[i] / SCALE_F) * sin(float(i) / 2);
        SDL_FillRect(screen, &r, red);
    }

    while(1)
        SDL_Flip(screen);

    return 0;
}
