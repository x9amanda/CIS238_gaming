#include "JungleCrossing.h"
#include "TextureLoader.h"
#include "CollisionHandler.h"
#include <iostream>

JungleCrossing::JungleCrossing() :
        mWindow(nullptr), mRenderer(nullptr), mFont(nullptr), mScore(0), mTicksCount(0) {}

bool JungleCrossing::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    mWindow = SDL_CreateWindow("Jungle Crossing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!mWindow) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(mWindow);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    mFont = TTF_OpenFont("comic_sans.ttf", 24);
    if (!mFont) {
        std::cerr << "TTF_OpenFont failed: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

void JungleCrossing::RunLoop() {
    while (true) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void JungleCrossing::Shutdown() {
    TTF_CloseFont(mFont);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    TTF_Quit();
    SDL_Quit();
}

void JungleCrossing::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            Shutdown();
        break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_UP]) {
        mRabbit.vel.y = -1;
    } else if (state[SDL_SCANCODE_DOWN]) {
        mRabbit.vel.y = 1;
    } else {
        mRabbit.vel.y = 0;
    }

    if (state[SDL_SCANCODE_LEFT]) {
        mRabbit.vel.x = -1;
    } else if (state[SDL_SCANCODE_RIGHT]) {
        mRabbit.vel.x = 1;
    } else {
        mRabbit.vel.x = 0;
    }
}

void JungleCrossing::UpdateGame() {
     // Calculate delta time
    Uint32 ticks = SDL_GetTicks();
    float deltaTime = (ticks - mTicksCount) / 1000.0f;
    mTicksCount = ticks;

    // Update rabbit position
    mRabbit.pos.x += mRabbit.vel.x * 200.0f * deltaTime;
    mRabbit.pos.y += mRabbit.vel.y * 200.0f * deltaTime;

    // Update rabbit collider
    mRabbit.collider.x = static_cast<int>(mRabbit.pos.x);
    mRabbit.collider.y = static_cast<int>(mRabbit.pos.y);

    // Check for collisions between the rabbit and carrots
    for (auto it = mCarrotPositions.begin(); it != mCarrotPositions.end(); ++it) {
        if (CheckCollision(mRabbit.pos, *it, RABBIT_WIDTH, RABBIT_HEIGHT, CARROT_WIDTH, CARROT_HEIGHT)) {
            // Remove the collected carrot from the vector
            it = mCarrotPositions.erase(it);
            // Increment the player's score
            ++mScore;
        }
    }
}

void JungleCrossing::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

 // Render rabbit
    SDL_RenderCopy(mRenderer, mRabbit.texture, nullptr, &mRabbit.collider);

    // Render score text
    SDL_Color textColor = {255, 255, 255}; // White color
    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, ("Score: " + std::to_string(mScore)).c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    SDL_Rect textRect = {SCREEN_WIDTH - 200, 20, textSurface->w, textSurface->h}; // Adjust position as needed
    SDL_RenderCopy(mRenderer, textTexture, nullptr, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Present the renderer
    SDL_RenderPresent(mRenderer);
}

SDL_Texture* JungleCrossing::LoadTexture(const std::string& fileName) {
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (!surface) {
        std::cerr << "IMG_Load failed: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }

    return texture;
}

bool JungleCrossing::CheckCollision(const Vector2& posA, const Vector2& posB, int widthA, int heightA, int widthB, int heightB) {
    if (posA.x < posB.x + widthB &&
        posA.x + widthA > posB.x &&
        posA.y < posB.y + heightB &&
        posA.y + heightA > posB.y) {
        return true;
    }
    return false;
}