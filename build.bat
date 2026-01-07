@echo off
setlocal

:: =========================================================
:: 1. CONFIGURATION DES CHEMINS (A MODIFIER IMPERATIVEMENT)
:: =========================================================

:: Indique ici le dossier où tu as installé SDL3
set SDL3_DIR=C:\chemin\vers\SDL3

:: Indique ici le dossier où tu as installé SDL3_Image (souvent le même que SDL3)
set SDL3_IMAGE_DIR=C:\chemin\vers\SDL3_image

:: =========================================================
:: 2. COMMANDE DE COMPILATION
:: =========================================================

echo Compilation en cours...

:: Explication des flags :
:: -std=c++17      : Utilise une version moderne du C++
:: -I include      : Cherche les .h dans ton dossier local "include"
:: -I ...          : Cherche les .h de la SDL
:: src/*.cpp       : Compile tous les fichiers .cpp du dossier src
:: -o Dame.exe     : Nom de l'exécutable final
:: -L ...          : Cherche les fichiers .lib/.a de la SDL
:: -lSDL3          : Lie la librairie SDL3
:: -lSDL3_image    : Lie la librairie SDL3_image

g++ -std=c++17 ^
    -I include ^
    -I "%SDL3_DIR%\include" ^
    -I "%SDL3_IMAGE_DIR%\include" ^
    src\*.cpp ^
    -o Dame.exe ^
    -L "%SDL3_DIR%\lib" ^
    -L "%SDL3_IMAGE_DIR%\lib" ^
    -lSDL3 -lSDL3_image

:: =========================================================
:: 3. VERIFICATION DES ERREURS
:: =========================================================

if %errorlevel% neq 0 (
    echo.
    echo [ERREUR] La compilation a echoue !
    echo Verifie les chemins dans le fichier build.bat et ton code.
    pause
    exit /b %errorlevel%
)

echo.
echo [SUCCES] Compilation terminee. L'executable Dame.exe a ete cree.
echo.
pause