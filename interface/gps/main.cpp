/*
    TODO : inline the byte swapping algorithm in conditional SWAPBYTES. would like to try asm
    TODO : use guaranteed sized data types (uint32_t, uint8_t) in ECEF_Msg and ECEF_Data unions
    TODO : streamline unions. combine so as to use just one
    TODO : read GPS data directly into program. current implementation uses pipe on command line
*/

#include <iostream>

#define SWAPBYTES

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

int main(int argc, char* argv[]) {

    cin.read(msgHeader, 540);

    ECEF_Msg myMsg;
    myMsg.msg[28] = 0;

    while(1 == 1) {
        // other code can go here
        cin.read(myMsg.msg, 28);
    }

        #ifdef SWAPBYTES

            for(int i = 1; i < 7; i++) {
                ECEF_Data datum;
                datum.data = myMsg.data[i];

                char y = datum.db[0];
                datum.db[0] = datum.db[3];
                datum.db[3] = y;

                y = datum.db[1];
                datum.db[1] = datum.db[2];
                datum.db[2] = y;

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