#ifndef BAC_A_SABLE_2_BFS_H
#define BAC_A_SABLE_2_BFS_H
//
#include "Macros.h"
#include "Graphe.h"
#include "verification.h"

void BFS_connexite(Jeu* jeu, Vector2 tuile, int num_connexite_teste);
void BFS_PCC(Jeu* jeu, Vector2 tuile, int num_connexite_teste, int terrain[ORDRE_EN_Y][ORDRE_EN_X], int num_chateau_eau);
int** init_conexite_route(Jeu* jeu);
void connexite_route_ajout_batiment(Jeu* jeu, Batiment* nouveau);
void connexite_route_ajout_route(Jeu* jeu, Vector2 route);
void connexite_route_destruction_batiment(Jeu* jeu, Vector2 coordonnee_batiment);
void connexite_route_destruction_route(Jeu* jeu,Vector2 route);
#endif //BAC_A_SABLE_2_BFS_H
