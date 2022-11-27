#include "Jeu.h"

Jeu* initialisation(){
    Jeu* j;
    printf("Destruction de votre ancien fichier de sauvegarde (si vous en aviez un)\n");
    remove(NOM_DU_FICHIER);
    //j = lire_graphe_console(); //psk pas console

    j->argent = ARGENT_DE_DEBUT;
    j->production_eau_restante = 0;
    j->production_elec_restante = 0;
    //initialisation_CONSTANTE(j);

    return j;
}

int difference_entre_2_nombres_VALEURABSOLUE(int a, int b){
    if (a<b){
        return b-a;
    }else return a-b;
}

void detecterCoordonneDouble(Jeu* jeu,int x,int y,int choix){
    Batiment *liste = jeu->batiments[choix];
    Batiment *parcours = liste;
    if(liste != NULL) {
        while (parcours->next != liste) {
            if (parcours->co.x == x && parcours->co.y == y) {
                printf("Coordonnees invalides\n");
            }
            parcours = parcours->next;
        }
    }
}

Batiment* maj_liste_chaine(Batiment *nouveau,Batiment *tail,Batiment * liste){
    if(liste == NULL){
        liste = nouveau;
        liste->next = liste;
    }
    else{
        tail = liste;
        while(tail->next != liste){
            tail = tail->next;
        }
        tail->next = nouveau;
        nouveau->next = liste;
    }return liste;
}

void ajouterBatiment_ListeChainee(Jeu* jeu, int x, int y, int choix){
    Batiment* nouveau = NULL;
    Batiment* tail = NULL;
    Batiment* liste = NULL;

    detecterCoordonneDouble(jeu,x,y,choix);
    nouveau = calloc(1,sizeof(Batiment));
    nouveau->co.x = x;
    nouveau->co.y = y;

    switch (choix) {
        case maison: {
            nouveau->taille.x = TAILLE_MAISON;
            nouveau->taille.y = TAILLE_MAISON;
            //initialisation_case_ajacentes(nouveau->cases_adjacentes,nouveau->co, TAILLE_MAISON, TAILLE_MAISON);
            nouveau->nom = "Maison";
            nouveau->stadeEvolution = 0;
            liste = jeu->batiments[maison];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[maison] = liste;
            compteurNbBatimentListe(jeu,maison);
            break;
        }
        case chateau_deau: {
            nouveau->taille.x = LONGUEUR_BATIMENTS;
            nouveau->taille.y = LARGEUR_BATIMENTS;
            //initialisation_case_ajacentes(nouveau->cases_adjacentes,nouveau->co, TAILLE_MAISON, TAILLE_MAISON);
            nouveau->nom = "Chateau d'eau";
            nouveau->stadeEvolution = 0;
            liste =  jeu->batiments[chateau_deau];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[chateau_deau] = liste;
            compteurNbBatimentListe(jeu,chateau_deau);
            break;
        }
        case usine_electrique: {
            nouveau->taille.x = LONGUEUR_BATIMENTS;
            nouveau->taille.y = LARGEUR_BATIMENTS;
            //initialisation_case_ajacentes(nouveau->cases_adjacentes,nouveau->co, TAILLE_MAISON, TAILLE_MAISON);
            nouveau->nom = "Usine electrique";
            nouveau->stadeEvolution = 0;
            liste =  jeu->batiments[usine_electrique];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[usine_electrique] = liste;
            compteurNbBatimentListe(jeu,usine_electrique);
            break;
        }
        default : {
            break;
        }
    }
}

void afficherM(Jeu* jeu) {
    int nbmaison = 1;
    int nbchateau = 1;
    int nbusine = 1;
    Batiment *listeMaison = jeu->batiments[maison];
    Batiment *listeChateau = jeu->batiments[chateau_deau];
    Batiment *listeUsine = jeu->batiments[usine_electrique];

    if(listeMaison != NULL) {
        do {
            printf("Maison %d : x: %d  y: %d    stade: %d\n", nbmaison, listeMaison->co.x, listeMaison->co.y,listeMaison->stadeEvolution);
            nbmaison++;
            listeMaison = listeMaison->next;

        } while (listeMaison != jeu->batiments[maison]);
    }
    else{printf("Liste maison vide\n");}

    if(listeChateau != NULL) {
        do {
            printf("Chateau d'eau %d : x: %d  y: %d\n", nbchateau, listeChateau->co.y, listeChateau->co.y);
            nbchateau++;
            listeChateau = listeChateau->next;

        } while (listeChateau != jeu->batiments[chateau_deau]);
    }
    else{printf("Liste chateau eau vide\n");}

    if(listeUsine != NULL) {
        do {
            printf("Usine electrique %d : x: %d   y: %d\n", nbusine, listeUsine->co.x, listeUsine->co.y);
            nbusine++;
            listeUsine = listeUsine->next;

        } while (listeUsine != jeu->batiments[usine_electrique]);
    }
    else{printf("Liste usine electrique vide\n");}
}

