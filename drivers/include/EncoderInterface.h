//hey soul sister
#ifndef __ENCODER_ARDUINO__H__
#define __ENCODER_ARDUINO__H__

#include <iostream>
#include <RS232_GenericController.h>

enum SIDE{
    ENC_LEFT, ENC_RIGHT
};
class ArduinoEncoder{

private:

    int16_t Lspeed;
    int16_t Rspeed;
    char* port;
    char sendByte;
    SerialController arduino;
    char buf[8];
    bool checkDatSum(char* buf);

public:

    ArduinoEncoder();

    // constructor with explict port that the arduino is plug in to
    ArduinoEncoder(char* usbPort);

    // set the port that the arduino is connected to on the computer.
    void setPort(char* usbPort);

    // gets the data from ENCODERS retunrs the first byte of the string
    char readEncoders(void);

    // retruns the speed of one wheel side of the snowplow
    int16_t getSpeed(SIDE side);

    //requests data ffrom the arduino and populates the speed.
    //returns the char sent to arduino
    char requestData(void);

};
#endif
