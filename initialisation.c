#include "initialisation.h"


void initialisation_Images(Jeu* jeu){
    // TODO: NE PAS OUBLIER DE Unload des imgs apres les avoir mises en texture /!\
    //  AVEC CA :  UnloadImage(jeu->tabImages[NOMDELIMAGE].image2D);

    for (int i = 0; i < nb_pages; i++) {
        for (int j = 0; j < nb_img; j++) {
            jeu->tabImages[i][j].colision_souris = false;
        }
    }

    //pour init une img en boutton
    ini_bouton(jeu);
    jeu->tabImages[menu_principale][img_menu].texture2D = LoadTexture("Menu.png");
    jeu->tabImages[menu_principale][img_menu].charge = 1;

    jeu->tabImages[en_jeu][img_fondJeu1].texture2D = LoadTexture("fond_jeu1.png");
    jeu->tabImages[en_jeu][img_fondJeu1].charge = 1;
    jeu->tabImages[en_jeu][img_fondJeu2].texture2D = LoadTexture("fond_jeu2.png");
    jeu->tabImages[en_jeu][img_fondJeu2].charge = 1;
    jeu->tabImages[en_jeu][img_fondJeu3].texture2D = LoadTexture("fond_jeu3.png");
    jeu->tabImages[en_jeu][img_fondJeu3].charge = 1;
    jeu->tabImages[en_jeu][img_fondJeu4].texture2D = LoadTexture("fond_jeu4.png");
    jeu->tabImages[en_jeu][img_fondJeu4].charge = 1;

    jeu->tabImages[en_jeu][img_logo_warning].texture2D = LoadTexture("logo_warning.png");
    jeu->tabImages[en_jeu][img_logo_warning].charge = 1;

    jeu->tabImages[regles][img_fond_panneau_affichage].texture2D = LoadTexture("affichage.png");
    jeu->tabImages[regles][img_fond_panneau_affichage].charge = 1;

    jeu->tabImages[credis][img_fond_credits].texture2D = LoadTexture("fond_credits.png");
    jeu->tabImages[credis][img_fond_credits].charge = 1;

    jeu->tabImages[en_jeu][img_logosJeu].texture2D = LoadTexture("logoJeu.png");
    jeu->tabImages[en_jeu][img_logosJeu].charge = 1;
    jeu->tabImages[en_jeu][img_logosJeu].frame_longueur = 90;
    jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur = 90;

    jeu->tabImages[en_jeu][img_logo_argent].texture2D = LoadTexture("logo_argent.png");
    jeu->tabImages[en_jeu][img_logo_argent].charge = 1;
    jeu->tabImages[en_jeu][img_logo_eau].texture2D = LoadTexture("logo_eau.png");
    jeu->tabImages[en_jeu][img_logo_eau].charge = 1;
    jeu->tabImages[en_jeu][img_logo_elec].texture2D = LoadTexture("logo_elec.png");
    jeu->tabImages[en_jeu][img_logo_elec].charge = 1;
    jeu->tabImages[en_jeu][img_logo_habitant].texture2D = LoadTexture("logo_habitant.png");
    jeu->tabImages[en_jeu][img_logo_habitant].charge = 1;

    jeu->tabImages[en_jeu][img_demolition].texture2D = LoadTexture("demolition.png");
    jeu->tabImages[en_jeu][img_demolition].charge = 1;

    jeu->tabImages[en_jeu][img_niveau_0].texture2D = LoadTexture("logo_niveau_0.png");
    jeu->tabImages[en_jeu][img_niveau_0].charge = 1;
    jeu->tabImages[en_jeu][img_niveau_1].texture2D = LoadTexture("logo_niveau_1.png");
    jeu->tabImages[en_jeu][img_niveau_1].charge = 1;
    jeu->tabImages[en_jeu][img_niveau_2].texture2D = LoadTexture("logo_niveau_2.png");
    jeu->tabImages[en_jeu][img_niveau_2].charge = 1;

    jeu->tabImages[en_jeu][img_route].texture2D = LoadTexture("route.png");
    jeu->tabImages[en_jeu][img_route].charge = 1;
    jeu->tabImages[en_jeu][img_usine].texture2D = LoadTexture("usine.png");
    jeu->tabImages[en_jeu][img_usine].charge = 1;
    jeu->tabImages[en_jeu][img_chateauDO].texture2D = LoadTexture("chateauDO.png");
    jeu->tabImages[en_jeu][img_chateauDO].charge = 1;
    //chargement texture maison car evolution comprise
    Texture2D texture_maison = LoadTexture("maison.png");
    float frame_longueur= (float)texture_maison.width / NB_FRAMES_MAISON;
    jeu->tabImages[en_jeu][img_maison].texture2D = texture_maison;
    jeu->tabImages[en_jeu][img_maison].charge = 1;
    jeu->tabImages[en_jeu][img_maison].frame_longueur = frame_longueur;
    Rectangle sourceRec = {0, 0, (float)jeu->tabImages[en_jeu][img_maison].frame_longueur, (float)jeu->tabImages[en_jeu][img_maison].texture2D.height };
    jeu->tabImages[en_jeu][img_maison].source_Rec = sourceRec;

    jeu->tabImages[selection_choix_jeu][img_fond_ChoixJeu].texture2D = LoadTexture("fond_choix.png");
    jeu->tabImages[selection_choix_jeu][img_fond_ChoixJeu].charge = 1;
}
void ini_fond_jeu(Jeu* jeu){
    jeu->tabImages[en_jeu][img_fondJeu1].alpha = 0;
    jeu->tabImages[en_jeu][img_fondJeu2].alpha = 0;
    jeu->tabImages[en_jeu][img_fondJeu3].alpha = 0;
    jeu->tabImages[en_jeu][img_fondJeu4].alpha = 0;
}
void ini_bouton(Jeu* jeu){
    jeu->tabImages[menu_principale][img_boutonoff].charge = 1;
    jeu->tabImages[selection_choix_jeu][img_bouton_Capitalisme].charge = 1; //pour detruire l'image cree.

    //Bouton QUITTER
    Image bouton_image = LoadImage("button.png");
    Texture2D bouton_texture =LoadTextureFromImage(bouton_image);
    float frame_hauteur= (float)bouton_texture.height / NB_FRAMES_BOUTON;
    Rectangle sourceRec = {0, 0, (float)bouton_texture.width, frame_hauteur };

    ImageResize(&bouton_image, bouton_texture.width + 100, bouton_texture.height);
    ImageCrop(&bouton_image, (Rectangle){12, 0, bouton_texture.width+100, bouton_texture.height});

    Rectangle sourceRec2 = {0, 0, (float)bouton_texture.width + 88, frame_hauteur };

    Texture2D bouton_texture_large = LoadTextureFromImage(bouton_image);

    jeu->tabImages[menu_principale][img_boutonoff].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_boutonoff].frame_hauteur = frame_hauteur;

    jeu->tabImages[menu_principale][img_boutonoff].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos1 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON + 4*(frame_hauteur + 5), (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonoff].pos_Rec = pos1;

    //Bouton JOUER
    jeu->tabImages[menu_principale][img_boutonJouer].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_boutonJouer].frame_hauteur = frame_hauteur;
    jeu->tabImages[menu_principale][img_boutonJouer].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos2 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON - (frame_hauteur + 5), (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonJouer].pos_Rec = pos2;

    //Bouton SAUVEGARDER
    jeu->tabImages[menu_principale][img_boutonSauvegarder].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_boutonSauvegarder].frame_hauteur = frame_hauteur;
    jeu->tabImages[menu_principale][img_boutonSauvegarder].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos5 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON , (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonSauvegarder].pos_Rec = pos5;

    //Bouton Regles
    jeu->tabImages[menu_principale][img_boutonRegles].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_boutonRegles].frame_hauteur = frame_hauteur;
    jeu->tabImages[menu_principale][img_boutonRegles].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos3 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON + (frame_hauteur + 5), (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonRegles].pos_Rec = pos3;

    //Bouton Credits
    jeu->tabImages[menu_principale][img_boutonCredits].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_boutonCredits].frame_hauteur = frame_hauteur;
    jeu->tabImages[menu_principale][img_boutonCredits].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos4 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON + 2*(frame_hauteur + 5), (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonCredits].pos_Rec = pos4;

    //Bouton RESET
    jeu->tabImages[menu_principale][img_bouton_suppSave].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_bouton_suppSave].frame_hauteur = frame_hauteur;
    jeu->tabImages[menu_principale][img_bouton_suppSave].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos6 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON + 3*(frame_hauteur + 5), (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_bouton_suppSave].pos_Rec = pos6;

    //Bouton Retour Menu Principale
    jeu->tabImages[en_jeu][img_boutonRetourMenu].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[en_jeu][img_boutonRetourMenu].frame_hauteur = frame_hauteur;
    jeu->tabImages[en_jeu][img_boutonRetourMenu].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos7 = {-10, (RESOLUTION_Y + 10) - bouton_texture.height / NB_FRAMES_BOUTON, (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[en_jeu][img_boutonRetourMenu].pos_Rec = pos7;

    //Bouton Communisme
    jeu->tabImages[selection_choix_jeu][img_bouton_Communisme].texture2D = bouton_texture_large; // Load button texture
    jeu->tabImages[selection_choix_jeu][img_bouton_Communisme].frame_hauteur = frame_hauteur;
    jeu->tabImages[selection_choix_jeu][img_bouton_Communisme].source_Rec = sourceRec2;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos8 = {RESOLUTION_X / 2.0f +600 - bouton_texture_large.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON + (frame_hauteur + 5), (float)bouton_texture_large.width, frame_hauteur };
    jeu->tabImages[selection_choix_jeu][img_bouton_Communisme].pos_Rec = pos8;

    //Bouton Capitalisme
    jeu->tabImages[selection_choix_jeu][img_bouton_Capitalisme].texture2D = bouton_texture_large; // Load button texture
    jeu->tabImages[selection_choix_jeu][img_bouton_Capitalisme].frame_hauteur = frame_hauteur;
    jeu->tabImages[selection_choix_jeu][img_bouton_Capitalisme].source_Rec = sourceRec2;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos9 = {RESOLUTION_X / 2.0f - 600 - bouton_texture_large.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON + (frame_hauteur + 5), (float)bouton_texture_large.width, frame_hauteur };
    jeu->tabImages[selection_choix_jeu][img_bouton_Capitalisme].pos_Rec = pos9;

    UnloadImage(bouton_image);
}
void unload_all(Jeu* jeu){
    for (int i = 0; i < nb_pages; i++) {
        for (int j = 0; j < nb_img; j++) {
            if(jeu->tabImages[i][j].charge==1){
                UnloadTexture(jeu->tabImages[i][j].texture2D);
            }
        }

    }
    for (int i = 0; i < nb_sons; i++) {
        UnloadSound(jeu->tabSon[i]);
    }
}
void initialisation_Sons(Jeu* jeu){
    jeu->tabSon[son_Bouton] = LoadSound("bouton_son.mp3");
    //SetSoundVolume(jeu->tabSon[img_boutonoff], VOLUME_GLOBAL-0.2f);

    jeu->tabSon[son_menu] = LoadSound("musique_ambiance_menu.mp3");
    //SetSoundVolume(jeu->tabSon[son_menu], VOLUME_GLOBAL);
}



void initialisation_Grille(){
    printf("Creation d'un graphe ... ...\n");
    FILE *ifs = fopen(NOM_DU_FICHIER, "w");
    fprintf(ifs, "%d\n", ORDRE_EN_X);
    fprintf(ifs, "%d\n", ORDRE_EN_Y);
    fprintf(ifs, "%d\n", 2777);
    fprintf(ifs, "%d\n", 0);
    fprintf(ifs, "%d\n", ARGENT_DE_DEBUT);
    fprintf(ifs, "%d\n", 0);
    fprintf(ifs, "%d\n", 0);
    fprintf(ifs, "%d\n", 0);
    fprintf(ifs,"%d\n", -1);
    for (int i = 0; i <= ORDRE_EN_Y; i++) {
        for (int j = 0; j <= ORDRE_EN_X; j++) {
            fprintf(ifs, "%d ", vide);
        }
        fprintf(ifs, "\n");
    }
    fclose(ifs);
    //on ne ferme pas ce fichier car nous allons le lire juste apres dans le cas ou nous avons pas de fichier
}