Batiment* maj_DeCompteur(Jeu* jeu, Batiment* liste){
    Batiment* parcours = liste;
    if(liste != NULL){
        do{
            if (parcours->numero > jeu->numero_maillon_supprime){
                parcours->numero--;
            }
            parcours = parcours->next;
        }while(parcours != liste);
        liste->nb_batiment--;
    }
    return liste;
}

void decompteurNbBatimentListe(Jeu* jeu,int choix) {
    Batiment *liste = NULL;
    switch (choix) {
        case maison: {
            liste = jeu->batiments[maison];
            liste = maj_DeCompteur(jeu, liste);
            jeu->batiments[maison] = liste;
            break;
        }
        case chateau_deau: {
            liste = jeu->batiments[chateau_deau];
            liste = maj_DeCompteur(jeu, liste);
            jeu->batiments[chateau_deau] = liste;
            break;
        }
        case usine_electrique: {
            liste = jeu->batiments[usine_electrique];
            liste = maj_DeCompteur(jeu, liste);
            jeu->batiments[usine_electrique] = liste;
            break;
        }
    }
}

Batiment* maj_destruction_maillon(Batiment* liste,int x,int y,Jeu* jeu) {
    if (liste != NULL) {
        Batiment *parcour = liste;
        Batiment *prev = liste;

        while (parcour->co.x != x || parcour->co.y != y){
            if (parcour->next == liste) {
                printf("Coordonnees invalides\n");
            }
            parcour = parcour->next;
        }

        do{
            prev = prev->next;
        }
        while (prev->next != parcour);

        if (parcour == liste) {
            liste = liste->next;
        }
        prev->next = parcour->next;
        if (liste == parcour) {
            liste = NULL;
        }
        free(parcour);
    }
    else{printf("Liste vide.\n");}

    return liste;
}

void detruireBatiment(Jeu* jeu,int x,int y,int choix) {
    Batiment *liste = NULL;
    switch (choix) {
        case maison: {
            if (jeu->batiments[maison] != NULL) {
                liste = jeu->batiments[maison];
                liste = maj_destruction_maillon(liste,x,y,jeu);
                jeu->batiments[maison] = liste;
                compteurNbBatimentListe(jeu,maison);
            }
            break;
        }
        case chateau_deau: {
            if (jeu->batiments[chateau_deau] != NULL) {
                liste = jeu->batiments[chateau_deau];
                liste = maj_destruction_maillon(liste,x,y,jeu);
                jeu->batiments[chateau_deau] = liste;
                compteurNbBatimentListe(jeu,chateau_deau);
            }
            break;
        }
        case usine_electrique: {
            if (jeu->batiments[usine_electrique] != NULL) {
                liste = jeu->batiments[usine_electrique];
                liste = maj_destruction_maillon(liste,x,y,jeu);
                jeu->batiments[usine_electrique] = liste;
                compteurNbBatimentListe(jeu,usine_electrique);
            }
            break;
        }
        default :{
            break;
        }
    }
}

