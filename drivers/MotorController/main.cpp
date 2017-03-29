#include <SDL/SDL.h>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include "RS232_Serial.hpp"
#include "NamedPipeUtility.h"

#define UPDATE_TIME 2000

using namespace std;

typedef struct {

int rightMotorSpeed;
int leftMotorSpeed;

} motorControlStructure;

void initMotorController(CppSerial cs) {
    char* resetWD = "^RWD 0\n";
    cs.writeBuffer(resetWD, strlen(resetWD));
}

void trackThread(void) {

    CppSerial cs("/dev/ttyUSB0");
    cs.set_BaudRate(B115200);
    cs.set_ParityDisable(); // no parity bit
    cs.set_StopBit1();      // one stop bit
    cs.set_WordSize8();     // 8-bit word
    cs.set_Start();         // save configuration

    initMotorController(cs);

    int currentMotor = 0;
    for(;;) {
        if(currentMotor > motorWanted)
            currentMotor -= 4;
        if(currentMotor < motorWanted)
            currentMotor += 4;
        timedMotorAdjust = currentMotor;

        if(needMotorControllerHandshake) {
            cs.set_Start();
            initMotorController(cs);
            needMotorControllerHandshake = false;

            cout << "motor controller handshake completed" << endl;
        }

        if(hasMotorControl) {
            string buf = "!G " + to_string(currentMotor) + '\n';
            cs.writeBuffer((char*)buf.c_str(), strlen(buf.c_str()));
        } else {
            currentMotor = 0;
            cs.writeBuffer("!G 0\n", strlen("!G 0\n")); // emergency stop
        }

        SDL_Delay(10);
    }

}

int main(int argc, char* argv[]) {

    int motorSpeed = 0;



    return 0;
}


















