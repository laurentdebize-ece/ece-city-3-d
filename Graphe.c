#include "Graphe.h"

void lire_graphe(Jeu* jeu) {
    FILE *ifs = fopen(NOM_DU_FICHIER, "r");
    int ordre_x;
    int ordre_y;
    int argent;
    int politique;

    if (!ifs) {
        printf("Vous n'avez pas encore de graphe\n");
        initialisation_Grille();
        ifs = fopen(NOM_DU_FICHIER, "r");
    }

    fscanf(ifs, "%d", &ordre_x);
    fscanf(ifs, "%d", &ordre_y);
    fscanf(ifs, "%d", &jeu->annee);
    fscanf(ifs, "%d", &jeu->mois);
    fscanf(ifs, "%d", &argent);
    fscanf(ifs, "%d", &jeu->nb_habitants_tot);
    fscanf(ifs, "%d", &jeu->production_eau_restante);
    fscanf(ifs, "%d", &jeu->production_elec_restante);
    fscanf(ifs, "%d", &politique);

    if(jeu->en_cours ==0)jeu->terrain = (int**) malloc(ordre_y * sizeof(int*));

    for (int i = 0; i <= ordre_y; i++) {
        jeu->terrain[i] = (int*) malloc(ordre_x * sizeof(int));
    }

    for (int i = 0; i < nb_type_batiments; i++){
        jeu->batiments[i] = (Batiment*) malloc(sizeof (Batiment));
    }
    jeu->batiments[maison] = NULL;
    jeu->batiments[chateau_deau] = NULL;
    jeu->batiments[usine_electrique] = NULL;

    for (int i = 0; i <= ordre_y; i++) {
        for (int j = 0; j <= ordre_x; j++) {
            fscanf(ifs, " %d", &jeu->terrain[i][j]);
        }
    }

    for (int y = 0; y <= ordre_y; y++) {
        for (int x = 0; x <= ordre_x; x++) {
            int stadeEvo = 0;
            if(jeu->terrain[y][x] == 2 || jeu->terrain[y][x] == 3 || jeu->terrain[y][x] == 4 || jeu->terrain[y][x] >= 20){
                if(jeu->terrain[y][x] >= 20){
                    stadeEvo = jeu->terrain[y][x] - 20;
                    jeu->terrain[y][x] = 2;
                }
                chargementListe(jeu, jeu->terrain[y][x], y, &x, &ifs, stadeEvo);
            }
        }
    }
    jeu->ordre.x = ordre_x;
    jeu->ordre.y = ordre_y;
    jeu->argent = argent;
    jeu->choix_politique = politique;
    fclose(ifs);
}



void enregistrer_Grille(Jeu* jeu){
    Batiment* parcoursMaison = jeu->batiments[maison];
    FILE *ifs = fopen(NOM_DU_FICHIER, "w");
    if(ifs==NULL){
        printf("Erreur lors de l'ouverture d'un fichier");
        exit(1);
    }
    fprintf(ifs, "%d\n",(int)jeu->ordre.x);
    fprintf(ifs, "%d\n",(int)jeu->ordre.y);
    fprintf(ifs, "%d\n",(int)jeu->annee);
    fprintf(ifs, "%d\n",(int)jeu->mois);
    fprintf(ifs, "%d\n",jeu->argent);
    fprintf(ifs, "%d\n", jeu->nb_habitants_tot);
    fprintf(ifs, "%d\n", jeu->production_eau_restante);
    fprintf(ifs, "%d\n", jeu->production_elec_restante);
    fprintf(ifs,"%d\n",jeu->choix_politique);
    for (int y = 0; y <= (int)jeu->ordre.y; y++) {
        for (int x = 0; x <= (int)jeu->ordre.x; x++) {
            bool passe = FALSE;
            if(jeu->terrain[y][x] == 2 && jeu->batiments[maison] != NULL){
                do{
                    if(y == (int)parcoursMaison->co.y && x == (int)parcoursMaison->co.x){
                        fprintf(ifs, "%d ", jeu->terrain[y][x] + 18 + parcoursMaison->stadeEvolution);
                        passe = TRUE;
                    }
                    parcoursMaison = parcoursMaison->next;
                    if (jeu->batiments[maison]->nb_batiment == 1) break;
                }while(parcoursMaison != jeu->batiments[maison]);
                if(passe == FALSE){
                    fprintf(ifs, "%d ", jeu->terrain[y][x]);
                }
            }
            else{fprintf(ifs, "%d ", jeu->terrain[y][x]);}
        }
        fprintf(ifs, "\n");
    }
    fclose(ifs);
}

