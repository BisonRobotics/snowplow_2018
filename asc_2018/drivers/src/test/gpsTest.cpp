#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <GpsInterface.h>
#include <GpsDataStructures.h>
#include <sys/time.h>

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 2) {
		cout << "USAGE: " << argv[0] << " <port name>\n";
		return 1;
	}

	GpsInterface gps(argv[1]);

	uint64_t start_time = 0;

	{ // dont need this stuff after first timestamp
		timeval tv;
		gettimeofday(&tv, NULL);
		start_time = ((tv.tv_sec * 1000000) + tv.tv_usec);
	}

	while(1) {

		// get all available data
		GpsMsgType gpsType = gps.update();
		if(gpsType == GpsMsgType_GGA) {
			// tokenize GPS data
			vector<string> str_vec = GpsInterface::splitGpsMessage(gps.getMessage(gpsType));
			
			cout << gps.getMessage(gpsType) << endl;

			// get numeric data
			GpsGGA gga_msg = GpsMsgResolve::Gga(str_vec);
			cout << gga_msg << endl;
		}

		usleep(50000); // update @ ~20Hz
	}

	return 0;
}
