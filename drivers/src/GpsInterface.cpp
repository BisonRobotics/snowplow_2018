#include <GpsInterface.h>
#include <RS232_GenericController.h>
#include <iostream>

GpsInterface::GpsInterface(const std::string& filename) {
	file.open(filename, std::ios::in | std::ios::binary);
}

GpsMsgType GpsInterface::update(void) {
	char c;
	file.read(&c, 1);
	std::cout << c;
}
