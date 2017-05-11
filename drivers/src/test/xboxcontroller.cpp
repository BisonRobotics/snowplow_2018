#include <iostream>
#include <SDL/SDL.h>

#include <SDL_Primitives.hpp>
#include <XboxControllerInterface.h>
#include <Colors.h>

using namespace std;

bool quit = false;

float mapFloat(float in_min, float in_max, float x, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32, SDL_HWACCEL | SDL_DOUBLEBUF);

    ColorPallette cp(screen);
    XboxController xc;

    int jStick = SDL_NumJoysticks();
    cout << "Joysticks: " << jStick << endl;


    if(jStick == 0) {
        SDL_Quit();
        return -1;
    }

    SDL_Joystick* j = SDL_JoystickOpen(0);
    cout << "Axes:      " << SDL_JoystickNumAxes(j);

    int rStartX = 430;
    int rStartY = 240;

    int rEndX = rStartX, rEndY = rStartY;

    int lStartX = 210;
    int lStartY = 240;

    int lEndX = lStartX, lEndY = lStartY;

    SDL_Rect lTrig;
    lTrig.y = 0;
    lTrig.x = 0;
    lTrig.w = 20;

    SDL_Rect rTrig;
    rTrig.y = 0;
    rTrig.x = 620;
    rTrig.w = 20;

    // we have a joystick!
    while(!quit) {
        SDL_FillRect(screen, NULL, NULL);
        sdlDrawPrim::circle(screen, lStartX, 240, 100, cp.aqua);
        sdlDrawPrim::circle(screen, rStartX, 240, 100, cp.aqua);

        xc.update();

        lEndX = lStartX + mapFloat(-32656.0, 32656.0, xc.getJoyX(STICK::LEFT), -90.0, 90.0);
        lEndY = lStartY + mapFloat(-32656.0, 32656.0, xc.getJoyY(STICK::LEFT), -90.0, 90.0);

        rEndX = rStartX + mapFloat(-32656.0, 32656.0, xc.getJoyX(STICK::RIGHT), -90.0, 90.0);
        rEndY = rStartY + mapFloat(-32656.0, 32656.0, xc.getJoyY(STICK::RIGHT), -90.0, 90.0);

        lTrig.h = mapFloat(-32656.0, 32656.0, xc.getTrigger(STICK::LEFT),  0.0, 480.0);
        rTrig.h = mapFloat(-32656.0, 32656.0, xc.getTrigger(STICK::RIGHT), 0.0, 480.0);

        sdlDrawPrim::target(screen, lEndX, lEndY, 10, cp.red);
        sdlDrawPrim::target(screen, rEndX, rEndY, 10, cp.fuschia);

        SDL_FillRect(screen, &lTrig, cp.lime);
        SDL_FillRect(screen, &rTrig, cp.lime);

        SDL_Flip(screen);
    }

    SDL_Quit();
    return 0;

}

