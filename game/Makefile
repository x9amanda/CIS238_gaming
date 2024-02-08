all: Game

Game: Main.cpp Game.o
	g++ -o t Main.cpp Game.o -I/usr/include/SDL2 -lSDL2
Game.o: Game.cpp
	g++ -c Game.cpp -I/usr/include/SDL2 -lSDL2

clean:
	rm Game.o t