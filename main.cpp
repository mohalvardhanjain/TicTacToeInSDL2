#include "game.hpp"
#include "textureManager.hpp"
#include <SDL2/SDL_mixer.h>

Game* game = nullptr;
SDL_Texture* spriteSheet = nullptr;
int currentFrame = 0;
Uint32 lastUpdateTime = 0;
const int frameInterval = 500;

int main(int argc, const char* argv[]){
SDL_Window* menuWindow = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
SDL_Renderer* menuRenderer = SDL_CreateRenderer(menuWindow, -1, SDL_RENDERER_ACCELERATED);
bool menuRunning = true;
SDL_Event event;
if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
}
Mix_Music* bgmu = Mix_LoadMUS("Zelda_s_Lofi_Kingdom(128k).mp3");
Mix_Music* bgmv = Mix_LoadMUS("game-start-317318.mp3");

if (bgmu == nullptr) {
    printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
}
Mix_PlayMusic(bgmu, 0);
SDL_Texture* spriteSheet = nullptr;

spriteSheet = IMG_LoadTexture(menuRenderer, "mainmenu.png"); // one image with two frames



int currentFrame = 0;  // 0 or 1

while (menuRunning) {
    // Handle input events (only input stuff here)
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_Quit();
            return 0;
        }

        if (event.type == SDL_KEYDOWN) {
Mix_HaltMusic();
Mix_PlayMusic(bgmv, 1); // Play once

// Wait for music to finish
while (Mix_PlayingMusic()) {
    SDL_Delay(100);
}
            menuRunning = false;
        }
    }

    //Always update frame timing
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > lastUpdateTime + frameInterval) {
        currentFrame = (currentFrame + 1) % 2; // toggle 0 / 1
        lastUpdateTime = currentTime;
    }

    //Render the appropriate frame
    SDL_Rect srcRect = { currentFrame * 1024, 0, 1024, 1024 };
    SDL_Rect destRect = { 0, 0, 1024, 1024 };

    SDL_RenderClear(menuRenderer);
    SDL_RenderCopy(menuRenderer, spriteSheet, &srcRect, &destRect);
    SDL_RenderPresent(menuRenderer);

    // Optional: cap the frame rate (e.g., to 60 FPS)
    SDL_Delay(16);
}

Mix_FreeMusic(bgmv);
Mix_FreeMusic(bgmu);
Mix_CloseAudio();
SDL_DestroyTexture(spriteSheet);
SDL_DestroyRenderer(menuRenderer);
SDL_DestroyWindow(menuWindow);



    game = new Game();
    game->init("!!! TIC TAC TOE !!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, false);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
}
Mix_Music* bgm = Mix_LoadMUS("Fairy_Fountain(128k).mp3");
if (bgm == nullptr) {
    printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
}
Mix_PlayMusic(bgm, -1);

 const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();   // Run every frame
        game->update();         // Run every frame
        game->render();         // Run every frame

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime); // Only delay as much as needed
        }
    }
Mix_FreeMusic(bgm);
Mix_CloseAudio();

    game->clean();
    return 0;
}