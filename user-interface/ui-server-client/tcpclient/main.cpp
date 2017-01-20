#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

#include "TCPSocket.hpp"

using namespace std;
using namespace JJC;

typedef struct {
    float leftY;
    float rightY;
    int A = 0;
    int B = 0;
} buttonData;

int main(int argc, char* argv[]) {

    //TCP::Socket<messageData> mysocket("www.google.com", 80);
    TCP::Socket<void> mysocket("localhost", 8092);
    //TCP::Socket<messageData> mysocket("1.1.4.5", 8089)

    cout << "Connection success!\n";
    cout << "Buffer size: " << mysocket.getBufferSize() << endl;

    char charBuf[256];
    char* recvData = nullptr;

    buttonData bd;

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

        if(print)
            printf("Ly: %3.3f, Lr: %3.3f, A: %d, B: %d\n", bd.leftY, bd.rightY, bd.A, bd.B);

        delete[] r; // last operation will always be a write

    }

    return 0;

}
















