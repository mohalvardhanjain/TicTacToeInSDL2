#include "textureManager.hpp"
#include<iostream>
using namespace std;

SDL_Texture* textureManager::LoadTexture(const char* texture, SDL_Renderer* ren){

    SDL_Surface* tempSurface = IMG_Load(texture);
    if (!tempSurface) {
        cout << "Failed to load image. Error: " << IMG_GetError() << endl;
        return nullptr;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}