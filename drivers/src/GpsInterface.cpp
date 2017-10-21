#include <GpsInterface.h>
#include <RS232_GenericController.h>
#include <iostream>
#include <fstream>
#include <sys/time.h>

GpsInterface::GpsInterface(const std::string& filename) {
	this->filename = filename;

	file.open(filename, std::ios::in | std::ios::binary);

/*	file.set_SerialPort(filename);
	file.set_BaudRate(B115200);      // baudrate
	file.set_WordSize(WordSize_8); // 8 data bits
	file.set_Parity(  Parity_Off); // no parity bits
	file.set_StopBits(StopBits_1); // 1 stop bits
	file.start();
*/
}

bool GpsInterface::compGpsTag(const char* orig, const char* comp) {
	for(int i = 0; i < 3; i++) {
		if(orig[i] != comp[i])
			return false;
	}
	return true; // all chars were the same
}

std::string GpsInterface::getMessage(GpsMsgType gpsmsgt) {
	switch(gpsmsgt) {
		case GpsMsgType_GSV:
			return __gsv; break;
		case GpsMsgType_GLL:
			return __gll; break;
		case GpsMsgType_GSA:
			return __gsa; break;
		case GpsMsgType_GRS:
			return __grs; break;
		case GpsMsgType_GGA:
			return __gga; break;
		case GpsMsgType_VTG:
			return __vtg; break;
		case GpsMsgType_RMC:
			return __rmc; break;
		default:
			return ""; // empty string
	}
}

// 012345
// $XXMMM
// strs: GSV, GLL, GSA, GRS, GGA, VTG, RMC
GpsMsgType GpsInterface::getGpsMsgType(const char* field) {
	if(compGpsTag(field+3, "GSV")) {
		__gsv = field;
		__gsv_ts = this->getTimestamp();
		return GpsMsgType_GSV;
	} else if(compGpsTag(field+3, "GLL")) {
		__gll = field;
		__gll_ts = this->getTimestamp();
		return GpsMsgType_GLL;
	} else if(compGpsTag(field+3, "GSA")) {
		__gsa = field;
		__gsa_ts = this->getTimestamp();
		return GpsMsgType_GSA;
	} else if(compGpsTag(field+3, "GGA")) {
		__gga = field;
		__gga_ts = this->getTimestamp();
		return GpsMsgType_GGA;
	} else if(compGpsTag(field+3, "VTG")) {
		__vtg = field;
		__vtg_ts = this->getTimestamp();
		return GpsMsgType_VTG;
	} else if(compGpsTag(field+3, "RMC")) {
		__rmc = field;
		__rmc_ts = this->getTimestamp();
		return GpsMsgType_RMC;
	} else if(compGpsTag(field+3, "GRS")) {
		__grs = field;
		__grs_ts = this->getTimestamp();
		return GpsMsgType_GRS;
	} else {
		return GpsMsgType_NONE; // no valid data detected
	}
}

uint64_t GpsInterface::getTimestamp(void) {
	timeval tv;
	gettimeofday(&tv, NULL);

	// return a relatively inaccurate usec timestamp, this shouldnt be used in any time sensitive calculations
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

/*
GpsMsgType_GGA,  // fix info
GpsMsgType_GLL,  // latitude/longitude data
GpsMsgType_GSA,  // overall satellite info
GpsMsgType_GRS,  // GPS range residuals
GpsMsgType_GSV,  // detailed satellite data
GpsMsgType_VTG,  // vector track and speed over ground
GpsMsgType_RMC,  // recommended minimum data for GPS
*/
uint64_t GpsInterface::getTimestamp(GpsMsgType gpstype) {
	switch(gpstype) {
		case GpsMsgType_GGA:
			return __gga_ts; break;
		case GpsMsgType_GLL:
			return __gll_ts; break;
		case GpsMsgType_GSA:
			return __gsa_ts; break;
		case GpsMsgType_GRS:
			return __grs_ts; break;
		case GpsMsgType_GSV:
			return __gsv_ts; break;
		case GpsMsgType_VTG:
			return __vtg_ts; break;
		case GpsMsgType_RMC:
			return __rmc_ts; break;
		default:
			return (uint64_t)0;
	}
}

GpsMsgType GpsInterface::parseGpsChar(char c) {
	const int STATE_expect_msg_begin = 0; // look for $
	const int STATE_expect_msg_end   = 1; // look for \n

	static int current_state = STATE_expect_msg_begin;
	static std::vector<char> _msg_buffer;

	switch(current_state) {
		case STATE_expect_msg_begin:
			_msg_buffer.clear();
			if(c == '$') {
				_msg_buffer.push_back(c);
				current_state = STATE_expect_msg_end;
			}
			break;
		case STATE_expect_msg_end:
			if(c == 0x0D || c == 0x0A) {
				current_state = STATE_expect_msg_begin;
				_msg_buffer.push_back('\0');
				//std::cout << &_msg_buffer[0] << std::endl;
				return getGpsMsgType(&_msg_buffer[0]);
			} else
				_msg_buffer.push_back(c);
			break;
		default:
			break; // idk what to do if this happens, so do nothing
	}
	return GpsMsgType_NONE;
}

GpsMsgType GpsInterface::update(void) {
	static std::vector<char> tmp_buffer;
	const int CHUNK_SIZE = 100;
	char buf[CHUNK_SIZE];

	file.read(buf, CHUNK_SIZE); // try to read the full allocation
	int bytes_read = CHUNK_SIZE;

	if(!file) {
		bytes_read = file.gcount();
		file.clear();
	}

	for(int i = 0; i < bytes_read; i++)
		tmp_buffer.push_back(buf[i]);

	int s = tmp_buffer.size();
	for(int i = 0; i < s; i++) {
		GpsMsgType gpstype = this->parseGpsChar(tmp_buffer[0]);

		// reduce the size of the vector
		for(int i = 0; i < tmp_buffer.size()-1; i++)
			tmp_buffer[i] = tmp_buffer[i+1];
		tmp_buffer.pop_back();

		if(gpstype != GpsMsgType_NONE) {
			return gpstype;
		}
	}

	return GpsMsgType_NONE; // no characters in this stream
}

std::vector<std::string> GpsInterface::splitGpsMessage(const std::string& input) {
	int s = input.length();

	std::vector<std::string> parsed_msg;
	std::vector<char> message_chunk;

	message_chunk.clear();

	const int STATE_expect_chunk_start = 0; // looking for start of message chunk or ',' 
	const int STATE_expect_chunk_end   = 1; // looking for ','
	int current_state = STATE_expect_chunk_start;

	for(int i = 0; i < s; i++) {
		char c = input[i];

		switch(current_state) {
			case STATE_expect_chunk_start:
				if(c == ',') {
					parsed_msg.push_back("");
					message_chunk.clear();
				} else {
					current_state = STATE_expect_chunk_end;
					message_chunk.push_back(c);
				}
				break;
			case STATE_expect_chunk_end:
				if(c == ',') {
					message_chunk.push_back('\0');
					parsed_msg.push_back(&message_chunk[0]);
					message_chunk.clear();
					current_state = STATE_expect_chunk_start;
				} else {
					message_chunk.push_back(c);
				}
				break;
			default:
				break;
		}
	}

	// checksum is the last element
	parsed_msg.push_back(&message_chunk[0]);

	return parsed_msg;
}








