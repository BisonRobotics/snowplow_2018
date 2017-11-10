//hey soul sister
#ifndef __ENCODER_ARDUINO__H__
#define __ENCODER_ARDUINO__H__

#include <iostream>
#include "../include/RS232_GenericController.h"

struct ENCODERS{
  int16_t leftSpeed_Raw;   //left wheel speed in raw ticks form
  int16_t rightSpeed_Raw;  //right wheel speed in raw ticks form
  double rightSpeed_MpS;   //Right wheel speed in Meters per second
  double leftSpeed_MpS;     //Left wheel speed in Meters per second
};

class arduino_encoder{
private:

public:

    ENCODERS encoders;
    enum SIDE{
        ENC_LEFT, ENC_RIGHT
    };

    // constructor with explict port that the arduino is plug in to
    arduino_encoder();

    arduino_encoder(char* usbPort);

    // set the port that the arduino is connected to on the computer.
    void setPort(char* usbPort);

    // gets the data from ENCODERS
    void updateEncoders(void);
};
#endif
