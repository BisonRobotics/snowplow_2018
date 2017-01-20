//#include "arduino-serial.c"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

union W_Vel
{
  int data[2];
  char msg[8];
};
union W_Vel_Data {
    int data;
    char db[4];
};

int main(int argc, char* argv[]) {

    //cin.read(0x02, 1);

    ifstream a_in("/dev/ttyACM0");

    ofstream a_out("/dev/ttyACM0");

    //sdt::ofstream out(

    W_Vel input;

    input.data[0] = 0;
    input.data[1] = 0;

    int value = 0;
    int txt;

    while(1) {

        a_out << value << endl;

        for(int i=0;i<10000;++i)
        for(int j=0;j<10000;++j){ //Waste a lot of time
           ++value;
           --value;
        }

        a_in.read(input.msg, 8);

        input.data[0] = 0;
        input.data[1] = 0;

                    //input.data[0] |= (input.msg[3] << 24);
                    //input.data[0] |= (input.msg[2] << 16 );
                    //input.data[0] |= (input.msg[1] << 8);
                    //input.data[0] |= (input.msg[0] );

                    //input.data[1] |= (input.msg[4] << 24);
                    //input.data[1] |= (input.msg[5] << 16 );
                    //input.data[1] |= (input.msg[6] << 8);
                    //input.data[1] |= (input.msg[7] );

         for(int i = 1; i < 2; i++) { // change encoding of integers
                W_Vel_Data datum;
                datum.data = input.data[i];

                datum.db[3] = datum.db[3] ^ datum.db[0];
                datum.db[0] = datum.db[3] ^ datum.db[0];
                datum.db[3] = datum.db[3] ^ datum.db[0];

                datum.db[2] = datum.db[2] ^ datum.db[1];
                datum.db[1] = datum.db[2] ^ datum.db[1];
                datum.db[2] = datum.db[2] ^ datum.db[1];

                input.data[i] = datum.data;
            }


        //a_in >> value2[0];
        //a_in >> value2[1];
         //I always recieve the "OK"
        //cout << txt; //I can see the "OK"

        //encode.write("1",1);

        //in.read(value, 4);



            //vel[1] = (int)value[1];
            //vel[2] = (int)value[2];
            cout << input.data[0] << ":" << input.data[1] << endl;

            for(int i = 0; i < 7; i++)
            {
                cout << input.msg[i] << endl;
            }
    }

   return 0;
}

