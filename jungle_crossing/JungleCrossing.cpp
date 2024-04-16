#include "JungleCrossing.h"

JungleCrossing::JungleCrossing()
    : mWindow(nullptr), mRenderer(nullptr), mTicksCount(0), mIsRunning(true)
{
    return;
}

bool JungleCrossing::Initialize()
{
    // Init SDL
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
    {
        SDL_Log("SDL VIDEO INIT FAILED. %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Jungle Crossing",
                               100,              // x coordinate
                               100,              // y coordinate
                               1024,             // Window width
                               768,              // Window height
                               SDL_WINDOW_OPENGL // Flags (0 is for no flags)
    );

    if (!mWindow)
    {
        SDL_Log("YOU (THE WINDOW) are A FAILURE, %s", SDL_GetError());
        return false;
    }

    mRenderer =
        SDL_CreateRenderer(mWindow, // Window to create for the renderer
                           -1,
                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!mRenderer)
    {
        SDL_Log("Render = no go, %s", SDL_GetError());
        return false;
    }

    return true;
}

void JungleCrossing::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void JungleCrossing::ProcessInput()
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
}

void JungleCrossing::UpdateGame()
{
    // Wait until 16ms have elapsed since the last frame render
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
    {
        ; // Do nothing
    }
}

void JungleCrossing::GenerateOutput()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        25, // Red
        100, // Green
        30, // Blue
        255  // Alpha (0=transparent 255=not)
    );

    // Clear Back buffer
    SDL_RenderClear(mRenderer);

    // Render the new output

    // Swap main view to be now the back buffer
    SDL_RenderPresent(mRenderer);

    return;
}

void JungleCrossing::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}