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
STDOPTS = -lpthread -lncurses -std=c++11

ALLOBJS =  $(OBJS)/rs232.o
ALLOBJS += $(OBJS)/tcp.o

final: rs232 gps tcp
	$(info nothing to do for final executable... yet)

test_rs232: rs232
	$(info no test for serial controller)

test_GPS: gps
	$(info no test for GPS)

# rules for all of the individual object files that need to be linked in final executable

rs232: $(SRC)/RS232_GenericController.cpp
	$(CXX) -c -o $(OBJS)/rs232.o -I$(INCLUDE)/ $(SRC)/RS232_GenericController.cpp $(STDOPTS)

gps:
	$(info nothing to do for GPS)

tcp: $(SRC)/TCP_Connection.cpp
	$(CXX) -c -o $(OBJS)/tcp.o -I$(INCLUDE)/ $(SRC)/TCP_Connection.cpp $(STDOPTS)
