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
    // stub
    return;
}

void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
    return;
}

void Game::ProcessInput()
{
    // stub
    return;
}

void Game::UpdateGame()
{
    // stub
    return;
}

void Game::GenerateOutput()
{
    // stub
    return;
}