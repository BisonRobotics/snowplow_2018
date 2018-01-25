/*
    Collect data at 10 Hz
    541 2-byte values, 10x/sec
     = 10820 bytes/second data produced
    or ~10KB/second
*/

#include <iostream>
#include <math.h>
#include <vector>
#include <LidarInterface.h>
#include <string>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>

#define PRINTLN cout << endl

using namespace std;

uint64_t getUsecTimestamp(void);

int main(int argc, char* argv[]) {

    int numIterations = 0;
    string filename = "/tmp/";

    if(argc != 3) {
        cerr << "Program usage:\n<progname> <iters> <filename>\n";
        return 1;
    } else {
        numIterations = stoi(argv[1]);
        filename += argv[2];
    }

    LidarInterface li;
    li.init();
    li.setAccessMode(USER::CLIENT);
    li.printReply();

    li.sendCmd("sRN LMPscancfg", true);
    li.printReply();
    PRINTLN;

    li.sendCmd("sRN LCMstate", true);
    li.printReply();
    PRINTLN;

    li.sendCmd("sRN STlms", true);
    li.printReply();
    PRINTLN;

    li.sendCmd("sRI 0", true);
    li.printReply();
    PRINTLN;

    li.sendCmd("sRN LocationName", true);
    li.printReply();
    PRINTLN;

    //return 0;

    ofstream outputStream(filename, ofstream::binary);

    uint64_t begin_time = getUsecTimestamp();

    uint64_t loop_time_start = getUsecTimestamp();

    for(int i = 0; i < numIterations; i++) {
        cout << "Iter: " << i+1 << endl;
        li.scanData();
        vector<uint16_t> data = li.getRawResults();
        outputStream.write((char*)&data[0], 541*2);

        //usleep(30000);

        // scan time regulation
        uint64_t loop_time_end = getUsecTimestamp();
        uint64_t loop_time_tot = loop_time_end - loop_time_start;
        cout << "Loop time: " << loop_time_tot << endl;
        loop_time_start = loop_time_end;
        //if(loop_time_tot < 100000)
            //usleep(100000 - loop_time_tot);
    }

    uint64_t end_time = getUsecTimestamp();

    outputStream.close();

    // figure out the scans/sec
    end_time -= begin_time;

    double d = end_time;
    d /= 1000000.0;

    cout << "Total time: " << d << " seconds" << endl;
    cout << "Scans/sec:  " << 1.0/(d/numIterations) << endl;

    return 0;
}

uint64_t getUsecTimestamp(void) {
    timeval t;
    gettimeofday(&t, 0);
    uint64_t micro = uint64_t(1000000)*t.tv_sec  +  t.tv_usec;
    return micro;
}
