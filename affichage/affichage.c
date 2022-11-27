#include "../Jeu.h"

void affichage_Boucle_G(Jeu* jeu){
    InitWindow(RESOLUTION_X, RESOLUTION_Y, "ECE-CITY BETA/ALPHA de L'OMEGA");
    SetWindowPosition(0, 15);
    InitAudioDevice();      // Initialise le haut-parleur
    jeu->quitter = 0;
    jeu->onClickSouris =false;
    jeu->niveau = 0;
    jeu->mode_de_selection = mode_neutre;
    jeu->timer_message_error = 0;
    initialisation_Images(jeu);
    initialisation_Sons(jeu);
    ini_fond_jeu(jeu);
    ToggleFullscreen();

    int ballPositionX = -100;
    int ballRadius = 20;
    float ballAlpha = 0.0f;
    int state = 0;
    int timer = 0;
    jeu->timer_jeu =0;
    float fade = 1;
    float fadeson = 0;

    SetTargetFPS(60);
    while (!jeu->quitter) {
        jeu->quitter = WindowShouldClose();
        if(IsKeyPressed(KEY_SPACE))jeu->page_actuel = en_jeu; //raccourci pour jouer
        Vector2 pos_Souris = GetMousePosition();
        switch (jeu->page_actuel) {
            case animation_Lancement:
                afficher_animation(jeu, &ballPositionX, &ballRadius, &ballAlpha, &state, &timer);
                break;
            case menu_principale:
                afficher_fenetre_menu(jeu, pos_Souris, &timer,&fade, &fadeson);
                break;
            case regles:
                afficher_REGLES(jeu);
                break;
            case credis:
                afficher_CREDITS(jeu);
                break;
            case selection_choix_jeu:
                afficher_choix_communisme(jeu, pos_Souris, &timer);
                break;
            case en_jeu:
                afficherJeu(jeu, pos_Souris, &timer);
                break;
        }
        timer++;
        jeu->timer_jeu++;
        jeu->timer_affichage++;
        jeu->timer_message_error++;
        maj_batiment_timer(jeu);
    }
    print_terrain_console(jeu); //TODO: retirer avant rendu juste pour test
    liberationListe(jeu);
    unload_all(jeu);
    CloseAudioDevice();
    CloseWindow();
}
void afficher_message(Jeu* jeu, char* message){
    Vector2 pos = {LARGEUR_FENETRE -610, (LONGUEUR_FENETRE/2)-80};
    DrawTexture(jeu->tabImages[en_jeu][img_logo_warning].texture2D, pos.x+205, pos.y-120, WHITE);
    DrawRectangle(pos.x-10, pos.y, 520, 80, Fade(RED, 0.75f));
    DrawText(message, pos.x, pos.y, 30, BLACK);
}

void afficher_fenetre_menu(Jeu* jeu, Vector2 pos_Souris, int* timer, float* rectAplha, float* sonAlpha){
    if(IsSoundPlaying(jeu->tabSon[son_menu])==0){
        PlaySound(jeu->tabSon[son_menu]);
        SetSoundVolume(jeu->tabSon[son_menu], VOLUME_GLOBAL);
    }BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(jeu->tabImages[menu_principale][img_menu].texture2D, 0, 0, WHITE);
    affi_bouton(jeu, jeu->page_actuel, img_boutonCredits, pos_Souris, "CREDITS", timer);
    affi_bouton(jeu, jeu->page_actuel, img_boutonRegles, pos_Souris, "RULES", timer);
    affi_bouton(jeu, jeu->page_actuel, img_boutonJouer, pos_Souris, "START", timer);
    affi_bouton(jeu, jeu->page_actuel, img_boutonSauvegarder, pos_Souris, "SAVE", timer);
    affi_bouton(jeu, jeu->page_actuel, img_boutonoff, pos_Souris, "EXIT", timer);
    affi_bouton(jeu, jeu->page_actuel, img_bouton_suppSave, pos_Souris, "RESET", timer);
    if (*timer <=300){
        *rectAplha -= 0.01f;
        *sonAlpha += 0.009f;
        if(*sonAlpha < 0.6f){
            SetSoundVolume(jeu->tabSon[son_menu], *sonAlpha);
        }
        DrawRectangle(0, 0, RESOLUTION_X, RESOLUTION_Y, Fade(BLACK, *rectAplha));
    }

    EndDrawing();
}

