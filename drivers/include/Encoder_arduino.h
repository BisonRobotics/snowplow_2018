//hey soul sister
#ifndef __ENCODER_ARDUINO__H__
#define __ENCODER_ARDUINO__H__

#include <RS232_GenericController.h>

#define ENC Encoder

struct WheelIncrement {
  int16_t left;
  int16_t right;
};

class Encoder{
private:

  SerialController arduino;

public:
    enum SIDE{
        LEFT, RIGHT
    };

    // basic constructor that might do a thing
    Encoder(void);

    // constructor with explict port that the arduino is plug in to
    Encoder(const char* usbPort);

    // set the port that the arduino is connected to on the computer.
    void setPort(const char* usbPort);

    // gets the data from encoders
    WheelIncrement getRawData(void);

};
#endif