void stocker(int nb,FILE* ifs){
    int n = 0;
    for(int i = 0; i < nb;i++){
        fscanf(ifs,"%d",&n);
    }
}
// dizaine type de batiment unite evolution
Batiment* maj_charge_liste(Jeu* jeu,Batiment* liste,int* x,int y,FILE* ifs,int choix,int stadeEvo){
    Batiment* parcours = liste;
    bool bouclePasse = 0;

    if(liste == NULL) {
        ajouterBatiment_ListeChainee(jeu, (*x), y, choix);
        jeu->batiments[choix]->enCours = 1;
        if(choix == maison){
            jeu->batiments[choix]->stadeEvolution = stadeEvo;
        }
        (*x) = (*x) + jeu->batiments[choix]->taille.x - 1;
        stocker(jeu->batiments[choix]->taille.x - 1,ifs);

    }
    else {
        do {
            bool conditionVerifie = 0;
            switch (choix) {
                case maison: {
                    if (((y == parcours->co.y + 2 && (*x) == parcours->co.x) ||
                         (y == parcours->co.y + 1 && (*x) == parcours->co.x)) &&
                        parcours->enCours == 1) {
                        conditionVerifie = 1;
                    }
                    break;
                }
                default: {
                    if (((y == parcours->co.y+ 3 && (*x) == parcours->co.x) ||
                         (y == parcours->co.y + 2 && (*x) == parcours->co.x) ||
                         (y == parcours->co.y + 1 && (*x) == parcours->co.x)) &&
                        parcours->enCours == 1) {
                        conditionVerifie = 1;
                    }
                }
            }
            if (conditionVerifie == 1) {
                (*x) = (*x) + jeu->batiments[choix]->taille.x - 1;
                stocker(jeu->batiments[choix]->taille.x - 1, ifs);
                if (y == parcours->co.y + jeu->batiments[choix]->taille.x - 1) {
                    parcours->enCours = 0;
                }
                bouclePasse = 1;
            }

            parcours = parcours->next;
        }while(parcours != jeu->batiments[choix]);

        if(bouclePasse == 0) {
            ajouterBatiment_ListeChainee(jeu, (*x), y, choix);
            Batiment *parcoursbis = liste;
            while (parcoursbis->next != liste) {
                parcoursbis = parcoursbis->next;
            }
            parcoursbis->co.y = y;
            parcoursbis->co.x = (*x);
            parcoursbis->enCours = 1;
            if(choix == maison){
                parcoursbis->stadeEvolution = stadeEvo;
            }
            (*x) = (*x) + jeu->batiments[choix]->taille.x - 1;
            stocker(jeu->batiments[choix]->taille.x - 1, ifs);
        }
    }
    return jeu->batiments[choix];
}

void chargementListe(Jeu* jeu,int num,int y,int* x,FILE** ifs,int stadeEvo){
    Batiment* liste = NULL;

    switch(num){
        case 2:{
            liste = jeu->batiments[maison];
            liste = maj_charge_liste(jeu,liste,x,y,*ifs,maison,stadeEvo);
            jeu->batiments[maison] = liste;
            break;
        }
        case 3:{
            liste = jeu->batiments[chateau_deau];
            liste = maj_charge_liste(jeu,liste,x,y,*ifs,chateau_deau,stadeEvo);
            jeu->batiments[chateau_deau] = liste;
            break;
        }
        case 4:{
            liste = jeu->batiments[usine_electrique];
            liste = maj_charge_liste(jeu,liste,x,y,*ifs,usine_electrique,stadeEvo);
            jeu->batiments[usine_electrique] = liste;
            break;
        }
    }
}

void liberationListe(Jeu* jeu) {
    if (jeu->batiments[maison] != NULL) {
        Batiment *parcour = jeu->batiments[maison];
        Batiment *prochain = NULL;
        do {
            prochain = parcour->next;
            free(parcour);
            parcour = prochain;

        } while (parcour != jeu->batiments[maison]);
        jeu->batiments[maison] = NULL;
    }

    if (jeu->batiments[chateau_deau] != NULL) {
        Batiment *parcour = jeu->batiments[chateau_deau];
        Batiment *prochain = NULL;
        do {
            prochain = parcour->next;
            free(parcour);
            parcour = prochain;

        } while (parcour != jeu->batiments[chateau_deau]);
        jeu->batiments[chateau_deau] = NULL;
    }

    if (jeu->batiments[usine_electrique] != NULL) {
        Batiment *parcour = jeu->batiments[usine_electrique];
        Batiment *prochain = NULL;
        do {
            prochain = parcour->next;
            free(parcour);
            parcour = prochain;

        } while (parcour != jeu->batiments[usine_electrique]);
        jeu->batiments[usine_electrique] = NULL;
    }
    jeu->batiments[maison] = NULL;
    jeu->batiments[chateau_deau] = NULL;
    jeu->batiments[usine_electrique] = NULL;
}

bool verifier_batiment_a_cote_route(Jeu *jeu, int type_de_batiment, int co_x, int co_y) {
    int nb_connexion = 0;
    switch (type_de_batiment) {
        case maison : {
            for (int i = 0; i < TAILLE_MAISON; i++) {
                if (co_y != 0 && (jeu->terrain[co_y - 1][co_x + i] == 1)) {
                    nb_connexion++;
                }
                if (co_x != 0 && (jeu->terrain[co_y + i][co_x - 1] == 1)) {
                    nb_connexion++;
                }
                if (co_y != ORDRE_EN_Y && (jeu->terrain[co_y + TAILLE_MAISON][co_x + i] == 1)) {
                    nb_connexion++;
                }
                if (co_x != ORDRE_EN_X && (jeu->terrain[co_y + i][co_x + TAILLE_MAISON] == 1)) {
                    nb_connexion++;
                }
            }
            return (nb_connexion != 0) ? true : false;
        }
        case chateau_deau :
        case usine_electrique : {
            for (int i = 0; i < LARGEUR_BATIMENTS; i++) {
                if (co_x != 0 && (jeu->terrain[co_y + i][co_x - 1] == 1)) {
                    nb_connexion++;
                }
                if (co_x != ORDRE_EN_X && (jeu->terrain[co_y + i][co_x + LONGUEUR_BATIMENTS] == 1)) {
                    nb_connexion++;
                }
            }
            for (int i = 0; i < LONGUEUR_BATIMENTS; i++) {
                if (co_y != 0 && (jeu->terrain[co_y - 1][co_x + i] == 1)) {
                    nb_connexion++;
                }
                if (co_y != ORDRE_EN_Y && (jeu->terrain[co_y + LARGEUR_BATIMENTS][co_x + i] == 1)) {
                    nb_connexion++;
                }
            }
            return (nb_connexion != 0) ? true : false;
        }
        default: {
            break;
        }
    }

}


