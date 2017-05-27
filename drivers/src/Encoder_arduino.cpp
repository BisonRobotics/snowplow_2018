//hello sexy
#include <Encoder_arduino.h>
//#include <sys/ioctl.h>

ENC::Encoder(void){
;
}
ENC::Encoder(const char* usbPort) {
    setPort(usbPort);

    arduino.set_BaudRate(B9600); //standard baudrate for arduinos
    arduino.set_Parity(SerialController::PARITY::OFF);
    arduino.set_StopBits(SerialController::STOPBITS::_1);
    arduino.set_WordSize(SerialController::WORDSIZE::_8);
    arduino.start();
}

void ENC::setPort(const char* usbPort)
{
    arduino.set_SerialPort(usbPort);

}
//returns the raw data from the encoder
WheelIncrement ENC::getRawData(void)
{

  WheelIncrement wi;
 wi.left = 0;
 wi.right =0;

  arduino.readBuffer((char*)&wi, 2);

  return wi;
}
