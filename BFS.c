#include "BFS.h"
//
// BFS pour les composantes connexes des routes
// matrices d'adjacences entre les composantes connexe des routes, les centrales, les chateaux d'eaux
// et les maisons

void BFS_connexite(Jeu* jeu, Vector2 tuile, int num_connexite_teste){
    Vector2* cases_adjacentes = NULL;
    Vector2* case_adjacentes_theorique = NULL;
    Vector2 position_case;
    Vector2 taille_case;
    taille_case.y = 1;
    taille_case.x = 1;
    position_case.y = tuile.y;
    position_case.x = tuile.x;
    Vector2** new_cases_adjacentes = NULL;// pour switch
    jeu->matrice_connexite_route[(int)tuile.y][(int)tuile.x] = jeu->num_connexite; //route parcourue, route marqué
    // nombre d'adjacences théorique si on prend en comptes toutes les adjacences possiles des cases marquées (même celles avec des coordonnées négatives)
    int nb_adjacence_theorique = initialisation_cases_adjacentes(cases_adjacentes, 1, position_case ); // 4 3 ou 2 fois le nombre de cases marquées car chaque cases ont 4 adjacences
    nb_adjacence_theorique = initialisation_cases_adjacentes(case_adjacentes_theorique,1,position_case);
    int nb_adjacence_theorique_2 = nb_adjacence_theorique;
    int nb_adjacence = 0; // nombre de routes découvertes
    int new_nb_adjacence;
    int* valeur_adjacence = calloc(nb_adjacence_theorique,sizeof(int));// valeurs des cases adjacentes découvertes initialisé à 0
    for (int i = 0; i < nb_adjacence_theorique; i++){
        // si case adjacente = route pas marquée, valeur_adjacence prend la valeur de la route et on incrémente le nombre de routes découvertes
        if((cases_adjacentes[i].y >= 0) && (cases_adjacentes[i].x >= 0) ) {
            if (jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 0
                && jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 2
                && jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 3
                && jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 4
                //jeu->terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] == 1;
                && jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != jeu->num_connexite) {
                valeur_adjacence[i] = jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x];
                nb_adjacence++;
            }
        }
    }
    printf("ok 1\n");
    if (nb_adjacence != 0) {
        new_cases_adjacentes = (Vector2 **) calloc(nb_adjacence, sizeof(Vector2 *));
        int y = 0;
        for (int h = 0; h < nb_adjacence; h++) {
            nb_adjacence_theorique = verif_nb_cases_adjacentes(jeu, cases_adjacentes[h], taille_case);
            for (int i = 0; i < nb_adjacence_theorique; i++) {

                if (valeur_adjacence[i] != 0) {
                    nb_adjacence_theorique_2 = initialisation_cases_adjacentes(new_cases_adjacentes[y],reseau, cases_adjacentes[h]);
                    y++;
                    if (valeur_adjacence[i] == num_connexite_teste) {
                        valeur_adjacence[i] = jeu->num_connexite;

                    } else {
                        if (valeur_adjacence[i] < jeu->num_connexite) {

                            for (int k = 0; k < ORDRE_EN_Y; k++) {
                                for (int l = 0; l < ORDRE_EN_X; l++) {
                                    if (jeu->matrice_connexite_route[k][l] == jeu->num_connexite) {
                                        jeu->matrice_connexite_route[k][l] = valeur_adjacence[i];
                                    }
                                }
                            }
                            jeu->num_connexite = valeur_adjacence[i];
                        } else {
                            for (int k = 0; k < ORDRE_EN_Y; k++) {
                                for (int l = 0; l < ORDRE_EN_X; l++) {
                                    if (jeu->matrice_connexite_route[k][l] == valeur_adjacence[i]) {
                                        jeu->matrice_connexite_route[k][l] = jeu->num_connexite;
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    } else{
        new_cases_adjacentes == NULL;
    }
    new_nb_adjacence = nb_adjacence;
    free (cases_adjacentes);
    cases_adjacentes = NULL;
    free(valeur_adjacence);
    valeur_adjacence = NULL;
    printf("ok 2\n");
    while (new_cases_adjacentes != NULL) {
        if (nb_adjacence != 0) {


            cases_adjacentes = calloc(4 * nb_adjacence, sizeof(Vector2));
            int x = 0;
            for (int i = 0; i < nb_adjacence; i++) {
                nb_adjacence_theorique = verif_nb_cases_adjacentes(jeu,case_adjacentes_theorique[i],taille_case);
                for (int j = 0; j < nb_adjacence_theorique; j++) {
                    cases_adjacentes[x].y = new_cases_adjacentes[i][j].y;
                    cases_adjacentes[x].x = new_cases_adjacentes[i][j].x;
                    x++;
                }
            }
            if (new_cases_adjacentes == NULL) {
                for (int i = 0; i < nb_adjacence_theorique; i++) {
                    if (new_cases_adjacentes[i]!=NULL) {
                        free(new_cases_adjacentes[i]);
                        new_cases_adjacentes[i] = NULL;
                    }
                }
                free(new_cases_adjacentes);
                new_cases_adjacentes = NULL;
            }
            nb_adjacence = new_nb_adjacence;
            if(case_adjacentes_theorique != NULL) {
                free(case_adjacentes_theorique);
                case_adjacentes_theorique = NULL;
            }
            new_nb_adjacence = 0;
            valeur_adjacence = calloc(nb_adjacence_theorique * nb_adjacence,sizeof(int));// valeurs des cases adjacentes découvertes initialisé à 0
            for (int i = 0; i < nb_adjacence_theorique * nb_adjacence; i++) {
                // si case adjacente = route pas marquée, valeur_adjacence prend la valeur de la route et on incrémente le nombre de routes découvertes
                if ((cases_adjacentes[i].y >= 0) && (cases_adjacentes[i].x>=0)) {
                    if (jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 0
                        && jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 2
                        && jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 3
                        && jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 4
                        && jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != jeu->num_connexite) {
                        valeur_adjacence[i] = jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x];
                        new_nb_adjacence++;
                    }
                }
            }
            new_cases_adjacentes = (Vector2 **) calloc(nb_adjacence, sizeof(Vector2 *));
            int y = 0;

            for (int h = 0; h < nb_adjacence; h++) {
                nb_adjacence_theorique = verif_nb_cases_adjacentes(jeu, cases_adjacentes[h], taille_case);
                for (int i = 0; i < nb_adjacence_theorique; i++) {

                    if (valeur_adjacence[i] != 0) {
                        nb_adjacence_theorique_2 = initialisation_cases_adjacentes(new_cases_adjacentes[y],reseau, cases_adjacentes[h]);
                        y++;
                        if (valeur_adjacence[i] == num_connexite_teste) {
                            valeur_adjacence[i] = jeu->num_connexite;

                        } else {
                            if (valeur_adjacence[i] < jeu->num_connexite) {

                                for (int k = 0; k < ORDRE_EN_Y; k++) {
                                    for (int l = 0; l < ORDRE_EN_X; l++) {
                                        if (jeu->matrice_connexite_route[k][l] == jeu->num_connexite) {
                                            jeu->matrice_connexite_route[k][l] = valeur_adjacence[i];
                                        }
                                    }
                                }
                                jeu->num_connexite = valeur_adjacence[i];
                            } else {
                                for (int k = 0; k < ORDRE_EN_Y; k++) {
                                    for (int l = 0; l < ORDRE_EN_X; l++) {
                                        if (jeu->matrice_connexite_route[k][l] == valeur_adjacence[i]) {
                                            jeu->matrice_connexite_route[k][l] = jeu->num_connexite;
                                        }
                                    }
                                }
                            }
                        }
                    }

                }
            }
            new_nb_adjacence = nb_adjacence;
            free(cases_adjacentes);
            cases_adjacentes = NULL;
            free(valeur_adjacence);
            valeur_adjacence = NULL;

        } else{
            if (new_cases_adjacentes != NULL) {
                for (int i = 0; i < nb_adjacence_theorique; i++) {
                    free(new_cases_adjacentes[i]);
                    new_cases_adjacentes[i] = NULL;
                }
                free(new_cases_adjacentes);
                new_cases_adjacentes = NULL;
            }
        }
    }
}

void BFS_PCC(Jeu* jeu, Vector2 tuile, int num_connexite_teste, int terrain[ORDRE_EN_Y][ORDRE_EN_X], int num_chateau_eau){
    int distance = 1;
    for (int i = 0; i < 0; i++) {
        jeu->matrice_connexite_eau[i][num_chateau_eau].distance = 0;
    }
    Vector2* cases_adjacentes = NULL;
    Vector2* case_adjacentes_theorique = NULL;
    Vector2 position_case;
    Vector2 taille_case;
    taille_case.y = LARGEUR_BATIMENTS;
    taille_case.x = LONGUEUR_BATIMENTS;
    position_case.y = tuile.y;
    position_case.x = tuile.x;
    Vector2** new_cases_adjacentes = NULL;// pour switch
    // nombre d'adjacences théorique si on prend en comptes toutes les adjacences possiles des cases marquées (même celles avec des coordonnées négatives)
    int nb_adjacence_theorique = initialisation_cases_adjacentes(cases_adjacentes, 1, position_case );// 4 3 ou 2 fois le nombre de cases marquées car chaque cases ont 4 adjacences
    nb_adjacence_theorique = initialisation_cases_adjacentes(case_adjacentes_theorique,1,position_case);
    int nb_adjacence_theorique_2 = nb_adjacence_theorique;
    int nb_adjacence = 0; // nombre de routes découvertes
    int new_nb_adjacence;
    int* valeur_adjacence = calloc(nb_adjacence_theorique,sizeof(int));// valeurs des cases adjacentes découvertes initialisé à 0
    for (int i = 0; i < nb_adjacence_theorique; i++){
        // si case adjacente = route pas marquée, valeur_adjacence prend la valeur de la route et on incrémente le nombre de routes découvertes
        if((cases_adjacentes[i].y >= 0) && (cases_adjacentes[i].x >= 0) ) {
            if (terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 0
                && terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 2
                && terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 3
                && terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 4
                //jeu->terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] == 1;
                && terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != jeu->num_connexite) {
                valeur_adjacence[i] = terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x];
                nb_adjacence++;
            }
        }
    }
    printf("ok 1\n");
    if (nb_adjacence != 0) {
        new_cases_adjacentes = (Vector2 **) calloc(nb_adjacence, sizeof(Vector2 *));
        int y = 0;
        for (int h = 0; h < nb_adjacence; h++) {
            nb_adjacence_theorique = verif_nb_cases_adjacentes(jeu, cases_adjacentes[h], taille_case);
            for (int i = 0; i < nb_adjacence_theorique; i++) {

                if (valeur_adjacence[i] != 0) {
                    nb_adjacence_theorique_2 = initialisation_cases_adjacentes(new_cases_adjacentes[y],reseau, cases_adjacentes[h]);
                    y++;
                    if (valeur_adjacence[i] == num_connexite_teste) {
                        valeur_adjacence[i] = jeu->num_connexite;

                    }


                }

            }
        }
    } else{
        new_cases_adjacentes == NULL;
    }
    new_nb_adjacence = nb_adjacence;
    free (cases_adjacentes);
    cases_adjacentes = NULL;
    free(valeur_adjacence);
    valeur_adjacence = NULL;
    printf("ok 2\n");
    while (new_cases_adjacentes != NULL) {
        if (nb_adjacence != 0) {


            cases_adjacentes = calloc(4 * nb_adjacence, sizeof(Vector2));
            int x = 0;
            for (int i = 0; i < nb_adjacence; i++) {
                nb_adjacence_theorique = verif_nb_cases_adjacentes(jeu,case_adjacentes_theorique[i],taille_case);
                for (int j = 0; j < nb_adjacence_theorique; j++) {
                    cases_adjacentes[x].y = new_cases_adjacentes[i][j].y;
                    cases_adjacentes[x].x = new_cases_adjacentes[i][j].x;
                    if (terrain[(int)cases_adjacentes[x].y][(int)cases_adjacentes[x].x] == 2){
                        for (int k = 0; k < 2; k++) {
                            for (int l = 0; l < 2; l++) {
                                if (((cases_adjacentes[x].y - k) >= 0) && ((cases_adjacentes[x].x - l) >= 0)){
                                    for (int m = 0; m < jeu->batiments[maison]->nb_batiment; m++) {
                                        if(jeu->matrice_connexite_eau[m][num_chateau_eau].distance == 0) {
                                            if (((cases_adjacentes[x].y - k) ==
                                                 jeu->matrice_connexite_eau[m][num_chateau_eau].batiments[0].y) &&
                                                ((cases_adjacentes[x].x - l) ==jeu->matrice_connexite_eau[m][num_chateau_eau].batiments[0].x)) {

                                                jeu->matrice_connexite_eau[m][num_chateau_eau].distance = distance;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    x++;

                }
            }
            distance++;
            if (new_cases_adjacentes == NULL) {
                for (int i = 0; i < nb_adjacence_theorique; i++) {
                    if (new_cases_adjacentes[i]!=NULL) {
                        free(new_cases_adjacentes[i]);
                        new_cases_adjacentes[i] = NULL;
                    }
                }
                free(new_cases_adjacentes);
                new_cases_adjacentes = NULL;
            }
            nb_adjacence = new_nb_adjacence;
            if(case_adjacentes_theorique != NULL) {
                free(case_adjacentes_theorique);
                case_adjacentes_theorique = NULL;
            }
            new_nb_adjacence = 0;
            valeur_adjacence = calloc(nb_adjacence_theorique * nb_adjacence,sizeof(int));// valeurs des cases adjacentes découvertes initialisé à 0
            for (int i = 0; i < nb_adjacence_theorique * nb_adjacence; i++) {
                // si case adjacente = route pas marquée, valeur_adjacence prend la valeur de la route et on incrémente le nombre de routes découvertes
                if ((cases_adjacentes[i].y >= 0) && (cases_adjacentes[i].x>=0)) {
                    if (terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 0
                        && terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 2
                        && terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 3
                        && terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != 4
                        && terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x] != jeu->num_connexite) {
                        valeur_adjacence[i] = terrain[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x];
                        new_nb_adjacence++;
                    }
                }
            }
            new_cases_adjacentes = (Vector2 **) calloc(nb_adjacence, sizeof(Vector2 *));
            int y = 0;

            for (int h = 0; h < nb_adjacence; h++) {
                nb_adjacence_theorique = verif_nb_cases_adjacentes(jeu, cases_adjacentes[h], taille_case);
                for (int i = 0; i < nb_adjacence_theorique; i++) {

                    if (valeur_adjacence[i] != 0) {
                        nb_adjacence_theorique_2 = initialisation_cases_adjacentes(new_cases_adjacentes[y],reseau, cases_adjacentes[h]);
                        y++;
                        if (valeur_adjacence[i] == num_connexite_teste) {
                            valeur_adjacence[i] = jeu->num_connexite;

                        }
                    }

                }
            }
            new_nb_adjacence = nb_adjacence;
            free(cases_adjacentes);
            cases_adjacentes = NULL;
            free(valeur_adjacence);
            valeur_adjacence = NULL;

        } else{
            if (new_cases_adjacentes != NULL) {
                for (int i = 0; i < nb_adjacence_theorique; i++) {
                    free(new_cases_adjacentes[i]);
                    new_cases_adjacentes[i] = NULL;
                }
                free(new_cases_adjacentes);
                new_cases_adjacentes = NULL;
            }
        }
    }
}

void BFS_PCC_ajout_construction(Jeu* jeu, int num_batiment){
    int matrice[ORDRE_EN_Y][ORDRE_EN_X];
    Batiment* b_chateau_eau = jeu->batiments[chateau_deau];
    Batiment* b_maison = jeu->batiments[maison];
    int nb_adjacence_chateau_eau;
    for (int i = 0; i < jeu->batiments[chateau_deau]->nb_batiment ; i++) {
        for (int i = 0; i < ORDRE_EN_Y; i++) {
            for (int j = 0; j < ORDRE_EN_X; j++) {
                matrice[i][j]= jeu->terrain[i][j];
            }
        }
        BFS_PCC(jeu,b_chateau_eau->co,1,matrice,i);
    }
    for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
        for (int j = 0; j < jeu->batiments[chateau_deau]->nb_batiment; j++) {
            if(jeu->matrice_connexite_eau[i][j].distance == 0){
                jeu->matrice_connexite_eau[i][j].connexite = 0;
            }
        }
    }
}
int** init_conexite_route(Jeu* jeu){
    Batiment* batiment = calloc(1, sizeof(Batiment));

    int** matrice_connexite_route = (int**) malloc(ORDRE_EN_Y * sizeof(int*));
    for (int i = 0; i < ORDRE_EN_Y; i++) {
        matrice_connexite_route[i] = (int*) malloc(ORDRE_EN_X * sizeof(int));
    }
    for (int i = 0; i < ORDRE_EN_Y; i++) {
        for (int j = 0; j < ORDRE_EN_X; j++) {
            matrice_connexite_route[i][j] = jeu->terrain[i][j];
        }
    }
    printf("matrice_connexite_route initialiser\n");
    for (int j = maison; j < nb_type_batiments ; j++) {
        batiment = jeu->batiments[j];
        for (int j = maison; j < jeu->batiments[maison]->nb_batiment ; j++) {
            batiment = batiment->next;
            int nb_batiment;
            switch (j) {
                case maison :
                    nb_batiment = jeu->batiments[maison]->nb_batiment;
                    break;
                case chateau_deau :
                    nb_batiment = jeu->batiments[chateau_deau]->nb_batiment;
                    break;
                case usine_electrique :
                    nb_batiment = jeu->batiments[usine_electrique]->nb_batiment;
                    break;
            }
            printf("switch case ok %d\n", nb_batiment);
            int longueur = jeu->batiments[j]->taille.x;
            int largeur = jeu->batiments[j]->taille.y;
            if (jeu->batiments[j]->next != NULL) {
                int num_connexite = 50;
                for (int k = 0; k < nb_batiment; k++) {
                    if (k != 0) {
                        batiment = batiment->next;
                    }
                    for (int i; i < ((longueur + largeur) * 2); i++) {
                        if (matrice_connexite_route[(int)batiment->cases_adjacentes[i].y][(int)batiment->cases_adjacentes[i].x] ==
                            1) {
                            BFS_connexite(jeu, batiment->cases_adjacentes[i], 1);
                            num_connexite++;
                        }

                    }
                }
            }
        }
    }
    return matrice_connexite_route;
}

void connexite_route_ajout_batiment(Jeu* jeu, Batiment* nouveau){
    for (int i = 0; i < nouveau->taille.y; i++) {
        for (int j = 0; j < nouveau->taille.x; j++) {
            jeu->matrice_connexite_route[(int)nouveau->co.y + i][(int)nouveau->co.x +j] = jeu->terrain[(int)nouveau->co.y + i][(int)nouveau->co.x +j];
        }
    }
    for (int i = 0; i < ((nouveau->taille.x + nouveau->taille.y ) * 2 ); i++) {
        if (jeu->matrice_connexite_route[(int)nouveau->cases_adjacentes[i].y][(int)nouveau->cases_adjacentes[i].x] == 1){
            BFS_connexite(jeu,nouveau->cases_adjacentes[i], 1);
            jeu->num_connexite++;
        }
    }
}

void connexite_route_ajout_route(Jeu* jeu, Vector2 route){
    int route_connexe = 0;
    int batiment_connexe;
    Vector2 taille_case;
    taille_case.y = 1;
    taille_case.x = 1;
    Vector2 * coordonnee_adjacente = NULL;
    int nb_coordonnee = initialisation_cases_adjacentes(coordonnee_adjacente,reseau, route);
    for(int i = 0; i < nb_coordonnee; i++){
        if (jeu->matrice_connexite_route[(int)coordonnee_adjacente[i].y][(int)coordonnee_adjacente[i].x] > 10){
            if (jeu->matrice_connexite_route[(int)route.y][(int)route.x] < 2){
                jeu->matrice_connexite_route[(int)route.y][(int)route.x] = jeu->matrice_connexite_route[(int)coordonnee_adjacente[i].y][(int)coordonnee_adjacente[i].x];
            }
            else if(jeu->matrice_connexite_route[(int)route.y][(int)route.x] > jeu->matrice_connexite_route[(int)coordonnee_adjacente[i].y][(int)coordonnee_adjacente[i].x]){
                int num_connexite = jeu->matrice_connexite_route[(int)route.y][(int)route.x];
                for (int j = 0; j < ORDRE_EN_Y; j++) {
                    for (int k = 0; k < ORDRE_EN_X; k++) {
                        if (jeu->matrice_connexite_route[j][k] == num_connexite){
                            jeu->matrice_connexite_route[j][k] = jeu->matrice_connexite_route[(int)coordonnee_adjacente[i].y][(int)coordonnee_adjacente[i].x];
                        }
                    }
                }

            }else{
                int num_connexite = jeu->matrice_connexite_route[(int)coordonnee_adjacente[i].y][(int)coordonnee_adjacente[i].x];
                for (int j = 0; j < ORDRE_EN_Y; j++) {
                    for (int k = 0; k < ORDRE_EN_X; k++) {
                        if (jeu->matrice_connexite_route[j][k] == num_connexite){
                            jeu->matrice_connexite_route[j][k] = jeu->matrice_connexite_route[(int)route.y][(int)route.x];
                        }
                    }
                }
            }
            route_connexe = 1;
        }
    }
    if (route_connexe == 0){
        for (int i = 0; i < nb_coordonnee; i++) {
            if (jeu->matrice_connexite_route[(int)coordonnee_adjacente[i].y][(int)coordonnee_adjacente[i].x] > 1){
                jeu->matrice_connexite_route[(int)route.y][(int)route.x] = jeu->num_connexite;
                batiment_connexe = 1;
            }

        }
        if(batiment_connexe != 0){
            jeu->num_connexite++;
        }
    }
    if(route_connexe || batiment_connexe){
        for (int i = 0; i < nb_coordonnee ; i++) {
            if(jeu->matrice_connexite_route[(int)coordonnee_adjacente[i].y][(int)coordonnee_adjacente[i].x] == 1){
                BFS_connexite(jeu,coordonnee_adjacente[i],jeu->matrice_connexite_route[(int)route.y][(int)route.x]);
            }
        }
    } else{
        jeu->matrice_connexite_route[(int)route.y][(int)route.x] = 1;
    }
}

void connexite_route_destruction_batiment(Jeu* jeu, Vector2 coordonnee_batiment){
    int nb_cases_adjacentes;
    if (jeu->terrain[(int)coordonnee_batiment.y][(int)coordonnee_batiment.x] == reseau){
        if (jeu->matrice_connexite_route[(int)coordonnee_batiment.y][(int)coordonnee_batiment.x] == 1){
            jeu->matrice_connexite_route[(int)coordonnee_batiment.y][(int)coordonnee_batiment.x] = 0;
        }
        else{
            Vector2* cases_adjacentes = NULL;
            nb_cases_adjacentes = initialisation_cases_adjacentes(cases_adjacentes, jeu->terrain[(int)coordonnee_batiment.y][(int)coordonnee_batiment.x], coordonnee_batiment);
            jeu->matrice_connexite_route[(int)coordonnee_batiment.y][(int)coordonnee_batiment.x] = 0;
            for (int i = 0; i < nb_cases_adjacentes; i++) {
                if (jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x]>4){
                    BFS_connexite(jeu,cases_adjacentes[i],jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].x]);
                }
            }
            free(cases_adjacentes);
            cases_adjacentes = NULL;
        }
    }
    else{
        for (int i = 0; i < jeu->batiments[jeu->terrain[(int)coordonnee_batiment.y][(int)coordonnee_batiment.x]]->taille.y; i++) {
            for (int j = 0; j < jeu->batiments[jeu->terrain[(int)coordonnee_batiment.y][(int)coordonnee_batiment.x]]->taille.x; j++) {
                jeu->matrice_connexite_route[(int)coordonnee_batiment.y + i][(int)coordonnee_batiment.x + j] = 0;
            }
        }
    }
}

void connexite_route_destruction_route(Jeu* jeu,Vector2 route){
    if(jeu->matrice_connexite_route[(int)route.y][(int)route.x] != 1) {
        Vector2 *cases_adjacentes = NULL;
        int nb_cases_adjacentes = initialisation_cases_adjacentes(cases_adjacentes, 1, route);
        jeu->matrice_connexite_route[(int)route.y][(int)route.x] = 0;
        for (int i = 0; i < nb_cases_adjacentes; i++) {
            if((jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].y]> 5)
            && (jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].y]) < jeu->num_connexite ) {
                int connexite = jeu->matrice_connexite_route[(int)cases_adjacentes[i].y][(int)cases_adjacentes[i].y];
                for (int j = 0; j < ORDRE_EN_Y; j++) {
                    for (int k = 0; k < ORDRE_EN_X; k++) {
                        if (jeu->matrice_connexite_route[j][k] == connexite){
                            jeu->matrice_connexite_route[j][k] = 1;
                        }
                    }
                }
                BFS_connexite(jeu, cases_adjacentes[i], jeu->num_connexite + i);


            }
        }
        jeu->num_connexite += nb_cases_adjacentes;
    }
    jeu->matrice_connexite_route[(int)route.y][(int)route.x] = 0;
}
