#pragma once

// --- CONSTANTES ---
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int TILE_SIZE = 80;

// --- STRUCTURES ---
struct Vector2 {
    int x;
    int y;
};

// --- ENUMS ---
enum ElementMap {
    CASEM = 0, // Case Marron (jouable)
    CASEJ,     // Case Jaune/Beige (non jouable)
};

enum ElementPlayer {
    PIONNOIR = 0,
    PIONBLANC,
    CASEV,     // Case Vide
};