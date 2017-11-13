#include <RoboteQ.h>
#include <RS232_GenericController.h>
#include <string>

RoboteQInterface::RoboteQInterface(char* fileSer) {
    this->fileName = fileSer;

    // initialize serial interface
    mainSC.set_SerialPort(fileSer);
    mainSC.set_BaudRate(B115200);
    mainSC.set_Parity(Parity_Off);
    mainSC.set_StopBits(StopBits_1);
    mainSC.set_WordSize(WordSize_8);
    mainSC.start();
}

void RoboteQInterface::wheelVelocity(int velocity, WHEEL w) {
    if(w == WHEEL::LEFT) {
        velocity *= -1; // left wheel is reversed
        std::string cmd = "!G 2 " + std::to_string(velocity) + '\n';
        mainSC.writeBuffer((char*)cmd.c_str(), cmd.length());
    } else if(w == WHEEL::RIGHT) {
        std::string cmd = "!G 1 " + std::to_string(velocity) + '\n';
        mainSC.writeBuffer((char*)cmd.c_str(), cmd.length());
    }
}

void RoboteQInterface::wheelHalt(void) {
    wheelVelocity(0, WHEEL::LEFT);
    wheelVelocity(0, WHEEL::RIGHT);
}

void RoboteQInterface::setWatchdogTimer(int ms) {
    std::string cmd = "^RWD " + std::to_string(ms) + "\n";
    mainSC.writeBuffer((char*)cmd.c_str(), cmd.length());
}
