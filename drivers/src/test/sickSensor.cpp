#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <errno.h>
#include <math.h>
#include <SDL/SDL.h>
#include <LidarInterface.h>

#ifndef SCALE_F
#define SCALE_F 20.0
#endif // SCALE_F

#define PIXEL_SIZE 2

// comment out to use file of pre-acquired data
//#define USE_SENSOR

#ifndef USE_SENSOR
#define VALS_PER_MEAS 541 // each is 16-bit unsigned value
#define TIME_PER_SCAN 100 // ms/scan
#endif // USE_SENSOR

using namespace std;

void putTarget(SDL_Surface* screen);
int getFileSize(string filename);

int main(int argc, char* argv[]) {
#ifdef USE_SENSOR
    LidarInterface li;
    li.init(); // initialize SICK sensor communication
    li.setAccessMode(USER::CLIENT);
    li.printReply();
#else
    if(argc != 2) {
        cerr << "Usage:\n<progname> <input_file>\n";
        return 1;
    }

    int num_iters = getFileSize(argv[1]);
    uint16_t* raw_values = new uint16_t[num_iters/2];

    //ifstream input_file(argv[1], ifstream::binary);
    //input_file.read((char*)raw_values, num_iters); // read entire file into memory
    //input_file.close();

    FILE* f = fopen(argv[1], "r");
    int num_bytes_read = fread((void*)raw_values, 1, num_iters, f);
    if(num_bytes_read != num_iters) {
        cerr << "Error reading file\n";
        cerr << "    error: " << errno << endl;
        cerr << "    bytes read: " << num_bytes_read << endl;
    }

    cout << "File size: " << num_iters << " bytes\n";
    num_iters /= (VALS_PER_MEAS * 2);
    cout << "Scans: " << num_iters << endl;

#endif

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(640, 640, 32, SDL_HWACCEL | SDL_DOUBLEBUF);
    int halfX = screen->w / 2;
    int halfY = screen->h / 2;

    uint32_t red = SDL_MapRGB(screen->format, 255, 0, 0);

    float factor = 3.14159265 / 360.00;

    //putTarget(screen);
#ifdef USE_SENSOR
    for(int ij = 0; ij < 2000; ij++) {
        li.scanData();
        vector<float> reply = li.getResults();
#else
    uint32_t time_start = SDL_GetTicks();
    for(int ij = 0; ij < num_iters; ij++) {
        cout << "Iter: " << ij << endl;
        vector<float> reply;
        for(int i = 0; i < VALS_PER_MEAS; i++)
            reply.push_back((float)raw_values[ij*VALS_PER_MEAS + i]);
#endif

        SDL_FillRect(screen, NULL, NULL);
        putTarget(screen);

        for(int i = 0; i < reply.size(); i++) {
            SDL_Rect r;
            r.w = PIXEL_SIZE; r.h = PIXEL_SIZE;
            r.x = halfX + (reply[i] / SCALE_F) * cos(float(i-90) * factor);
            r.y = screen->h - (halfY + (reply[i] / SCALE_F) * sin(float(i-90) * factor));
            SDL_FillRect(screen, &r, red);
        }

        reply.clear(); // not needed but be nice to OS
        SDL_Flip(screen);

#ifdef USE_SENSOR
        li.getDeviceState();
        li.printReply();
#else
        // frame regulation
        uint32_t time_end = SDL_GetTicks();
        cout << "Delay time: " << TIME_PER_SCAN - (time_end - time_start) << endl;
        SDL_Delay(TIME_PER_SCAN - (time_end - time_start));
        time_start = SDL_GetTicks();
        //SDL_Delay(100);
#endif
    }

    //SDL_Delay(10000);

    return 0;
}

int getFileSize(string filename) {
    long beg_, end_;
    ifstream file(filename);
    beg_ = file.tellg();
    file.seekg(0, ios::end);
    end_ = file.tellg();
    file.close();
    return (int)(end_ - beg_);
}

void putTarget(SDL_Surface* screen) {
    uint32_t white = SDL_MapRGB(screen->format, 255, 255, 255);

    SDL_Rect r;
    r.h = 1;
    r.w = screen->w;
    r.x = 0;
    r.y = screen->h / 2;

    SDL_FillRect(screen, &r, white);

    r.h = screen->h / 2;
    r.w = 1;
    r.x = screen->w / 2;
    r.y = 0;

    SDL_FillRect(screen, &r, white);

    for(int i = screen->h / 2; i < screen->h; i++) {
        r.x = i;
        r.y = i;
        r.w = 1;
        r.h = 1;

        SDL_FillRect(screen, &r, white);

        r.x = screen->w - r.x;

        SDL_FillRect(screen, &r, white);
    }

}

