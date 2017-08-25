#ifndef __JJC__ROBOTEQ__H__
#define __JJC__ROBOTEQ__H__

#include <iostream>
#include <RS232_GenericController.h>

enum Bot_WHEEL {
    Bot_LEFT, Bot_RIGHT
};

class RoboteQInterface {
private:
    // serial interface used internally by RoboteQInterface
    SerialController mainSC;

    // RoboteQ can be reached by reading/writing this file
    char* fileName;

public:
    // constructor given a
    RoboteQInterface(char* fileSer);

    // set the corresponding wheel to a given velocity
    void wheelVelocity(int velocity, Bot_WHEEL w);

    // bring speed of both wheels to zero immediately
    void wheelHalt(void);

    // set watchdog timer to the specified number of milliseconds
    void setWatchdogTimer(int ms);

};

#endif // __JJC__ROBOTEQ__H__
