#include "TextureLoader.h"
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& fileName) {
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (!surface) {
        SDL_Log("IMG_Load FAILED. %s", SDL_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        SDL_Log("SDL_CreateTextureFromSurface FAILED. %s", SDL_GetError());
    }

    return texture;
}