void afficher_REGLES(Jeu* jeu){
    BeginDrawing();
    DrawTexture(jeu->tabImages[regles][img_fond_panneau_affichage].texture2D, 0, 0, WHITE);
    DrawRectangle(100, 100, LARGEUR_FENETRE-200, LONGUEUR_FENETRE-200, Fade(BLACK, 0.3f));
    DrawText("Dans ce jeu, vous êtes le maire de la ville ECE-city, en charge du bien-être de ses citoyens. \n"
             "Vous avez le pouvoir de construire des infrastructures (routes, lignes électriques, \n"
             "canalisation d’eau potable) et des bâtiments (châteaux d'eau, centrales électriques, \n"
             "caserne de pompiers,...). \n"
             "Toutes ces tâches seront à réaliser en gérant un budget serré qui doit équilibrer les \n"
             "dépenses liées à ces constructions et les recettes liées aux impôts et taxes.\n\n"
             "L'objectif pour le joueur est de favoriser le développement automatique de sa population.\n"
             "- Pour que la population se développe, il faut donner aux gens une habitation.\n"
             "- Pour qu'une habitation se construise, il faut la connecter au réseau routier (qu'il \n"
             "faut donc construire au préalable) et l'alimenter en eau et en électricité.\n"
             "- Pour distribuer de l’électricité et de l'eau aux maisons, il faut construire des usines \n"
             "électriques et des châteaux d'eau.\n"
             "- La banque centrale de la ville dispose d'une certaine somme pour construire les \n"
             "infrastructures (routes, lignes électriques, canalisation d’eau potable), les usines \n"
             "électriques, les châteaux d'eau, les maisons, les casernes de pompiers... \n"
             "- Les habitants payent automatiquement des impôts à la banque centrale.\n"
             "- Les constructions évoluent individuellement au rythme de « cycles » de 15\n"
             "secondes représentant 1 mois de la vie réelle.", 120, 120, 30, WHITE);
    affi_bouton(jeu, en_jeu, img_boutonRetourMenu, GetMousePosition(), "MENU", &jeu->timer_jeu);
    EndDrawing();
}

void afficher_CREDITS(Jeu* jeu){
    BeginDrawing();
    DrawTexture(jeu->tabImages[credis][img_fond_credits].texture2D, 0, 0, WHITE);
    affi_bouton(jeu, en_jeu, img_boutonRetourMenu, GetMousePosition(), "MENU", &jeu->timer_jeu);
    EndDrawing();
}

void afficher_animation(Jeu* jeu, int* ballPositionX, int* ballRadius, float* ballAlpha, int* state, int* framesCounter){
    if (*state == 0){
        *ballPositionX = (int)EaseElasticOut((float)*framesCounter, -100, RESOLUTION_X / 2.0f + 100, 120);

        if (*framesCounter >= 120){
            *framesCounter = 0;
            *state = 1;
        }
    }
    else if (*state == 1){
        *ballRadius = (int)EaseElasticIn((float)*framesCounter, 20, 5000, 200);

        if (*framesCounter >= 200)
        {
            *framesCounter = 0;
            *state = 2;
        }
    }
    else if (*state == 2){
        *ballAlpha = EaseCubicOut((float)*framesCounter, 0.0f, 1.0f, 200);

        if (*framesCounter >= 150)
        {
            *framesCounter = 0;
            *state = 3;
        }
    }
    BeginDrawing();

    ClearBackground(RAYWHITE);
    if (*state >= 2) {
        DrawRectangle(0, 0, RESOLUTION_X, RESOLUTION_Y, BLACK);
        DrawText("ECE - CITY", RESOLUTION_X/2 - 95, RESOLUTION_Y/2, 30, BLUE);
    }
    DrawCircle(*ballPositionX, RESOLUTION_Y/2, (float)*ballRadius, Fade(BLUE, 1.0f - *ballAlpha));

    if (*state == 3) {
        *framesCounter = 0;
        jeu->page_actuel = menu_principale;
    }
    EndDrawing();
}

