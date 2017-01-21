#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h> // for getting timestamps

#include <netinet/in.h>
#include <netdb.h>

// C++ libs
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

#include "TCPSocket.hpp"
#include "RS232_Serial.hpp"
#include "LinkedListLiteral.h"

using namespace std;
using namespace JJC;

typedef struct {
    char status; // r/R = regular operation, e/E = emergency stop
    int lDat;
    int rDat;
} motorData;

LinkedList<motorData> llQ; // queue of motor commands, cmds added to end, taken from beginning
mutex mtx; // for controlling access to cmd queue

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

uint64_t getTimeStamp(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*(uint64_t)1000000 + tv.tv_usec;
}

void t_nextThread(void) {
    // RS-232 communications
    CppSerial cs("/dev/ttyS0");
    cs.set_BaudRate(B115200);
    cs.set_ParityOdd();     // odd parity
    cs.set_StopBit2();      // two stop bits
    cs.set_WordSize8();     // 8-bit word
    cs.set_Start();         // save configuration
    initMotorController(cs);

    motorData md;

    while(1) {
        if(llQ.getSize() > 0) {
            mtx.lock();
            md = llQ.at(0); // retrieve first element in queue
            llQ.removeBegin();
            mtx.unlock();

            cout << "Cmd available: ";

            string rCom = "!G 1 " + to_string(md.rDat) + '\n';
            string lCom = "!G 2 " + to_string(md.lDat) + '\n';

            cs.writeBuffer((char*)rCom.c_str(), strlen(rCom.c_str()));
            cs.writeBuffer((char*)lCom.c_str(), strlen(lCom.c_str()));

            cout << "Command strings: \n" << rCom << lCom << endl;
        }
    }
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

    motorData md;

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

        md.lDat = leftMotorSpeed;
        md.rDat = rightMotorSpeed;

        mtx.lock();
        llQ.addToEnd(md); // add elememt to queue
        mtx.unlock();

    }

    return 0;

}
















