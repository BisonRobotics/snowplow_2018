/*
this file was made by Andrew Vetter.
This progrma is used for testing and deveoplment of the ecnoder driver class.
*/
//#include <Encoder_arduino.h>
#include <iostream>
#include <unistd.h>
#include "../../include/RS232_GenericController.h"

using namespace std;
SerialController arduino;
string port;

int16_t pChecksum = 0;

void readChunk(SerialController& sc, char* buf, int n) {
    int bytes_read = 0;

    while(bytes_read < n) {
        cout << "trying to read. N:" << n << endl;
        bytes_read += sc.readBuffer(buf+bytes_read, n-bytes_read);
    }
}

//compares checksum from arduino with CPU
bool checkDatSum(char* buf, char __char){

    //test if the char we sent match the one returned
    int16_t arCheckSum = *(int16_t*)(buf+7);
    if(__char != (char)*(int16_t*)(buf)){
        cout << "Error: char recieved: "<< (char)*(int16_t*)(buf) << endl;
        return false;
    }
    // makes sure the 2nd byte is a capital L
    if('L' != (*(int16_t*)(buf+1))){
        // cout << "L not in right spot  L: "<< *(int16_t*)(buf+1) << endl;
        return false;
    }
    // makes sure the 4th byte is a capital R
    if('R' != (char)(*(int16_t*)(buf+4))){
        cout << "R not in right spot" << endl;
        return false;
    }

    //build our checksum
    int16_t cpuCheckSum = __char ^ 'L'^ *(int16_t*)(buf+2) ^ 'R' ^ *(int16_t*)(buf+5) ;

    if(arCheckSum == cpuCheckSum) {
        //update previous checksum
        pChecksum = arCheckSum;
        return true;
    }  else if(arCheckSum == pChecksum){
        return false;
    } else {
        // cout << "checksum does not match cpu: " << cpuCheckSum << " recieved:  " << *(int16_t*)(buf+7) << endl;
        return false;
    }

}

void StartDatEncoder(SerialController encoders){

    encoders.set_SerialPort(port);
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
    port = argv[1];
   StartDatEncoder(arduino);

    char buf[8];
    //uint8_t ping = 1;

    cout << "getting data from arduino" << endl;
    char _char = 'a';
    while(1) {
        //if(arduino.is_open()){

        // cout << "sending char " << endl;
        arduino.writeBuffer(&_char, 1);

        for(int i = 0; i < 8; i++){
            buf[i] = 0x00;
        }

        // readChunk(arduino, buf, 8);
        // cout << "reading Data" << endl;
       arduino.readBuffer(buf, 8);

       cout << (char)(*(int16_t*)(buf)) << (char)(*(int16_t*)(buf+1)) << *(int16_t*)(buf+2) << *(int16_t*)(buf+3) << (char)(*(int16_t*)(buf+4)) << *(int16_t*)(buf+5) << *(int16_t*)(buf+6) << *(int16_t*)(buf+7)<< endl;

       int16_t ch = *(int16_t*)(buf);
       if(checkDatSum(buf, (char)ch)){

            int16_t right = *(int16_t*)(buf+5);
            int16_t left  = *(int16_t*)(buf+2);
        //    cout << *(int16_t*)(buf) << *(int16_t*)(buf+1) << *(int16_t*)(buf+2) << *(int16_t*)(buf+3) << *(int16_t*)(buf+4) << *(int16_t*)(buf+5) << *(int16_t*)(buf+6) << *(int16_t*)(buf+7)<< endl;
            cout << "char " << (char)ch <<" Right: " << right << " Left: " << left << endl;
       }
       usleep(1000000);

    }

    return 0;
}
