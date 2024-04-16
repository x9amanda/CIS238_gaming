all: JungleCrossing

JungleCrossing: Main.cpp JungleCrossing.o
	g++ -o jungle_crossing Main.cpp JungleCrossing.o -I/usr/include/SDL2 -lSDL2
JungleCrossing.o: JungleCrossing.cpp
	g++ -c JungleCrossing.cpp -I/usr/include/SDL2 -lSDL2

clean:
	rm JungleCrossing.o jungle_crossing