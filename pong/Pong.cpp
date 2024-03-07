#include "Pong.h"

bool hitPaddle();
bool hitTopWall();
bool hitBottomWall();
bool hitRightWall();

const float paddleH = 100.0f;

#define MAX_WIDTH 1024 // Max x resolution value
#define MAX_HEIGHT 768 // Max y resolution value
#define THICKNESS 20   // Top/bottom wall & paddle thickness

// bool flag = true;

Pong::Pong()
    : mWindow(nullptr), mRenderer(nullptr), mTicksCount(0), mIsRunning(true)
{
}

bool Pong::Initialize()
{
    // Init SDL
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
    {
        SDL_Log("SDL VIDEO INIT FAILED. %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("PONG",
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

    // where the paddle will be positioned
    mPaddlePos.x = 10.0f;
    mPaddlePos.y = 768 / 2.0f;

    // where the ball will start moving from
    mBallPos.x = 1024 / 4.0f;
    mBallPos.y = 768 / 4.0f;

    // set simulated velocity of the ball
    mBallVel.x = -200.0f;
    mBallVel.y = 200.0f;
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

    // Update the paddle direction based on Up and Down keys
    mPaddleDir = 0;
    if (state[SDL_SCANCODE_UP])
    {
        mPaddleDir -= 1;
    }

    if (state[SDL_SCANCODE_DOWN])
    {
        mPaddleDir += 1;
    }
}

void Pong::UpdateGame()
{
    // Wait until 16ms have elapsed since the last frame render
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
    {
        ; // Do nothing
    }

    // Delta time is the difference in ticks from the last frame
    // converted to seconds
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    // Force max delta timeto limit at 0.05
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    // Update tick count for the next loop (next frame)
    mTicksCount = SDL_GetTicks();

    // How much to move the paddle
    if (mPaddleDir != 0)
    {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

        // SDL_Log(
        //"mPaddlePos.x == %f, mPaddlePos.y == %f",
        // mPaddlePos.x, mPaddlePos.y);
        // SDL_Log("mBallPos.x == %f, mBallPos.y == %f", mBallPos.x, mBallPos.y);
        SDL_Log("mBallVel.x == %f, mBallPos.y == %f", mBallVel.x, mBallPos.y);

        // Make sure the paddle does NOT go off the screen
        if (mPaddlePos.y < (paddleH / 2.0f + THICKNESS))
        {
            mPaddlePos.y = paddleH / 2.0f + THICKNESS;
        }
        else if (mPaddlePos.y >= 697.412354f)
        {
            mPaddlePos.y = MAX_HEIGHT - paddleH / 2.0f - THICKNESS;
        }
    }

    // Update the ball position based on velocity
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallPos.y * deltaTime;

    // Bounce if appropriate
    
    if (hitPaddle())    // Did we intersect with the paddle?
    {
        mBallVel.y = mBallVel * -1.0f;
    } 
    else if (hitTopWall())// Did we intersect with the top wall?
    {
        mBallVel.y = mBallVel * -1.0f;
    }
       else if (hitBottomWall())// Did we intersect with the bottom wall?
    {
        mBallVel.y = mBallVel * -1.0f;
    }    
    else if (hitRightWall())// Did we intersect with the opposite wall?
    {
        mBallVel.y = mBallVel * -1.0f;
    }
    // Did the ball go past the paddle and off screen?
    else if (mBallPos.x < 0)
    {
        mIsrunning = false;
    }
    // If yes, mIsRunning = false ... gave over)
}

void Pong::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer,
                           120, // Red
                           95,  // Green
                           140, // Blue
                           255  // Alpha (0=transparent 255=not)
    );

    // Clear Back buffer
    SDL_RenderClear(mRenderer);

    // Render the new output
    SDL_SetRenderDrawColor(mRenderer, 70, 70, 70, 255);

    // Draw a top wall
    SDL_Rect wall{
        0,         // top left x
        0,         // top teft y
        MAX_WIDTH, // width
        THICKNESS  // thickness
    };
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw a bottom wall
    wall.y = MAX_HEIGHT - 20;
    SDL_RenderFillRect(mRenderer, &wall);

    SDL_Rect sideborder{1000, 20, 5, 728};
    SDL_RenderFillRect(mRenderer, &sideborder);

    // Render the new output
    SDL_SetRenderDrawColor(mRenderer, 0, 150, 150, 255);

    // Draw right wall
    SDL_Rect sidewall{
        MAX_WIDTH - THICKNESS,     // top right x
        THICKNESS,                 // top left y
        THICKNESS,                 // width
        MAX_HEIGHT - THICKNESS * 2 // height
    };
    SDL_RenderFillRect(mRenderer, &sidewall);

    // Draw paddle
    SDL_Rect paddle{
        // 0,   // paddle x
        // 234, // paddle starting y
        // 20,  // paddle width
        // 150, // paddle height
        static_cast<int>(mPaddlePos.x),               // paddle x pos
        static_cast<int>(mPaddlePos.y - paddleH / 2), // paddle y pos
        THICKNESS,                                    // paddle width
        static_cast<int>(paddleH)};                   // paddle height
    SDL_RenderFillRect(mRenderer, &paddle);

    // Render the new output
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    // Draw ball
    SDL_Rect ball{
        // 50,  // ball starting x
        // 284, // ball starting y
        static_cast<int>(mBallPos.x - THICKNESS / 2), // ball x pos
        static_cast<int>(mBallPos.y - THICKNESS / 2), // ball y pos
        THICKNESS / 2,                                // ball width
        THICKNESS / 2                                 // ball height
    };
    SDL_RenderFillRect(mRenderer, &ball);

    // Update the screen with any rendering performed since the previous call
    // AKA: Swap main view to be now the back buffer
    SDL_RenderPresent(mRenderer);

    return;
}

void Pong::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

// STUB
bool hitPaddle(); {
    return false;
}
bool hitTopWall(); {
    return false;
}
bool hitBottomWall(); {
    return false;
}
bool hitRightWall(); {
    return false;
}