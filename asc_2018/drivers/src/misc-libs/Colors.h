#ifndef __JJC__COLORS__H__
#define __JJC__COLORS__H__

#include <SDL/SDL.h>

class ColorPallette {
public:
    ColorPallette(SDL_Surface* screen);
    uint32_t white;
    uint32_t silver;
    uint32_t grey;
    uint32_t black;
    uint32_t red;
    uint32_t maroon;
    uint32_t yellow;
    uint32_t olive;
    uint32_t lime;
    uint32_t green;
    uint32_t aqua;
    uint32_t teal;
    uint32_t blue;
    uint32_t navy;
    uint32_t fuschia;
    uint32_t purple;

private:
    SDL_Surface* screen;
};

#endif // __JJC__COLORS__H__
