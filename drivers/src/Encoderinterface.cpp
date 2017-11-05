/*
this file was made by Andrew Vetter.
This progrma is used for testing and deveoplment of the ecnoder driver class.
*/
//#include <Encoder_arduino.h>
#include <iostream>
#include <unistd.h>
#include "../include/RS232_GenericController.h"

using namespace std

void readChunk(SerialController& sc, char* buf, int n) {
    int bytes_read = 0;

    while(bytes_read < n) {
        bytes_read += sc.readBuffer(buf+bytes_read, n-bytes_read);
    }
}

void arduino_encoder(){

    //arduino.set_SerialPort(port);
    encoders.set_BaudRate(B57600);
    encoders.set_Parity(Parity_Off);
    encoders.set_WordSize(WordSize_8);
    encoders.set_StopBits(StopBits_1);
    encoders.start();


}

int main(int argc, char *argv[]) {

    if(argc != 2) {
        cerr << "Usage: " << argv[0] << "<port name>" << endl;
        return 1;
    }
/*
    std::ifstream arduino;
    arduino.open(argv[1], ios::in | ios::binary);
*/
    SerialController arduino(argv[1]);
    arduino.set_BaudRate(B57600);
    arduino.set_Parity(Parity_Off);
    arduino.set_WordSize(WordSize_8);
    arduino.set_StopBits(StopBits_1);
    arduino.start();

    char buf[8];
    //uint8_t ping = 1;

    cout << "getting data from arduino" << endl;
    char a = 'a';
    while(1) {
        //if(arduino.is_open()){
        cout << "sending char*" << endl;
        arduino.writeBuffer(&a, 1);

        for(int i = 0; i < 8; i++)
            buf[i] = 0x00;
        cout << "reading data*" << endl;
    //    readChunk(arduino, buf, 8);
       arduino.readBuffer(buf, 8);

        int16_t right = *(int16_t*)(buf+5);
        int16_t left  = *(int16_t*)(buf+2);

        cout << "Right: " << right << " Left: " << left << endl;
        usleep(100000);
    }


    return 0;
}
