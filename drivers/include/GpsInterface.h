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
	GpsMsgType_GSA,  // overall satellite info
	GpsMsgType_GRS,  // GPS range residuals
	GpsMsgType_GSV,  // detailed satellite data
};

/*
	GpsInterface attempts to open every gps device as an ifstream object
*/
class GpsInterface {
private:
	std::string filename;
	std::ifstream file;

	// internal storage of various message types
	std::string __gga;
	std::string __gsa;
	std::string __grs;
	std::string __gsv;

public:
	// only constructor, supply a file to open
	GpsInterface(const std::string& filename);

	// update the internal gps character buffer
	// and tell if a particular message type has arrived
	GpsMsgType update(void);

	// return the most recent GPS message of a particular type
	//... functions yet to be defined
};

#endif // __JJC__GPS__INTERFACE__H__