void afficher_choix_communisme(Jeu* jeu, Vector2 pos_Souris, int* timer){
    BeginDrawing();
    if(IsSoundPlaying(jeu->tabSon[son_menu])==0){
        PlaySound(jeu->tabSon[son_menu]);
    }
    DrawTexture(jeu->tabImages[selection_choix_jeu][img_fond_ChoixJeu].texture2D, 0, 0, WHITE);
    affi_bouton(jeu, jeu->page_actuel, img_bouton_Capitalisme, pos_Souris, "CAPITALISME", timer);
    affi_bouton(jeu, jeu->page_actuel, img_bouton_Communisme, pos_Souris, "COMMUNISME", timer);
    if (jeu->tabImages[selection_choix_jeu][img_bouton_Capitalisme].colision_souris == true){
        DrawRectangle((LARGEUR_FENETRE/2)+40, 290, 880, 360, Fade(BLUE, 0.68f));
        DrawText("Capitalisme : Dans ce mode, une construction \npasse systématiquement au stade supérieur, que les \n"
                 "ressources (eau+électricité) soient disponibles ou\n pas. L'évolution de l'ensemble des \n"
                 "constructions s'en trouve alors bouleversée, toujours\n dans le respect des règles de \n"
                 "régression qui maximisent le nombre d'habitants\n total de la ville.", (LARGEUR_FENETRE/2)+50, 300, 30, WHITE);
    } else if (jeu->tabImages[selection_choix_jeu][img_bouton_Communisme].colision_souris == true){
        DrawRectangle(40, 190, 910, 590, Fade(RED, 0.68f));
        DrawText("Communiste : Dans ce mode, une construction n'évolue\npas si les ressources (eau+électricité) \n"
                 "nécessaires à sa croissance ne sont pas disponibles.\nLa construction va donc :\n"
                 "- Evoluer à chaque cycle si les conditions eau+électricité \ndu jeu le permettent. \n"
                 "- Conserver son stade actuel tant que les conditions \neau+électricité le permettent, et"
                 "qu'elle n'a \npas pu évoluer. \n"
                 "- Régresser au stade précédent si les conditions ne lui \npermettent plus de se "
                 "maintenir ou \nd'évoluer (une cabane régresse au stade de ruine avant \nd'évoluer de"
                 "nouveau)", 50, 200, 30, WHITE);
    }

    EndDrawing();
}
void affi_bouton(Jeu* jeu, int page, int image, Vector2 pos_souris, char* nom, int* timer){
    int btnState;
    bool btnAction;
    btnAction = false;
    Rectangle hit_box_bouton = {jeu->tabImages[page][image].pos_Rec.x, jeu->tabImages[page][image].pos_Rec.y, jeu->tabImages[page][image].pos_Rec.width, jeu->tabImages[page][image].pos_Rec.height-18};
    if (CheckCollisionPointRec(pos_souris, hit_box_bouton))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
        jeu->tabImages[page][image].colision_souris = true;
    }
    else {
        jeu->tabImages[page][image].colision_souris = false;
        btnState = 0;
    }
    if (btnAction)
    {
        PlaySound(jeu->tabSon[son_Bouton]); // +ce qu'on souhaite faire en appuyant sur l'image
        switch (image) {
            case img_boutonoff:
                jeu->quitter = 1;
                break;
            case img_boutonJouer:
                ini_fond_jeu(jeu);
                *timer = 0;
                if (jeu->choix_politique == -1){
                    jeu->page_actuel = selection_choix_jeu;
                } else jeu->page_actuel = en_jeu;
                break;
            case img_boutonSauvegarder:
                enregistrer_Grille(jeu);
                printf("enregistrement effectue");
                break;
            case img_boutonRegles:
                jeu->page_actuel = regles;
                break;
            case img_boutonCredits:
                jeu->page_actuel = credis;
                break;
            case img_bouton_suppSave:
                printf("Destruction de votre ancien fichier de sauvegarde (si vous en aviez un)\n");
                remove(NOM_DU_FICHIER);
                lire_graphe(jeu);
                break;
            case img_bouton_Capitalisme:
                ini_fond_jeu(jeu);
                jeu->choix_politique = capitalisme;
                *timer = 0;
                jeu->page_actuel = en_jeu;
                break;
            case img_bouton_Communisme:
                ini_fond_jeu(jeu);
                jeu->choix_politique = communisme;
                *timer = 0;
                jeu->page_actuel = en_jeu;
                break;
            case img_boutonRetourMenu:
                //faire la save ici
                *timer = 0;
                jeu->page_actuel = menu_principale;
                break;
            default:
                break;
        }
    }
    jeu->tabImages[page][image].source_Rec.y = btnState * jeu->tabImages[page][image].frame_hauteur;
    DrawTextureRec(jeu->tabImages[page][image].texture2D, jeu->tabImages[page][image].source_Rec, (Vector2){jeu->tabImages[page][image].pos_Rec.x, jeu->tabImages[page][image].pos_Rec.y }, WHITE);
    DrawText(nom, jeu->tabImages[page][image].pos_Rec.x + 42, jeu->tabImages[page][image].pos_Rec.y + 40, 30, BLACK);
}