int conditionAchatBatiment(Jeu* jeu,int choix){
    switch(choix){
        case maison:{
            if(jeu->argent >= COUT_MAISON){
                jeu->argent = jeu->argent - COUT_MAISON;
                return 1;
            }
            break;
        }
        case chateau_deau:{
            if(jeu->argent >= COUT_CHATEAU_EAU){
                jeu->production_eau_restante += CAPACITE_CHATEAU_EAU;
                jeu->argent = jeu->argent - COUT_CHATEAU_EAU;
                return 1;
            }
            break;
        }
        case usine_electrique:{
            if(jeu->argent >= COUT_USINE_ELECTRIQUE){
                jeu->production_elec_restante += CAPACITE_USINE;
                jeu->argent = jeu->argent - COUT_USINE_ELECTRIQUE;
                return 1;
            }
            break;
        }
    }
    return 0;
}

Batiment* maj_Compteur(Batiment* liste){
    Batiment* parcours = liste;
    int compteur = 0;
    if(liste != NULL){
        do{
            parcours->numero = compteur;
            compteur++;
            parcours = parcours->next;
        }while(parcours != liste);
        liste->nb_batiment = compteur;
    }
    return liste;
}

void compteurNbBatimentListe(Jeu* jeu,int choix) {
    Batiment *liste = NULL;
    switch (choix) {
        case maison: {
            liste = jeu->batiments[maison];
            liste = maj_Compteur(liste);
            jeu->batiments[maison] = liste;
            break;
        }
        case chateau_deau: {
            liste = jeu->batiments[chateau_deau];
            liste = maj_Compteur(liste);
            jeu->batiments[chateau_deau] = liste;
            break;
        }
        case usine_electrique: {
            liste = jeu->batiments[usine_electrique];
            liste = maj_Compteur(liste);
            jeu->batiments[usine_electrique] = liste;
            break;
        }
    }
}

void maj_reatribution_eau(Jeu* jeu,int numeroChateauEau){

    Stockage_batiment tabMaison[jeu->batiments[maison]->nb_batiment];
    Stockage_batiment tabMaisonPlusProche[jeu->batiments[maison]->nb_batiment];
    int nbCaseTabMaison = 0, nbCasetabMaisonPlusProche = 0;
    int eauDistrib;

    //Parcours matrice deux dimensions et recuperation des maisons connexe au chateau eau
    for(int i = 0;i < jeu->batiments[maison]->nb_batiment;i++){
        for(int j = 0;j < jeu->batiments[chateau_deau]->nb_batiment;j++){
            if(jeu->matrice_connexite_eau[i][j].distance > 0){
                tabMaison[nbCaseTabMaison].distance = jeu->matrice_connexite_eau[i][j].distance;
                tabMaison[nbCaseTabMaison].numero_batiment = j;
                tabMaison[nbCaseTabMaison].numero_maison = i;
                nbCaseTabMaison++;
            }
        }
    }

    //Tri par ordre croissant des distances
    while(nbCaseTabMaison != nbCasetabMaisonPlusProche) {
        int plusProche = 10000;
        for (int i = 0; i <= nbCaseTabMaison; i++) {
            if ( tabMaison[nbCaseTabMaison].distance< plusProche) {
                tabMaisonPlusProche[nbCasetabMaisonPlusProche].distance = tabMaison[nbCaseTabMaison].distance;
                tabMaisonPlusProche[nbCasetabMaisonPlusProche].numero_batiment = tabMaison[nbCaseTabMaison].numero_batiment;
                tabMaisonPlusProche[nbCasetabMaisonPlusProche].numero_maison = tabMaison[nbCaseTabMaison].numero_maison;
                plusProche = tabMaison[nbCaseTabMaison].distance;
                nbCasetabMaisonPlusProche++;
            }
        }
    }

    //Attribution
    //while(eauDistrib != jeu->batiments[chateau_deau]->nb_batiment * CAPACITE_CHATEAU_EAU){
    //}

}


