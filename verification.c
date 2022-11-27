#include "verification.h"

// 1 quand pas d obstacle
// 0 quand obstacle
//
bool verif_achat_route(Jeu* jeu){
    if (jeu->argent >= COUT_ROUTE){
        jeu->argent -= COUT_ROUTE;
        return 1;
    }else {

        return 0;
    }
}

bool verification_colision_batiment(Jeu* jeu, int nomDuBatiment){
    int co_x = (int)jeu->selection.x-1;
    int co_y = (int)jeu->selection.y-1;
    if (nomDuBatiment == reseau){
        if ((co_x + 1)<0 || (co_y + 1)<0) return 0;
        else if (jeu->terrain[co_y + 1][co_x + 1] != 0) return 0;
    }
    else if (nomDuBatiment == maison){
        for (int i = 0; i < TAILLE_MAISON ; i++) {
            for (int j = 0; j < TAILLE_MAISON; j++) {
                if (jeu->terrain[co_y + i][co_x + j] != 0) return 0;
            }
        }
    }
    else if (nomDuBatiment == usine_electrique || nomDuBatiment == chateau_deau){
        for (int i = 0; i < LARGEUR_BATIMENTS ; i++) {
            for (int j = 0; j < LONGUEUR_BATIMENTS; j++) {
                if (jeu->terrain[co_y + i][co_x + j] != 0){
                    return 0;
                }
            }
        }

    }
    return 1;
}

bool verification_batiment_peut_se_placer(Jeu* jeu, int nomDuBatiment, Vector2 pos_ini_batiment){
    int longueur;
    int largeur;
    Vector2 pos_souris = GetMousePosition();
    if (pos_souris.x <0 || pos_souris.y <0 || pos_souris.x > TAILLE_CASE_GRILLE*jeu->ordre.x || pos_souris.y> TAILLE_CASE_GRILLE*jeu->ordre.y) {
        return 0;
    } else{
        switch (nomDuBatiment) {
            case reseau:
                if (pos_ini_batiment.x >= 0 && pos_ini_batiment.y >= 0 && pos_ini_batiment.x <= jeu->ordre.x && pos_ini_batiment.y <= jeu->ordre.y){
                    if (verification_colision_batiment(jeu, nomDuBatiment) == 1) return 1;
                }
                return 0;
            case maison:
                longueur = TAILLE_MAISON;
                largeur = TAILLE_MAISON; //car c'est un carre pour la maison
                if (pos_ini_batiment.x >= 0 && pos_ini_batiment.y >= 0 && pos_ini_batiment.x + longueur <= jeu->ordre.x && pos_ini_batiment.y + largeur <= jeu->ordre.y){
                    if (verification_colision_batiment(jeu, nomDuBatiment) == 1) return 1;
                }
                return 0;
            case usine_electrique:
            case chateau_deau:
                longueur = LONGUEUR_BATIMENTS;
                largeur = LARGEUR_BATIMENTS;
                if (pos_ini_batiment.x >= 0 && pos_ini_batiment.y >= 0 && pos_ini_batiment.x + longueur <= jeu->ordre.x && pos_ini_batiment.y + largeur <= jeu->ordre.y) {
                    if (verification_colision_batiment(jeu, nomDuBatiment) == 1) return 1;
                }
                return 0;
            default:
                return 0;
        }
    }
}

void ajout_batiment_terrain(Jeu* jeu, int nomDuBatiment, Vector2 pos1) {
    if (nomDuBatiment != reseau) {
        for (int y = 0; y < (int)jeu->batiments[nomDuBatiment]->taille.y; y++) {
            for (int x = 0; x < (int)jeu->batiments[nomDuBatiment]->taille.x; x++) {
                jeu->terrain[(int) pos1.y + y][(int) pos1.x + x] = nomDuBatiment;
            }
        }
        printf("%s construite\n", jeu->batiments[nomDuBatiment]->nom);
    } else {
        jeu->terrain[(int) pos1.y][(int) pos1.x] = reseau;
    }
}