void afficher_jeu_logo_interactionAvecClick(Jeu* jeu, Vector2 pos_souris){
    float alphalogojeu1 = 0.5f;
    float alphalogojeu2 = 0.85f;
    //RECTANGLE DETECTION POUR BARRE DES CONSTRUCTIONS
    Rectangle logo_reseau = {0, TAILLE_CASE_GRILLE*(jeu->ordre.y), jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur};
    Rectangle logo_maison = {90, TAILLE_CASE_GRILLE*(jeu->ordre.y), jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur};
    Rectangle logo_usine = {180, TAILLE_CASE_GRILLE*(jeu->ordre.y), jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur};
    Rectangle logo_chateauDO = {270, TAILLE_CASE_GRILLE*(jeu->ordre.y), jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur};
    Rectangle logo_demolition = {360, TAILLE_CASE_GRILLE*(jeu->ordre.y), jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur};
    //RECTANGLE DETECTION POUR CHOIX DU NIVEAU D'AFFICHAGE
    Rectangle logo_niveau_affichage = {LARGEUR_FENETRE-122, LONGUEUR_FENETRE-122, jeu->tabImages[en_jeu][img_niveau_0].texture2D.width, jeu->tabImages[en_jeu][img_niveau_0].texture2D.height};

    int selection = -1;
    DrawRectangle(0, TAILLE_CASE_GRILLE*(jeu->ordre.y), jeu->tabImages[en_jeu][img_logosJeu].texture2D.width, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur,Fade(BLUE, 0.7f));
    DrawTexture(jeu->tabImages[en_jeu][img_logosJeu].texture2D, 0, TAILLE_CASE_GRILLE*(jeu->ordre.y), WHITE);

    if (jeu->niveau == 0){
        DrawTexture(jeu->tabImages[en_jeu][img_niveau_0].texture2D, LARGEUR_FENETRE-122, LONGUEUR_FENETRE-122, WHITE);
    }else if (jeu->niveau == -1){
        DrawTexture(jeu->tabImages[en_jeu][img_niveau_1].texture2D, LARGEUR_FENETRE-122, LONGUEUR_FENETRE-122, WHITE);
    }else if (jeu->niveau == -2){
        DrawTexture(jeu->tabImages[en_jeu][img_niveau_2].texture2D, LARGEUR_FENETRE-122, LONGUEUR_FENETRE-122, WHITE);
    }
    if (CheckCollisionPointRec(pos_souris, logo_reseau)){
        selection = reseau;
    }
    if (CheckCollisionPointRec(pos_souris, logo_maison)){
        selection = maison;
    }
    if (CheckCollisionPointRec(pos_souris, logo_usine)){
        selection = usine_electrique;
    }
    if (CheckCollisionPointRec(pos_souris, logo_chateauDO)){
        selection = chateau_deau;
    }
    if (CheckCollisionPointRec(pos_souris, logo_demolition)){
        selection = demolition;
    }
    if (CheckCollisionPointRec(pos_souris, logo_niveau_affichage)){
        DrawRectangle((int)logo_niveau_affichage.x, (int)logo_niveau_affichage.y, (int)logo_niveau_affichage.width, (int)logo_niveau_affichage.height,Fade(BLACK, 0.1f));
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            DrawRectangle((int)logo_niveau_affichage.x, (int)logo_niveau_affichage.y, (int)logo_niveau_affichage.width, (int)logo_niveau_affichage.height,Fade(WHITE, 0.1f));
            jeu->niveau--;
            if (jeu->niveau < -2) jeu->niveau = 0;
        }
    }
    if (selection != -1){
        switch (selection) {
            case reseau:
                DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_reseau, (Vector2){0, TAILLE_CASE_GRILLE*(jeu->ordre.y)}, Fade(PURPLE, alphalogojeu1));
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->mode_de_selection = (jeu->mode_de_selection != mode_reseau) ? mode_reseau : mode_neutre;
                }
                break;
            case maison:
                DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_maison, (Vector2){90, TAILLE_CASE_GRILLE*(jeu->ordre.y)}, Fade(PURPLE, alphalogojeu1));
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->mode_de_selection = (jeu->mode_de_selection != mode_maison) ? mode_maison : mode_neutre;
                }
                break;
            case usine_electrique:
                DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_usine, (Vector2){180, TAILLE_CASE_GRILLE*(jeu->ordre.y)}, Fade(PURPLE, alphalogojeu1));
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->mode_de_selection = (jeu->mode_de_selection != mode_usine) ? mode_usine : mode_neutre;
                }
                break;
            case chateau_deau:
                DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_chateauDO, (Vector2){270, TAILLE_CASE_GRILLE*(jeu->ordre.y)}, Fade(PURPLE, alphalogojeu1));
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->mode_de_selection = (jeu->mode_de_selection != mode_chateauDO) ? mode_chateauDO : mode_neutre;
                }
                break;
            case demolition:
                DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_demolition, (Vector2){360, TAILLE_CASE_GRILLE*(jeu->ordre.y)}, Fade(PURPLE, alphalogojeu1));
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->mode_de_selection = (jeu->mode_de_selection != mode_demolition) ? mode_demolition : mode_neutre;
                }
                break;
            default:
                break;
        }
    }
    if (jeu->mode_de_selection == mode_reseau)DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_reseau, (Vector2){0, TAILLE_CASE_GRILLE * jeu->ordre.y-3}, Fade(BLUE, alphalogojeu2));
    if (jeu->mode_de_selection == mode_maison)DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_maison, (Vector2){90, TAILLE_CASE_GRILLE * jeu->ordre.y-3}, Fade(BLUE, alphalogojeu2));
    if (jeu->mode_de_selection == mode_usine)DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_usine, (Vector2){180, TAILLE_CASE_GRILLE * jeu->ordre.y-3}, Fade(BLUE, alphalogojeu2));
    if (jeu->mode_de_selection == mode_chateauDO)DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_chateauDO, (Vector2){270, TAILLE_CASE_GRILLE * jeu->ordre.y-3}, Fade(BLUE, alphalogojeu2));
    if (jeu->mode_de_selection == mode_demolition)DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_demolition, (Vector2){360, TAILLE_CASE_GRILLE * jeu->ordre.y-3}, Fade(BLUE, alphalogojeu2));
}

