
#include <unistd.h>
#include <stdlib.h>
#include "../include/EncoderInterface.h"
#include "../include/RS232_GenericController.h"

using namespace std;

//defualt port
char* port = "/dev/ttyUSB0";
char sendByte;
SerialController arduino;
char buf[8];

int16_t pChecksum = 0;

arduino_encoder::arduino_encoder(void){

    arduino.set_SerialPort(port);
    arduino.set_BaudRate(B57600);
    arduino.set_Parity(Parity_Off);
    arduino.set_WordSize(WordSize_8);
    arduino.set_StopBits(StopBits_1);
    arduino.start();
}

arduino_encoder::arduino_encoder(char* usbPort){

    port = usbPort
    arduino.set_SerialPort(port);
    arduino.set_BaudRate(B57600);
    arduino.set_Parity(Parity_Off);
    arduino.set_WordSize(WordSize_8);
    arduino.set_StopBits(StopBits_1);
    arduino.start();
}

//generate random char for the send byte
void randomChar(void){
    sendByte = (char)(32 + (rand() % (126 - 31)));// generate a random byte between 32 abd 125. ie Space to ~ in ascii
}

void arduino_encoder::setPort(char* usbPort){
    port = usbPort;
    arduino.set_SerialPort(usbPort);
}

//compares checksum from arduino with CPU
bool checkDatSum(char* buf){

    //test if the char we sent match the one returned
    int16_t arCheckSum = *(int16_t*)(buf+7);
    if(sendByte != (char)*(int16_t*)(buf)){
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
    int16_t cpuCheckSum = sendByte ^ 'L' ^ *(int16_t*)(buf+2) ^ 'R' ^ *(int16_t*)(buf+5);

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

void arduino_encoder::updateEncoders(void){
    //ask for data
    randomChar();
    arduino.writeBuffer(&sendByte, 1);

    //set all values in the buf to 0
    for(int i = 0; i < 8; i++){
        buf[i] = 0x00;
    }

    //read recieved data
    arduino.readBuffer(buf, 8);

    //if the schecksum is valid populate values in the struct
    if(checkDatSum(buf)){

        arduino_encoder::encoders.rightSpeed_Raw = *(int16_t*)(buf+5);
        arduino_encoder::encoders.leftSpeed_Raw  = *(int16_t*)(buf+2);
    //    arduino_encoder::encoders.rightSpeed_MpS = encoders.rightSpeed_Raw * some converstion factor.;
    //    arduino_encoder::encoders.leftSpeed_MpS = encoders.rightSpeed_Raw * convervstion factor;

        // cout << *(int16_t*)(buf) << *(int16_t*)(buf+1) << *(int16_t*)(buf+2) << *(int16_t*)(buf+3) << *(int16_t*)(buf+4) << *(int16_t*)(buf+5) << *(int16_t*)(buf+6) << *(int16_t*)(buf+7)<< endl;
        // cout << "char " << (char)ch <<" Right: " << right << " Left: " << left << endl;
    }
    usleep(10000);
}
/*
void readChunk(SerialController& sc, char* buf, int n) {
    int bytes_read = 0;

    while(bytes_read < n) {
        bytes_read += sc.readBuffer(buf+bytes_read, n-bytes_read);
    }
}
 */