void suppression_batiment_terrain(Jeu* jeu, Vector2 pos1, int typeDeBatiment){
    switch (typeDeBatiment) {
        case vide:
            break;
        case reseau:
            jeu->terrain[(int)pos1.y][(int)pos1.x] = vide;
            printf("DESTRUCTION\n");
            break;
        case maison:
            detruireBatiment(jeu, (int)pos1.x, (int)pos1.y, maison);
            for (int i = 0; i < TAILLE_MAISON; i++) {
                for (int j = 0; j < TAILLE_MAISON; j++) {
                    jeu->terrain[(int)pos1.y + i][(int)pos1.x + j] = vide;
                }
            }
            break;
        case chateau_deau:
            detruireBatiment(jeu, (int)pos1.x, (int)pos1.y, chateau_deau);
            for (int i = 0; i < LARGEUR_BATIMENTS; i++) {
                for (int j = 0; j < LONGUEUR_BATIMENTS; j++) {
                    jeu->terrain[(int)pos1.y + i][(int)pos1.x + j] = vide;
                }
            }
            break;
        case usine_electrique:
            detruireBatiment(jeu, (int)pos1.x, (int)pos1.y, usine_electrique);
            for (int i = 0; i < LARGEUR_BATIMENTS; i++) {
                for (int j = 0; j < LONGUEUR_BATIMENTS; j++) {
                    jeu->terrain[((int)pos1.y + i)][((int)pos1.x + j)] = vide;
                }
            }
            break;
        default:
            break;
    }
}
void verif_batiment_suppression(Jeu* jeu){
    Vector2 pos_batiment = position_batiment(jeu, jeu->selection.x, jeu->selection.y);
    if (pos_batiment.x != -1 && pos_batiment.y != -1) {
        int type_de_batiment = jeu->terrain[(int)pos_batiment.y][(int)pos_batiment.x];
        suppression_batiment_terrain(jeu, pos_batiment, type_de_batiment);
    }
}

void poser_batiment(Jeu* jeu){
    Vector2 posBatiment = jeu->selection;
    posBatiment.x -= 1;
    posBatiment.y -= 1;
    Vector2 pos_souris = GetMousePosition();
    Batiment* liste = jeu->batiments[maison];
    Batiment* parcours = liste;
    if (jeu->page_actuel == en_jeu) {
        switch (jeu->mode_de_selection) {
            case mode_neutre:
                break;
            case mode_reseau:
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) jeu->onClickSouris = true;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) jeu->onClickSouris = false;
                if (jeu->onClickSouris == true){
                    if (verification_batiment_peut_se_placer(jeu, reseau, jeu->selection) == 1) {
                        if (verif_achat_route(jeu) == true){
                            ajout_batiment_terrain(jeu, reseau, jeu->selection);
                        }else jeu->timer_message_error = 0;
                    } else jeu->timer_affichage = 0;
                }
                break;
            case mode_maison:
                /*do{
                    parcours = parcours->next;
                }while(liste != parcours);*/
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    if (verification_batiment_peut_se_placer(jeu, maison, posBatiment) == 1) {
                        if(verifier_batiment_a_cote_route(jeu, maison, posBatiment.x, posBatiment.y) == true) {
                            if (conditionAchatBatiment(jeu, maison) == true){
                                ajouterBatiment_ListeChainee(jeu, (int) posBatiment.x, (int) posBatiment.y, maison);
                                ajout_batiment_terrain(jeu, maison, posBatiment);
                            }else jeu->timer_message_error = 0;
                        }
                    } else {
                        jeu->timer_affichage = 0;
                    }

                }
                break;
            case mode_usine:
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (verification_batiment_peut_se_placer(jeu, usine_electrique, posBatiment) == 1) {
                        if(verifier_batiment_a_cote_route(jeu, usine_electrique, posBatiment.x, posBatiment.y) == true) {
                            if (conditionAchatBatiment(jeu, usine_electrique) == true) {
                                ajouterBatiment_ListeChainee(jeu, (int) posBatiment.x, (int) posBatiment.y,usine_electrique);
                                ajout_batiment_terrain(jeu, usine_electrique, posBatiment);
                            }else jeu->timer_message_error = 0;
                        }
                    } else {
                        jeu->timer_affichage = 0;
                    }

                }
                break;
            case mode_chateauDO:
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (verification_batiment_peut_se_placer(jeu, chateau_deau, posBatiment) == 1) {
                        if(verifier_batiment_a_cote_route(jeu, chateau_deau, posBatiment.x, posBatiment.y) == true) {
                            if (conditionAchatBatiment(jeu, chateau_deau) == true) {
                                ajouterBatiment_ListeChainee(jeu, (int) posBatiment.x, (int) posBatiment.y,chateau_deau);
                                ajout_batiment_terrain(jeu, chateau_deau, posBatiment);
                            }else jeu->timer_message_error = 0;
                        }
                    } else {
                        jeu->timer_affichage = 0;
                    }
                }
                break;
            case demolition:
                if (pos_souris.x>0 && pos_souris.y>0 && pos_souris.x<TAILLE_CASE_GRILLE*jeu->ordre.x && pos_souris.y<TAILLE_CASE_GRILLE*jeu->ordre.y){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) jeu->onClickSouris = true;
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) jeu->onClickSouris = false;
                    if (jeu->onClickSouris == true){
                        verif_batiment_suppression(jeu);
                    }
                }
                break;
            default:
                break;
        }
    }
}

