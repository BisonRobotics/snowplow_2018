#ifndef __JJC__TCPCONNECTION__H__
#define __JJC__TCPCONNECTION__H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include <sys/ioctl.h>

class TCP_Controller {
public:
    // constructor that does very little
    TCP_Controller(void);

    // arguments are IP address and a network port number
    TCP_Controller(const char* hostname, int port);

    // set the hostname this socket will use
    void set_Hostname(const char* hostname);

    // set the port that this socket will use
    void set_PortNumber(int port);

    // read number of bytes given by bufSize
    // and store them in buffer, assumes buffer
    // will always have sufficient space
    // method zeroes buffer space before reading
    void readSocket(char* buffer, int bufSize);

    // read bytes until flag is encountered in stream
    // return as a single std vector
    std::vector<char> readUntil(uint8_t flag);

    // write number of bytes given by bufSize
    // to the socket. assumes the buffer is always full
    void writeSocket(char* buffer, int bufSize);

    // write the contents of the string to the socket
    // size is given by the string itself
    void writeSocket(std::string buffer);

    // initialize socket with information given
    // opens a streaming, persistant tcp connection
    void start(void);

    void setBlocking(void) {
        int i = 0;
        ioctl(sockfd, FIONBIO, &i);
    }

    void setNonBlocking(void) {
        int i = 1;
        ioctl(sockfd, FIONBIO, &i);
    }

private:
    // private data. idk what it all does...yet
    // but its all needed for proper tcp usage
    int sockfd, portno, n;
    sockaddr_in serv_addr;
    hostent *server;

    // private copies of data supplied by user
    // flags tell start function if info is
    // actually available
    const char* hostname;
    int port;
    bool hostnameSet = false;
    bool portnumSet  = false;
};

#endif // __JJC__TCPCONNECTION__H__
