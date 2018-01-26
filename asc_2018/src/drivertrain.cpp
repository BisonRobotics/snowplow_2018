#include <RoboteQ.h>


drivetrain::drivetrain(char* serialPort){

    RoboteQInterface rqi(serialPort);

    wheelHalt();
    this->speed = 0;

}
void drivetrain::setDesiredSpeed(int speed){

    this->speed = speed;

    //PID loop

}
