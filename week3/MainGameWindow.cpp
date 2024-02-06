// to complie
// g++ MainGameWindow.cpp -I/usr/include/SDL1 -lSDL2

#include "SDL.h"

int
main(int argc, char *argv[])
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if ( sdlResult != 0)
    {
        SDL_Log("SDL VIDEO INIT FAILED. %s",
        SDL_GetError());
        return false;
    }

    // Create a window with the specified position, dimensions, and flags
    SDL_Window *mWindow = SDL_CreateWindow(
        "Game Programming is Killer!",  // game title
        100,                            // top left x coordinate
        100,                            // top left y coordinate
        1024,
        1768,
        0
    );


    // bail out if game window creation fails
    if (!mWindow)
    {
        SDL_Log("Failed to create game window %s",
        SDL_GetError());
        return false;
    }

// A structure that contains a rendering state.
    SDL_Renderer *renderer =
        // Create a 2D rendering context for a window.
        SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_SOFTWARE);
    // Set the color used for drawing operations (Rect, Line and Clear).
    SDL_SetRenderDrawColor(renderer, 0, 205, 205, 50); // R, G, B, Alpha
    // Clear the current rendering target with the drawing color.
    SDL_RenderClear(renderer);
    // Update the screen with any rendering performed since the previous call.
    SDL_RenderPresent(renderer);
    // Wait a specified number of milliseconds before returning.
    SDL_Delay(10000);

    // Destroy a window/Clear up memory
    SDL_DestroyWindow(mWindow);
    // Clean up all initialized subsystems.
    SDL_Quit();

    return 0;
}