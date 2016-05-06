/*
    This code serves to demonstrate the usage of the second generation named pipe utility
    It spawns multiple threads (described in-depth in a different project). JJC::Thread
    library used for mutlithreading functionality. In current state, this code will compile
    but get hung up during runtime. It should be noted that the compiler is told where to
    look for 'NamedPipeUtility.h', thus the angle brackets instead of quotes.
*/

#include <NamedPipeUtility.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    //as the base data type is the same size, JJC::NPU should have no trouble sending data
    JJC::NamedPipeUtility<int>          writer_pipe;
    JJC::NamedPipeUtility<unsigned int> reader_pipe;

    writer_pipe.Simplex_create("/tmp/myfifo-1", true);
    reader_pipe.Simplex_create("/tmp/myfifo-1", false);

    reader_pipe.Simplex_open(IS_READER);
    writer_pipe.Simplex_open(IS_WRITER);

    writer_pipe.Simplex_close();
    reader_pipe.Simplex_close();
    writer_pipe.Simplex_destroy();

    return 0;
}

