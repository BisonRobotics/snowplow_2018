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

int16_t XboxController::getJoyX(XboxController::STICK s) {
    switch(s) {
        case XboxController::STICK::LEFT:
            return leftJoystickX;
        case XboxController::STICK::RIGHT:
            return rightJoystickX;
    }
}

int16_t XboxController::getJoyY(XboxController::STICK s) {
    switch(s) {
        case XboxController::STICK::LEFT:
            return leftJoystickY;
        case XboxController::STICK::RIGHT:
            return rightJoystickY;
    }
}

int16_t XboxController::getTrigger(STICK s) {
    switch(s) {
        case STICK::LEFT:
            return leftTrigger;
        case STICK::RIGHT:
            return rightTrigger;
    }
}
