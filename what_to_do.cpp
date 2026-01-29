#include<iostream>
#include<SDL2/SDL.h>

using namespace std;
int main(){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
    SDL_Window* window = SDL_CreateWindow("something", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2000, 2000, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    SDL_Event event;
    bool isRunning = true;
    while(isRunning){
        while(SDL_PollEvent (&event)){
            if(event.type == SDL_QUIT){
                isRunning = false;
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_a){
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    return 0;
                }
            }       }
    }
    return 0;
}