void afficher_construction_batiment(Jeu* jeu, Vector2 pos_souris){
    Vector2 pos_souris_maison = pos_souris;
    pos_souris_maison.x -= TAILLE_CASE_GRILLE*3/2;
    pos_souris_maison.y -= TAILLE_CASE_GRILLE*3/2;
    Color color_construction = Fade(WHITE, 0.6f);
    switch (jeu->mode_de_selection) {
        case mode_neutre:
            break;
        case mode_reseau:
            if (jeu->timer_affichage < 120){
                afficher_message(jeu, "\t\t\terreur de construction:\n\t\t\t\t\t\t\t\t\t\t\tROUTE");
            }
            DrawTexture(jeu->tabImages[en_jeu][img_route].texture2D, (int)pos_souris.x-TAILLE_CASE_GRILLE/2, (int)pos_souris.y-TAILLE_CASE_GRILLE/2, color_construction);
            break;
        case mode_maison:
            if (jeu->timer_affichage < 120){
                afficher_message(jeu, "\t\t\terreur de construction:\n\t\t\t\t\t\t\t\t\t\tMAISON");
            }
            jeu->tabImages[en_jeu][img_maison].source_Rec.x = 0 * jeu->tabImages[en_jeu][img_maison].frame_longueur; //c normal c pour me souvenir qu'il faut utiliser la mm structure de code pour augmenter les niv
            DrawTextureRec(jeu->tabImages[en_jeu][img_maison].texture2D, jeu->tabImages[en_jeu][img_maison].source_Rec, pos_souris_maison, color_construction);
            break;
        case mode_usine:
            if (jeu->timer_affichage < 120){
                afficher_message(jeu, "\t\t\terreur de construction:\n\t\t\t\t\t\t\t\t\t\t\tUSINE");
            }
            DrawTexture(jeu->tabImages[en_jeu][img_usine].texture2D, (int)pos_souris.x-(TAILLE_CASE_GRILLE/2)+((-3/2)*(TAILLE_CASE_GRILLE)), (int)pos_souris.y-(TAILLE_CASE_GRILLE/2)+((-3/2)*(TAILLE_CASE_GRILLE)), color_construction);
            break;
        case mode_chateauDO:
            if (jeu->timer_affichage < 120){
                afficher_message(jeu, "\t\t\terreur de construction:\n\t\t\t\t\t\t\tCHATEAU D'EAU");
            }
            DrawTexture(jeu->tabImages[en_jeu][img_chateauDO].texture2D, (int)pos_souris.x-(TAILLE_CASE_GRILLE/2)+((-3/2)*(TAILLE_CASE_GRILLE)), (int)pos_souris.y-(TAILLE_CASE_GRILLE/2)+((-3/2)*(TAILLE_CASE_GRILLE)), color_construction);
            break;
        case mode_demolition:
            DrawTexture(jeu->tabImages[en_jeu][img_demolition].texture2D, (int)pos_souris.x-TAILLE_CASE_GRILLE, (int)pos_souris.y-TAILLE_CASE_GRILLE, color_construction);
            break;
        default:
            break;
    }
}
void actualiser_nb_habitants_maison(Batiment* liste_maison){
    switch (liste_maison->stadeEvolution) {
        case 0 : {
            liste_maison->nb_habitants = 0;
            break;
        }
        case 1 : {
            liste_maison->nb_habitants = HABITANT_NIVEAU_MAISON1;
            break;
        }
        case 2 : {
            liste_maison->nb_habitants = HABITANT_NIVEAU_MAISON2;
            break;
        }
        case 3 : {
            liste_maison->nb_habitants = HABITANT_NIVEAU_MAISON3;
            break;
        }
        case 4 : {
            liste_maison->nb_habitants = HABITANT_NIVEAU_MAISON4;
            break;
        }
        default : {
            break;
        }
    }
}


