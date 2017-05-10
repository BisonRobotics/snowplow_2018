#ifndef __JJC__KEYBOARDEVENT__H__
#define __JJC__KEYBOARDEVENT__H__

#include <SDL/SDL.h>

class KeyboardEventHandler {
public:
    // default constructor, does nothing
    KeyboardEventHandler(void) { ; }

    // set the appropiate callback functions
    void setKeyPressedCallback(void(*pressedFunc)(SDLKey key));
    void setKeyReleasedCallback(void(*releasedFunc)(SDLKey key));

    void loopEvents(void);

private:
    // has the callback for pressed keys been set?
    bool pressedCallbackSet = false;

    // callback for keyboard press events
    void (*eventPressCallback)(SDLKey key);

    // has the callback for released keys been set?
    bool releasedCallbackSet = false;

    // callback for keyboard release events
    void (*eventReleaseCallback)(SDLKey key);
};

#endif // __JJC__KEYBOARDEVENT__H__
