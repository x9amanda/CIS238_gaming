#include "JungleCrossing.h"
#include <SDL_image.h>

class JungleCrossing : public Game
{
public:
    JungleCrossing();
    bool Initialize() override;
    void RunLoop() override;
    void Shutdown() override;

private:
    SDL_Texture *LoadTexture(const std::string &fileName);
    void ProcessInput() override;
    void UpdateGame() override;
    void GenerateOutput() override;

    SDL_Texture *mRabbitTexture;
    SDL_Texture *mPantherTexture;
    SDL_Texture *mSnakeTexture;
    SDL_Texture *mMonkeyTexture;
    SDL_Texture *mCrocodileTexture;

    // Define positions and other necessary variables for the actors
};

JungleCrossing::JungleCrossing()
    : Game(), mRabbitTexture(nullptr), mPantherTexture(nullptr),
      mSnakeTexture(nullptr), mMonkeyTexture(nullptr), mCrocodileTexture(nullptr)
{
}

bool JungleCrossing::Initialize()
{
    if (!Game::Initialize())
        return false;

    // Load textures
    mRabbitTexture = LoadTexture("rabbit.png");
    mPantherTexture = LoadTexture("panther.png");
    mSnakeTexture = LoadTexture("snake.png");
    mMonkeyTexture = LoadTexture("monkey.png");
    mCrocodileTexture = LoadTexture("crocodile.png");

    if (!mRabbitTexture || !mPantherTexture || !mSnakeTexture || !mMonkeyTexture || !mCrocodileTexture)
    {
        SDL_Log("Failed to load textures.");
        return false;
    }

    // Initialize other necessary variables for the actors

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
    Game::ProcessInput();
    // Add input processing specific to your game
}

void JungleCrossing::UpdateGame()
{
    // Update game logic
    // Move actors, check collisions, etc.
}

void JungleCrossing::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 25, 100, 30, 255);
    SDL_RenderClear(mRenderer);

    // Render actors
    // Example:
    SDL_Rect rabbitRect = {x, y, width, height}; // Set rabbit position and size
    SDL_RenderCopy(mRenderer, mRabbitTexture, nullptr, &rabbitRect);

    // Render other actors in a similar way

    SDL_RenderPresent(mRenderer);
}

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
    if (mCrocodileTexture)
        SDL_DestroyTexture(mCrocodileTexture);

    Game::Shutdown();
}

SDL_Texture *JungleCrossing::LoadTexture(const std::string &fileName)
{
    SDL_Surface *surface = IMG_Load(fileName.c_str());
    if (!surface)
    {
        SDL_Log("Failed to load texture: %s", fileName.c_str());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        SDL_Log("Failed to create texture from surface: %s", fileName.c_str());
        return nullptr;
    }

    return texture;
}

int main(int argc, char **argv)
{
    JungleCrossing game;
    if (game.Initialize())
    {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
