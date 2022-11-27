cmake_minimum_required(VERSION 3.23)
project(ece-city-3-d C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(raylib)

add_executable(ece-city-3-d main.c Jeu.c Jeu.h affichage/affichage.c affichage/affichage.h Graphe.c Graphe.h Macros.h initialisation.c initialisation.h matrice_adjacence.c matrice_adjacence.h BFS.c BFS.h verification.c verification.h affichage/Sacha_affichage.c affichage/Sacha_affichage.h affichage/affichage_console.c affichage/affichage_console.h)

target_link_libraries(ece-city-3-d raylib)