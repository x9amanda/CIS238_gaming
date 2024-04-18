// Include necessary headers
#include "JungleCrossing.h"
#include <SDL_image.h>

// Implement methods of the JungleCrossing class

// Constructor
JungleCrossing::JungleCrossing()
    : mWindow(nullptr), mRenderer(nullptr), mTicksCount(0),
      mIsRunning(true), mRabbitTexture(nullptr), mPantherTexture(nullptr),
      mSnakeTexture(nullptr), mMonkeyTexture(nullptr), mCrocTexture(nullptr)
{
    ;
}

// Method to initialize the game
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

    // Load textures
    mRabbitTexture = LoadTexture("rabbit.png");
    mPantherTexture = LoadTexture("panther.png");
    mSnakeTexture = LoadTexture("snake.png");
    mMonkeyTexture = LoadTexture("monkey.png");
    mCrocTexture = LoadTexture("crocodile.png");

    // Return true if successful, false otherwise
    if (!mRabbitTexture || !mPantherTexture || !mSnakeTexture || !mMonkeyTexture || !mCrocTexture)
    {
        SDL_Log("Failed to load textures.");
        return false;
    }

    // Initialize other necessary variables for the actors

    return true;
}

// Method to run the game loop
void JungleCrossing::RunLoop()
{
    // Call base class's RunLoop method
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
    // Update game logic
    // Move actors, check collisions, etc.

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
        25,  // Red
        100, // Green
        30,  // Blue
        255  // Alpha (0=transparent 255=not)
    );

    // Clear Back buffer
    SDL_RenderClear(mRenderer);

    // Render actors
    // Rabbit
    SDL_Rect rabbitRect = {x, y, width, height}; // Set rabbit position and size
    SDL_RenderCopy(mRenderer, mRabbitTexture, nullptr, &rabbitRect);

    // Monkey
    SDL_Rect monkeyRect = {x, y, width, height}; // Set monkey position and size
    SDL_RenderCopy(mRenderer, mMonkeyTexture, nullptr, &monkeyRect);

    // Panther
    SDL_Rect pantherRect = {x, y, width, height}; // Set panther position and size
    SDL_RenderCopy(mRenderer, mPantherTexture, nullptr, &pantherRect);

    // Snake
    SDL_Rect snakeRect = {x, y, width, height}; // Set snake position and size
    SDL_RenderCopy(mRenderer, mSnakeTexture, nullptr, &snakeRect);

    // Croc
    SDL_Rect crocRect = {x, y, width, height}; // Set croc position and size
    SDL_RenderCopy(mRenderer, mCrocTexture, nullptr, &crocRect);

    // Swap main view to be now the back buffer
    SDL_RenderPresent(mRenderer);

    return;
}

// Method to shut down the game and clear memory
void JungleCrossing::Shutdown()
{
    // Cleanup textures
    if (mRabbitTexture)
        SDL_DestroyTexture(mRabbitTexture);
    if (mPantherTexture)
        SDL_DestroyTexture(mPantherTexture);
    if (mSnakeTexture)
        SDL_DestroyTexture(mSnakeTexture);
    if (mMonkeyTexture)
        SDL_DestroyTexture(mMonkeyTexture);
    if (mCrocTexture)
        SDL_DestroyTexture(mCrocTexture);

    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}