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

struct messageData {
    char msg[512];
};

struct MsgData {
    int iArr[4];
    float xPos;
    float yPos;
    float zPos;
};

int main(int argc, char* argv[]) {

    messageData md;

    //TCP::Socket<messageData> mysocket("www.google.com", 80);
    TCP::Socket<MsgData> mysocket("192.168.12.109", 8090);
    //TCP::Socket<messageData> mysocket("1.1.4.5", 8089)
    cout << "Buffer size: " << mysocket.getBufferSize() << endl;

    return 0;

}
















