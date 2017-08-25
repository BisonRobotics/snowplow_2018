#ifndef __JJC__XBOXCONTROLLERINTERFACE__H__
#define __JJC__XBOXCONTROLLERINTERFACE__H__

#include <SDL/SDL.h>

enum xBox_STICK {
    xBox_LEFT, xBox_RIGHT
};

class XboxController {
public:
    // empty constructor
    XboxController(void) { }

    // cycle events on the xbox controller
    void update(void);

    int16_t getJoyX(xBox_STICK s);
    int16_t getJoyY(xBox_STICK s);
    int16_t getTrigger(xBox_STICK s);

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
