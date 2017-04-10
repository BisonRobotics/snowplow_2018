// test file for rs232 library
// used with Arduino serial device

#include <RS232_GenericController.h>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

    SerialController sc;

    sc.set_SerialPort("/dev/ttyUSB0");

    sc.set_BaudRate(B9600);
    sc.set_Parity  (SerialController::PARITY::OFF);
    sc.set_StopBits(SerialController::STOPBITS::_1);
    sc.set_WordSize(SerialController::WORDSIZE::_8);

    sc.start();

    cout << "Serial port opening successful" << endl;

    vector<char> rIn;

    while(1) {
        int bAvail;
        ioctl()
        char buf;
        sc.readBuffer(&buf, 1);
        if(buf == '\n') {
            cout << &rIn[0] << endl;
            rIn.clear();
        } else {
            rIn.push_back(buf);
        }
    }

    return 0;
}
