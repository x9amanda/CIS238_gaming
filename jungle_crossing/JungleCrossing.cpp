#include "JungleCrossing.h"
#include "TextureLoader.h"
#include "CollisionHandler.h"
#include <iostream>
#include <vector>
#include <SDL_image.h>

// Screen and actor dimensions
#define SCREEN_WIDTH 1024  // Max x resolution value
#define SCREEN_HEIGHT 768  // Max y resolution value
#define RABBIT_WIDTH 140   // Width of the Rabbit image
#define RABBIT_HEIGHT 120  // Height of the Rabbit image
#define PANTHER_WIDTH 140  // Width of Panther image
#define PANTHER_HEIGHT 120 // Height of the Panther image
#define SNAKE_WIDTH 120    // Width of Snake image
#define SNAKE_HEIGHT 120   // Height of the Snake image
#define MONKEY_WIDTH 140   // Width of Monkey image
#define MONKEY_HEIGHT 120  // Height of the Monkey image
#define CROC_WIDTH 175     // Width of Crocodile image
#define CROC_HEIGHT 120    // Height of the Crocodile image
#define CARROT_WIDTH 51    // Width of Carrot image
#define CARROT_HEIGHT 51   // Height of the Carrot image

// Named constants for screen percentages
const float JUNGLE_PERCENTAGE = 0.75f; // 75% of the screen
const float MEADOW_PERCENTAGE = 0.25f; // 25% of the screen

// Named constants for jungle and meadow widths
const float JUNGLE_WIDTH = SCREEN_WIDTH * JUNGLE_PERCENTAGE;
const float MEADOW_WIDTH = SCREEN_WIDTH * MEADOW_PERCENTAGE;

JungleCrossing::JungleCrossing() : mWindow(nullptr), mRenderer(nullptr), mFont(nullptr), mScore(0), mTicksCount(0), mIsRunning(true) {}

