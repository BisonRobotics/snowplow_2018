#ifndef __RS232__SERIAL__HPP__
#define __RS232__SERIAL__HPP__

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

class CppSerial {
public:
    CppSerial(const char* serialPort) {
        memset(&tty, 0, sizeof tty);
        fd = open(serialPort, O_RDWR | O_NOCTTY | O_NDELAY); // pretty standard flags
        if(tcgetattr(fd, &tty) < 0) {
            std::cout << "error opening file" << std::endl;
        }
    }

    void readBuffer(char* buf, int bufSize) {
        read(fd, buf, bufSize);
    }

    void writeBuffer(char* buf, int bufSize) {
        write(fd, buf, bufSize);
    }

    void set_BaudRate(int baudrate) {
        cfsetispeed(&tty, baudrate);
        cfsetospeed(&tty, baudrate);
    }

    void set_ParityEnable(void) {
        tty.c_cflag |= PARENB;
    }

    void set_ParityDisable(void) {
        tty.c_cflag &= ~PARENB;
    }

    void set_ParityEven(void) {
        tty.c_cflag &= ~PARODD;
    }

    void set_ParityOdd(void) {
        tty.c_cflag |= PARODD;
    }

    void set_WordSize7(void) {
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS7;
    }

    void set_WordSize8(void) {
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8;
    }

    void set_Start(void) {
        if(tcsetattr(fd, TCSANOW, &tty)!= 0) {
            std::cout << "error starting serial communications" << std::endl;
        }
    }

    void set_StopBit1(void) {
        tty.c_cflag &= ~CSTOPB;
    }

    void set_StopBit2(void) {
        tty.c_cflag |= CSTOPB;
    }

private:
    termios tty;
    int fd = -1; // file descriptor
};

#endif// __RS232__SERIAL__HPP__
