#include "TextureLoader.h"
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& fileName) {
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (!surface) {
        std::cerr << "IMG_Load failed: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }

    return texture;
}
