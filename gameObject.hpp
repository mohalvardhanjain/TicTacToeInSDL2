#pragma once
#include "game.hpp"


class GameObject{
public:
    GameObject(const char *textureSheet, SDL_Renderer* renderer, int x, int y, int original_width, int original_height, int new_width, int new_height);
    
    ~GameObject();

    void updatePosition(int newX, int newY);
    void update();
    void render();
    int getX() const;
    int getY() const;

private:
    int xpos;
    int ypos;

    int width, height;

    SDL_Texture *objTexture;
    SDL_Rect srcRect , destRect;
    SDL_Renderer* renderer;

};


// ██████╗  █████╗  ██████╗██╗ ██████╗ ██████╗
// ██╔══██╗██╔══██╗██╔════╝██║██╔════╝██╔════╝
// ██████╔╝███████║███████╗██║██║     ███████╗
// ██╔══██╗██╔══██║╚════██║██║██║     ╚════██║
// ██████╔╝██║  ██║██████╔╝██║╚██████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚═╝ ╚═════╝╚═════╝