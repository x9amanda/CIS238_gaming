// Include necessary headers
#include "JungleCrossing.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH 1024 // Max x resolution value
#define SCREEN_HEIGHT 768 // Max y resolution value

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
                               SCREEN_WIDTH,             // Window width
                               SCREEN_HEIGHT,              // Window height
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

    // Set initial position of the rabbit
mRabbitPos.x = 100.0f;
mRabbitPos.y = SCREEN_HEIGHT / 2.0f; // Centered vertically on the screen

// Set initial position of the panther
mPantherPos.x = SCREEN_WIDTH - 100.0f; // Right side of the screen
mPantherPos.y = 100.0f;

// Set initial position of the snake
mSnakePos.x = SCREEN_WIDTH / 2.0f; // Centered horizontally on the screen
mSnakePos.y = SCREEN_HEIGHT - 100.0f; // Bottom of the screen

// Set initial position of the monkey
mMonkeyPos.x = 200.0f;
mMonkeyPos.y = 200.0f;

// Set initial position of the crocodile
mCrocPos.x = SCREEN_WIDTH - 200.0f;
mCrocPos.y = SCREEN_HEIGHT - 200.0f;

// Set movement velocity for the rabbit
float rabbitSpeed = 200.0f; // Adjust as needed
mRabbitVel.x = rabbitSpeed;
mRabbitVel.y = rabbitSpeed;

// Set movement velocity for the panther
float pantherSpeed = 150.0f; // Adjust as needed
mPantherVel.x = -pantherSpeed; // Move towards the left
mPantherVel.y = 0.0f; // No vertical movement

// Set movement velocity for the snake
float snakeSpeed = 100.0f; // Adjust as needed
mSnakeVel.x = 0.0f; // No horizontal movement
mSnakeVel.y = -snakeSpeed; // Move upwards

// Set movement velocity for the monkey
float monkeySpeed = 120.0f; // Adjust as needed
mMonkeyVel.x = monkeySpeed;
mMonkeyVel.y = monkeySpeed;

// Set movement velocity for the crocodile
float crocSpeed = 180.0f; // Adjust as needed
mCrocVel.x = -crocSpeed; // Move towards the left
mCrocVel.y = 0.0f; // No vertical movement

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

// Update the rabbit direction based on arrow keys
mRabbitDir = Vector2(0, 0); // Initialize rabbit direction vector

// Check if the Up arrow key is pressed
if (state[SDL_SCANCODE_UP])
{
    mRabbitDir.y -= 1; // Move rabbit up
}

// Check if the Down arrow key is pressed
if (state[SDL_SCANCODE_DOWN])
{
    mRabbitDir.y += 1; // Move rabbit down
}

// Check if the Left arrow key is pressed
if (state[SDL_SCANCODE_LEFT])
{
    mRabbitDir.x -= 1; // Move rabbit to the left
}

// Check if the Right arrow key is pressed
if (state[SDL_SCANCODE_RIGHT])
{
    mRabbitDir.x += 1; // Move rabbit to the right
}

}

