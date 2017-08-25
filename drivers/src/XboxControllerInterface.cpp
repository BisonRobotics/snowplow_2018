/*
    Implementation for XboxControllerInterface library
*/
#include <iostream>
#include <SDL/SDL.h>
#include "XboxControllerInterface.h"

void XboxController::update(void) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_JOYAXISMOTION:
                switch(event.jaxis.axis) {
                    case 0:
                        this->leftJoystickX = event.jaxis.value;
                        break;
                    case 1:
                        this->leftJoystickY = event.jaxis.value;
                        break;
                    case 2:
                        this->leftTrigger = event.jaxis.value;
                        break;
                    case 3:
                        this->rightJoystickX = event.jaxis.value;
                        break;
                    case 4:
                        this->rightJoystickY = event.jaxis.value;
                        break;
                    case 5:
                        this->rightTrigger = event.jaxis.value;
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}

int16_t XboxController::getJoyX(xBox_STICK s) {
    switch(s) {
        case xBox_LEFT:
            return leftJoystickX;
        case xBox_RIGHT:
            return rightJoystickX;
    }
}

int16_t XboxController::getJoyY(xBox_STICK s) {
    switch(s) {
        case xBox_LEFT:
            return leftJoystickY;
        case xBox_RIGHT:
            return rightJoystickY;
        default:
            std::cerr << "ERROR in XboxControllerInterface" << std::endl;
            exit(EXIT_FAILURE);
            break;
    }
}

int16_t XboxController::getTrigger(xBox_STICK s) {
    switch(s) {
        case xBox_LEFT:
            return leftTrigger;
        case xBox_RIGHT:
            return rightTrigger;
    }
}
