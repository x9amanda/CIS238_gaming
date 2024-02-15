#include "Game.h"

Game::Game()
  : mWindow(nullptr),
    mRenderer(nullptr),
    mTicksCount(0),
    mIsRunning (true)
{ }

bool Game::Initialize()
{
    // init SDL
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if ( sdlResult !=0 )
    {
        SDL_Log("SDL VIDEO INIT FAILED. %s",
        SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        "Game Name goes here",
        100,        // x coordinate
        100,        // y coordinate
        1024,       // window width
        768,        // window height
        0           // flags (0 is for no flags)
    );

    if (!mWindow)
    {
        SDL_Log("YOU (THE WINDOW) are A FAILURE, %s",
        SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
        mWindow,        // window to create for the renderer
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );
    
    if(!mRenderer)
    {
        SDL_Log("Render = no go, %s",
        SDL_GetError());
        return false; 
    }
    return true;
}

void Game::RunLoop()
{
    while(mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event; // Handler for different event types
                     // Reads from event queue
                     // Places events on event queue

    while (SDL_PollEvent( &event ))
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

void Game::UpdateGame()
{
    // stub
    return;
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        178,    // Red
        102,    // Green
        255,    // Blue
        255     // Alpha (0=transparent 255=not)
    );

    // Clear Back buffer
    SDL_RenderClear(mRenderer);

    // Render the new output
    SDL_SetRenderDrawColor(mRenderer, 140, 140, 140, 255);

    // Draw a top wall
    SDL_Rect wall{
        0,          // top left x
        0,          // top teft y
        1024,       // width
        68          // height
    };
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw a bottom wall
    wall.y = 768 - 68;
    SDL_RenderFillRect(mRenderer, &wall);

    // Swap main view to be now the back buffer
    SDL_RenderPresent(mRenderer);

    return;
}

void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}