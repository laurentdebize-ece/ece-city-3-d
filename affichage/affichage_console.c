#include "affichage_console.h"

void afficher_choix_joueur(Jeu* jeu) {
    int choix = 0;
    int co_x = 0, co_y = 0, co_x1 = -1, co_y1 = -1;
    printf("\t\t\t\t------------------- ECE - CITY -------------------\t\t\t\t");
    printf("Temps : \n");
    printf("argent : %d\t\t\t", jeu->argent);
    printf("eau total restant : %d\t\t\t", jeu->production_eau_restante);
    printf("elec total restant : %d\n", jeu->production_elec_restante);
    printf("\nChoix :\n");
    printf("0 : Revenir au Menu Principale\n");
    printf("1 : placer une route\n");
    printf("2 : placer une maison\n");
    printf("3 : placer un chateau d eau\n");
    printf("4 : placer une usine elec\n");
    printf("5 : afficher Liste chaine\n");
    printf("6 : Detruire batiment\n");
    printf("9 : ~~~~ AFFICHER LA MAP ~~~~\n");
    printf("10 : Quel batiment ?\n");
    printf("11 : Matrice afficher route\n");
    scanf(" %d", &choix);
    switch (choix) {
        case 0: {
            afficher_menu_console(jeu);
            break;
        }
        case reseau: {
            printf("\nCoordonnees du point initiale? (x / y)\n");
            scanf(" %d %d", &co_x, &co_y);
            printf("\nCoordonnees du point final? (x / y)\n");
            scanf(" %d %d", &co_x1, &co_y1);
            if (co_x < 0 || co_y < 0 || co_x1 < 0 || co_y1 < 0 || co_x > ORDRE_EN_X || co_y > ORDRE_EN_Y ||
                co_x1 > ORDRE_EN_X || co_y1 > ORDRE_EN_Y) {

                break;
            }
            ajout_Batiment_Grille(jeu, reseau, co_x, co_y, co_x1, co_y1);
            sleep(1);
            break;
        }
        case maison: {
            printf("\nCoordonnees ? (x / y)\n");
            scanf(" %d %d", &co_x, &co_y);
            if (co_x < 0 || co_y < 0 || co_x > ORDRE_EN_X || co_y > ORDRE_EN_Y) {
                break;
            }
            if(verifier_batiment_a_cote_route(jeu, maison, co_x, co_y) && conditionAchatBatiment(jeu, maison)){
                printf("Ajout d'une maison ...\n");
                ajouterBatiment_ListeChainee(jeu, co_x, co_y, choix);
                ajout_Batiment_Grille(jeu, maison, co_x, co_y, co_x1, co_y1);
            }
            else { printf("Vous ne pouvez pas placer un batiment s'il n'est pas a cote d'une route\n");}
            break;
        }
        case chateau_deau: {
            printf("\nCoordonnees ? (x / y)\n");
            scanf(" %d %d", &co_x, &co_y);
            if (co_x < 0 || co_y < 0 || co_x > ORDRE_EN_X || co_y > ORDRE_EN_Y) {
                break;
            }
            if(verifier_batiment_a_cote_route(jeu, chateau_deau, co_x, co_y) && conditionAchatBatiment(jeu, chateau_deau)){
                printf("Ajout d'un chateau d'eau ...\n");
                ajouterBatiment_ListeChainee(jeu, co_x, co_y, choix);
                ajout_Batiment_Grille(jeu, chateau_deau, co_x, co_y, co_x1, co_y1);
                sleep(1);
            }
            else { printf("Vous ne pouvez pas placer un batiment s'il n'est pas a cote d'une route\n");}
            break;
        }
        case usine_electrique: {
            printf("\nCoordonnees ? (x / y)\n");
            scanf(" %d %d", &co_x, &co_y);
            if (co_x < 0 || co_y < 0 || co_x > ORDRE_EN_X || co_y > ORDRE_EN_Y) {
                break;
            }
            if (verifier_batiment_a_cote_route(jeu, usine_electrique, co_x, co_y) && conditionAchatBatiment(jeu, usine_electrique)){
                printf("Ajout d'une usine electrique ...\n");
                ajouterBatiment_ListeChainee(jeu, co_x, co_y, choix);
                ajout_Batiment_Grille(jeu, usine_electrique, co_x, co_y, co_x1, co_y1);
                sleep(1);
            }
            else { printf("Vous ne pouvez pas placer un batiment s'il n'est pas a cote d'une route\n");}
            break;
        }
        case 5: {
            afficherM(jeu);
            break;
        }
        case 6: {
            printf("Quel type de batiment voulez vous detruire ?\n1 : Route\n2 : Maison\n3 : Chateau d'eau\n4 : Usine electrique\n");
            scanf("%d", &choix);
            Vector2 co_batiment;
            switch (choix) {
                case reseau : {
                    printf("\nCoordonnees du point initiale? (x / y)\n");
                    scanf(" %d %d", &co_x, &co_y);
                    printf("\nCoordonnees du point final? (x / y)\n");
                    scanf(" %d %d", &co_x1, &co_y1);
                    if (co_x < 0 || co_y < 0 || co_x1 < 0 || co_y1 < 0 || co_x > ORDRE_EN_X || co_y > ORDRE_EN_Y ||
                        co_x1 > ORDRE_EN_X || co_y1 > ORDRE_EN_Y) {
                    }
                    suppression_Batiment_Grille(jeu, reseau, co_x, co_y, co_x1, co_y1);
                    sleep(1);
                    break;
                }
                case maison: {
                    printf("\nCoordonnees ? (x / y)\n");
                    scanf(" %d %d", &co_x, &co_y);
                    if (co_x < 0 || co_y < 0 || co_x > ORDRE_EN_X || co_y > ORDRE_EN_Y) {
                        break;
                    }
                    co_batiment = position_batiment(jeu, co_x,co_y);
                    if ((co_batiment.x == -1 && co_batiment.y == -1)|| jeu->terrain[(int)co_batiment.y][(int)co_batiment.x] != maison){
                        printf("La destruction n'est pas possible : coordonnees invalides\n");
                    }
                    else {
                        printf("Destruction d'une maison ...\n");
                        suppression_Batiment_Grille(jeu, maison, co_batiment.x, co_batiment.y, co_x1, co_y1);
                        detruireBatiment(jeu, co_batiment.x, co_batiment.y, maison);
                        sleep(1);
                    }
                    break;
                }
                case chateau_deau: {
                    printf("\nCoordonnees ? (x / y)\n");
                    scanf(" %d %d", &co_x, &co_y);
                    if (co_x < 0 || co_y < 0 || co_x > ORDRE_EN_X || co_y > ORDRE_EN_Y) {
                        break;
                    }
                    co_batiment = position_batiment(jeu, co_x,co_y);
                    if ((co_batiment.x == -1 && co_batiment.y == -1) || jeu->terrain[(int)co_batiment.y][(int)co_batiment.x] != chateau_deau){
                        printf("La destruction n'est pas possible : coordonnees invalides\n");
                    }
                    else {
                        printf("Destruction d'un chateau d'eau ...\n");
                        suppression_Batiment_Grille(jeu, chateau_deau, co_batiment.x, co_batiment.y, co_x1, co_y1);
                        detruireBatiment(jeu, co_batiment.x, co_batiment.y, chateau_deau);
                        sleep(1);
                    }
                    break;
                }
                case usine_electrique: {
                    printf("\nCoordonnees ? (x / y)\n");
                    scanf(" %d %d", &co_x, &co_y);
                    if (co_x < 0 || co_y < 0 || co_x > ORDRE_EN_X || co_y > ORDRE_EN_Y) {
                        break;
                    }
                    co_batiment = position_batiment(jeu, co_x,co_y);
                    if ((co_batiment.x == -1 && co_batiment.y == -1)|| jeu->terrain[(int)co_batiment.y][(int)co_batiment.x] != usine_electrique) {
                        printf("La destruction n'est pas possible : coordonnees invalides\n");
                    }
                    else {
                        printf("Destruction d'une usine electrique ...\n");
                        suppression_Batiment_Grille(jeu, usine_electrique, co_batiment.x, co_batiment.y, co_x1, co_y1);
                        detruireBatiment(jeu, co_batiment.x, co_batiment.y, usine_electrique);
                        sleep(1);
                    }
                    break;
                }
                default :{
                    break;
                }
            }
            case 9: {
                break;
            }
            case 10: {
                int a = 0, b = 0;
                printf("Coordonnee:\n");
                scanf("%d  %d", &a, &b);
                position_batiment(jeu, a, b); //retourne les coordonnées
                break;
            }
            case 11:{
                afficherMatriceConnexiteRoute(jeu);
            }
            default : {
                break;
            }

        }
    }
    afficher_choix_joueur(jeu);
}

