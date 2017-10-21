#ifndef __JJC__GPS__INTERFACE__H__
#define __JJC__GPS__INTERFACE__H__

#include <RS232_GenericController.h>
#include <fstream>
#include <string>
#include <vector>

/*
	Enumeration of GPS message types
*/
enum GpsMsgType {
	GpsMsgType_NONE, // no gps message
	GpsMsgType_GGA,  // fix info
	GpsMsgType_GLL,  // latitude/longitude data
	GpsMsgType_GSA,  // overall satellite info
	GpsMsgType_GRS,  // GPS range residuals
	GpsMsgType_GSV,  // detailed satellite data
	GpsMsgType_VTG,  // vector track and speed over ground
	GpsMsgType_RMC,  // recommended minimum data for GPS
};

/*
	GpsInterface attempts to open every gps device as an ifstream object
*/
class GpsInterface {
private:
	std::string filename;
	std::ifstream file;
	
	// internal storage of various message types and timestamps
	std::string __gga; uint64_t __gga_ts; 
	std::string __gll; uint64_t __gll_ts;
	std::string __gsa; uint64_t __gsa_ts;
	std::string __grs; uint64_t __grs_ts;
	std::string __gsv; uint64_t __gsv_ts;
	std::string __vtg; uint64_t __vtg_ts;
	std::string __rmc; uint64_t __rmc_ts;

	// incoming chars stored here before processing
	std::vector<char> __gps_buffer;

	bool compGpsTag(const char* orig, const char* comp);
	GpsMsgType getGpsMsgType(const char* field);
	uint64_t getTimestamp(void); 

	GpsMsgType parseGpsChar(char c);

public:
	// only constructor, supply a file to open
	GpsInterface(const std::string& filename);

	// update the internal gps character buffer
	// and tell if a particular message type has arrived
	GpsMsgType update(void);

	// get the most recent message of a particular type
	// this does not update anything, only retrieves data
	std::string getMessage(GpsMsgType msgType);

	// get the most recent timestamp associated 
	// with the most recent message of a particular
	// type
	uint64_t getTimestamp(GpsMsgType gpstype);

	// object-less method to parse GPS message strings
	static std::vector<std::string> splitGpsMessage(const std::string& input);

};

#endif // __JJC__GPS__INTERFACE__H__



