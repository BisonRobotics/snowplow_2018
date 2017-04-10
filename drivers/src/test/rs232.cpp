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

    sc.set_BaudRate(B115200);
    sc.set_Parity  (SerialController::PARITY::OFF);
    sc.set_StopBits(SerialController::STOPBITS::_1);
    sc.set_WordSize(SerialController::WORDSIZE::_8);

    sc.start();

    cout << "Serial port opening successful" << endl;

    vector<char>* rIn = new vector<char>;
    int reads = 0;

    while(1) {
        int bAvail;
        ioctl(sc.get_FileDescriptor(), FIONREAD, &bAvail);
        if(bAvail) {
            char buf;
            sc.readBuffer(&buf, 1);
            if(buf == '\n') {
                for(int i = 0; i < rIn->size(); i++)
                    cout << rIn->at(i);

                cout << ' ' << reads << endl;
                reads++;

                rIn->clear();
                delete rIn;
                rIn = new vector<char>;
            } else {
                rIn->push_back(buf);
            }
        }
    }

    return 0;
}