void afficher_menu_console(Jeu* jeu){
    int choix = 0;
    printf("-------BIENVENUE DANS ECE-CITY CONSOLE -------- (v.APLHA)\n");
    printf("\nMenu :\n\n");
    printf("0 : Revenir a la partie en cours\n");
    printf("1 : Lancer une partie\n");
    printf("2 : Sauvegarde \n");
    printf("3 : Charger une partie\n");
    printf("4 : Quitter\n");
    printf("9 : delet.txt\n");
    scanf(" %d", &choix);
    switch(choix){
        case 0:{
            if (jeu == NULL){
                printf("Vous ne pouvez pas revenir a une partie que vous n'avez pas commence\n");
                break;
            } else{
                afficher_choix_joueur(jeu);
                break;
            }
        }
        case 1:{
            afficher_choix_joueur(jeu);
            break;
        }
        case 2: {
            if (jeu == NULL) {
                printf("vous ne pouvez pas sauvegarder car vous n'avez pas charge de partie.\n");
                break;
            } else {
                printf("SAUVEGARDE EN COURS...\n");
                enregistrer_Grille(jeu);
                printf("SAUVEGARDE EFFECTUEE\n");
                break;
            }
        }
        case 3:{
            printf("CHARGEMENT EN COURS...\n");
            printf("CHARGEMENT TERMINE !\n");
            afficher_choix_joueur(jeu);
            break;
        }
        case 4:{
            liberationListe(jeu);
            exit(0);
        }
        case 9:{
            remove(NOM_DU_FICHIER);
            printf("\nFICHIER DETRUIT\n");
        }
        default :{
            break;
        }
    }
    afficher_menu_console(jeu);
}


void afficherMatriceConnexiteRoute(Jeu* jeu){
    for(int i = 0;i < ORDRE_EN_Y;i++){
        for(int j = 0;j < ORDRE_EN_X;j++) {
            printf("%d", jeu->matrice_connexite_route[i][j]);
        }
    }
}

void print_terrain_console(Jeu* jeu){
    for (int i = 0; i < jeu->ordre.y; i++) {
        for (int j = 0; j < jeu->ordre.x ;j++) {
            printf(" %d",jeu->terrain[i][j]);
        }
        printf("\n");
    }
}
