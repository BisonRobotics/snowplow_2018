/*
    Implementation of RoboteQ interface
*/

#include <iostream>
#include <RoboteQ.h>
#include <RS232_GenericController.h>
#include <string>

RoboteQInterface::RoboteQInterface(char* fileSer) {
    this->fileName = fileSer;

    // initialize serial interface
    mainSC.set_SerialPort(fileSer);
    mainSC.set_BaudRate(B115200);
    mainSC.set_Parity(SerialController::PARITY::OFF);
    mainSC.set_StopBits(SerialController::STOPBITS::_1);
    mainSC.set_WordSize(SerialController::WORDSIZE::_8);
    mainSC.start();
}

void RoboteQInterface::wheelVelocity(int velocity, Bot_WHEEL w) {
    if(w == Bot_LEFT) {
        velocity *= -1; // left wheel is reversed
        std::string cmd = "!G 2 " + std::to_string(velocity) + '\n';
        mainSC.writeBuffer((char*)cmd.c_str(), cmd.length());
    } else if(w == Bot_RIGHT) {
        std::string cmd = "!G 1 " + std::to_string(velocity) + '\n';
        mainSC.writeBuffer((char*)cmd.c_str(), cmd.length());
    } else {
        std::cerr << "ERROR in RoboteQInterface\n";
        wheelHalt();
        exit(EXIT_FAILURE);
    }
}

void RoboteQInterface::wheelHalt(void) {
    wheelVelocity(0, Bot_LEFT);
    wheelVelocity(0, Bot_RIGHT);
}

void RoboteQInterface::setWatchdogTimer(int ms) {
    std::string cmd = "^RWD " + std::to_string(ms) + "\n";
    mainSC.writeBuffer((char*)cmd.c_str(), cmd.length());
}
