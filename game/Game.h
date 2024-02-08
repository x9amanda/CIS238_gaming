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

    // Member data
    SDL_Window *mWindow;   // Window created by SDL2 Lib
    SDL_Renderer *mRenderer; // Renderer for 2D drawing
    Uint32 mTicksCount;    // Number of ticks since the start of the game
    bool mIsRunning;       // Game should continue to run
};