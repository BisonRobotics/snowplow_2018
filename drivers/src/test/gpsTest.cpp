#include <iostream>
#include <GpsInterface.h>

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 2) {
		cout << "USAGE: " << argv[0] << " <port name>\n";
		return 1;
	}

	GpsInterface gps(argv[1]);

	while(1) {
		gps.update();
	}

	return 0;
}