
🏁 README — Dames anglaises en C++ avec SDL3 & ImGui
🎯 Objectif du projet
Ce projet est une implémentation simple mais élégante du jeu de dames anglaises (checkers) en C++, avec une interface graphique moderne grâce à SDL3 et ImGui. Il est conçu pour être jouable à deux joueurs, avec une interface intuitive, des règles fidèles, et une architecture claire pour les débutants.

🧱 Structure du projet
MonProjet/
├── build.bat                  # Script de compilation Windows
├── include/                   # Fichiers d'en-tête (.h)
│   ├── Game.h                 # Logique du jeu
│   ├── Renderer.h             # Rendu SDL
│   ├── UI.h                   # Interface ImGui
│   └── Utils.h                # Fonctions utilitaires
├── src/                       # Fichiers source (.cpp)
│   ├── main.cpp               # Point d'entrée
│   ├── Game.cpp
│   ├── Renderer.cpp
│   ├── UI.cpp
│   └── Utils.cpp
├── assets/                    # Ressources graphiques et polices
│   ├── toutes les images.png             # images
│ 
└── README.md                  # Ce fichier



🖥️ Fonctionnalités
- ✅ Jeu de dames anglaises à deux joueurs
- ✅ Déplacement et capture avec règles officielles
- ✅ Promotion en dame
- ✅ Interface graphique avec SDL3
- ✅ Panneau de contrôle avec ImGui
- ✅ Indicateurs visuels (sélection, coups légaux)
- ✅ Redémarrage de partie, aide intégrée

🚀 Installation et compilation (Windows)
🔧 Prérequis
- SDL3 installé via vcpkg ou manuellement
- ImGui avec les backends SDL3 + SDLRenderer3
- Un compilateur C++ compatible (MSVC, MinGW, Clang)
📦 Installation avec vcpkg (recommandé)
vcpkg install sdl3


Assure-toi que le chemin vers vcpkg est bien configuré dans ton environnement.

🛠️ Compilation avec build.bat
Crée un fichier build.bat à la racine du projet :
@echo off
setlocal

REM Configuration
set SRC=src\main.cpp src\Game.cpp src\Renderer.cpp src\UI.cpp src\Utils.cpp
set INC=-Iinclude -Iimgui -Iimgui\backends
set LIBS=-Lpath\to\sdl3\lib -lSDL3
set IMGUI=imgui\imgui.cpp imgui\imgui_draw.cpp imgui\imgui_tables.cpp imgui\imgui_widgets.cpp imgui\imgui_demo.cpp imgui\backends\imgui_impl_sdl3.cpp imgui\backends\imgui_impl_sdlrenderer3.cpp

REM Compilation
echo Compiling project...
g++ -std=c++17 %SRC% %IMGUI% %INC% %LIBS% -o DamesAnglaises.exe

if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)

echo Compilation successful. Run DamesAnglaises.exe to play.
endlocal


🔁 Remplace path\to\sdl3\lib par le chemin réel vers tes bibliothèques SDL3.

🎮 Lancer le jeu
Une fois compilé, exécute simplement :
Dame.exe



📚 Pour les débutants
Chaque fichier du projet est conçu pour être simple à comprendre :
- Game.cpp : contient les règles du jeu, les mouvements, les captures.
- Renderer.cpp : dessine le plateau et les pièces.
- UI.cpp : affiche les boutons et infos avec ImGui.
- main.cpp : initialise SDL, lance la boucle du jeu.
Tu peux suivre les étapes dans le README pour apprendre à chaque niveau.

📌 À venir
- 🔄 IA simple pour jouer contre l’ordinateur
- 💾 Sauvegarde et chargement de partie
- 🌐 Version en ligne avec SDL_net

🧑‍💻 Auteur
Projet conçu par Daiki, passionné de jeux, d’architecture logicielle et d’interface élégante. Ce projet est un tremplin vers la maîtrise de C++, SDL et ImGui.