void afficher_batiment_Raylib(Jeu* jeu){
    Batiment *listeMaison = jeu->batiments[maison];
    Batiment *listeChateau = jeu->batiments[chateau_deau];
    Batiment *listeUsine = jeu->batiments[usine_electrique];


    for (int y = 0; y < (int)jeu->ordre.y; y++) {
        for (int x = 0; x < (int)jeu->ordre.x; x++) {
            if (jeu->terrain[y][x] == reseau){
                if (jeu->niveau == 0){
                    DrawTexture(jeu->tabImages[en_jeu][img_route].texture2D, x*TAILLE_CASE_GRILLE, y*TAILLE_CASE_GRILLE, WHITE);
                }
                else if (jeu->niveau == -1){
                    DrawRectangle(x*TAILLE_CASE_GRILLE, y*TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE,Fade(BLUE, 0.8f));
                }
                else if (jeu->niveau == -2){
                    DrawRectangle(x*TAILLE_CASE_GRILLE, y*TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE,Fade(YELLOW, 0.85f));
                }
            }
        }
    }

    if(listeMaison != NULL) {
        do {
            if (jeu->terrain[(int)listeMaison->co.y][(int)listeMaison->co.x] == maison){
                if (listeMaison->timer > 60*15){
                    if (listeMaison->stadeEvolution == 5){
                        listeMaison->nb_habitants = 0;
                        actualiser_nb_habitants_maison(listeMaison);
                        listeMaison->stadeEvolution = 1;
                    } else if (listeMaison->stadeEvolution < 4){
                        listeMaison->stadeEvolution++;
                        int nb_habitants = listeMaison->nb_habitants;
                        actualiser_nb_habitants_maison(listeMaison);
                        nb_habitants = listeMaison->nb_habitants - nb_habitants;
                        jeu->nb_habitants_tot += nb_habitants;
                        listeMaison->timer = 0;
                    }
                }
                jeu->tabImages[en_jeu][img_maison].source_Rec.x = listeMaison->stadeEvolution * jeu->tabImages[en_jeu][img_maison].frame_longueur;
                DrawTextureRec(jeu->tabImages[en_jeu][img_maison].texture2D, jeu->tabImages[en_jeu][img_maison].source_Rec, (Vector2){listeMaison->co.x*TAILLE_CASE_GRILLE, listeMaison->co.y*TAILLE_CASE_GRILLE}, WHITE); //TODO : DOIS CHANGER CAR PAS EVOLUTION LA
            } else printf("ERROR tu peux pas dessinner une maison alors que le terrain n'a pas de maison\n");
            listeMaison = listeMaison->next;
        } while (listeMaison != jeu->batiments[maison]);

    }
    //else DrawText("ERROR LISTE MAISON VIDE", LONGUEUR_FENETRE + 100, LONGUEUR_FENETRE-100, 10, WHITE);

    if(listeChateau != NULL) {
        do {
            if (jeu->terrain[(int)listeChateau->co.y][(int)listeChateau->co.x] == chateau_deau) {
                DrawTexture(jeu->tabImages[en_jeu][img_chateauDO].texture2D, listeChateau->co.x * TAILLE_CASE_GRILLE,
                            listeChateau->co.y * TAILLE_CASE_GRILLE, WHITE); //TODO : DOIS CHANGER CAR PAS EVOLUTION LA
            } else printf("ERROR tu peux pas dessinner un chateauDO alors que le terrain n'a pas de chateauDO\n");
            listeChateau = listeChateau->next;
        } while (listeChateau != jeu->batiments[chateau_deau]);
    }
    //else DrawText("ERROR LISTE CHATEAU VIDE", LONGUEUR_FENETRE + 100, LONGUEUR_FENETRE-110, 10, WHITE);

    if(listeUsine != NULL) {
        do {
            if (jeu->terrain[(int)listeUsine->co.y][(int)listeUsine->co.x] == usine_electrique) {
                DrawTexture(jeu->tabImages[en_jeu][img_usine].texture2D, listeUsine->co.x*TAILLE_CASE_GRILLE, listeUsine->co.y*TAILLE_CASE_GRILLE, WHITE); //TODO : DOIS CHANGER CAR PAS EVOLUTION LA
            } else {
                print_terrain_console(jeu);
                printf("ERROR tu peux pas dessinner un usine alors que le terrain n'a pas d usine\n");
            }
            listeUsine = listeUsine->next;
        } while (listeUsine != jeu->batiments[usine_electrique]);
    }
    //else DrawText("ERROR LISTE USINE VIDE", LONGUEUR_FENETRE + 100, LONGUEUR_FENETRE-120, 10, WHITE);
}

