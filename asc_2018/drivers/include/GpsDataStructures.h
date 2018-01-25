#ifndef __JJC__GPS__DATA__STRUCTURES__H__
#define __JJC__GPS__DATA__STRUCTURES__H__

#include <string>
#include <stdlib.h>

// every GPS message contains this information
struct GpsUniversalData {
	std::string name;
	int checksum;
};

struct GpsGGA : GpsUniversalData {
	uint32_t utcTimestamp;

	// latitude info
	int    latitudeDegrees;
	float  latitudeMinutes;
	char   latitudeDirection;

	// longitude info
	int    longitudeDegrees;
	float  longitudeMinutes;
	char   longitudeDirection;

	// 0 (lowest) -> 8 (highest)
	int fixQuality;

	// number of satellites used in calculation
	int numberSatellites;

	// meters above sea level
	float altitude;

	friend std::ostream& operator<<(std::ostream& os, const GpsGGA& gps) {
		os << "GPS:GGS Message\n";
		os << "  Timestamp:  " << gps.utcTimestamp << std::endl;
		os << "  Lat:\n";
		os << "    Deg: " << gps.latitudeDegrees << std::endl;
		os << "    Min: " << gps.latitudeMinutes << std::endl;
		os << "    Dir: " << (gps.latitudeDirection=='N'?"NORTH":"SOUTH") << std::endl;
		os << "  Lon:\n";
		os << "    Deg: " << gps.longitudeDegrees << std::endl;
		os << "    Min: " << gps.longitudeMinutes << std::endl;
		os << "    Dir: " << (gps.longitudeDirection=='E'?"EAST":"WEST") << std::endl;
		os << "  # Sat: \n    "      << gps.numberSatellites << std::endl;
		os << "  Fix Quality:\n    " << gps.fixQuality << std::endl;
		os << "  Checksum:\n    "    << std::hex << gps.checksum << std::dec << std::endl;

		return os;

	}

};

#endif // __JJC__GPS__DATA__STRUCTURES__H__