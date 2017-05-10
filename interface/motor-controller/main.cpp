#include <SDL/SDL.h>
#include <iostream>
#include <thread>
#include <vector>
#include <string>

#include "KeyboardEvent.h"
#include "RS232_Serial.hpp"
#include "NamedPipeUtility.h"

#define UPDATE_TIME 2000

using namespace std;

void initMotorController(CppSerial cs) {
    char* resetWD = "^RWD 1000\n";
    cs.writeBuffer(resetWD, strlen(resetWD));
}

int leftMotor = 0;
int riteMotor = 0;
bool quitLoop = false;

void keyPressed(SDLKey key) {
    switch(key) {
        // right motor
        case 'w':
            riteMotor += 100;
            break;
        case 's':
            riteMotor -= 100;
            break;
        // left motor
        case 'q':
            leftMotor += 100;
            break;
        case 'a':
            leftMotor -= 100;
            break;
        case 'p':
            quitLoop = true;
            break;
        default:
            break;
    }
}

int main(int argc, char* argv[]) {

    CppSerial cs("/dev/ttyUSB0");
    cs.set_BaudRate(B115200);
    cs.set_ParityDisable(); // no parity bit
    cs.set_StopBit1();      // one stop bit
    cs.set_WordSize8();     // 8-bit word
    cs.set_Start();         // save configuration

    initMotorController(cs);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(200, 200, 32, SDL_HWACCEL);

    KeyboardEventHandler keh;
    keh.setKeyPressedCallback(keyPressed);

    while(!quitLoop) {
        keh.loopEvents();
        system("clear");
        cout << "Motor speeds:" << endl;
        cout << "\tLeft:  " << leftMotor << endl;
        cout << "\tRight: " << riteMotor << endl << endl;

        string command1 = "!G 2 " + to_string(-1 * leftMotor) + '\n';
        string command2 = "!G 1 " + to_string(riteMotor)      + '\n';

        cs.writeBuffer((char*)command1.c_str(), command1.length());
        cs.writeBuffer((char*)command2.c_str(), command2.length());
    }

    return 0;
}


















