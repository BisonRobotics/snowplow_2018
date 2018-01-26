# makefile for executable


CXX     = g++
INCLUDE = ../include
INCLUDEDRIVERS = ../drivers/include
SRC     = ../src
SRCDrivers = ../drivers/src
OBJS    = obj
BINS    = bin
STDOPTS = -w -lpthread -lncurses -std=c++11 -lm
MISCLIB = $(SRCDrivers)/misc-libs
TESTSRC = $(SRCDrivers)/test
SDLGFX  = --lSDL_gfx -lSDL

ALLOBJS =  $(OBJS)/rs232.o
ALLOBJS += $(OBJS)/tcp.o
ALLOBJS += $(OBJS)/xbox.o
ALLOBJS += $(OBJS)/gps.o
ALLOBJS += $(OBJS)/encoder.o
ALLOBJS += $(OBJS)/lidar.o
ALLOBJS += $(OBJS)/roboteq.o

auto: rs232 tcp roboteq lidar encoder
	$(info -- building autonmous program for the ASC 2018 commpetion main)
	$(CXX) -c -o $(OBJS)/$@.o $(SRC)/autoPlow.cpp -I$(INCLUDE)/ -I$(INCLUDEDRIVERS)/ -I$(MISCLIB)/ $(STDOPTS)
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/tcp.o $(OBJS)/lidar.o $(OBJS)/rs232.o $(OBJS)/encoder.o $(OBJS)/roboteq.o $(STDOPTS) $(SDLGFX)

teleOp: rs232 roboteq xbox encoder
	$(info -- building teleop program for manuvering)
	$(CXX) -c -o $(OBJS)/$@.o $(SRC)/teleOpPlow.cpp -I$(INCLUDE)/ $(STDOPTS)
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/xbox.o $(OBJS)/roboteq.o $(OBJS)/rs232.o $(STDOPTS) $(SDLGFX)


all: rs232 gps tcp xbox roboteq lidar encoder
	$(info -- building all the files for the lulz)

# rules for all of the individual object files that need to be linked in final executable

rs232: $(SRCDrivers)/RS232_GenericController.cpp
	$(info ==  building rs232 interface)
	$(CXX) -c -o $(OBJS)/rs232.o -I$(INCLUDEDRIVERS)/ $(SRCDrivers)/RS232_GenericController.cpp $(STDOPTS)

gps: $(SRCDrivers)/GpsInterface.cpp
	$(info ==  building gps interface)
	$(CXX) -c -o $(OBJS)/gps.o -I$(INCLUDEDRIVERS)/ $(SRCDrivers)/GpsInterface.cpp $(STDOPTS)

tcp: $(SRCDrivers)/TCP_Connection.cpp
	$(info ==  building tcp client interface)
	$(CXX) -c -o $(OBJS)/tcp.o -I$(INCLUDEDRIVERS)/ $(SRCDrivers)/TCP_Connection.cpp $(STDOPTS)

xbox: $(SRCDrivers)/XboxControllerInterface.cpp
	$(info ==  building xbox controller interface)
	$(CXX) -c -o $(OBJS)/xbox.o -I$(INCLUDEDRIVERS)/ $(SRCDrivers)/XboxControllerInterface.cpp $(STDOPTS) -I$(MISCLIB)/ -lSDL

roboteq: $(SRCDrivers)/RoboteQ.cpp
	$(info ==  building roboteq interface)
	$(CXX) -c -o $(OBJS)/roboteq.o -I$(INCLUDEDRIVERS)/ $(SRCDrivers)/RoboteQ.cpp $(STDOPTS)

lidar: $(SRCDrivers)/LidarInterface.cpp
	$(info ==  building SICK sensor interface)
	$(CXX) -c -o $(OBJS)/lidar.o -I$(INCLUDEDRIVERS)/ $(SRCDrivers)/LidarInterface.cpp $(STDOPTS)

encoder: $(SRCDrivers)/EncoderInterface.cpp
	$(info == building encoder interface files)
	$(CXX) -c -o $(OBJS)/encoder.o -I$(INCLUDEDRIVERS)/ $(SRCDrivers)/EncoderInterface.cpp $(STDOPTS)

clean:
	$(info -- removing all binaries and object files)
	#remove all object files
	rm obj/*
	#remove all binary files
	rm bin/*
