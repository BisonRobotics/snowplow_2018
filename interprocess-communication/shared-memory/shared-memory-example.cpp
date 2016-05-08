/*
    Studying shared memory with Linux
    making example C++ compliant

    Currently this example will compile but will throw a segmentation fault during execution, investigation in progress
*/

#include <iostream>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>

using namespace std;

int main_(int argc, char* argv[]) {
    int segment_id;
    char* shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = 0x6400; //25600 base-ten

    /* allocate a shared memory segment */
    segment_id = shmget(IPC_PRIVATE, shared_segment_size, IPC_CREAT | IPC_EXCL | S_IRUSR);

    /* attach the shared memory segment */
    shared_memory = (char*)shmat(segment_id, 0, 0);
    cout << "shared memory attached at address: " << (void*)shared_memory << endl;

    /* determine segment's size */
    shmctl(segment_id, IPC_STAT, &shmbuffer);
    segment_size = shmbuffer.shm_segsz;
    cout << "segment size: " << segment_size << endl;

    /* write a string to shared memory segment */
    sprintf(shared_memory, "Hello World");

    /* print string before detaching */
    cout << shared_memory << endl;

    /* detach the shared memory segment */
    shmdt(shared_memory);

    /* reattach shared memory segment at different address */
    shared_memory = (char*)shmat(segment_id, (void*)0x5000000, 0); //dont usually hardcode pointer values
    cout << "shared memory reattached at address: " << (void*)shared_memory << endl;

    /* print out string from shared memory */
    cout << shared_memory << endl;

    /* detach shared memory segment */
    shmdt(shared_memory);

    /* free memory associated with shared memory segment, effectively deleting shared memory */
    shmctl(segment_id, IPC_RMID, 0);

    return 0;
}

