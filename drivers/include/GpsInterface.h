#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>

class GpsInterface
{
private:
    std::ifstream msgStream;
    const char[2] msgHeader = {0xB5, 0x62};
    char* msg[20];
public:
    GpsInterface(void);
    GpsInterface(std::string device);
    storeData(void);
    getECEFPOS(void);
    syncMsg(void);

}
