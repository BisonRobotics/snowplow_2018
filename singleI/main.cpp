//#include "arduino-serial.c"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

union W_Vel
{
  int wheels[2];
};

int main(int argc, char* argv[]) {

    //cin.read(0x02, 1);

    char value2[2] = {0,0};

    ifstream a_in("/dev/ttyACM0");

    ofstream a_out("/dev/ttyACM0");

    //sdt::ofstream out(

    int value = 0;
    int txt;

    while(1) {

        a_out << value << endl;

        for(int i=0;i<10000;++i)
        for(int j=0;j<10000;++j){ //Waste a lot of time
           ++value;
           --value;
        }

        a_in.read(value2, 2); //I always recieve the "OK"
        //cout << txt; //I can see the "OK"

        //encode.write("1",1);

        //in.read(value, 4);

        for(int i = 0; i < 4; i++)
            cout << " " << value2[1] << ":" << value2[2] << endl;

    }

   return 0;
}

