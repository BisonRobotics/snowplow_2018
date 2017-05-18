#ifndef __LIDARINTERFACE__H__
#define __LIDARINTERFACE__H__

#include <string>
#include <TCP_Connection.h>
#include <vector>
#include <fstream>

enum FREQ {
    _25Hz, _50Hz
};

enum RES {
    _05Deg, _025Deg
};

enum USER {
    MAINTENANCE, CLIENT, SERVICE
};

class LidarInterface {
private:
    // TCP connection used to connect to the SICK sensor
    TCP_Controller tc;

    // carries the results of parsed data
    std::vector<float> floatVec;

    // data is saved to disk through this thing
    std::ofstream outputStream;

    // data is read through here
    std::ifstream inputStream;

public:
    // initialize the sick sensor connection
    void init(void);

    // generic command for sending arbitrary commands to the SICK sensor
    void sendCmd(std::string cmd);

    // sets the access mode of the SICK sensor
    void setAccessMode(USER mode);

    // take a data scan and store the results in floatVec
    void scanData(void);

    // return the results from the most recent scan
    std::vector<float> getResults(void);
};

#endif // __LIDARINTERFACE__H__
