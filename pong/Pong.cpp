#include "Pong.h"

// #define MAX_WIDTH 1024  // Max x resolution value
// #define MAX_HEIGHT 768 // Max y resolution value
// #define TW_THICKNESS 20 // Top wall thickness
// #define BW_THICKNESS 20 // Bottom wall thickness

// bool flag = true;

Pong::Pong()
    : mWindow(nullptr),
      mRenderer(nullptr),
      mTicksCount(0),
      mIsRunning(true)
{
}

bool Pong::Initialize()
{
    // Init SDL
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
    {
        SDL_Log("SDL VIDEO INIT FAILED. %s",
                SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        "PONG",
        100,              // x coordinate
        100,              // y coordinate
        1024,             // Window width
        768,              // Window height
        SDL_WINDOW_OPENGL // Flags (0 is for no flags)
    );

    if (!mWindow)
    {
        SDL_Log("YOU (THE WINDOW) are A FAILURE, %s",
                SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
        mWindow, // Window to create for the renderer
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!mRenderer)
    {
        SDL_Log("Render = no go, %s", SDL_GetError());
        return false;
    }
    return true;
}

void Pong::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Pong::ProcessInput()
{
    SDL_Event event; // Handler for different event types
                     // Reads from event queue
                     // Places events on event queue

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    // Get the state of the keyboard
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    // If user presses escape, end the game loop
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }

    return;
}

void Pong::UpdateGame()
{
    // stub
    return;
}

void Pong::GenerateOutput()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        120, // Red
        95, // Green
        140, // Blue
        255  // Alpha (0=transparent 255=not)
    );

    // Clear Back buffer
    SDL_RenderClear(mRenderer);

    // Render the new output
    SDL_SetRenderDrawColor(mRenderer, 70, 70, 70, 255);

    // Draw a top wall
    SDL_Rect wall{
        0,    // top left x
        0,    // top teft y
        1024, // width
        20    // height
    };
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw a bottom wall
    wall.y = 768 - 20;
    SDL_RenderFillRect(mRenderer, &wall);

    SDL_Rect sideborder{
        1000,
        20,
        5,
        728};
    SDL_RenderFillRect(mRenderer, &sideborder);

    // Render the new output
    SDL_SetRenderDrawColor(mRenderer, 0, 150, 150, 255);

    // Draw right wall
    SDL_Rect sidewall{
        1004, // top right x
        20,   // top left y
        20,   // width
        728   // height
    };
    SDL_RenderFillRect(mRenderer, &sidewall);

    // Draw paddle
    SDL_Rect paddle{
        0,   // paddle x
        234, // paddle starting y
        20,  // paddle width
        150, // paddle height
    };
    SDL_RenderFillRect(mRenderer, &paddle);

    // Render the new output
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    // Draw ball
    SDL_Rect ball{
        50,  // ball starting x
        284, // ball starting y
        10,  // ball width
        10,  // ball height
    };
    SDL_RenderFillRect(mRenderer, &ball);

    // Swap main view to be now the back buffer
    SDL_RenderPresent(mRenderer);

    return;
}

void Pong::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}