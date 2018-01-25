#include <SDL/SDL.h>
#include "KeyboardEvent.h"

void KeyboardEventHandler::setKeyPressedCallback(void(*pressedFunc)(SDLKey key)) {
    this->eventPressCallback = pressedFunc;
    this->pressedCallbackSet = true;
}

void KeyboardEventHandler::setKeyReleasedCallback(void(*releasedFunc)(SDLKey key)) {
    this->eventReleaseCallback = releasedFunc;
    this->releasedCallbackSet  = true;
}

void KeyboardEventHandler::loopEvents(void) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_KEYDOWN && pressedCallbackSet)
            eventPressCallback(event.key.keysym.sym);
        else if(event.type == SDL_KEYUP && releasedCallbackSet)
            eventReleaseCallback(event.key.keysym.sym);
    }
}
