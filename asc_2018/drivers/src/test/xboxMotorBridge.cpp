#include <iostream>

#include <XboxControllerInterface.h>
#include <RoboteQ.h>
#include <unistd.h>
#include <EncoderInterface.h>

using namespace std;

float mapFloat(float in_min, float in_max, float x, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING); // initialize joysticks

    if(argc != 2) {
        cerr << "Not enough arguments\n";
        cerr << "Usage: <progname> <seial device mount location>\n";
        exit(EXIT_FAILURE);
    }

    RoboteQInterface rqi(argv[1]); // always first argument to program
    XboxController xc;
    // ArduinoEncoder ard = ArduinoEncoder("??");//set udev rules

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

    rqi.setWatchdogTimer(200); // 200 ms

    while(1) {
        xc.update();

        const float max_speed = 500.0;
        const float min_speed = -500.0;

        rightSpeed = -1 * mapFloat(-32768.0, 32767.0, xc.getJoyY(sRight), min_speed, max_speed);
        leftSpeed  = -1 * mapFloat(-32768.0, 32767.0, xc.getJoyY(sLeft),  min_speed, max_speed);

        if(rightSpeed < 150 && rightSpeed > -150){
            rightSpeed = 0;
        }
        if(leftSpeed < 150 && leftSpeed > -150){
            leftSpeed = 0;
        }

        cout << "Leftjo: " << leftSpeed << " Rightjoy: " << rightSpeed << endl;


        rqi.wheelVelocity(rightSpeed, rMotor);
        rqi.wheelVelocity(leftSpeed,  lMotor);

        usleep(50000);
    }

}
