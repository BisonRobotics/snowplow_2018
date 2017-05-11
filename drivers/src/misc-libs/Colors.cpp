#include <SDL/SDL.h>
#include "Colors.h"

ColorPallette::ColorPallette(SDL_Surface* screen) {
    this->screen = screen;
    SDL_PixelFormat* sdlf = screen->format;

    white   = SDL_MapRGB(sdlf, 0xFF, 0xFF, 0xFF);
    silver  = SDL_MapRGB(sdlf, 0xC0, 0xC0, 0xC0);
    grey    = SDL_MapRGB(sdlf, 0x80, 0x80, 0x80);
    black   = SDL_MapRGB(sdlf, 0x00, 0x00, 0x00);
    red     = SDL_MapRGB(sdlf, 0xFF, 0x00, 0x00);
    maroon  = SDL_MapRGB(sdlf, 0x80, 0x00, 0x00);
    yellow  = SDL_MapRGB(sdlf, 0xFF, 0xFF, 0x00);
    olive   = SDL_MapRGB(sdlf, 0x80, 0x80, 0x00);
    lime    = SDL_MapRGB(sdlf, 0x00, 0xFF, 0x00);
    green   = SDL_MapRGB(sdlf, 0x00, 0x80, 0x00);
    aqua    = SDL_MapRGB(sdlf, 0x00, 0xFF, 0xFF);
    teal    = SDL_MapRGB(sdlf, 0x00, 0x80, 0x80);
    blue    = SDL_MapRGB(sdlf, 0x00, 0x00, 0xFF);
    navy    = SDL_MapRGB(sdlf, 0x00, 0x00, 0x80);
    fuschia = SDL_MapRGB(sdlf, 0xFF, 0x00, 0xFF);
    purple  = SDL_MapRGB(sdlf, 0x80, 0x00, 0x80);
}


