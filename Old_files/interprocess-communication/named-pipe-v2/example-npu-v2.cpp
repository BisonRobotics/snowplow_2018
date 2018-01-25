/*
    This code serves to demonstrate the usage of the second generation named pipe utility
    for interprocess communication (IPC). It spawns multiple threads (described in-depth
    in a different project). JJC::Thread library used for mutlithreading functionality.

    Speed tests--
    tests performed on personal computer
        cpu specs:
        - i5-4590 @ 3.7GHz x4
        - 16GB RAM
        - 64KB L1 cache
        - 256KB L2 cache

        transmit speeds of various data types:
        - char (8-bit)
            ~1,212,856 char/sec   || ~1,212,856 bytes/sec
        - int (32-bit)
            ~1,245,950 int/sec    || ~4,983,800 bytes/sec
        - float (32-bit)
            ~1,245,019 float/sec  || ~4,980,076 bytes/sec
        - long long int (64-bit integer)
            ~1,241,773 long/sec   || ~9,934,184 bytes/sec
        - double (64-bit floating-point)
            ~1,250,781 double/sec || ~10,006,248 bytes/sec
*/

#include <NamedPipeUtility.h>
#include <Thread.h>
#include <iostream>

//speed test runs
#define maxtransmit 10000000

/* test using doubly nested struct */
struct deep_data {
    double aa;
    double bb;
};

/* test using a nested struct */
struct nested_data {
    float a;
    float b;
    deep_data deep_nest;
};

/* test sending more than a single piece of data at once */
struct custom_data {
    int i[4];
    nested_data nd;
};

//change this to whatever primitive you want
typedef custom_data mytype;

using namespace std;

void* write_thread(void*) { //as per JJC::Thread rules, function must accept void* argument even if there is no data. working on fixing this

    JJC::NamedPipeUtility<mytype> writer_pipe;         //instantiate pipe object
    writer_pipe.Simplex_create("/tmp/myfifo-1", true); //specify pipe name and whether it needs to be created
    writer_pipe.Simplex_open(IS_WRITER);               //specify operations this thread will perform on pipe

    /* continue sending data over pipe until user enters zero */
    mytype i_num;
    do {
        cout << "enter 4 ints and 2 floats and 2 doubles:  ";
        cin >> i_num.i[0];
        cin >> i_num.i[1];
        cin >> i_num.i[2];
        cin >> i_num.i[3];
        cin >> i_num.nd.a;
        cin >> i_num.nd.b;
        cin >> i_num.nd.deep_nest.aa;
        cin >> i_num.nd.deep_nest.bb;
        writer_pipe.Simplex_write(&i_num); //single write function
        usleep(200);
    } while(i_num.i[0] != 0);

    /* close and destroy pipe. only one thread needs to destroy the pipe, however both must close their ends */
    writer_pipe.Simplex_close();
    writer_pipe.Simplex_destroy();
}

void* read_thread(void*) {

    JJC::NamedPipeUtility<mytype> reader_pipe;          //instantiate pipe object
    reader_pipe.Simplex_create("/tmp/myfifo-1", false); //specify pipe name and whether it needs to be created
    reader_pipe.Simplex_open(IS_READER);                //specify operations this thread will perform on pipe

    /* continue reading data until recieve zero */
    mytype i_num;
    do {
        reader_pipe.Simplex_read(&i_num); //single read function
        cout << "i_1 = " << i_num.i[0] << endl << "i_2 = " << i_num.i[1] << endl << "i_3 = " << i_num.i[2] << endl << "i_4 = " << i_num.i[3] << endl;
        cout << "a = " << i_num.nd.a << endl << "b = " << i_num.nd.b << endl;
        cout << "aa = " << i_num.nd.deep_nest.aa << endl << "bb = " << i_num.nd.deep_nest.bb << endl;
    } while(i_num.i[0] != 0);

    /* thread closes but does not destroy pipe. pipe destruction is write_thread's job */
    reader_pipe.Simplex_close();
}

int main(int argc, char* argv[]) {

    /* instantiate 2 thread objects to demonstrate IPC with named pipes */
    JJC::Thread<void> send_thread(write_thread);
    JJC::Thread<void> rcv_thread(read_thread);

    /* fork both threads, order doesnt really matter */
    send_thread.forkThread();
    rcv_thread.forkThread();

    /* wait for thread(s) to finish execution */
    rcv_thread.syncThread();

    return 0;
}
