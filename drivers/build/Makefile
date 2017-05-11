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
STDOPTS = -w -lpthread -lncurses -std=c++11
MISCLIB = $(SRC)/misc-libs
TESTSRC = $(SRC)/test
ALLOBJS =  $(OBJS)/rs232.o
ALLOBJS += $(OBJS)/tcp.o
ALLOBJS += $(OBJS)/xbox.o

final: rs232 gps tcp xbox
	$(info nothing to do for final executable... yet)

all: test_rs232 test_GPS test_xBox
	# build every test

# every library has a test here

test_rs232: rs232
	$(info --  building rs232 test program)
	$(CXX) -c -o $(OBJS)/$@.o $(TESTSRC)/rs232.cpp -I$(INCLUDE)/ $(STDOPTS)
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/rs232.o -I$(INCLUDE)/ $(STDOPTS)

test_GPS: gps
	$(info no test for GPS)

test_xBox: xbox
	$(info --  building color object used by test_xBox target)
	$(CXX) -c -o $(MISCLIB)/color.o $(MISCLIB)/Colors.cpp
	$(info --  building xBox controller test program)
	$(CXX) -c -o $(OBJS)/$@.o $(TESTSRC)/xboxcontroller.cpp -I$(INCLUDE)/ $(STDOPTS) -I$(MISCLIB)/ -lSDL
	$(CXX) -o $(BINS)/$@ $(OBJS)/$@.o $(OBJS)/xbox.o $(MISCLIB)/color.o -I$(INCLUDE)/ $(STDOPTS) -lSDL

# rules for all of the individual object files that need to be linked in final executable

rs232: $(SRC)/RS232_GenericController.cpp
	$(CXX) -c -o $(OBJS)/rs232.o -I$(INCLUDE)/ $(SRC)/RS232_GenericController.cpp $(STDOPTS)

gps:
	$(info nothing to do for GPS)

tcp: $(SRC)/TCP_Connection.cpp
	$(CXX) -c -o $(OBJS)/tcp.o -I$(INCLUDE)/ $(SRC)/TCP_Connection.cpp $(STDOPTS)

xbox: $(SRC)/XboxControllerInterface.cpp
	$(CXX) -c -o $(OBJS)/xbox.o -I$(INCLUDE)/ $(SRC)/XboxControllerInterface.cpp $(STDOPTS) -I$(MISCLIB)/ -lSDL
