#include <LidarInterface.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

void LidarInterface::init(void) {
    tc.set_Hostname("192.168.0.1");
    tc.set_PortNumber(2111);
    tc.start();
}

void LidarInterface::setAccessMode(USER mode) {
    switch(mode) {
        case USER::MAINTENANCE:
            sendCmd(std::string("sMN SetAccessMode 02 B21ACE26"));
            return;
        case USER::CLIENT:
            sendCmd(std::string("sMN SetAccessMode 03 F4724744"));
            return;
        case USER::SERVICE:
            sendCmd(std::string("sMN SetAccessMode 04 81BE23AA"));
            return;
        default:
            break;
    }
}

void LidarInterface::scanData(void) {
    outputStream.open("/tmp/scanresults_ax8846");
    sendCmd(std::string("sRN LMDscandata"));

    std::vector<char> reply = tc.readUntil(0x03);
    reply.push_back(0x00);
    int s = reply.size() - 2;

    outputStream.write(&reply[1], s);
    outputStream.close();

    inputStream.open("/tmp/scanresults_ax8846");

    this->floatVec.clear();
    this->floatVec.reserve(1000);

    std::string str = "";
    while(str != "DIST1")
        inputStream >> str;

    uint32_t numMeas;
    for(int i = 0; i < 5; i++)
        inputStream >> std::hex >> numMeas;

    std::cout << numMeas << std::endl;
}

void LidarInterface::sendCmd(std::string cmd) {
    static char stx = 0x02;
    static char etx = 0x03;

    std::cout << "cmd: " << cmd << std::endl;

    tc.writeSocket(&stx, 1); // start transmission
    tc.writeSocket((char*)cmd.c_str());
    tc.writeSocket(&etx, 1); // end transmission
}

std::vector<float> LidarInterface::getResults(void) {
    return this->floatVec;
}

