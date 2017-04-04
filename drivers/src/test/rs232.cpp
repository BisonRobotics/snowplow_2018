// test file for rs232 library
// used with Arduino serial device

#include <RS232_GenericController.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    SerialController sc;

    sc.set_BaudRate(B9600);
    sc.set_Parity  (SerialController::PARITY::OFF);
    sc.set_StopBits(SerialController::STOPBITS::_1);
    sc.set_WordSize(SerialController::WORDSIZE::_8);

    sc.set_SerialPort("/dev/")

    return 0;
}
