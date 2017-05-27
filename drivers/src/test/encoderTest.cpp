/*
this file was made by Andrew Vetter.
This progrma is used for testing and deveoplment of the ecnoder driver class.
*/

#include <Encoder_arduino.h>
#include <iostream>
#include <unistd.h>

using namespace std;

 const char* port = "/dev/ttyUSB2";
int main(int argc, char const *argv[]) {
  Encoder encoder = Encoder(port);

  cout << "getting data from port" << std::endl;

WheelIncrement stuff;

  //std::cerr << *data  << std::endl;
  while(1) {

    static int iters= 0;

    stuff = encoder.getRawData();
    cout << ++iters << ' ';
    cout << stuff.left <<"  other: "<< stuff.right << endl;
    sleep(500);
  }


  return 0;
}
