#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <vector>
#include <string>

#include "TCPSocket.hpp"
#include "RS232_Serial.hpp"

using namespace std;
using namespace JJC;

typedef struct {
    float leftY;
    float rightY;
    int A = 0;
    int B = 0;
} buttonData;

int leftMotorSpeed;
int rightMotorSpeed;

void initMotorController(CppSerial cs) {
    char* resetWD = "^RWD 0\n";
    cs.writeBuffer(resetWD, strlen(resetWD));
}

int main(int argc, char* argv[]) {

    //TCP::Socket<messageData> mysocket("www.google.com", 80);
    TCP::Socket<void> mysocket("192.168.12.171", 8096);
    //TCP::Socket<messageData> mysocket("1.1.4.5", 8089)

    cout << "Connection success!\n";
    cout << "Buffer size: " << mysocket.getBufferSize() << endl;

    char charBuf[256];
    char* recvData = nullptr;

    buttonData bd;

    leftMotorSpeed  = 0;
    rightMotorSpeed = 0;

    // RS-232 communications
    CppSerial cs("/dev/ttyS0");
    cs.set_BaudRate(B115200);
    cs.set_ParityOdd();     // odd parity
    cs.set_StopBit2();      // two stop bits
    cs.set_WordSize8();     // 8-bit word
    cs.set_Start();         // save configuration
    initMotorController(cs);

    while(1) {

        char* r = mysocket.readString(); // dynamically allocates memory
        //cout << "Input: \n" << r << endl;
        bool print = false;

        if(strcmp(r, "nil") == 0) {
            //cout << "No new data\n";
        } else
        if(r[0] == 'L' && r[1] == 'y') {
            delete[] r;
            r = mysocket.readString();
            bd.leftY = strtof(r, NULL);
        } else
        if(r[0] == 'R' && r[1] == 'y') {
            delete[] r;
            r = mysocket.readString();
            bd.rightY = strtof(r, NULL);
        } else
        if(r[0] == 'A') {
            delete[] r;
            r = mysocket.readString();
            if(r[0] == '1') {
                bd.A = 1;
            } else {
                bd.A = 0;
            }
        } else
        if(r[0] == 'B') {
            delete[] r;
            r = mysocket.readString();
            if(r[0] == '1') {
                bd.B = 1;
            } else {
                bd.B = 0;
            }
        } else
        if(r[0] == 'P') {
            print = true;
        }

//        if(print)
//            printf("Ly: %3.3f, Lr: %3.3f, A: %d, B: %d\n", bd.leftY, bd.rightY, bd.A, bd.B);

        delete[] r; // last operation will always be a write

        float leftTemp  = bd.leftY * 1000.0;
        float rightTemp = bd.rightY * 1000.0;
        leftMotorSpeed  = (int)leftTemp;
        rightMotorSpeed = (int)rightTemp;
        leftMotorSpeed  -= 1000;
        rightMotorSpeed -= 1000;

	leftMotorSpeed  *= -1; // just this side needs to be multiplied

        string rCom = "!G 1 " + to_string(rightMotorSpeed) + '\n';
        cs.writeBuffer((char*)rCom.c_str(), strlen(rCom.c_str()));

	string lCom = "!G 2 " + to_string(leftMotorSpeed) + '\n';
	cs.writeBuffer((char*)lCom.c_str(), strlen(lCom.c_str()));

	cout << "Command string: " << rCom << lCom << endl;
    }

    return 0;

}
















