# makefile for executable

# every class interface library has a test file (for testing the library functionality)
# i recommend two tests for each library to ensure that they are fault tolerant
# the 'final' target wont have much use until more of the application has been made
# until then, the main objective is getting the component pieces working

CXX     = g++
INCLUDE = ../include
SRC     = ../src
OBJS    = obj
BINS    = bin
STDOPTS = -w -lpthread -lncurses -std=c++11 -lm
MISCLIB = $(SRC)/misc-libs
TESTSRC = $(SRC)/test
SDLGFX  = -lSDL_gfx

ALLOBJS =  $(OBJS)/rs232.o
ALLOBJS += $(OBJS)/tcp.o
ALLOBJS += $(OBJS)/xbox.o
ALLOBJS += $(OBJS)/gps.o

final: rs232 gps tcp xbox
	$(info -- nothing to do for final executable... yet)

all: test_rs232 test_GPS test_xBox test_xboxMotorBridge test_lidar test_lidarDataCollect #test_encoder
	$(info -- built every test)

# every library has a test here

test_rs232: rs232
	$(info --  building rs232 test program)
	$(CXX) -c -o $(OBJS)/$@.o $(TESTSRC)/rs232.cpp -I$(INCLUDE)/ $(STDOPTS)
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/rs232.o -I$(INCLUDE)/ $(STDOPTS)

test_GPS: gps
	$(info -- building gps test program)
	$(CXX) -c -o $(OBJS)/$@.o $(TESTSRC)/gpsTest.cpp -I$(INCLUDE)/ $(STDOPTS)
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/gps.o $(OBJS)/rs232.o -I$(INCLUDE)/ $(STDOPTS)

test_xBox: xbox
	$(info --  building color object used by test_xBox target)
	$(CXX) -c -o $(MISCLIB)/color.o $(MISCLIB)/Colors.cpp
	$(info --  building xBox controller test program)
	$(CXX) -c -o $(OBJS)/$@.o $(TESTSRC)/xboxcontroller.cpp -I$(INCLUDE)/ $(STDOPTS) -I$(MISCLIB)/ -lSDL
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/xbox.o $(MISCLIB)/color.o -I$(INCLUDE)/ $(STDOPTS) -lSDL

test_xboxMotorBridge: xbox roboteq rs232
	$(info --  building xboxMotorBridge test program)
	$(CXX) -c -o $(OBJS)/$@.o $(TESTSRC)/xboxMotorBridge.cpp -I$(INCLUDE)/ $(STDOPTS) -lSDL
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/xbox.o $(OBJS)/roboteq.o $(OBJS)/rs232.o $(STDOPTS) -lSDL

test_lidar: tcp lidar
	$(info --  building SICK Lidar test program)
	$(CXX) -c -o $(OBJS)/$@.o $(TESTSRC)/sickSensor.cpp -I$(INCLUDE)/ $(STDOPTS) -I$(MISCLIB) -lSDL
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/tcp.o $(OBJS)/lidar.o $(STDOPTS) -lSDL $(SDLGFX)

test_lidarDataCollect: tcp lidar
	$(info --  building SICK Lidar data collection test)
	$(CXX) -c -o $(OBJS)/$@.o $(TESTSRC)/sickDataCollection.cpp -I$(INCLUDE)/ $(STDOPTS)
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/tcp.o $(OBJS)/lidar.o $(STDOPTS)

test_encoder: rs232 encoder
	$(info --  building encoder test program)
	$(CXX) -c -o $(OBJS)/$@.o $(TESTSRC)/encoderTest.cpp -I$(INCLUDE)/ $(STDOPTS)
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/rs232.o $(OBJS)/encoder.o $(STDOPTS)

# rules for all of the individual object files that need to be linked in final executable

rs232: $(SRC)/RS232_GenericController.cpp
	$(info ==  building rs232 interface)
	$(CXX) -c -o $(OBJS)/rs232.o -I$(INCLUDE)/ $(SRC)/RS232_GenericController.cpp $(STDOPTS)

gps: $(SRC)/GpsInterface.cpp
	$(info ==  building gps interface)
	$(CXX) -c -o $(OBJS)/gps.o -I$(INCLUDE)/ $(SRC)/GpsInterface.cpp $(STDOPTS)

tcp: $(SRC)/TCP_Connection.cpp
	$(info ==  building tcp client interface)
	$(CXX) -c -o $(OBJS)/tcp.o -I$(INCLUDE)/ $(SRC)/TCP_Connection.cpp $(STDOPTS)

xbox: $(SRC)/XboxControllerInterface.cpp
	$(info ==  building xbox controller interface)
	$(CXX) -c -o $(OBJS)/xbox.o -I$(INCLUDE)/ $(SRC)/XboxControllerInterface.cpp $(STDOPTS) -I$(MISCLIB)/ -lSDL

roboteq: $(SRC)/RoboteQ.cpp
	$(info ==  building roboteq interface)
	$(CXX) -c -o $(OBJS)/roboteq.o -I$(INCLUDE)/ $(SRC)/RoboteQ.cpp $(STDOPTS)

lidar: $(SRC)/LidarInterface.cpp
	$(info ==  building SICK sensor interface)
	$(CXX) -c -o $(OBJS)/lidar.o -I$(INCLUDE)/ $(SRC)/LidarInterface.cpp $(STDOPTS)

encoder: $(SRC)/Encoder_arduino.cpp
	$(CXX) -c -o $(OBJS)/encoder.o -I$(INCLUDE)/ $(SRC)/Encoder_arduino.cpp $(STDOPTS)

# remove all built binaries
clean:
	$(info -- removing all binaries)
	rm bin/*
