#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

#include <errno.h>
#include <math.h>
#include <SDL/SDL.h>
#include <drivetrain.h>
#include <objectDection.h>
// #include <LidarInterface.h>
#include <Colors_v2.h>
#include <spod.h>
// #include <SDL/SDL_gfxPrimitives.h>




    int main(int argc, char const *argv[]) {
    //check if user entered a field
    if(argc != 2) {
        std::cout << "USAGE: " << argv[0] << " I or III\n";
        return 1;
    }
    bool singleI;
    //determine which path to take
    if(strcmp(argv[1], "I")==0){
        std::cout << "runnning the single I.. press ctrl + C to stop" << std::endl;
        singleI = true;
    }else if(strcmp(argv[1], "III") == 0){
        // do single III shit
        std::cout << "running the Triple III ... press ctrl + C to stop" << std::endl;
        singleI = false;
    }else{
        std::cout << "you're an idiot try again." << std::endl;
        return 1;
    }

    usleep(10000);
    cout << "initializing drivetrain" << endl;
    drivetrain chasis = drivetrain();

    // cout << "initializing lidar shannagains" << endl;
    // objectDection lidar;
    // lider.init();


    if(singleI){
        chasis.
    }else{ //run Triple I program

    }

    return 0;
}