void ajout_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute){
    bool obstacle = FALSE;
    int y_temporaire = co_y;

    if (co_xroute !=-1 || co_yroute != -1){
        int x_temporaire = co_x;
        int x_distance=difference_entre_2_nombres_VALEURABSOLUE(co_x, co_xroute), y_distance=difference_entre_2_nombres_VALEURABSOLUE(co_y, co_yroute);
        for (int i = 0; i < x_distance ; i++) {
            if (jeu->terrain[co_y][x_temporaire] != 0){
                obstacle = TRUE;
                break;
            }
            if (co_x < co_xroute){
                x_temporaire++;
            }else x_temporaire--;
        }
        for (int i = 0; i <= y_distance ; i++) {
            if (jeu->terrain[y_temporaire][co_x] != 0){
                obstacle = TRUE;
                break;
            }
            if (co_y < co_yroute){
                y_temporaire++;
            }else y_temporaire--;
        }
        if (obstacle == FALSE){
            for (int i = 0; i < x_distance ; i++) {
                if (jeu->argent - COUT_ROUTE >= 0){
                    jeu->terrain[co_y][co_x] = nomDuBatiment;
                    jeu->argent-= COUT_ROUTE;
                    if (co_x < co_xroute){
                        co_x++;
                    }else co_x--;
                }

            }
            for (int i = 0; i <= y_distance ; i++) {
                if (jeu->argent - COUT_ROUTE >= 0){
                    jeu->terrain[co_y][co_x] = nomDuBatiment;
                    jeu->argent-= COUT_ROUTE;
                    if (co_y < co_yroute){
                        co_y++;
                    }else co_y--;
                }

            }
            printf("La construction : route, est un succes !\n");
        } else {
            printf("Vous ne pouvez pas construire ici, un obstacle vous en empeche !\n");
            detruireBatiment(jeu,co_x,co_y,nomDuBatiment);
        }
    }else{
        for (int i = 0; i < jeu->batiments[nomDuBatiment]->taille.y ; i++) {
            for (int j = 0; j < jeu->batiments[nomDuBatiment]->taille.x; j++) {
                if (jeu->terrain[co_y][co_x + j] != 0){
                    obstacle = TRUE;
                    break;
                }
            }
            if (obstacle == TRUE){
                break;
            }
            y_temporaire ++;
        }
        if (obstacle == FALSE){
            for (int i = 0; i < jeu->batiments[nomDuBatiment]->taille.y ; i++) {
                for (int j = 0; j < jeu->batiments[nomDuBatiment]->taille.x; j++) {
                    jeu->terrain[co_y][co_x + j] = nomDuBatiment;
                }co_y ++;
            }
            printf("La construction : %s, est un succes !\n", jeu->batiments[nomDuBatiment]->nom);
        } else {
            printf("Vous ne pouvez pas construire ici, un obstacle vous en empeche !\n");
            detruireBatiment(jeu,co_x,co_y,nomDuBatiment);
        }
    }
}


