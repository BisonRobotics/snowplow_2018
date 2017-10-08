#ifndef __LIDARINTERFACE__H__
#define __LIDARINTERFACE__H__

#include <string>
#include <TCP_Connection.h>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>

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

    // carries the converted results of parsed data
    std::vector<float> floatVec;

    // carries the raw values of parsed data
    std::vector<uint16_t> shortVec;

    // cartesian equivalent of polar measurements
    std::vector<glm::vec2> cartVec;

    float __angles[541];

public:
    // initialize the sick sensor connection
    void init(void);

    // generic command for sending arbitrary commands to the SICK sensor
    void sendCmd(std::string cmd, bool should_echo = false);

    // sets the access mode of the SICK sensor
    void setAccessMode(USER mode);

    // take a data scan and store the results in floatVec
    void scanData(void);

    // run the SICK sensor (continuously...?)_
    void run(void);

    // get state of SICK sensor
    void getDeviceState(void);

    // print the ASCII reply
    void printReply(void);

    // get reply in ASCII character array (std::vector<char>)
    std::vector<char> getReply(void);

    // return the results from the most recent scan
    std::vector<float> getResults(void);

    // return the raw results form the most recent scan
    std::vector<uint16_t> getRawResults(void);

    // get various pieces of processed data
    void generateVectorData(void); // take most recent scan, generate float vec and glm::vec2 vec
    void linearizeData(void);
    std::vector<glm::vec2>* getVectorCartesian(void);
    std::vector<float>*     getVectorPolarFloat(void);
    std::vector<uint16_t>*  getVectorPolarInt(void);
};

#endif // __LIDARINTERFACE__H__
