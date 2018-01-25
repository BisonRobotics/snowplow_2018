#include <TCP_Connection.h>

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
#include <vector>
#include <string>

TCP_Controller::TCP_Controller(void) {
    ;
}

TCP_Controller::TCP_Controller(const char* hostname, int port) {
    set_Hostname(hostname);
    set_PortNumber(port);
}

void TCP_Controller::set_Hostname(const char* hostname) {
    this->hostname = hostname;
    this->hostnameSet = true;
}

void TCP_Controller::set_PortNumber(int port) {
    this->port = port;
    this->portnumSet = true;
}

void TCP_Controller::readSocket(char* buffer, int bufSize) {
    //bzero(buffer, bufSize);
    int n = read(this->sockfd, buffer, bufSize);

    if(n < 0) {
        std::cerr << "Read error" << std::endl;
        std::cerr << "    code: " << errno << std::endl;
    }

}

std::vector<char> TCP_Controller::readUntil(uint8_t flag) {
    std::vector<char> charBuf; // characters are simply stored here as they arrive
    uint8_t c;

    // this loop will eventually exit by returning a char vector
    while(1) {
        read(this->sockfd, &c, 1);
        if(c == flag)
            return charBuf;
        charBuf.push_back((char)c);
    }
}

void TCP_Controller::writeSocket(std::string buffer) {
    write(this->sockfd, buffer.c_str(), buffer.size());
}

void TCP_Controller::writeSocket(char* buffer, int bufSize) {
    write(this->sockfd, buffer, bufSize);
}

void TCP_Controller::start(void) {

    if(portnumSet == false) {
        std::cerr << "ERROR port number not set" << std::endl;
        exit(-1);
    }

    if(hostnameSet == false) {
        std::cerr << "ERROR hostname not set" << std::endl;
        exit(-1);
    }

    this->portno = port;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        std::cerr << "ERROR opening socket" << std::endl;
        std::cerr << "    code: " << errno << std::endl;
        exit(-1);
    }

    this->server = gethostbyname(hostname);
    if (server == NULL) {
        std::cerr << "ERROR, no such host: " << hostname << std::endl;
        exit(-1);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)  this->server->h_addr,
          (char*) &this->serv_addr.sin_addr.s_addr,
                   this->server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "ERROR connecting" << std::endl;
        std::cerr << "Hostname: " << hostname << " Port: " << port << std::endl;
        std::cerr << "    error code: " << errno << std::endl;
        exit(-1);
    }
}
















