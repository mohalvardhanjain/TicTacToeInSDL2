#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class textureManager {
public:
    static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* ren);


};

#endif