void affichage_defilement_fond(Jeu* jeu, int *timer){
    float alpha_fondu = 0.01f;
    if (*timer < 60*TEMPS_DEFILEMENT_FOND){
        DrawTexture(jeu->tabImages[en_jeu][img_fondJeu1].texture2D, 0, 0, Fade(WHITE, jeu->tabImages[en_jeu][img_fondJeu1].alpha));
    }else if (*timer < 60*(TEMPS_DEFILEMENT_FOND*2)){
        DrawTexture(jeu->tabImages[en_jeu][img_fondJeu2].texture2D, 0, 0, Fade(WHITE, jeu->tabImages[en_jeu][img_fondJeu2].alpha));
    }else if (*timer < 60*(TEMPS_DEFILEMENT_FOND*3)){
        DrawTexture(jeu->tabImages[en_jeu][img_fondJeu3].texture2D, 0, 0, Fade(WHITE, jeu->tabImages[en_jeu][img_fondJeu3].alpha));
    }else if (*timer < 60*(TEMPS_DEFILEMENT_FOND*4)){
        DrawTexture(jeu->tabImages[en_jeu][img_fondJeu4].texture2D, 0, 0, Fade(WHITE, jeu->tabImages[en_jeu][img_fondJeu4].alpha));
    }else if (*timer >= 60*(TEMPS_DEFILEMENT_FOND*4)) *timer = 0;
    if (*timer < 60*2)jeu->tabImages[en_jeu][img_fondJeu1].alpha += alpha_fondu;
    else if (*timer > 60*5 && *timer < 60*7)jeu->tabImages[en_jeu][img_fondJeu1].alpha -= alpha_fondu;
    else if (*timer > 60*7 && *timer < 60*9)jeu->tabImages[en_jeu][img_fondJeu2].alpha += alpha_fondu;
    else if (*timer > 60*12 && *timer < 60*14)jeu->tabImages[en_jeu][img_fondJeu2].alpha -= alpha_fondu;
    else if (*timer > 60*14 && *timer < 60*16)jeu->tabImages[en_jeu][img_fondJeu3].alpha += alpha_fondu;
    else if (*timer > 60*19 && *timer < 60*21)jeu->tabImages[en_jeu][img_fondJeu3].alpha -= alpha_fondu;
    else if (*timer > 60*21 && *timer < 60*23)jeu->tabImages[en_jeu][img_fondJeu4].alpha += alpha_fondu;
    else if (*timer > 60*26 && *timer < 60*28)jeu->tabImages[en_jeu][img_fondJeu4].alpha -= alpha_fondu;
}