int verificationElec(Jeu* jeu,int num,int nbHabitantEnPlus) {
    int elecDistribueParUsineConnexe = 0;
    Stockage_batiment tabUsineElec[jeu->batiments[usine_electrique]->nb_batiment];
    int nbCaseTab = 0;

    for (int i = 0; i < jeu->batiments[usine_electrique]->nb_batiment; i++) {
        if (jeu->matrice_connexite_electricite[num][i].connexite >= 1) {
            tabUsineElec[nbCaseTab].numero_batiment = i;
            tabUsineElec[i].numero_maison = num;
            nbCaseTab++;
        }
    }

    for (int i = 0; i < nbCaseTab; i++) {
        for (int j = 0; j < jeu->batiments[maison]->nb_batiment; j++) {
            elecDistribueParUsineConnexe = jeu->matrice_connexite_electricite[i][tabUsineElec[i].numero_batiment].capacite_utilise;
        }
    }

    if (elecDistribueParUsineConnexe + nbHabitantEnPlus <= CAPACITE_USINE * nbCaseTab) {
        int compteur = 0;
        while(nbHabitantEnPlus != 0){
            int ajoutElec = 0;
            ajoutElec = CAPACITE_USINE - jeu->matrice_connexite_electricite[num][tabUsineElec[compteur].numero_batiment].capacite_utilise;
            if(ajoutElec > nbHabitantEnPlus){
                ajoutElec = nbHabitantEnPlus;
                jeu->matrice_connexite_electricite[num][tabUsineElec[compteur].numero_batiment].capacite_utilise = jeu->matrice_connexite_electricite[num][tabUsineElec[compteur].numero_batiment].capacite_utilise + ajoutElec;
                nbHabitantEnPlus = 0;
            }
            else{
                jeu->matrice_connexite_electricite[num][tabUsineElec[compteur].numero_batiment].capacite_utilise = jeu->matrice_connexite_electricite[num][tabUsineElec[compteur].numero_batiment].capacite_utilise + ajoutElec;
                nbHabitantEnPlus = nbHabitantEnPlus - ajoutElec;
            }
        }
        return 1;
    }
    return 0;
}

void ajoutEau(Jeu* jeu,int numMaison,int numChateauEau,int quantite){
    jeu->matrice_connexite_eau[numMaison][numChateauEau].capacite_utilise = jeu->matrice_connexite_eau[numMaison][numChateauEau].capacite_utilise + quantite;
}

