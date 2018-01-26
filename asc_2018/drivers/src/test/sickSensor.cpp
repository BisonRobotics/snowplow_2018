#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <errno.h>
#include <math.h>
#include <SDL/SDL.h>
#include <LidarInterface.h>
#include <Colors_v2.h>
#include <spod.h>
#include <SDL/SDL_gfxPrimitives.h>

#ifndef SCALE_F
#define SCALE_F 30.0
#endif // SCALE_F

#define PIXEL_SIZE 3
#define DETECT_THRESHOLD 800.0f // distance between pts to be considered one object (mm)
#define OBJECT_THRESHOLD 1200.0f // distance between objs to be considered together (mm)

// comment out to use file of pre-acquired data
#define USE_SENSOR

// comment out to not use Object Detection algorithm
#define USE_SPOD

// comment out to not plot raw data
#define PLOT_RAW_DATA

#ifndef USE_SENSOR
#define VALS_PER_MEAS 541 // each is 16-bit unsigned value
#define TIME_PER_SCAN 100 // ms/scan
#endif // USE_SENSOR

using namespace std;

void putTarget(SDL_Surface* screen);
int getFileSize(string filename);
void drawDetectedObject(      const zone__& z, SDL_Surface* screen, uint32_t color);
void drawDetectedObjectBox(   const zone__& z, SDL_Surface* screen, uint32_t color);
void drawDetectedObjectCircle(const zone__& z, SDL_Surface* screen, uint32_t color);

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
        return 1;
    }

    cout << "File size: " << num_iters << " bytes\n";
    num_iters /= (VALS_PER_MEAS * 2);
    cout << "Scans: " << num_iters << endl;
#endif

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(640, 640, 32, SDL_HWACCEL | SDL_DOUBLEBUF);
    int halfX = screen->w / 2;
    int halfY = screen->h / 2;

    ColorPallette cp_std(screen);
    ColorPallette cp_gfx(screen);
    cp_gfx.convertColorsToGfxMode();

    uint32_t red = cp_std.red;

    float factor = 3.14159265 / 360.00; // degree to rad conversion

#ifdef USE_SENSOR
    for(int ij = 0; ij < 2000; ij++) {
        li.scanData();
        vector<float> reply = li.getResults();
#else
    uint32_t time_start = SDL_GetTicks();
    for(int ij = 0; ij < num_iters; ij++) {
        //cout << "Iter: " << ij << endl;
        vector<float> reply;
        for(int i = 0; i < VALS_PER_MEAS; i++)
            reply.push_back((float)raw_values[ij*VALS_PER_MEAS + i]);
#endif

        SDL_FillRect(screen, NULL, NULL);
        putTarget(screen);

        const float MIN_MEASURE = 10.0;
        // pre-process the data before passing it to spod
        for(int i = 1; i < reply.size(); i++) {
            if(reply[i] < MIN_MEASURE)
                reply[i] = reply[i-1]; // should cover arbitrary ranges of bad data
        }

#ifdef PLOT_RAW_DATA
        for(int i = 0; i < reply.size(); i++) {
            SDL_Rect r;
            r.w = PIXEL_SIZE; r.h = PIXEL_SIZE;
            r.x = halfX + (reply[i] / SCALE_F) * cos(float(i-90) * factor) -1;
            r.y = screen->h - (halfY + (reply[i] / SCALE_F) * sin(float(i-90) * factor)) -1;
            SDL_FillRect(screen, &r, red);
        }
#endif // PLOT_RAW_DATA

#ifdef USE_SPOD

        vector<v2f> v_vec(541);
        for(int i = 0; i < reply.size(); i++) { // convert mesaurements into cartesian coordinates
            v2f v_temp;
            v_temp.x = reply[i] * cos(float(i-90) * factor);
            v_temp.y = reply[i] * sin(float(i-90) * factor);
            v_vec.push_back(v_temp);
        }

        // we have access to an array of floats representing measurement values in mm
        vector<zone__> objs = spodAlgo(v_vec, DETECT_THRESHOLD); // second arg is threashold in mm
        //vector<zone__> objs = spodAlgoMaximizeCoverage(v_vec, DETECT_THRESHOLD);
        for(int i = 0; i < objs.size(); i++) {
            drawDetectedObjectCircle(objs[i], screen, cp_gfx.aqua);
            //drawDetectedObjectBox(objs[i], screen, cp_gfx.aqua);
        }

        cout << "Objs: " << objs.size() << endl;

        vector<zone__> reduce_objs = spodReduceObjs(objs, OBJECT_THRESHOLD);
        for(int i = 0; i < reduce_objs.size(); i++) {
            //drawDetectedObject(reduce_objs[i], screen, cp_gfx.fuschia);
            //drawDetectedObjectBox(reduce_objs[i], screen, cp_gfx.fuschia);
        }
        cout << "Reduced obj count: " << reduce_objs.size() << endl;

#endif // USE_SPOD

        reply.clear(); // not needed but be nice to OS
        SDL_Flip(screen);

#ifdef USE_SENSOR
        li.getDeviceState();
        li.printReply();
#else
        // frame regulation
        uint32_t time_end = SDL_GetTicks();
        //cout << "Delay time: " << TIME_PER_SCAN - (time_end - time_start) << endl;
        SDL_Delay(TIME_PER_SCAN - (time_end - time_start));
        time_start = SDL_GetTicks();
        //SDL_Delay(100);
#endif
    }

    SDL_Quit();
    //SDL_Delay(10000);

    return 0;
}

void drawDetectedObject(const zone__& z, SDL_Surface* screen, uint32_t color) {
    lineColor(screen,
            (z.x1/SCALE_F) + screen->w/2,
            screen->h - (z.y1/SCALE_F) - screen->h/2,
            (z.x2/SCALE_F) + screen->w/2,
            screen->h - (z.y2/SCALE_F) - screen->h/2,
            color);
}

void drawDetectedObjectBox(const zone__& z, SDL_Surface* screen, uint32_t color) {
    rectangleColor(screen,
            (z.x1/SCALE_F) + screen->w/2,
            screen->h - (z.y1/SCALE_F) - screen->h/2,
            (z.x2/SCALE_F) + screen->w/2,
            screen->h - (z.y2/SCALE_F) - screen->h/2,
            color);
}

void drawDetectedObjectCircle(const zone__& z, SDL_Surface* screen, uint32_t color) {
    float half_x = (z.x1 + z.x2) / 2.0;
    float half_y = (z.y1 + z.y2) / 2.0;
    float radius = distance(z.x1, z.y1, z.x2, z.y2) / 2.0; // from spod.h

    circleColor(screen,
            (half_x/SCALE_F) + screen->w/2,
            screen->h - (half_y/SCALE_F) - screen->h/2,
            radius/SCALE_F,
            color);
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
    uint32_t grey = SDL_MapRGB(screen->format, 80, 80, 80);

    const float plow_w = 685.8f / SCALE_F;
    const float plow_l = 1143.0f / SCALE_F;

    // position the snowplow in proper location
    float x = screen->w/2 - plow_w/2;
    float y = screen->h/2;

    SDL_Rect s;
    s.x = x;
    s.y = y;
    s.w = plow_w;
    s.h = plow_l;

    SDL_FillRect(screen, &s, grey);

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
