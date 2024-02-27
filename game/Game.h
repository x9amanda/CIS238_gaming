#include "SDL.h"

class Game
{
public:
    Game(); // empty default constructor

    // Initialize the game
    bool Initialize();

    // Run the game loop until the game is over
    void RunLoop();

    // Shut down the game when it ends
    void Shutdown();

private:
    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // SDL_Point: A data stucture that defines a two dimensional point.
    // Data Fields: int x, int y
    SDL_Point mWindowPosition; // Position of window
    SDL_Point mWindowSize;     // Size of window
    SDL_Point mMousePosition;  // Mouse position coordinates

    // Member data
    SDL_Window *mWindow;     // Window created by SDL2 Lib
    SDL_Renderer *mRenderer; // Renderer for 2D drawing
    Uint32 mTicksCount;      // Number of ticks since the start of the game
    bool mIsRunning;         // Flag for if game should continue to run
};