void JungleCrossing::UpdateGame()
{
    // Wait until 16ms have elapsed since the last frame render
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
    {
        ; // Do nothing
    }

    // Calculate delta time (time elapsed since the last frame) in seconds
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    // Limit maximum delta time to avoid large jumps in movement
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    // Update tick count for the next loop (next frame)
    mTicksCount = SDL_GetTicks();

    // Move the rabbit based on its direction and velocity
    mRabbitPos.x += mRabbitDir.x * mRabbitVel.x * deltaTime;
    mRabbitPos.y += mRabbitDir.y * mRabbitVel.y * deltaTime;

    // Ensure the rabbit stays within the screen boundaries
    if (mRabbitPos.x < 0)
    {
        mRabbitPos.x = 0;
    }
    else if (mRabbitPos.x > SCREEN_WIDTH)
    {
        mRabbitPos.x = SCREEN_WIDTH;
    }

    if (mRabbitPos.y < 0)
    {
        mRabbitPos.y = 0;
    }
    else if (mRabbitPos.y > SCREEN_HEIGHT)
    {
        mRabbitPos.y = SCREEN_HEIGHT;
    }

    // Continuously move other actors (panther, snake, monkey, crocodile)
    // Move the panther
    mPantherPos.x += mPantherVel.x * deltaTime;
    mPantherPos.y += mPantherVel.y * deltaTime;

    // Move the snake
    mSnakePos.x += mSnakeVel.x * deltaTime;
    mSnakePos.y += mSnakeVel.y * deltaTime;

    // Move the monkey
    mMonkeyPos.x += mMonkeyVel.x * deltaTime;
    mMonkeyPos.y += mMonkeyVel.y * deltaTime;

    // Move the crocodile
    mCrocPos.x += mCrocVel.x * deltaTime;
    mCrocPos.y += mCrocVel.y * deltaTime;

  // Check for collisions between the rabbit and other actors
    if (CheckCollisions()) {
        // Collision detected, set game over
        mIsRunning = false;
    }

    // Check for game over conditions (e.g., rabbit reaches the end goal)
    if (RabbitReachesGoal()) {
        // Game over, rabbit reached the goal
        mIsRunning = false;
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
SDL_Rect rabbitRect = { static_cast<int>(mRabbitPos.x), static_cast<int>(mRabbitPos.y), rabbitWidth, rabbitHeight };
SDL_RenderCopy(mRenderer, mRabbitTexture, nullptr, &rabbitRect);

// Monkey
SDL_Rect monkeyRect = { static_cast<int>(mMonkeyPos.x), static_cast<int>(mMonkeyPos.y), monkeyWidth, monkeyHeight };
SDL_RenderCopy(mRenderer, mMonkeyTexture, nullptr, &monkeyRect);

// Panther
SDL_Rect pantherRect = { static_cast<int>(mPantherPos.x), static_cast<int>(mPantherPos.y), pantherWidth, pantherHeight };
SDL_RenderCopy(mRenderer, mPantherTexture, nullptr, &pantherRect);

// Snake
SDL_Rect snakeRect = { static_cast<int>(mSnakePos.x), static_cast<int>(mSnakePos.y), snakeWidth, snakeHeight };
SDL_RenderCopy(mRenderer, mSnakeTexture, nullptr, &snakeRect);

// Crocodile
SDL_Rect crocodileRect = { static_cast<int>(mCrocodilePos.x), static_cast<int>(mCrocodilePos.y), crocodileWidth, crocodileHeight };
SDL_RenderCopy(mRenderer, mCrocTexture, nullptr, &crocRect);

        // Render text if the game is over
    if (!mIsRunning)
    {
        RenderText("Game Over", 400, 300); // Adjust position as needed
    }
    
    // Render text if the rabbit reaches the goal
    if (RabbitReachesGoal())
    {
        RenderText("YAY", 400, 300); // Adjust position as needed
    }

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

// Check for collisions between the rabbit and other actors
bool JungleCrossing::CheckCollisions()
{
   // Check collision with panther
    if (CheckCollision(mRabbitPos, mRabbitSize, mPantherPos, mPantherSize) ||
        // Check collision with snake
        CheckCollision(mRabbitPos, mRabbitSize, mSnakePos, mSnakeSize) ||
        // Check collision with monkey
        CheckCollision(mRabbitPos, mRabbitSize, mMonkeyPos, mMonkeySize) ||
        // Check collision with crocodile
        CheckCollision(mRabbitPos, mRabbitSize, mCrocPos, mCrocSize))
    {
        // Collision detected with any actor, return true
        return true;
    }

    return false; // No collision detected
}

// Function to check collision between two rectangles
bool JungleCrossing::CheckCollision(const Vector2& pos1, const Vector2& size1, const Vector2& pos2, const Vector2& size2)
{
    // Calculate bounding box for first rectangle
    float left1 = pos1.x;
    float right1 = pos1.x + size1.x;
    float top1 = pos1.y;
    float bottom1 = pos1.y + size1.y;

    // Calculate bounding box for second rectangle
    float left2 = pos2.x;
    float right2 = pos2.x + size2.x;
    float top2 = pos2.y;
    float bottom2 = pos2.y + size2.y;

    // Check for intersection of bounding boxes
    if (right1 >= left2 && left1 <= right2 && bottom1 >= top2 && top1 <= bottom2) {
        return true; // Collision detected
    }

    return false; // No collision detected
}

// Function to load an image file and create an SDL texture from it
// Parameters:
// - filePath: The file path of the image to load
// Returns:
// - Pointer to the loaded SDL texture, or nullptr if loading fails
SDL_Texture* JungleCrossing::LoadTexture(const std::string& filePath)
{
    // Load the image surface from the specified file path
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    
    // Check if the surface was loaded successfully
    if (!surface)
    {
        // Log an error message if loading failed and return nullptr
        SDL_Log("Failed to load image %s: %s", filePath.c_str(), IMG_GetError());
        return nullptr;
    }

    // Create an SDL texture from the loaded surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    
    // Free the surface as it's no longer needed after creating the texture
    SDL_FreeSurface(surface);

    // Check if the texture creation was successful
    if (!texture)
    {
        // Log an error message if texture creation failed and return nullptr
        SDL_Log("Failed to create texture from image %s: %s", filePath.c_str(), SDL_GetError());
        return nullptr;
    }

    // Return the pointer to the created texture
    return texture;
}

void JungleCrossing::RenderText(const std::string& text, int x, int y)
{
    // Load font
    TTF_Font* font = TTF_OpenFont("comic.ttf", 24); // Adjust font and size as needed

    if (!font)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    // Render text surface
    SDL_Color color = { 255, 255, 255 }; // White color
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);

    if (!textSurface)
    {
        SDL_Log("Failed to render text surface: %s", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    // Create texture from surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);

    if (!textTexture)
    {
        SDL_Log("Failed to create text texture: %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Get text dimensions
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Render text texture
    SDL_Rect dstRect = { x, y, textWidth, textHeight };
    SDL_RenderCopy(mRenderer, textTexture, nullptr, &dstRect);

    // Clean up
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}