void maj_batiment_timer(Jeu* jeu){
    if(jeu->batiments[maison] != NULL) {
        Batiment *list_maison = jeu->batiments[maison];
        for (int m = 0; m < jeu->batiments[maison]->nb_batiment; m++) {
            list_maison->timer++;
            list_maison = list_maison->next;
        }
    }
    if(jeu->batiments[chateau_deau] != NULL) {
        Batiment *list_chateauDO = jeu->batiments[chateau_deau];
        for (int c = 0; c < jeu->batiments[chateau_deau]->nb_batiment; c++) {
            list_chateauDO->timer++;
            list_chateauDO = list_chateauDO->next;
        }
    }
    if(jeu->batiments[usine_electrique] != NULL){
        Batiment* list_usine = jeu->batiments[usine_electrique];
        for (int u = 0; u < jeu->batiments[usine_electrique]->nb_batiment; u++) {
            list_usine->timer++;
            list_usine = list_usine->next;
        }
    }
}

int verif_nb_cases_adjacentes(Jeu* jeu, Vector2 coordonnee_batiment, Vector2 taille){
    int nb_cases_adjacentes = (int)(taille.y + taille.x)*2;
    if (coordonnee_batiment.y == 0 || (coordonnee_batiment.y + taille.y) == ORDRE_EN_Y){
        nb_cases_adjacentes -= (int)taille.x;
    }
    if (coordonnee_batiment.x == 0 || (coordonnee_batiment.x + taille.x) == ORDRE_EN_X){
        nb_cases_adjacentes -= (int)taille.y;
    }
    return nb_cases_adjacentes;
}
int verif_liaison_maison_chateau(Jeu* jeu, Vector2 position){
    int connexite = jeu->matrice_connexite_route[(int)position.y][(int)position.x];
    Batiment* batiment_maison = (Batiment*) calloc(1, sizeof(Batiment));
    Batiment* batiment_chateau = (Batiment*) calloc(1, sizeof(Batiment));
    batiment_maison = jeu->batiments[maison];
    batiment_chateau = jeu->batiments[chateau_deau];
    int ok = 0;
    int ok2 = 0;
    for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
        if(ok ==0 ){
            int num_connexite = verif_nb_cases_adjacentes(jeu,batiment_maison->co,batiment_maison->taille);
            for (int j = 0; j < num_connexite; j++) {
                if((ok == 0) && (jeu->matrice_connexite_route[(int)batiment_maison->cases_adjacentes[j].y][(int)batiment_maison->cases_adjacentes[j].y] == num_connexite)) {
                    ok = num_connexite;
                }
            }
            batiment_maison = batiment_maison->next;
        }
    }
    for (int i = 0; i < jeu->batiments[chateau_deau]->nb_batiment; i++) {
        if(ok2 ==0 ){
            int num_connexite = verif_nb_cases_adjacentes(jeu,batiment_chateau->co,batiment_chateau->taille);
            for (int j = 0; j < num_connexite; j++) {
                if((ok2 == 0) && (jeu->matrice_connexite_route[(int)batiment_chateau->cases_adjacentes[j].y][(int)batiment_chateau->cases_adjacentes[j].y] == num_connexite)) {
                    ok2 = num_connexite;
                }
            }
            batiment_chateau = batiment_chateau->next;
        }
    }
    if (ok && ok2){
        return ok;
    }
    else {
        return 0;
    }
}

int verif_liaison_maison_usine_elec(Jeu* jeu, Vector2 position){
    int connexite = jeu->matrice_connexite_route[(int)position.y][(int)position.x];
    Batiment* batiment_maison = (Batiment*) calloc(1, sizeof(Batiment));
    Batiment* batiment_usine_elec = (Batiment*) calloc(1, sizeof(Batiment));
    batiment_maison = jeu->batiments[maison];
    batiment_usine_elec = jeu->batiments[usine_electrique];
    int ok = 0;
    int ok2 = 0;
    for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
        if(ok ==0 ){
            int num_connexite = verif_nb_cases_adjacentes(jeu,batiment_maison->co,batiment_maison->taille);
            for (int j = 0; j < num_connexite; j++) {
                if((ok == 0) && (jeu->matrice_connexite_route[(int)batiment_maison->cases_adjacentes[j].y][(int)batiment_maison->cases_adjacentes[j].y] == num_connexite)) {
                    ok = num_connexite;
                }
            }
            batiment_maison = batiment_maison->next;
        }
    }
    for (int i = 0; i < jeu->batiments[usine_electrique]->nb_batiment; i++) {
        if(ok2 ==0 ){
            int num_connexite = verif_nb_cases_adjacentes(jeu,batiment_usine_elec->co,batiment_usine_elec->taille);
            for (int j = 0; j < num_connexite; j++) {
                if((ok2 == 0) && (jeu->matrice_connexite_route[(int)batiment_usine_elec->cases_adjacentes[j].y][(int)batiment_usine_elec->cases_adjacentes[j].y] == num_connexite)) {
                    ok2 = num_connexite;
                }
            }
            batiment_usine_elec = batiment_usine_elec->next;
        }
    }
    if (ok && ok2){
        return ok;
    }
    else {
        return 0;
    }
}