void evolutionBatiment(Jeu* jeu,int num) {
    Batiment *listeMaison = jeu->batiments[maison];
    Batiment *parcoursMaison = listeMaison;
    Stockage_batiment tabChateauEau[jeu->batiments[chateau_deau]->nb_batiment];
    Stockage_batiment tabChateauEauPlusProche[jeu->batiments[chateau_deau]->nb_batiment];
    int nbCaseTabChateauEau = 0, nbCasetabChateauEauPlusProche = 0;
    int eauDistribueParLeChateau = 0;
    int eauDispoParLesChateauxConnexes = 0;

    if (jeu->choix_politique == communisme) {

        //Récupère tous les chateaux d'eau connexe à la maison
        for (int i = 0; i < jeu->batiments[chateau_deau]->nb_batiment; i++) {
            if (jeu->matrice_connexite_eau[num][i].connexite >= 1) {
                tabChateauEau[nbCaseTabChateauEau].distance = jeu->matrice_connexite_eau[num][i].distance;
                tabChateauEau[nbCaseTabChateauEau].numero_maison = num;
                tabChateauEau[nbCaseTabChateauEau].numero_batiment = i;
                eauDispoParLesChateauxConnexes = CAPACITE_CHATEAU_EAU - jeu->matrice_connexite_eau[num][i].capacite_utilise;
                nbCaseTabChateauEau++;
            }
        }

        //Tri des chateau d'eau par rapport à sa distance (ordre croissant)
        while (nbCasetabChateauEauPlusProche != nbCaseTabChateauEau) {
            int plusProche = 10000;
            for (int i = 0; i <= nbCaseTabChateauEau; i++) {
                if (tabChateauEauPlusProche[nbCasetabChateauEauPlusProche].distance < plusProche) {
                    tabChateauEauPlusProche[nbCasetabChateauEauPlusProche].distance = i;
                    tabChateauEauPlusProche[nbCasetabChateauEauPlusProche].numero_batiment = tabChateauEau[i].numero_batiment;
                    tabChateauEauPlusProche[nbCasetabChateauEauPlusProche].numero_maison = num;
                    nbCasetabChateauEauPlusProche++;
                }
            }
        }

        int k = 0;
        bool finBoucle = FALSE;
        while (k != nbCasetabChateauEauPlusProche || finBoucle != TRUE) {
            //Calcul du nombre d'eau distrib par le chateau d'eau
            for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
                eauDistribueParLeChateau = jeu->matrice_connexite_eau[i][tabChateauEauPlusProche[k].numero_batiment].capacite_utilise;
            }


            do {
                parcoursMaison = parcoursMaison->next;
            } while (parcoursMaison->numero != num);

            if (eauDistribueParLeChateau < CAPACITE_CHATEAU_EAU) {
                //On regarde si le chateau peu distribuer plus
                switch (parcoursMaison->stadeEvolution) {
                    case 0: {
                        if (CAPACITE_CHATEAU_EAU - (eauDistribueParLeChateau + HABITANT_NIVEAU_MAISON1) >= 0) {
                            if (verificationElec(jeu, num, HABITANT_NIVEAU_MAISON1)) {
                                finBoucle = TRUE;
                                parcoursMaison->stadeEvolution++;
                                ajoutEau(jeu,num,tabChateauEauPlusProche[k].numero_batiment,HABITANT_NIVEAU_MAISON1);
                            }
                        } else {
                            if(eauDispoParLesChateauxConnexes >= HABITANT_NIVEAU_MAISON1){
                                ajoutEau(jeu,num,tabChateauEauPlusProche[k].numero_batiment,CAPACITE_CHATEAU_EAU-eauDistribueParLeChateau);
                                parcoursMaison->stadeEvolution++;
                            }
                        }
                        break;
                    }
                    case 1: {
                        if (CAPACITE_CHATEAU_EAU - (eauDistribueParLeChateau + HABITANT_NIVEAU_MAISON2) >= 0) {
                            if (verificationElec(jeu, num, HABITANT_NIVEAU_MAISON2)) {
                                finBoucle = TRUE;
                                parcoursMaison->stadeEvolution++;
                                ajoutEau(jeu,num,tabChateauEauPlusProche[k].numero_batiment,HABITANT_NIVEAU_MAISON1);
                            } else {
                                if(eauDispoParLesChateauxConnexes >= HABITANT_NIVEAU_MAISON2){
                                    ajoutEau(jeu,num,tabChateauEauPlusProche[k].numero_batiment,CAPACITE_CHATEAU_EAU-eauDistribueParLeChateau);
                                    parcoursMaison->stadeEvolution++;
                                }
                            }
                        }
                        break;
                    }
                    case 2: {
                        if (CAPACITE_CHATEAU_EAU - (eauDistribueParLeChateau + HABITANT_NIVEAU_MAISON3) >= 0) {
                            if (verificationElec(jeu, num, HABITANT_NIVEAU_MAISON3)) {
                                finBoucle = TRUE;
                                parcoursMaison->stadeEvolution++;
                                ajoutEau(jeu,num,tabChateauEauPlusProche[k].numero_batiment,HABITANT_NIVEAU_MAISON1);
                            } else {
                                if(eauDispoParLesChateauxConnexes >= HABITANT_NIVEAU_MAISON3){
                                    ajoutEau(jeu,num,tabChateauEauPlusProche[k].numero_batiment,CAPACITE_CHATEAU_EAU-eauDistribueParLeChateau);
                                    parcoursMaison->stadeEvolution++;
                                }
                            }
                        }
                        break;
                    }
                    case 3: {
                        if (CAPACITE_CHATEAU_EAU - (eauDistribueParLeChateau + HABITANT_NIVEAU_MAISON4) >= 0) {
                            if (verificationElec(jeu, num, HABITANT_NIVEAU_MAISON4)) {
                                finBoucle = TRUE;
                                parcoursMaison->stadeEvolution++;
                                ajoutEau(jeu,num,tabChateauEauPlusProche[k].numero_batiment,HABITANT_NIVEAU_MAISON1);
                            } else {
                                if(eauDispoParLesChateauxConnexes >= HABITANT_NIVEAU_MAISON4){
                                    ajoutEau(jeu,num,tabChateauEauPlusProche[k].numero_batiment,CAPACITE_CHATEAU_EAU-eauDistribueParLeChateau);
                                    parcoursMaison->stadeEvolution++;
                                }
                            }
                        }
                        break;
                    }
                }
            }
            k++;
        }
    }
}


