#ifndef TEMPLATE_RAYLIB_JEU_H
#define TEMPLATE_RAYLIB_JEU_H
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

//TODO: LISTE CHAINE POUR BATIMENTS

enum {communisme, capitalisme};
enum {animation_Lancement, menu_principale, selection_choix_jeu,en_jeu, regles, credis, nb_pages};
enum {img_menu, img_boutonoff, img_boutonJouer, img_boutonSauvegarder, img_boutonRegles, img_boutonCredits, img_bouton_suppSave, img_bouton_Communisme, img_bouton_Capitalisme, img_fond_ChoixJeu, img_fondJeu1, img_fondJeu2, img_fondJeu3, img_fondJeu4, img_logosJeu, img_boutonRetourMenu, img_route, img_maison, img_usine, img_chateauDO, img_niveau_0, img_niveau_1, img_niveau_2, img_demolition, img_logo_argent, img_logo_eau, img_logo_elec, img_logo_habitant, img_logo_warning, img_fond_panneau_affichage, img_fond_credits, nb_img};
enum {mode_neutre, mode_reseau ,mode_maison, mode_usine, mode_chateauDO, mode_demolition, nb_modes};
enum {vide, reseau, maison, chateau_deau, usine_electrique, demolition, nb_type_batiments};
enum {son_Bouton, son_menu, nb_sons};


typedef struct {
    int distance;
    int numero_batiment;
    int numero_maison;
}Stockage_batiment;


typedef struct S_Image{
    bool charge;
    Texture2D texture2D;
    Rectangle source_Rec;
    Rectangle pos_Rec;
    int x;
    int y;
    float frame_hauteur;
    float frame_longueur;
    float alpha;
    bool colision_souris;
}S_Image;

typedef struct Matrice_batiment {
    Vector2 batiments[2];
    int distance;
    int connexite;
    int capacite_utilise;
}Matrice_batiment;

typedef struct Batiment{
    bool alimente_eau;
    bool alimente_elec;
    Vector2 taille;
    Vector2 co;
    Vector2 * cases_adjacentes;
    char* nom;
    int capacite;
    int nb_habitants;
    bool enCours;
    int stadeEvolution;
    int nb_batiment;
    int experience;
    int numero;
    struct Batiment* next;
    int timer;
}Batiment;

typedef struct Jeu{
    bool onClickSouris;
    bool en_cours;
    bool quitter;
    int annee;
    int mois;
    int numero_maillon_supprime;
    int niveau;
    int choix_politique;
    int page_actuel;
    int mode_de_selection;
    int** terrain;
    int** matrice_connexite_route;
    Matrice_batiment** matrice_connexite_eau;
    Matrice_batiment** matrice_connexite_electricite;
    int num_connexite;
    Vector2 ordre;
    Vector2 selection;
    int nb_habitants_tot;
    int argent;
    int production_eau_restante;
    int production_elec_restante;
    int timer_jeu;
    int timer_affichage;
    int timer_message_error;
    Batiment* batiments[nb_type_batiments];
    S_Image tabImages[nb_pages][nb_img];
    Sound tabSon[nb_sons];
}Jeu;

// TODO: NE PAS CHANGER LORDRE DES INCLUDES IMPORTANT !!!

#include "Macros.h"
#include "initialisation.h"
#include "affichage/affichage.h"
#include "raylib.h"
#include "Graphe.h"
#include "reasings.h"
#include "verification.h"
#include "affichage/Sacha_affichage.h"
#include "affichage/affichage_console.h"


int difference_entre_2_nombres_VALEURABSOLUE(int a, int b);
void ajouterBatiment_ListeChainee(Jeu* jeu, int x, int y, int choix);
void afficherM(Jeu* jeu);
void detruireBatiment(Jeu* jeu,int x,int y,int choix);
void chargementListe(Jeu* jeu,int num,int y,int* x,FILE **ifs,int stadeEvo);
void liberationListe(Jeu* jeu);
int conditionAchatBatiment(Jeu* jeu,int choix);
bool verifier_batiment_a_cote_route(Jeu* jeu, int type_de_batiment, int co_x, int co_y);
int initialisation_cases_adjacentes(Vector2* case_adjacente, int type_de_batiment, Vector2 co_bat);
void compteurNbBatimentListe(Jeu* jeu,int choix);
void decompteurNbBatimentListe(Jeu* jeu,int choix);

#endif //TEMPLATE_RAYLIB_JEU_H
