OPTS = -w -lm -lSDL -std=c++11

# bullshit target
all: keyevent main
	g++ -o main main.o keyboard.o $(OPTS)

keyevent: KeyboardEvent.cpp
	g++ -c -o keyboard.o KeyboardEvent.cpp $(OPTS)

main: main.cpp
	g++ -c -o main.o main.cpp $(OPTS)

