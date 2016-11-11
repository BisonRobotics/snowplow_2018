#ifndef _JJC_TCP_SOCKET_HPP_
#define _JJC_TCP_SOCKET_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <iostream>
#include <cstring> // for memcpy function

namespace JJC {
namespace TCP { // using namespace JJC; will make it TCP::Socket

template<class T>
class Socket {

public:

    Socket(const char* hostname, int port);
    int readSocket (T* t_type);
    int writeSocket(T* t_type);
    int getBufferSize(void);

private:

    char* getAdequateBufferSize(void);

    int sockfd, portno, n;
    sockaddr_in serv_addr;
    hostent *server;
    char* buffer;

    T* t_data;
    size_t bufferSize;

};

template<class T>
Socket<T>::Socket(const char* hostname, int port) {

    this->buffer = getAdequateBufferSize();

    // quick error check, size of buffer needs to be greater than zero
    if(this->bufferSize == 0 || this->buffer == 0) {
        std::cerr << "ERROR allocating buffer space" << std::endl;
        exit(1);
    }

    this->portno = port;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        std::cerr << "ERROR opening socket" << std::endl;

    this->server = gethostbyname(hostname);

    if (server == NULL) {
        std::cerr << "ERROR, no such host: " << hostname << std::endl;
        exit(1);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)  this->server->h_addr,
          (char*) &this->serv_addr.sin_addr.s_addr,
                   this->server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "ERROR connecting" << std::endl;
    }

}

template<class T>
char* Socket<T>::getAdequateBufferSize(void) {
    for(int i = 128; i <= 8192; i *= 2) {
        if(i >= sizeof(T)) {
            this->bufferSize = i;
            return new char[i];
        }
    }
    this->bufferSize = 0;
    return 0;
}

template<class T>
int Socket<T>::readSocket(T* t_type) {
    bzero(buffer, this->bufferSize);
    n = read(this->sockfd, buffer, this->bufferSize);
    memcpy(t_type, buffer, sizeof(T));
    return n;
}

template<class T>
int Socket<T>::writeSocket(T* t_type) {
    bzero(buffer, bufferSize);
    n = write(this->sockfd, buffer, this->bufferSize);
    memcpy(t_type, buffer, sizeof(T));
}

template<class T>
int Socket<T>::getBufferSize(void) {
    return bufferSize;
}

} // end of TCP namespace
} // end of JJC namespace

#endif // _JJC_TCP_SOCKET_HPP_