/*Coordonnee* initialisation_case_ajacentes(Coordonnee coordonnee_batiment,int longueur, int hauteur ){
    Coordonnee* case_adjacente = malloc((longueur+hauteur)*2* sizeof(Coordonnee));
    for (int i = 0; i < longueur*hauteur*2; i++) {
        if (i < hauteur){
            case_adjacente[i].x = coordonnee_batiment.x - 1;
            case_adjacente[i].y = coordonnee_batiment.y + i;
        }
        else if ( i < (hauteur + longueur)){
            case_adjacente[i].x = coordonnee_batiment.x + i - hauteur;
            case_adjacente[i].y = coordonnee_batiment.y + hauteur;
        }
        else if (i < (hauteur*2 + longueur)){
            case_adjacente[i].x = coordonnee_batiment.x + longueur;
            case_adjacente[i].y = coordonnee_batiment.y - i + hauteur*2 + longueur;
        }
        else{
            case_adjacente[i].x = coordonnee_batiment.x - i + hauteur*2 + longueur*2;
            case_adjacente[i].y = coordonnee_batiment.y - 1;
        }
    }
    return case_adjacente;
}

    printf("Nb cases adjacences : %d", nb_cases_adjacentes);
    for (int i = 0; i < nb_cases_adjacentes; ++i) {
        printf(">> (%d %d)", case_adjacente[i].x, case_adjacente[i].y);
    }
    return nb_cases_adjacentes;
}*/

