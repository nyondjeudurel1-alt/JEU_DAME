#include <iostream>
#include <SDL3/SDL.h>
#include "../include/Game.h"
#include "../include/Renderer.h"
#include "../include/Utils.h"

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Erreur SDL Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Jeu de Dames", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        std::cout << "Erreur Window: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Instanciation
    Game game;
    Renderer renderer;

    // Initialisation graphique
    if (!renderer.init(window)) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    bool run = true;
    SDL_Event event;

    // Boucle principale
    while (run) {
        // 1. Logique (Calcul des prises obligatoires)
        game.checkTurnLogic();

        // 2. Events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                run = false;
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                int mx = (int)event.button.x / TILE_SIZE;
                int my = (int)event.button.y / TILE_SIZE;
                game.handleInput(mx, my);
            }
        }

        // 3. Rendu
        renderer.render(game);
    }

    renderer.clean();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}