void suppression_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute){
    bool obstacle = FALSE;
    int y_temporaire = co_y;

    if (co_xroute !=-1 || co_yroute != -1){
        int x_temporaire = co_x;
        int x_distance=difference_entre_2_nombres_VALEURABSOLUE(co_x, co_xroute), y_distance=difference_entre_2_nombres_VALEURABSOLUE(co_y, co_yroute);
        for (int i = 0; i < x_distance ; i++) {
            if (jeu->terrain[co_y][x_temporaire] != 0){
                obstacle = TRUE;
                break;
            }
            if (co_x < co_xroute){
                x_temporaire++;
            }else x_temporaire--;
        }
        for (int i = 0; i <= y_distance ; i++) {
            if (jeu->terrain[y_temporaire][co_x] != 0){
                obstacle = TRUE;
                break;
            }
            if (co_y < co_yroute){
                y_temporaire++;
            }else y_temporaire--;
        }
        if (obstacle == TRUE){
            for (int i = 0; i < x_distance ; i++) {
                jeu->terrain[co_y][co_x] = 0;
                if (co_x < co_xroute){
                    co_x++;
                }else co_x--;
            }
            for (int i = 0; i <= y_distance ; i++) {
                jeu->terrain[co_y][co_x] = 0;
                if (co_y < co_yroute){
                    co_y++;
                }else co_y--;
            }
            printf("La destruction : route, est un succes !\n");
        } else {
            printf("Il n'y a pas de route a detruire !\n");
        }
    }else{
        for (int i = 0; i < jeu->batiments[nomDuBatiment]->taille.y ; i++) {
            for (int j = 0; j < jeu->batiments[nomDuBatiment]->taille.x; j++) {
                if (jeu->terrain[co_y][co_x + j] != 0){
                    obstacle = TRUE;
                    break;
                }
            }
            if (obstacle == TRUE){
                break;
            }
            y_temporaire ++;
        }
        if (obstacle == TRUE){
            for (int i = 0; i < jeu->batiments[nomDuBatiment]->taille.y ; i++) {
                for (int j = 0; j < jeu->batiments[nomDuBatiment]->taille.x; j++) {
                    jeu->terrain[co_y][co_x + j] = 0;
                }co_y ++;
            }
            printf("La destruction : %s, est un succes !\n", jeu->batiments[nomDuBatiment]->nom);
        } else {
            printf("Il n'y a rien a detruire ici !\n");
        }
    }
}



Vector2 position_maison(Jeu* jeu, int x, int y){
    Vector2 pos_maison;
    pos_maison.x = -1;
    pos_maison.y = -1;
    bool batiment_trouve = FALSE;
    Batiment* batiment_actuel = jeu->batiments[maison];
    while(batiment_trouve == FALSE){
        for(int i = 0; i < TAILLE_MAISON; i++){
            if (x - i == batiment_actuel->co.x){
                pos_maison.x = batiment_actuel->co.x;
            }
            if (y - i == batiment_actuel->co.y){
                pos_maison.y = batiment_actuel->co.y;
            }
        }
        if (pos_maison.x != -1 && pos_maison.y != -1){
            batiment_trouve = TRUE;
        }
        batiment_actuel = batiment_actuel->next;
    }
    return pos_maison;
}

Vector2 position_usine(Jeu* jeu, int x, int y, int type_usine){
    Vector2 pos_usine;
    pos_usine.x = -1;
    pos_usine.y = -1;
    bool batiment_trouve = FALSE;
    Batiment* batiment_actuel = jeu->batiments[type_usine];
    while(batiment_trouve == FALSE){
        for(int i = 0; i < LONGUEUR_BATIMENTS; i++) {
            if (x - i == batiment_actuel->co.x) {
                pos_usine.x = batiment_actuel->co.x;
            }
        }
        for(int i = 0; i < LARGEUR_BATIMENTS; i++) {
            if (y - i == batiment_actuel->co.y) {
                pos_usine.y = batiment_actuel->co.y;
            }
        }
        if (pos_usine.x != -1 && pos_usine.y != -1){
            batiment_trouve = TRUE;
        }
        batiment_actuel = batiment_actuel->next;
    }
    return pos_usine;
}

Vector2 position_batiment(Jeu* jeu, int x, int y){
    Vector2 pos_batiment;
    int type_batiment = jeu->terrain[y][x];
    switch (type_batiment) {
        case vide : {
            printf("Cette case est vide\n");
            pos_batiment.x = -1;
            pos_batiment.y = -1;
            break;
        }
        case reseau : {
            pos_batiment.x = x;
            pos_batiment.y = y;
            printf("Cette case est une route placée en (%d,%d)\n", x, y);
            break;
        }
        case maison : {
            pos_batiment = position_maison(jeu, x, y);
            printf("Cette case correspond a une maison placee en (%d,%d)\n", pos_batiment.x, pos_batiment.y);
            break;
        }
        case chateau_deau : {
            pos_batiment = position_usine(jeu, x, y, chateau_deau);
            printf("Cette case correspond a un chateau d'eau place en (%d,%d)\n", pos_batiment.x, pos_batiment.y);
            break;
        }
        case usine_electrique : {
            pos_batiment = position_usine(jeu, x, y, usine_electrique);
            printf("Cette case correspond a une centrale electrique placee en (%d,%d)\n", pos_batiment.x, pos_batiment.y);
            break;
        }
        default : {
            break;
        }

    }
    return pos_batiment;
}