bool JungleCrossing::Initialize()
{
    // Initialize Video
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("SDL VIDEO INIT FAILED. %s", SDL_GetError());
        return false;
    }
    // Initialize text rendering
    if (TTF_Init() != 0)
    {
        SDL_Log("SDL TTF INIT FAILED. %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    // Create window and renderer
    mWindow = SDL_CreateWindow("Jungle Crossing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!mWindow)
    {
        SDL_Log("SDL CREATE WINDOW FAILED. %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("SDL CREATE RENDERER. %s", SDL_GetError());
        SDL_DestroyWindow(mWindow);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    // Load Font
    mFont = TTF_OpenFont("comic_sans.ttf", 24);
    if (!mFont)
    {
        SDL_Log("TTF_OpenFont FAILED. %s", SDL_GetError());
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    // Load textures
    mTextures["jungle"] = LoadTexture("jungle.jpg");
    mTextures["meadow"] = LoadTexture("meadow.png");
    mTextures["rabbit"] = LoadTexture("rabbit.png");
    mTextures["snake"] = LoadTexture("snake.png");
    mTextures["crocodile"] = LoadTexture("crocodile.png");
    mTextures["panther"] = LoadTexture("panther.png");
    mTextures["monkey"] = LoadTexture("monkey.png");
    mTextures["carrot"] = LoadTexture("carrot.png");

    // Seed random number generator
    std::srand(std::time(nullptr));

    // Initialize rabbit
    mRabbit.texture = mTextures["rabbit"];
    mRabbit.pos = {50.0f, SCREEN_HEIGHT / 2 - RABBIT_HEIGHT / 2}; // Initial position of the rabbit
    mRabbit.vel = {0.0f, 0.0f};                                   // Initial velocity of the rabbit

    // Initialize other actors
    int numActors = 4;                                   // Number of actors to evenly space across the jungle
    float actorSpacing = JUNGLE_WIDTH / (numActors + 1); // Evenly spaced positions
    for (int i = 0; i < numActors; ++i)
    {
        Actor actor;
        actor.pos = {JUNGLE_WIDTH + actorSpacing * (i + 1), static_cast<float>(std::rand() % SCREEN_HEIGHT)};
        actor.vel = {0.0f, 50.0f};                                                                                  // Random velocity for demonstration
        actor.texture = mTextures["snake"];                                                                         // Example actor texture
        actor.collider = {static_cast<int>(actor.pos.x), static_cast<int>(actor.pos.y), SNAKE_WIDTH, SNAKE_HEIGHT}; // Collider for collision detection
        mActors.push_back(actor);
    }

    // Initialize tick count
    mTicksCount = SDL_GetTicks();

    // Initialization successful
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
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            Shutdown();
            break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
    if (state[SDL_SCANCODE_UP])
    {
        mRabbit.vel.y = -1;
    }
    else if (state[SDL_SCANCODE_DOWN])
    {
        mRabbit.vel.y = 1;
    }
    else if (state[SDL_SCANCODE_LEFT])
    {
        mRabbit.vel.x = -1;
    }
    else if (state[SDL_SCANCODE_RIGHT])
    {
        mRabbit.vel.x = 1;
    }
    else
    {
        mRabbit.vel.y = 0;
        mRabbit.vel.x = 0; // Assuming you want to stop movement if no keys are pressed
    }
}

void JungleCrossing::UpdateGame()
{
    // Calculate delta time
    Uint32 ticks = SDL_GetTicks();
    float deltaTime = (ticks - mTicksCount) / 1000.0f;

    // Limit maximum delta time to avoid large jumps in movement
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    // Update tick count for the next loop (next frame)
    mTicksCount = ticks;

    // Update rabbit position
    mRabbit.pos.x += mRabbit.vel.x * 200.0f * deltaTime;
    mRabbit.pos.y += mRabbit.vel.y * 200.0f * deltaTime;

    // Update rabbit collider
    mRabbit.collider.x = static_cast<int>(mRabbit.pos.x);
    mRabbit.collider.y = static_cast<int>(mRabbit.pos.y);

    // Ensure the rabbit stays within the screen boundaries
    if (mRabbit.y < 0)
    {
        mRabbit.y = 0;
    }
    else if (mRabbit.y > 768 - RABBIT_HEIGHT)
    {
        mRabbit.y = 768 - RABBIT_HEIGHT;
    }

    // Update positions of other actors

    // Check for collisions between rabbit and other actors

    // Check for collisions between the rabbit and carrots
    for (auto it = mCarrotPositions.begin(); it != mCarrotPositions.end(); ++it)
    {
        if (CheckCollision(mRabbit.pos, *it, RABBIT_WIDTH, RABBIT_HEIGHT, CARROT_WIDTH, CARROT_HEIGHT))
        {
            // Remove the collected carrot from the vector
            it = mCarrotPositions.erase(it);
            // Increment the player's score
            ++mScore;
        }
    }
};

void JungleCrossing::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    // Render rabbit
    SDL_RenderCopy(mRenderer, mRabbit.texture, nullptr, &mRabbit.collider);

    // Render score text
    SDL_Color textColor = {255, 255, 255}; // White color
    SDL_Surface *textSurface = TTF_RenderText_Solid(mFont, ("Score: " + std::to_string(mScore)).c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    SDL_Rect textRect = {SCREEN_WIDTH - 200, 20, textSurface->w, textSurface->h}; // Adjust position as needed
    SDL_RenderCopy(mRenderer, textTexture, nullptr, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Present the renderer
    SDL_RenderPresent(mRenderer);
}

void JungleCrossing::Shutdown()
{
    TTF_CloseFont(mFont);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_DestroyTexture(mTextures["jungle"]);
    SDL_DestroyTexture(mTextures["meadow"]);
    SDL_DestroyTexture(mTextures["rabbit"]);
    SDL_DestroyTexture(mTextures["snake"]);
    SDL_DestroyTexture(mTextures["crocodile"]);
    SDL_DestroyTexture(mTextures["panther"]);
    SDL_DestroyTexture(mTextures["monkey"]);
    SDL_DestroyTexture(mTextures["carrot"]);

    TTF_Quit();
    SDL_Quit();
}

SDL_Texture *JungleCrossing::LoadTexture(const std::string &fileName)
{
    SDL_Surface *surface = IMG_Load(fileName.c_str());
    if (!surface)
    {
        SDL_Log("IMG_Load FAILED. %s", SDL_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        SDL_Log("SDL_CreateTextureFromSurface FAILED. %s", SDL_GetError());
    }

    return texture;
}

bool JungleCrossing::CheckCollision(const Vector2 &posA, const Vector2 &posB, int widthA, int heightA, int widthB, int heightB)
{
    // Check for overlap
    if (posA.x < posB.x + widthB &&
        posA.x + widthA > posB.x &&
        posA.y < posB.y + heightB &&
        posA.y + heightA > posB.y)
    {
        // Collision detected
        return true;
    }
    // Collision not detected
    return false;
}