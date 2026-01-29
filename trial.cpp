#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

// --- Constants ---
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int BOARD_SIZE = 3;
const int CELL_SIZE = SCREEN_WIDTH / BOARD_SIZE;

// --- Game State Enum ---
enum class GameState { PLAYING, WINNER_X, WINNER_O, DRAW, QUIT };

// --- Function Prototypes ---
bool init(SDL_Window** window, SDL_Renderer** renderer);
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
void close(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* bg, SDL_Texture* x, SDL_Texture* o);
void renderBoard(SDL_Renderer* renderer, SDL_Texture* bgTexture, const std::vector<std::vector<int>>& board, SDL_Texture* xTexture, SDL_Texture* oTexture);
void handleMouseClick(const SDL_MouseButtonEvent& b, std::vector<std::vector<int>>& board, int& currentPlayer, GameState& gameState);
GameState checkWinCondition(const std::vector<std::vector<int>>& board);


int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;


    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    std::cout << "Compiled against SDL version: "
              << (int)compiled.major << "."
              << (int)compiled.minor << "."
              << (int)compiled.patch << "\n";

    // Version actually linked/loaded at runtime
    SDL_GetVersion(&linked);
    std::cout << "Linked against SDL version: "
              << (int)linked.major << "."
              << (int)linked.minor << "."
              << (int)linked.patch << "\n";



    // --- Initialization ---
    if (!init(&window, &renderer)) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    // --- Load Textures ---
    SDL_Texture* bgTexture = loadTexture("Board.png", renderer);
    SDL_Texture* xTexture = loadTexture("X.png", renderer);
    SDL_Texture* oTexture = loadTexture("O.png", renderer);

    if (bgTexture == nullptr || xTexture == nullptr || oTexture == nullptr) {
        close(window, renderer, bgTexture, xTexture, oTexture);
        return -1;
    }

    // --- Game Variables ---
    std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0)); // 0: empty, 1: X, 2: O
    int currentPlayer = 1; // Player 1 starts (X)
    GameState gameState = GameState::PLAYING;

    // --- Main Game Loop ---
    SDL_Event e;
    while (gameState != GameState::QUIT) {
        // --- Event Handling ---
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                gameState = GameState::QUIT;
            } else if (e.type == SDL_MOUSEBUTTONDOWN && gameState == GameState::PLAYING) {
                handleMouseClick(e.button, board, currentPlayer, gameState);
                gameState = checkWinCondition(board);
            }
        }

        // --- Rendering ---
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        renderBoard(renderer, bgTexture, board, xTexture, oTexture);

        // --- Display Winner Message (simple console output) ---
        if (gameState != GameState::PLAYING && gameState != GameState::QUIT) {
             if (gameState == GameState::WINNER_X) {
                std::cout << "Player X Wins!" << std::endl;
            } else if (gameState == GameState::WINNER_O) {
                std::cout << "Player O Wins!" << std::endl;
            } else if (gameState == GameState::DRAW) {
                std::cout << "It's a Draw!" << std::endl;
            }
            // A simple delay to see the final board before quitting
            SDL_Delay(2000);
            gameState = GameState::QUIT;
        }


        SDL_RenderPresent(renderer);
    }

    // --- Cleanup ---
    close(window, renderer, bgTexture, xTexture, oTexture);

    return 0;
}

// --- Function Definitions ---

/**
 * @brief Initializes SDL, SDL_image, window, and renderer.
 */
bool init(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Loads a texture from a file path.
 */
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

/**
 * @brief Renders the game board and pieces.
 */
void renderBoard(SDL_Renderer* renderer, SDL_Texture* bgTexture, const std::vector<std::vector<int>>& board, SDL_Texture* xTexture, SDL_Texture* oTexture) {
    // Render background
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

    // Render X's and O's
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] != 0) {
                SDL_Rect destRect = { j * CELL_SIZE + 20, i * CELL_SIZE + 20, CELL_SIZE - 40, CELL_SIZE - 40 };
                if (board[i][j] == 1) {
                    SDL_RenderCopy(renderer, xTexture, NULL, &destRect);
                } else if (board[i][j] == 2) {
                    SDL_RenderCopy(renderer, oTexture, NULL, &destRect);
                }
            }
        }
    }
}

/**
 * @brief Handles mouse clicks to place pieces.
 */
void handleMouseClick(const SDL_MouseButtonEvent& b, std::vector<std::vector<int>>& board, int& currentPlayer, GameState& gameState) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    int clickedRow = y / CELL_SIZE;
    int clickedCol = x / CELL_SIZE;

    if (board[clickedRow][clickedCol] == 0) {
        board[clickedRow][clickedCol] = currentPlayer;
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}

/**
 * @brief Checks for a win or draw condition.
 */
GameState checkWinCondition(const std::vector<std::vector<int>>& board) {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0] == 1 ? GameState::WINNER_X : GameState::WINNER_O;
        }
        if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i] == 1 ? GameState::WINNER_X : GameState::WINNER_O;
        }
    }

    // Check diagonals
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0] == 1 ? GameState::WINNER_X : GameState::WINNER_O;
    }
    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2] == 1 ? GameState::WINNER_X : GameState::WINNER_O;
    }

    // Check for draw
    bool isDraw = true;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 0) {
                isDraw = false;
                break;
            }
        }
        if (!isDraw) break;
    }

    if (isDraw) {
        return GameState::DRAW;
    }

    return GameState::PLAYING;
}

/**
 * @brief Frees resources and quits SDL.
 */
void close(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* bg, SDL_Texture* x, SDL_Texture* o) {
    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(x);
    SDL_DestroyTexture(o);
    bg = nullptr;
    x = nullptr;
    o = nullptr;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}