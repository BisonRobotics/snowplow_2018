#ifndef __JJC__XBOXCONTROLLERINTERFACE__H__
#define __JJC__XBOXCONTROLLERINTERFACE__H__

#include <SDL/SDL.h>

class XboxController {
public:
    // empty constructor
    XboxController(void) { }

    void update(void);

    enum STICK {
        LEFT, RIGHT
    };

    int16_t getJoyX(STICK s);
    int16_t getJoyY(STICK s);
    int16_t getTrigger(STICK s);

private:
    // left joystick x/y values
    int16_t leftJoystickX = 0;
    int16_t leftJoystickY = 0;

    // right joystick x/y values
    int16_t rightJoystickX = 0;
    int16_t rightJoystickY = 0;

    // triggers
    int16_t rightTrigger = -32768;
    int16_t leftTrigger  = -32768;
};

#endif // __JJC__XBOXCONTROLLERINTERFACE__H__
