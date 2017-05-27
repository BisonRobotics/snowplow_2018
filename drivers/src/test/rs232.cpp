// test file for rs232 library
// used with Arduino serial device

#include <RS232_GenericController.h>
#include <sys/ioctl.h>
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

    sc.set_ModeNonblocking();
    int iters = 0;

    while(1) {
        if(sc.hasData()) {
            uint32_t data;
            sc.readBuffer((char*)&data, 4);
            cout << "Iters: " << ++iters << "  " << data << endl;
        }
    }

    return 0;
}
