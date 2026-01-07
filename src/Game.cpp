#include "../include/Game.h"
#include <cmath> // Pour abs()
#include <iostream>

Game::Game() {
    init();
}

Game::~Game() {}

void Game::init() {
    tourActuel = PIONBLANC;
    rafleEnCours = false;
    selectionState = 0;
    priseObligatoireExiste = false;
    possibleMoves.clear();

    // Initialisation du plateau
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            // Damier
            if ((i + j) % 2 == 0) map[i][j] = CASEM;
            else map[i][j] = CASEJ;

            // Pions
            plateau[i][j] = CASEV;
            if (map[i][j] == CASEM) {
                if (i < 4) plateau[i][j] = PIONNOIR;
                else if (i > 5) plateau[i][j] = PIONBLANC;
            }
        }
    }
}

ElementPlayer Game::getPieceAt(int y, int x) const { return plateau[y][x]; }
ElementMap Game::getMapTypeAt(int y, int x) const { return map[y][x]; }

// --- COEUR DE LA LOGIQUE : Calcul des points rouges ---
void Game::computeValidMoves(int x, int y) {
    possibleMoves.clear();
    ElementPlayer p = plateau[y][x];

    // 1. Vérification des PRISES (Saut de 2 cases)
    // La prise est autorisée dans toutes les directions (arrière inclus) pour les dames internationales,
    // ou souvent restreinte vers l'avant pour les pions simples selon les variantes.
    // Ici, j'autorise la prise dans les 4 directions car c'est souvent la règle standard.
    for (int dy = -2; dy <= 2; dy += 4) { // -2 et +2
        for (int dx = -2; dx <= 2; dx += 4) { // -2 et +2
            int tx = x + dx;
            int ty = y + dy;
            int mx = x + dx / 2; // Case intermédiaire
            int my = y + dy / 2;

            if (tx >= 0 && tx < 10 && ty >= 0 && ty < 10) {
                // Si on saute un ennemi et qu'on atterrit sur du vide
                if (plateau[my][mx] != CASEV && plateau[my][mx] != tourActuel && plateau[ty][tx] == CASEV) {
                    Vector2 move = {tx, ty};
                    possibleMoves.push_back(move);
                }
            }
        }
    }

    // 2. Vérification du DÉPLACEMENT SIMPLE
    // SEULEMENT si aucune prise n'est obligatoire ailleurs
    if (!priseObligatoireExiste && possibleMoves.empty()) {
        // LOGIQUE DE NON RETOUR :
        // Blanc (en bas, index grand) -> Monte (index diminue, -1)
        // Noir (en haut, index petit) -> Descend (index augmente, +1)
        int direction = (p == PIONBLANC) ? -1 : 1;

        for (int dx = -1; dx <= 1; dx += 2) { // Gauche (-1) et Droite (+1)
            int tx = x + dx;
            int ty = y + direction; // On force la direction unique

            if (tx >= 0 && tx < 10 && ty >= 0 && ty < 10) {
                if (plateau[ty][tx] == CASEV) {
                    Vector2 move = {tx, ty};
                    possibleMoves.push_back(move);
                }
            }
        }
    }
}

void Game::checkTurnLogic() {
    // On scanne tout le plateau pour voir si une prise est disponible
    priseObligatoireExiste = false;

    if (!rafleEnCours) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (plateau[i][j] == tourActuel) {
                    // Test des 4 diagonales pour une prise
                    for (int dy = -2; dy <= 2; dy += 4) {
                        for (int dx = -2; dx <= 2; dx += 4) {
                            int tx = j + dx, ty = i + dy;
                            int mx = j + dx / 2, my = i + dy / 2;
                            if (tx >= 0 && tx < 10 && ty >= 0 && ty < 10) {
                                if (plateau[my][mx] != CASEV && plateau[my][mx] != tourActuel && plateau[ty][tx] == CASEV) {
                                    priseObligatoireExiste = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        // En pleine rafle, on est obligé de continuer à manger
        priseObligatoireExiste = true;
    }
}

void Game::handleInput(int mouseX, int mouseY) {
    // Si clic hors map, on ignore
    if (mouseX < 0 || mouseX >= 10 || mouseY < 0 || mouseY >= 10) return;

    if (selectionState == 0) {
        // --- ETAPE 1 : SELECTION ---
        if (plateau[mouseY][mouseX] == tourActuel) {
            
            // Calcul des coups possibles pour ce pion
            computeValidMoves(mouseX, mouseY);

            // Vérification : A-t-on le droit de sélectionner ce pion ?
            // Si une prise globale existe, ce pion DOIT avoir une prise dans ses coups possibles.
            bool cePionPeutManger = false;
            for (const auto& m : possibleMoves) {
                if (abs(m.x - mouseX) == 2) cePionPeutManger = true;
            }

            if (!priseObligatoireExiste || cePionPeutManger) {
                // Si le pion a des mouvements valides, on le sélectionne
                if (!possibleMoves.empty()) {
                    selectedPos.x = mouseX;
                    selectedPos.y = mouseY;
                    selectionState = 1;
                }
            }
        }
    } 
    else if (selectionState == 1) {
        // --- ETAPE 2 : DEPLACEMENT ---
        
        // On vérifie si la case cliquée est un des "points rouges"
        bool mouvementValide = false;
        for (const auto& m : possibleMoves) {
            if (m.x == mouseX && m.y == mouseY) {
                mouvementValide = true;
                break;
            }
        }

        if (mouvementValide) {
            int oldX = selectedPos.x;
            int oldY = selectedPos.y;
            
            // On déplace le pion
            plateau[mouseY][mouseX] = plateau[oldY][oldX];
            plateau[oldY][oldX] = CASEV;
            
            bool aMange = false;

            // Est-ce une prise (distance de 2) ?
            if (abs(mouseX - oldX) == 2) {
                int midX = (oldX + mouseX) / 2;
                int midY = (oldY + mouseY) / 2;
                plateau[midY][midX] = CASEV; // Supprime le pion mangé
                aMange = true;
                
                // Mise à jour position actuelle pour la suite de la rafle
                selectedPos.x = mouseX;
                selectedPos.y = mouseY;
            }

            // Gestion de la suite du tour
            bool peutEncoreManger = false;
            if (aMange) {
                computeValidMoves(mouseX, mouseY);
                // Y a-t-il encore des prises (saut de 2) possibles depuis la nouvelle case ?
                for (const auto& m : possibleMoves) {
                    if (abs(m.x - mouseX) == 2) peutEncoreManger = true;
                }
            }

            if (peutEncoreManger) {
                rafleEnCours = true;
                selectionState = 1; // Reste sélectionné pour enchaîner
                // possibleMoves est déjà mis à jour par le computeValidMoves ci-dessus
            } else {
                // Fin du tour
                tourActuel = (tourActuel == PIONBLANC) ? PIONNOIR : PIONBLANC;
                rafleEnCours = false;
                selectionState = 0;
                possibleMoves.clear();
            }

        } else {
            // Clic invalide (ex: case occupée ou trop loin)
            // Si on n'est pas en rafle, on annule la sélection
            if (!rafleEnCours) {
                selectionState = 0;
                possibleMoves.clear();
            }
        }
    }
}