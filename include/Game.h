#pragma once
#include <vector>
#include "Utils.h"

class Game {
public:
    Game();
    ~Game();

    void init();
    
    // Gère le clic de la souris
    void handleInput(int mouseX, int mouseY);
    
    // Vérifie si une prise est obligatoire au début du tour
    void checkTurnLogic();

    // Getters pour l'affichage
    ElementPlayer getPieceAt(int y, int x) const;
    ElementMap getMapTypeAt(int y, int x) const;
    bool isPieceSelected() const { return selectionState == 1; }
    Vector2 getSelectedPos() const { return selectedPos; }
    
    // Renvoie la liste des cases valides (pour les points rouges)
    const std::vector<Vector2>& getPossibleMoves() const { return possibleMoves; }

private:
    // Calcule où le pion sélectionné peut aller
    void computeValidMoves(int x, int y);

    ElementMap map[10][10];
    ElementPlayer plateau[10][10];

    ElementPlayer tourActuel;
    bool rafleEnCours;          // Si on est au milieu d'une série de prises
    bool priseObligatoireExiste; // Si une prise existe quelque part sur le plateau
    
    int selectionState; // 0 = Rien sélectionné, 1 = Pion sélectionné
    Vector2 selectedPos;

    std::vector<Vector2> possibleMoves; // Liste des coordonnées pour les points rouges
};