int initialisation_cases_adjacentes(Vector2 *case_adjacente, int type_de_batiment, Vector2 co_bat) {
    int nb_cases_adjacentes = 0;
    int case_rempli = 0;
    switch (type_de_batiment) {

        case reseau : {
            nb_cases_adjacentes =  4;
            if (co_bat.y == 0) {
                nb_cases_adjacentes --;
            }
            if (co_bat.x == 0) {
                nb_cases_adjacentes --;
            }
             if (co_bat.y == ORDRE_EN_Y - 1 ) {
                nb_cases_adjacentes --;
            }
            if (co_bat.x == ORDRE_EN_X - 1) {
                nb_cases_adjacentes --;
            }
            case_adjacente = malloc(nb_cases_adjacentes * sizeof(Vector2));
            for (int i = 0; i < nb_cases_adjacentes + case_rempli; i++) {
                if (i < 1) {
                    if (co_bat.x != 0) {
                        case_adjacente[i - case_rempli].x = co_bat.x - 1;
                        case_adjacente[i - case_rempli].y = co_bat.y + i;
                    } else {
                        case_rempli += 1;
                        i = 1 - 1;
                    }
                } else if (i < 1 * 2) {
                    if (co_bat.y != ORDRE_EN_Y - 1 ) {
                        case_adjacente[i - case_rempli].x = co_bat.x + i - 1;
                        case_adjacente[i - case_rempli].y = co_bat.y + 1;
                    } else {
                        case_rempli += 1;
                        i = 1 * 2 - 1;
                    }
                } else if (i < 1 * 3) {
                    if (co_bat.x != ORDRE_EN_X - 1 ) {
                        case_adjacente[i - case_rempli].x = co_bat.x + 1;
                        case_adjacente[i - case_rempli].y = co_bat.y - i + 1 * 3 - 1;
                    } else {
                        case_rempli += 1;
                        i = 1 * 3 - 1;
                    }
                } else {
                    if (co_bat.y != 0) {
                        case_adjacente[i - case_rempli].x = co_bat.x - i + 1 * 4 - 1;
                        case_adjacente[i - case_rempli].y = co_bat.y - 1;
                    }
                }

            }
            break;
        }


        case maison : {
            nb_cases_adjacentes = TAILLE_MAISON * 4;
            if (co_bat.y == 0) {
                nb_cases_adjacentes -= TAILLE_MAISON;
            }
            if (co_bat.x == 0) {
                nb_cases_adjacentes -= TAILLE_MAISON;
            }
            if (co_bat.y == ORDRE_EN_Y - TAILLE_MAISON ) {
                nb_cases_adjacentes -= TAILLE_MAISON;
            }
            if (co_bat.x == ORDRE_EN_X - TAILLE_MAISON ) {
                nb_cases_adjacentes -= TAILLE_MAISON;
            }
            case_adjacente = malloc(nb_cases_adjacentes * sizeof(Vector2));
            for (int i = 0; i < nb_cases_adjacentes + case_rempli; i++) {
                if (i < TAILLE_MAISON) {
                    if (co_bat.x != 0) {
                        case_adjacente[i - case_rempli].x = co_bat.x - 1;
                        case_adjacente[i - case_rempli].y = co_bat.y + i;
                    } else {
                        case_rempli += TAILLE_MAISON;
                        i = TAILLE_MAISON - 1;
                    }
                } else if (i < TAILLE_MAISON * 2) {
                    if (co_bat.y != ORDRE_EN_Y - TAILLE_MAISON ) {
                        case_adjacente[i - case_rempli].x = co_bat.x + i - TAILLE_MAISON;
                        case_adjacente[i - case_rempli].y = co_bat.y + TAILLE_MAISON;
                    } else {
                        case_rempli += TAILLE_MAISON;
                        i = TAILLE_MAISON * 2 - 1;
                    }
                } else if (i < TAILLE_MAISON * 3) {
                    if (co_bat.x != ORDRE_EN_X - TAILLE_MAISON ) {
                        case_adjacente[i - case_rempli].x = co_bat.x + TAILLE_MAISON;
                        case_adjacente[i - case_rempli].y = co_bat.y - i + TAILLE_MAISON * 3 - 1;
                    } else {
                        case_rempli += TAILLE_MAISON;
                        i = TAILLE_MAISON * 3 - 1;
                    }
                } else {
                    if (co_bat.y != 0) {
                        case_adjacente[i - case_rempli].x = co_bat.x - i + TAILLE_MAISON * 4 - 1;
                        case_adjacente[i - case_rempli].y = co_bat.y - 1;
                    }
                }

            }
            break;
        }
        case chateau_deau :
        case usine_electrique : {
            nb_cases_adjacentes = LARGEUR_BATIMENTS * 2 + LONGUEUR_BATIMENTS * 2;
            if (co_bat.y == 0) {
                nb_cases_adjacentes -= LONGUEUR_BATIMENTS;
            }
            if (co_bat.x == 0) {
                nb_cases_adjacentes -= LARGEUR_BATIMENTS;
            }
            if (co_bat.y == ORDRE_EN_Y - LARGEUR_BATIMENTS ) {
                nb_cases_adjacentes -= LARGEUR_BATIMENTS;
            }
            if (co_bat.x == ORDRE_EN_X - LONGUEUR_BATIMENTS ) {
                nb_cases_adjacentes -= LONGUEUR_BATIMENTS;
            }
            case_adjacente = malloc(nb_cases_adjacentes * sizeof(Vector2));
            for (int i = 0; i < nb_cases_adjacentes + case_rempli; i++) {
                if (i < LARGEUR_BATIMENTS) {
                    if (co_bat.x != 0) {
                        case_adjacente[i - case_rempli].x = co_bat.x - 1;
                        case_adjacente[i - case_rempli].y = co_bat.y + i;
                    } else {
                        case_rempli += LARGEUR_BATIMENTS;
                        i = LARGEUR_BATIMENTS - 1;
                    }
                } else if (i < LARGEUR_BATIMENTS + LONGUEUR_BATIMENTS) {
                    if (co_bat.x != ORDRE_EN_X - LONGUEUR_BATIMENTS ) {
                        case_adjacente[i - case_rempli].x = co_bat.x + i - LARGEUR_BATIMENTS;
                        case_adjacente[i - case_rempli].y = co_bat.y + LARGEUR_BATIMENTS;
                    } else {
                        case_rempli += LONGUEUR_BATIMENTS;
                        i = LARGEUR_BATIMENTS + LONGUEUR_BATIMENTS - 1;
                    }
                } else if (i < LARGEUR_BATIMENTS * 2 + LONGUEUR_BATIMENTS) {
                    if (co_bat.y != ORDRE_EN_Y - LARGEUR_BATIMENTS ) {
                        case_adjacente[i - case_rempli].x = co_bat.x + LONGUEUR_BATIMENTS;
                        case_adjacente[i - case_rempli].y = co_bat.y - i + LARGEUR_BATIMENTS * 2 + LONGUEUR_BATIMENTS - 1;
                    } else {
                        case_rempli += LARGEUR_BATIMENTS;
                        i = LARGEUR_BATIMENTS * 2 + LONGUEUR_BATIMENTS - 1;
                    }
                } else {
                    if (co_bat.y != 0) {
                        case_adjacente[i - case_rempli].x = co_bat.x - i + LARGEUR_BATIMENTS * 2 + LONGUEUR_BATIMENTS * 2 - 1;
                        case_adjacente[i - case_rempli].y = co_bat.y - 1;
                    }
                }
            }
            break;
        }
        default: {
            break;
        }
    }

    printf("Nb cases adjacences : %d", nb_cases_adjacentes);
    for (int i = 0; i < nb_cases_adjacentes; ++i) {
        printf(">> (%d %d)", (int)case_adjacente[i].x, (int)case_adjacente[i].y);
    }
    return nb_cases_adjacentes;
}
