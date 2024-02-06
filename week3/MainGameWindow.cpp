// to complie
// g++ MainGameWindow.cpp -I/usr/include/SDL1 -lSDL2

#include "SDL.h"

int
main(int argc, char *argv[])
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if ( sdlResult != 0)
    {
        SDL_Log("SDL VIDEO INIT FAILED. %s", SDL_GetError());
        return false;
    }
}