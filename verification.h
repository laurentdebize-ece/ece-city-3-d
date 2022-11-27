#ifndef BAC_A_SABLE_2_VERIFICATION_H
#define BAC_A_SABLE_2_VERIFICATION_H
#include "Jeu.h"

bool verif_achat_route(Jeu* jeu);
bool verification_batiment_peut_se_placer(Jeu* jeu, int nomDuBatiment, Vector2 pos_ini_batiment);
void ajout_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute);
void poser_batiment(Jeu* jeu);

void maj_batiment_timer(Jeu* jeu);


int verif_nb_cases_adjacentes(Jeu* jeu, Vector2 coordonnee_batiment, Vector2 taille);

// si num case == case_adjacente d'une maison et d'un chateau d'eau,
// retourne la valeur de la position de la case de jeu->matrice_connexite_route = case_connexe a maison et chateau d'eau
// sinon retourne 0
// on peut se servir du numero de la case dans  jeu->matrice_connexite_route pour dire que toutes les cases ayant ce numero sont connexe entre elle
int verif_liaison_maison_chateau(Jeu* jeu, Vector2 position);
int verif_liaison_maison_usine_elec(Jeu* jeu, Vector2 position);


#endif //BAC_A_SABLE_2_VERIFICATION_H
