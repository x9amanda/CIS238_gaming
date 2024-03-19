all: Pong

Pong: Main.cpp Pong.o
	g++ -o pong Main.cpp Pong.o -I/usr/include/SDL2 -lSDL2
Pong.o: Pong.cpp
	g++ -c Pong.cpp -I/usr/include/SDL2 -lSDL2

clean:
	rm Pong.o pong