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


main(int argc, char* argv[]){


	sleep(2);
	
	CppSerial cs("/dev/ttyttyS0");
    	cs.set_BaudRate(B115200);
    	cs.set_ParityDisable(); // no parity bit
    	cs.set_StopBit1();      // one stop bit
    	cs.set_WordSize8();     // 8-bit word
    	cs.set_Start();         // save configuration
    	initMotorController(cs);

	
