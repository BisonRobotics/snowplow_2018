#include <iostream>

#include <XboxControllerInterface.h>
#include <RoboteQ.h>

using namespace std;

float mapFloat(float in_min, float in_max, float x, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING); // initialize joysticks

    RoboteQInterface rqi("/dev/ttyUSB0");
    XboxController xc;

    SDL_Joystick* j = 0;

    if(SDL_NumJoysticks()) {
        j = SDL_JoystickOpen(0);
    } else {
        SDL_Quit();
        return -1;
    }

    int rightSpeed = 0;
    int leftSpeed  = 0;

    xBox_STICK sRight = xBox_RIGHT;
    xBox_STICK sLeft  = xBox_LEFT;

    Bot_WHEEL lMotor = Bot_LEFT;
    Bot_WHEEL rMotor = Bot_RIGHT;

    while(1) {
        xc.update();

        rightSpeed = -1 * mapFloat(-32768.0, 32767.0, xc.getJoyY(sRight), -1000.0, 1000.0);
        leftSpeed  = -1 * mapFloat(-32768.0, 32767.0, xc.getJoyY(sLeft),  -1000.0, 1000.0);

        if(rightSpeed < 100 && rightSpeed > -100)
            rightSpeed = 0;

        if(leftSpeed < 100 && leftSpeed > -100)
            leftSpeed = 0;

        cout  << "Left speed: " << leftSpeed << " Right speed: " << rightSpeed << endl;

        rqi.wheelVelocity(rightSpeed, rMotor);
        rqi.wheelVelocity(leftSpeed,  lMotor);
    }

}
