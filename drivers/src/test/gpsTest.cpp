#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <GpsInterface.h>

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 2) {
		cout << "USAGE: " << argv[0] << " <port name>\n";
		return 1;
	}

	GpsInterface gps(argv[1]);

	while(1) {
		GpsMsgType gpsmsgt = gps.update();
		
		if(gpsmsgt == GpsMsgType_GGA) {
			cout << gps.getTimestamp(gpsmsgt) << " : " << gps.getMessage(gpsmsgt) << endl;
			vector<string> parsed_message = GpsInterface::splitGpsMessage(gps.getMessage(gpsmsgt));
			for(string s : parsed_message)
				cout << "    " << s << endl;
			cout << endl;
		}

		usleep(50000); // update @ ~20Hz
	}

	return 0;
}

