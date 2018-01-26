#ifndef __DRIVETRAIN__H__
#define  __DRIVETRAIN__H__

#include <RoboteQ.h>

const char* robQSerialPort = "/dev/ttyUSB4"; //please implement udev rules

class drivetrain{
private:
    RoboteQInterface rqi(robQSerialPort);
    int speedLimit;
    float heading;

public:
    drivetrain(char* serialPort);

    void setSpeedLimit(int speed);

    void setDesiredHeading(float heading);

    float getCurrentHeading();

    int getCurrentSpeed();

};

#endif