/*int* verif_liaison_maison_chateau(Jeu* jeu){
    int nb_cases_adjacentes = 0;
    int nb_cases_adjacentes_prec = 0;
    int num_connexites_maison_chateau[100];
    int x = 0;
    for (int i = 0; i < 100; i++) {
        num_connexites_maison_chateau[i]=0;
    }
    int num_connexite;
    int pas_de_connexite_maison = jeu->batiments[maison]->nb_batiment* 12;
    int pas_de_connexite_chateau = jeu->batiments[chateau_deau]->nb_batiment* 20;
    int num_connexite_maison[jeu->batiments[maison]->nb_batiment * TAILLE_MAISON*4];
    int num_connexite_chateau_eau[jeu->batiments[chateau_deau]->nb_batiment* 20];
    Batiment* batiment = (Batiment*) calloc(1, sizeof(Batiment));
    batiment = jeu->batiments[maison];
    for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
        nb_cases_adjacentes_prec = nb_cases_adjacentes;
        nb_cases_adjacentes += verif_nb_cases_adjacentes(jeu,jeu->matrice_connexite_eau[i][0].batiments[0], jeu->batiments[maison]->taille);
        for (int j = nb_cases_adjacentes_prec; j < nb_cases_adjacentes; j++) {
            num_connexite_maison[j] = jeu->matrice_connexite_route[(int)batiment->cases_adjacentes->y][(int)batiment->cases_adjacentes->x];
        }
        batiment = batiment->next;
    }
    batiment = jeu->batiments[chateau_deau];
    for (int i = 0; i < jeu->batiments[chateau_deau]->nb_batiment; i++) {
        nb_cases_adjacentes_prec = nb_cases_adjacentes;
        nb_cases_adjacentes += verif_nb_cases_adjacentes(jeu,jeu->matrice_connexite_eau[i][1].batiments[0], jeu->batiments[chateau_deau]->taille);
        for (int j = nb_cases_adjacentes_prec; j < nb_cases_adjacentes; j++) {
            num_connexite_chateau_eau[j] = jeu->matrice_connexite_route[(int)batiment->cases_adjacentes->y][(int)batiment->cases_adjacentes->x];
        }
        batiment = batiment->next;
    }
    if (batiment != NULL){
        free(batiment);
        batiment = NULL;
    }
    while((pas_de_connexite_maison && pas_de_connexite_chateau) != 0){
        pas_de_connexite_maison = jeu->batiments[maison]->nb_batiment* 12;
        pas_de_connexite_chateau = jeu->batiments[chateau_deau]->nb_batiment* 20;
        int ok1 = 0;
        int ok2 = 0;

        for (int i = 0; i < jeu->batiments[maison]->nb_batiment * TAILLE_MAISON*4; i++) {
            if ((ok1 == 0) && (num_connexite_maison[i]!= 0)){
                ok1 = num_connexite_maison[i];
                num_connexite_maison[i] = 0;
            }
            if(num_connexite_maison[i] == ok1){
                num_connexite_maison[i]=0;
            }
            if (num_connexite_maison[i] == 0){
                pas_de_connexite_maison--;
            }

        }
        for (int i = 0; i < jeu->batiments[chateau_deau]->nb_batiment* 20; i++) {
            if (num_connexite_chateau_eau[i] == ok1){
                ok2 = ok1;
                num_connexite_chateau_eau[i] == 0;
            }

            if (num_connexite_chateau_eau[i] == 0){
                pas_de_connexite_chateau--;
            }
        }
        while(num_connexites_maison_chateau[x] != 0){
            x++;
        }
        num_connexites_maison_chateau[x] = ok2;
    }
    return num_connexites_maison_chateau;
}*/