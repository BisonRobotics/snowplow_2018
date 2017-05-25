/*
    TODO : inline the byte swapping algorithm in conditional SWAPBYTES. would like to try asm
    TODO : use guaranteed sized data types (uint32_t, uint8_t) in ECEF_Msg and ECEF_Data unions
    TODO : streamline unions. combine so as to use just one
    TODO : read GPS data directly into program. current implementation uses pipe on command line
*/


#include <iostream>
#include <unistd.h>

#define SWAPBYTES
#define SETCOMM

using namespace std;

char msgHeader[540];

union ECEF_Msg {
    int data[7];
    char msg[28];
};

#ifdef SWAPBYTES
union ECEF_Data {
    int data;
    char db[4];
};
#endif // SWAPBYTES

int setComm()
{
  char noNMEA1[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x24};
  char noNMEA2[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x2B};
  char noNMEA3[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x32};
  char noNMEA4[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x39};
  char noNMEA5[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x40};
  char noNMEA6[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x05, 0x47};
}

int main(int argc, char* argv[]) {

    cin.read(msgHeader, 540);

    ECEF_Msg myMsg;
    myMsg.msg[28] = 0;

    while(1) {
        cin.read(myMsg.msg, 28);

        #ifdef SWAPBYTES

            for(int i = 1; i < 7; i++) { // change encoding of integers
                ECEF_Data datum;
                datum.data = myMsg.data[i];

                datum.db[3] = datum.db[3] ^ datum.db[0];
                datum.db[0] = datum.db[3] ^ datum.db[0];
                datum.db[3] = datum.db[3] ^ datum.db[0];

                datum.db[2] = datum.db[2] ^ datum.db[1];
                datum.db[1] = datum.db[2] ^ datum.db[1];
                datum.db[2] = datum.db[2] ^ datum.db[1];

                myMsg.data[i] = datum.data;
            }

        #endif // SWAPBYTES

        for(int i = 0; i < 7; i++) {
            cout << "Msg " << i+1 << ": " << myMsg.data[i] << endl;
        }
        cout << endl;
    }

    return 0;
}