void afficherJeu(Jeu* jeu, Vector2 pos_souris, int* timer){
    Vector2 playerPosition = { 0, 0 };
    int playerTileX = 0;
    int playerTileY = 0;
    playerPosition.x = pos_souris.x - 8;
    playerPosition.y = pos_souris.y - 8;

    if (playerPosition.x < 0) playerPosition.x = 0;
    else if ((playerPosition.x + PLAYER_SIZE) > ((jeu->ordre.x +1)* TAILLE_CASE_GRILLE )) playerPosition.x = (jeu->ordre.x+1) * TAILLE_CASE_GRILLE - PLAYER_SIZE;
    if (playerPosition.y < 0) playerPosition.y = 0;
    else if ((playerPosition.y + PLAYER_SIZE) > ((jeu->ordre.y +1)* TAILLE_CASE_GRILLE )) playerPosition.y = (jeu->ordre.y+1) * TAILLE_CASE_GRILLE - PLAYER_SIZE;

    if (jeu->timer_jeu >= 60*15){
        jeu->argent += jeu->nb_habitants_tot * IMPOTS_PAR_HABITANT;
        jeu->mois++;
        if (jeu->mois >= 13){
            jeu->mois = 0;
            jeu->annee++;
        }
        jeu->timer_jeu = 0;
    }

    playerTileX = (int)((playerPosition.x + TAILLE_CASE_GRILLE / 2) / TAILLE_CASE_GRILLE);
    playerTileY = (int)((playerPosition.y + TAILLE_CASE_GRILLE / 2) / TAILLE_CASE_GRILLE);

    ClearBackground(RAYWHITE);
    BeginDrawing();

    ClearBackground(BLACK);

    affichage_defilement_fond(jeu, timer);

    for (int y = 0; y <= jeu->ordre.y-1; y++){
        for (int x = 0; x <= jeu->ordre.x-1; x++){
            DrawRectangle(x * TAILLE_CASE_GRILLE, (y) * TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, WHITE);
            DrawRectangle(x * TAILLE_CASE_GRILLE, (y) * TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, Fade(BLACK, 0.8f));
            DrawRectangleLines(x * TAILLE_CASE_GRILLE, (y) * TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, Fade(WHITE, 0.6f));
        }
    }
    //draw les ressources du jeu à droite de la grille
    DrawTexture(jeu->tabImages[en_jeu][img_logo_argent].texture2D, ORDRE_EN_X*TAILLE_CASE_GRILLE, 5, Fade(WHITE, 0.7f));
    DrawTexture(jeu->tabImages[en_jeu][img_logo_habitant].texture2D, ORDRE_EN_X*TAILLE_CASE_GRILLE, 105, Fade(WHITE, 0.7f));
    DrawTexture(jeu->tabImages[en_jeu][img_logo_eau].texture2D, ORDRE_EN_X*TAILLE_CASE_GRILLE, 205, WHITE);
    DrawTexture(jeu->tabImages[en_jeu][img_logo_elec].texture2D, ORDRE_EN_X*TAILLE_CASE_GRILLE, 305, Fade(WHITE, 0.7f));
    DrawText(TextFormat("%d ", jeu->argent), ORDRE_EN_X*TAILLE_CASE_GRILLE+100, 30, 50, Fade(WHITE, 0.85f));
    DrawText(TextFormat("%d ", jeu->nb_habitants_tot), ORDRE_EN_X*TAILLE_CASE_GRILLE+100, 130, 50, Fade(WHITE, 0.85f));
    DrawText(TextFormat("%d ", jeu->production_eau_restante), ORDRE_EN_X*TAILLE_CASE_GRILLE+100, 230, 50, Fade(WHITE, 0.85f));
    DrawText(TextFormat("%d ", jeu->production_elec_restante), ORDRE_EN_X*TAILLE_CASE_GRILLE+100, 330, 50, Fade(WHITE, 0.85f));
    //Message erreur
    if (jeu->timer_message_error < 120) {
        afficher_message(jeu, "\t\t\terreur de construction\nVous n'avez pas assez d'argent");
    }

    DrawRectangle((TAILLE_CASE_GRILLE*ORDRE_EN_X)+30, (LONGUEUR_FENETRE/2)+30, 600, 250, Fade(BLUE, 0.6f));
    DrawText("\n Prix MAISON : 1000$\n Prix ROUTE : 10$\n Prix USINE ELECTRIQUE : 100 000$\n Prix CHATEAU D'EAU : 100 000$",(TAILLE_CASE_GRILLE*ORDRE_EN_X)+40, (LONGUEUR_FENETRE/2)+50, 30,
             Fade(WHITE, 0.8f));
    DrawText("\t\t\t\t\t\t\tPRIX UNITE", (TAILLE_CASE_GRILLE*ORDRE_EN_X)+40, (LONGUEUR_FENETRE/2)+50, 30,
             Fade(YELLOW, 0.8f));


    DrawRectangle(450, ORDRE_EN_Y*TAILLE_CASE_GRILLE, 500, 40,Fade(BLUE, 0.7f));
    DrawText(TextFormat("Année Numéro: %d\t Mois Numéro: %d", jeu->annee, jeu->mois), 460, (ORDRE_EN_Y*TAILLE_CASE_GRILLE)+10, 25,
             Fade(WHITE, 0.85f));

    poser_batiment(jeu);
    afficher_batiment_Raylib(jeu);
    affi_bouton(jeu, jeu->page_actuel, img_boutonRetourMenu, pos_souris, "MENU", timer);
    afficher_jeu_logo_interactionAvecClick(jeu, pos_souris);
    afficher_construction_batiment(jeu, pos_souris);

    DrawText(TextFormat("Case Actuelle: [%i,%i]", playerTileX, playerTileY), RESOLUTION_X-220, 25, 20, WHITE);
    jeu->selection.x = playerTileX;
    jeu->selection.y = playerTileY;
    EndDrawing();
}

