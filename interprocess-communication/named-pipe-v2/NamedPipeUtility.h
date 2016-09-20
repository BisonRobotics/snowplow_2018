/*
    NamedPipeUtility, named pipe library
    Copyright (C) 2016  Joseph Cluett

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Author(s):
        Joseph Cluett (main author)

    File Type: header/implementation, NamedPipeUtility

    Date Created: 5/5/2016

    Date Last Modified: 5/5/2016

    Purpose:
        The second gen named pipe library. This particular version focuses on transmitting single pieces of
        primitive data through a named pipe. Uses a template to create named pipes for arbitrarily sized data
        Should work with any data with well-defined copy constructor

    Misc. Notes:
        simplex and half-duplex pipes will be supported, interface will be almost identical to other named pipe
        utility. It should be noted that using a half-duplex pipe still requires you to send and recieve the
        same type/size data. However the library does not care if the data is signed or unsigned. Simplex pipes
        use same infrastructure as half-duplex pipes but present it to the programmer differently
*/

#ifndef JJC_NAMEDPIPEUTILITY_H
#define JJC_NAMEDPIPEUTILITY_H

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define IS_WRITER 1
#define IS_READER 2
#define OPEN_WRITER_FIRST 3
#define OPEN_READER_FIRST 4

//the following notation is one that i have used in a few of my other projects

#ifndef NPU
#define NPU  NamedPipeUtility
#endif // NPU

#ifndef npu
#define npu  NamedPipeUtility
#endif // npu

#ifndef _NPU //underscore indicates inclusion of namespace prefix, in this case JJC
#define _NPU JJC::NamedPipeUtility
#endif // _NPU

#ifndef _npu
#define _npu JJC::NamedPipeUtility
#endif // _npu

//================================================================================

namespace JJC {
template<class primitive>
class NamedPipeUtility {
    public:

        /* As of yet, constructor does nothing. This is because the template argument tells
        the object everything it needs to know to set up communication. */
        NamedPipeUtility(void);

    //===============================================================================================================================

        void Simplex_create(char* pipename, bool create); //only one process needs to create the pipe, the other simply needs to attach
        int  Simplex_open(int r_wr_flag); //1 = writer, 2 = reader

        /* single read and write functions */
        void Simplex_write(primitive* data);
        void Simplex_read(primitive* data);

        void Simplex_close(void);
        void Simplex_destroy(void);

    //===============================================================================================================================

        void HalfDuplex_create(char* tx_pipename, char* rx_pipename, bool create); //both programs must have pipenames but only one needs to create them
        int HalfDuplex_open(int first_pipe);

        /* single read and write functions */
        void HalfDuplex_write(primitive* data);
        void HalfDuplex_read(primitive* data);

        void HalfDuplex_close(void);
        void HalfDuplex_destroy(void);

    protected:
        void HalfDuplex_open_method_1(void); //Pipe operations are automatically assigned
        void HalfDuplex_open_method_2(void); //--
        char* rx_pipe; //receive pipe name handle
        char* tx_pipe; //transmit pipe name handle
        int fd_rx;
        int fd_tx;
};
}

    // Constructor that does nothing ================================================================================================

template<class primitive>
JJC::NPU<primitive>::NamedPipeUtility(void) {
    return;
}

    // Simplex pipe operations ======================================================================================================

template<class primitive>
void JJC::NPU<primitive>::Simplex_create(char* pipename, bool create) {
    tx_pipe = pipename;
    if(create) {
        mkfifo(tx_pipe, 0666);
    }
}

template<class primitive>
int JJC::NPU<primitive>::Simplex_open(int r_wr_flag) {
    switch(r_wr_flag) {
        case IS_WRITER:
            //open pipe as writer
            fd_tx = open(tx_pipe, O_WRONLY);
            return 0; break;
        case IS_READER:
            //open pipe as reader
            fd_tx = open(tx_pipe, O_RDONLY);
            return 0; break;
        default:
            return -1; break;
    }
}

template<class primitive>
void JJC::NPU<primitive>::Simplex_write(primitive* data) {
    write(fd_tx, data, sizeof(primitive));
}

template<class primitive>
void JJC::NPU<primitive>::Simplex_read(primitive* data) {
    read(fd_tx, data, sizeof(primitive));
}

template<class primitive>
void JJC::NPU<primitive>::Simplex_close(void) {
    close(fd_tx);
}

template<class primitive>
void JJC::NPU<primitive>::Simplex_destroy(void) {
    unlink(tx_pipe);
}

    // Half-duplex pipe operations ==================================================================================================

template<class primitive>
void JJC::NPU<primitive>::HalfDuplex_create(char* tx_pipename, char* rx_pipename, bool create) {
    tx_pipe = tx_pipename;
    rx_pipe = rx_pipename;
    if(create) {
        mkfifo(tx_pipe, 0666);
        mkfifo(rx_pipe, 0666);
    }
}

template<class primitive>
int JJC::NPU<primitive>::HalfDuplex_open(int first_pipe) {
    switch(first_pipe) {
        case OPEN_WRITER_FIRST:
            HalfDuplex_open_method_1();
            return 0;
            break;
        case OPEN_READER_FIRST:
            HalfDuplex_open_method_2();
            return 0;
            break;
        default:
            return -1;
            break;
    }
}

template<class primitive>
void JJC::NPU<primitive>::HalfDuplex_write(primitive* data) {
    write(fd_tx, data, sizeof(primitive));
}

template<class primitive>
void JJC::NPU<primitive>::HalfDuplex_read(primitive* data) {
    read(fd_rx, data, sizeof(primitive));
}

template<class primitive>
void JJC::NPU<primitive>::HalfDuplex_close(void) {
    close(fd_tx);
    close(fd_rx);
}

template<class primitive>
void JJC::NPU<primitive>::HalfDuplex_destroy(void) {
    unlink(rx_pipe);
    unlink(tx_pipe);
}

    // Half-duplex pipe operations not presented directly to programmer =========================================================

/* Open writer first */
template<class primitive>
void JJC::NPU<primitive>::HalfDuplex_open_method_1(void) {
    //open first pipe as writer then open second pipe as reader
    fd_tx = open(tx_pipe, O_WRONLY);
    fd_rx = open(rx_pipe, O_RDONLY);
}

/* Open reader first */
template<class primitive>
void JJC::NPU<primitive>::HalfDuplex_open_method_2(void) {
    //open first pipe as reader then open second pipe as writer
    fd_rx = open(rx_pipe, O_RDONLY);
    fd_tx = open(tx_pipe, O_WRONLY);
}

#endif // JJC_NAMEDPIPEUTILITY_H

// I never finish anythi
