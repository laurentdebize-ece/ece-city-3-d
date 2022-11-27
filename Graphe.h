#ifndef TEMPLATE_RAYLIB_GRAPHE_H
#define TEMPLATE_RAYLIB_GRAPHE_H
#include "Jeu.h"
//
void initialisation_Grille();
void lire_graphe(Jeu* jeu);
void enregistrer_Grille(Jeu* jeu);
void ajout_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute);
void suppression_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute);


Vector2 position_maison(Jeu* jeu, int x, int y);
Vector2 position_usine(Jeu* jeu, int x, int y, int type_usine);

Vector2 position_batiment(Jeu* jeu, int x, int y);

#endif //TEMPLATE_RAYLIB_GRAPHE_H
