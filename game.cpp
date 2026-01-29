#include "game.hpp"
#include "gameObject.hpp"
using namespace std;

GameObject* background;
GameObject* X;
GameObject* O;

Game::Game(){}
Game::~Game(){}

void Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    cout << "IMG_Init Error: " << IMG_GetError() << endl;
}


    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0){
        std::cout<< "Subsystem Initialised!..."<<std::endl;

        window = SDL_CreateWindow("!!! TIC TAC TOE !!!", xpos, ypos, width, height, flags);
        if(window){
            std::cout<< "Window Created!"<<std::endl; 

        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout<<"Renderer created!"<<std::endl;
            isRunning = true;
        }
        
        else{
            isRunning = false;  
        }
    }

    background = new GameObject("Board.png", renderer, 0, 0, 1000, 1000, 1280, 1280);
    X = new GameObject("X.png", renderer, 0, 0, 196, 196, 196, 196);
    O = new GameObject("O.png", renderer, 0, 0, 196, 196,196, 196);
}

void Game::handleEvents(){

    SDL_Event event;
    SDL_PollEvent(&event);
;

    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            cout << "Mouse Clicked at " << event.button.x << ", " << event.button.y << endl;
            break;   

        case SDL_MOUSEBUTTONUP:
            cout << "Mouse Button Up " <<endl;
            break;   

        default:
        break;
    }

}

void Game::update(){

}

void Game::render(){
    SDL_RenderClear(renderer);
    

    background->render();
    X->render();
    O->render();
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    cout<< "Window Cleaned"<<endl;
}