
/* This file is used as a reference for communicating with the vectNAV IMU 
 * using the provided libraries from the vectNAV web site
 * The make file is created to work with the current setup of folders 
 *  
 * The methods were created fromt the examples provided by vectNAV
 */

#include <iostream>

// Include this header file to get access to VectorNav sensors.
#include "vn/sensors.h"

// We need this file for our sleep function.
#include "vn/thread.h"

using namespace std;
using namespace vn::math;
using namespace vn::sensors;
using namespace vn::protocol::uart;
using namespace vn::xplat;

int main(int argc, char *argv[])
{
	//initialize sensor

	//sensor port
	const string SensorPort = "/dev/ttyUSB0"; 
	//sensor 	
	const uint32_t SensorBaudrate = 115200;

	//Create VnSensor class
	VnSensor vs;
	vs.connect(SensorPort, SensorBaudrate);

	
}

double* readSensorData()
{
	

}
