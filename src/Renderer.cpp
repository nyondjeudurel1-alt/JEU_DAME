#include "../include/Renderer.h"
#include <iostream>

Renderer::Renderer() : renderer(nullptr), caseM_texture(nullptr), caseJ_texture(nullptr), pionNoir_texture(nullptr), pionBlanc_texture(nullptr) {}

Renderer::~Renderer() { clean(); }

bool Renderer::init(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) return false;

    // ATTENTION : Assure-toi que le dossier "assets" est au bon endroit !
    caseM_texture = IMG_LoadTexture(renderer, "assets/caseM.jpg");
    caseJ_texture = IMG_LoadTexture(renderer, "assets/caseJ.jpg");
    pionNoir_texture = IMG_LoadTexture(renderer, "assets/pionNoir.png");
    pionBlanc_texture = IMG_LoadTexture(renderer, "assets/pionBlanc.png");

    if (!caseM_texture || !caseJ_texture || !pionNoir_texture || !pionBlanc_texture) {
        std::cout << "Erreur chargement textures: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Renderer::render(const Game& game) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 1. DESSINER LE PLATEAU ET LES PIONS
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            SDL_FRect r = { (float)j * TILE_SIZE, (float)i * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };

            // Sol
            if (game.getMapTypeAt(i, j) == CASEM) SDL_RenderTexture(renderer, caseM_texture, NULL, &r);
            else SDL_RenderTexture(renderer, caseJ_texture, NULL, &r);

            // Pions
            ElementPlayer p = game.getPieceAt(i, j);
            if (p == PIONNOIR) SDL_RenderTexture(renderer, pionNoir_texture, NULL, &r);
            else if (p == PIONBLANC) SDL_RenderTexture(renderer, pionBlanc_texture, NULL, &r);
        }
    }

    // 2. DESSINER L'INTERFACE (SÉLECTION ET POINTS ROUGES)
    if (game.isPieceSelected()) {
        // A. Cadre Vert autour du pion
        Vector2 sel = game.getSelectedPos();
        SDL_FRect selRect = { (float)sel.x * TILE_SIZE, (float)sel.y * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderRect(renderer, &selRect);

        // B. Points Rouges
        const std::vector<Vector2>& moves = game.getPossibleMoves();
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge

        for (const auto& m : moves) {
            // Petit carré rouge centré
            float size = 20.0f;
            SDL_FRect dot = { 
                (float)m.x * TILE_SIZE + (TILE_SIZE - size) / 2, 
                (float)m.y * TILE_SIZE + (TILE_SIZE - size) / 2, 
                size, size 
            };
            SDL_RenderFillRect(renderer, &dot);
        }
    }

    SDL_RenderPresent(renderer);
}

void Renderer::clean() {
    if (caseM_texture) SDL_DestroyTexture(caseM_texture);
    if (caseJ_texture) SDL_DestroyTexture(caseJ_texture);
    if (pionNoir_texture) SDL_DestroyTexture(pionNoir_texture);
    if (pionBlanc_texture) SDL_DestroyTexture(pionBlanc_texture);
    if (renderer) SDL_DestroyRenderer(renderer);
}