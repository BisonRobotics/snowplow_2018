
#include <iostream>
#include <XboxControllerInterface.h>
#include <RoboteQ.h>
#include <EncoderInterface.h>

using namespace std;

int main(int argc, char* argv[]) {

    ArduinoEncoder AEs = ArduinoEncoder("/dev/ttyUSB0");

    char firstByte;
    char datbyte;// = AEs.requestData();

    while(1) {

        datbyte = AEs.requestData();
        usleep(5000);
        firstByte = AEs.readEncoders();

        if(datbyte == firstByte){
            int16_t speed = AEs.getSpeed(ENC_LEFT);
            cout << "Left encoderSpeed: " <<  speed << " Right encoderSpeed " << AEs.getSpeed(ENC_RIGHT) << endl;
        }else{
            cout << "sendByte: " << datbyte << " recieved: " << firstByte << endl;
        }
        usleep(10000);
    }

}
