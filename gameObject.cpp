#include "gameObject.hpp"
#include "textureManager.hpp"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, int ow, int oh, int nw, int nh){
    renderer = ren;
    objTexture = textureManager::LoadTexture(texturesheet, ren);

    xpos = x;
    ypos = y;
    width = ow;
    height = oh;
    
    srcRect = {0, 0, ow, oh};
    destRect = {x, y, nw, nh};

}

int GameObject::getX() const{
    return xpos;

}
int GameObject::getY() const{
    return ypos;
}

void GameObject::update(){

}
void GameObject::updatePosition(int newX, int newY) {
    destRect.x = newX;
    destRect.y = newY;
}

void GameObject::render() {
    SDL_Rect renderQuad = { destRect.x, destRect.y, destRect.w, destRect.h };  // <-- declare here
    SDL_RenderCopy(renderer, objTexture, &srcRect, &renderQuad);
}
