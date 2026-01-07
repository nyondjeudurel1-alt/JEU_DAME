#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Game.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(SDL_Window* window);
    void render(const Game& game);
    void clean();

private:
    SDL_Renderer* renderer;
    
    // Textures
    SDL_Texture* caseM_texture;
    SDL_Texture* caseJ_texture;
    SDL_Texture* pionNoir_texture;
    SDL_Texture* pionBlanc_texture;
};