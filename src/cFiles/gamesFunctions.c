//
// Created by matt0 on 11/16/2022.
//
#include "../headers/includes.h"
#pragma region constructeurs
/// Cette fonction crée l'objet Game qui va contenir 4ptr et le window Handle
/// un ptr vers le doubleTableau de type Case_t* pour le joueur et un autre ptr identique pour le bot
/// un ptr vers une struct qui contient les infos des bateau du joueur et un autre ptr identique pour le bot
/// \param window
/// \return un ptr vers l'objet Game crée
/*
 *                                           Game
 *                                            |
 *         ---------------------------------------------------------------------------
 *         |            |                   |                   |                    |
 *       window         |                   |                   |                    |
 *                ptr grille player     ptr grille bot    ptr bateau player      ptr bateau bot
 * (type)         (Case_t* tab[][])    (Case_t* tab[][])   (pPLayerBoats*)       (pBotsBoats*) -> (identique que pPlayerBoats*)
 *                                                              |
 *                                                              |
 *                                                         ptr porteAvion -> un tab de 7 Case_t qui represente la vie, les ptr vers les textures...
 *                                                         ptr croiseur[2] -> un tab de 5 qui .....
 *                                                         ptr destroyer[3] -> un tab de 3  qui .......
 *                                                         ptr sousMarin[4] -> un tab du 1 Case_t qui .....
 *                                                                       |
 *                                                          cet index correspond au nombre d'entités
 */
Game_t* game_new(HWND window)
{
    Game_t* pGame = (Game_t*)(malloc(sizeof(Game_t)));
    if(pGame != NULL){

        pGame->window = window;
        pGame->fireballBuffer = GameSprite_new();
        initTex(pGame->fireballBuffer,"../img/explosion.png",20,20);
        //bot side
        for(int i = 0; i < GAME_DIMENSION;i++){
            for(int j = 0; j < GAME_DIMENSION;j++){
                pGame->botPlayground[i][j] = case_new(pGame->fireballBuffer,i,j,1);
            }
        }
        //player side
        for(int k = 0; k < GAME_DIMENSION;k++){
            for(int l = 0; l < GAME_DIMENSION;l++){
                pGame->playerPlayground[k][l] = case_new(pGame->fireballBuffer,k,l,0);
            }
        }
        pGame->pBots_boats = NULL;
        pGame->pBots_boats = bots_boats_new();
        if(pGame->pBots_boats == NULL){
            MessageBoxA(NULL,"creation du ptr pBots_boats failed",NULL,0);
            exit(1);
        }
        pGame->pPlayer_boats = NULL;
        pGame->pPlayer_boats = player_boats_new();
        if(pGame->pPlayer_boats == NULL){
            MessageBoxA(NULL,"creation du ptr pPlayer_boats failed",NULL,0);
            exit(1);
        }
        pGame->waitingInput = 0;
        pGame->inputHasBeenSend = 0;
        pGame->index = 0;
        pGame->cursorPos = malloc(sizeof(LPPOINT));
        pGame->pClickedCase = NULL;
        pGame->toggleMenu = 0;
        pGame->playerTurn = 1;
        pGame->toggleIntero = 0;
        for(int i = 0; i < 9;i++){
            pGame->intero[i] = GameSprite_new();
            pGame->intero[i]->init(pGame->intero[i],"../img/intero.png",38,38);
        }
        pGame->saveFile = fopen("../save.txt","w+");
        pGame->menusIsTogged = 0;
        pGame->scoutingRemaining = 4;
        return pGame;
    }else{
        MessageBoxA(NULL,"Game* is NULL",NULL,0);
        exit(1);
    }
}
Game_t* game_load(HWND window){
    Game_t* pGame = (Game_t*)(malloc(sizeof(Game_t)));

    if(pGame != NULL){

        pGame->window = window;
        pGame->fireballBuffer = GameSprite_new();
        initTex(pGame->fireballBuffer,"../img/explosion.png",20,20);
        //bot side
        for(int i = 0; i < GAME_DIMENSION;i++){
            for(int j = 0; j < GAME_DIMENSION;j++){
                pGame->botPlayground[i][j] = case_new(pGame->fireballBuffer,i,j,1);
            }
        }
        //player side
        for(int k = 0; k < GAME_DIMENSION;k++){
            for(int l = 0; l < GAME_DIMENSION;l++){
                pGame->playerPlayground[k][l] = case_new(pGame->fireballBuffer,k,l,0);
            }
        }

        pGame->pBots_boats = NULL;
        pGame->pBots_boats = bots_boats_new();
        if(pGame->pBots_boats == NULL){
            MessageBoxA(NULL,"creation du ptr pBots_boats failed",NULL,0);
            exit(1);
        }
        pGame->pPlayer_boats = NULL;
        pGame->pPlayer_boats = player_boats_new();
        if(pGame->pPlayer_boats == NULL){
            MessageBoxA(NULL,"creation du ptr pPlayer_boats failed",NULL,0);
            exit(1);
        }


        pGame->waitingInput = 0;
        pGame->inputHasBeenSend = 0;
        pGame->index = 0;
        pGame->cursorPos = malloc(sizeof(LPPOINT));
        pGame->pClickedCase = NULL;
        pGame->toggleMenu = 0;
        pGame->playerTurn = 1;
        pGame->toggleIntero = 0;
        for(int i = 0; i < 9;i++){
            pGame->intero[i] = GameSprite_new();
            pGame->intero[i]->init(pGame->intero[i],"../img/intero.png",38,38);
        }
        pGame->saveFile = fopen("../save.txt","r+");
        pGame->menusIsTogged = 0;
        pGame->scoutingRemaining = 4;
        return pGame;
    }else{
        MessageBoxA(NULL,"Game* is NULL",NULL,0);
        exit(1);
    }

}
/// ce constructeur est utilisé dans le constructeur de Game pour initialiser chaque case de la grille
/// \param rowIndex sur quelle ligne on est
/// \param collumnIndex sur quelle collone on est
/// \param bBot si ce param est true on rajoute 600px lors de l'attribution du x du vec2 attribut de Case_t
/// \return un ptr vers une Case_t
Case_t* case_new(GameSprite_t* fireballTex,int rowIndex,int collumnIndex,int bBot)
{
    Case_t* pCase = (Case_t*)(malloc(sizeof(Case_t)));
    if(pCase != NULL){
        pCase->id = ((rowIndex*15) + collumnIndex);
        pCase->isOccupied = 0;
        pCase->healthStatus = 0;
        if(bBot){
            //on assigne la pos du coin hut gauche en px
            pCase->posInGrid.x = (WINDOW_WIDTH/2) +collumnIndex*((WINDOW_WIDTH/2)/15);
            pCase->posInGrid.y = rowIndex*((WINDOW_WIDTH/2)/15);
        }
        else{
            pCase->posInGrid.x =  collumnIndex*((WINDOW_WIDTH/2)/15);
            pCase->posInGrid.y = rowIndex*((WINDOW_WIDTH/2)/15);
        }
        pCase->fireBall = GameSprite_new();
        pCase->fireBall->sprite = fireballTex->sprite; //on ne peut pas init() 2*225 la meme image pour chaque case sinon load time >20sec
        pCase->fireBall->tex = fireballTex->tex;
        pCase->fireBall->setPos(pCase->fireBall,(float)pCase->posInGrid.x+10,(float)pCase->posInGrid.y+10);
        return pCase;
    }else{
        MessageBoxA(NULL,"Case_t* is NULL",NULL,0);
        exit(1);
    }
}
/// ce constructeur est utilisé dans le constructeur de Game pour initialiser les tableau de ptrs vers les bateau du bot
/// \return
bots_boats_t* bots_boats_new(){
    bots_boats_t* pBotsBoats = (bots_boats_t*)(malloc(sizeof(bots_boats_t)));
    pBotsBoats->pPorteAvion = porteAvion_new();
    for(int i = 0; i < 2;i++){
        pBotsBoats->pCroiseurs[i] = croiseur_new();
    }
    for(int k = 0;k < 3;k++){
        pBotsBoats->pDestroyers[k] = destroyer_new();
    }
    for(int l = 0; l < 4; l++){
        pBotsBoats->pSousMarins[l] = sousMarin_new();
    }
    return pBotsBoats;
}
/// ce constructeur est utilisé dans le constructeur de Game pour initialiser les tableau de ptrs vers les bateau du player
/// \return
player_boats_t* player_boats_new(){
    player_boats_t* pPlayerBoats = (player_boats_t*)(malloc(sizeof(player_boats_t)));
    pPlayerBoats->pPorteAvion = porteAvion_new();
    for(int i = 0; i < 2;i++){
        pPlayerBoats->pCroiseurs[i] = croiseur_new();
    }
    for(int k = 0;k < 3;k++){
        pPlayerBoats->pDestroyers[k] = destroyer_new();
    }
    for(int l = 0; l < 4; l++){
        pPlayerBoats->pSousMarins[l] = sousMarin_new();
    }
    return pPlayerBoats;
}
/// ce constructeur est utilisé par le constructeur player_boats_new et bots_boats_new pour initaliser les cases des tableaux
/// \return
porte_avion_t* porteAvion_new(){
    porte_avion_t* pPorteAvion = (porte_avion_t*)(malloc(sizeof(porte_avion_t)));

    pPorteAvion->pPorteAvionTex = GameSprite_new();
    initTex(pPorteAvion->pPorteAvionTex,"../img/porteAvion.png",(40*7)-10,35);

    pPorteAvion->pPorteAvionTex90right = GameSprite_new();
    initTex(pPorteAvion->pPorteAvionTex90right,"../img/porteAvion90right.png",35,(40*7)-10);

    pPorteAvion->pPorteAvionTex90rightMirrored = GameSprite_new();
    initTex(pPorteAvion->pPorteAvionTex90rightMirrored,"../img/porteAvion90rightMirrored.png",35,(40*7)-10);

    pPorteAvion->pPorteAvionTexMirrored = GameSprite_new();
    initTex(pPorteAvion->pPorteAvionTexMirrored,"../img/porteAvionMirrored.png",(40*7)-10,35);

    pPorteAvion->len = 7;
    pPorteAvion->canMove =1;

    pPorteAvion->flammes = GameSprite_new();
    pPorteAvion->flammes->init(pPorteAvion->flammes,"../img/flammes.png",(40*7)-10,35);
    pPorteAvion->flammes->color = D3DCOLOR_ARGB(100,255,255,255);
    pPorteAvion->flammesRight = GameSprite_new();
    pPorteAvion->flammesRight->init(pPorteAvion->flammesRight,"../img/flammesRight.png",35,(40*7)-10);
    pPorteAvion->flammesRight->color = D3DCOLOR_ARGB(100,255,255,255);
    return pPorteAvion;
}
/// ce constructeur est utilisé par le constructeur player_boats_new et bots_boats_new pour initaliser les cases des tableaux
/// \return
croiseur_t* croiseur_new(){
    croiseur_t* pCroiseur = (croiseur_t*)(malloc(sizeof(croiseur_t)));

    pCroiseur->pCroiseurTex = GameSprite_new();
    initTex(pCroiseur->pCroiseurTex,"../img/croiseur.png",(40*5)-10,35);

    pCroiseur->pCroiseurTex90right = GameSprite_new();
    initTex(pCroiseur->pCroiseurTex90right,"../img/croiseur90right.png",35 ,(40*5)-10);

    pCroiseur->pCroiseurTex90rightMirrored = GameSprite_new();
    initTex(pCroiseur->pCroiseurTex90rightMirrored,"../img/croiseur90rightMirrored.png",35 ,(40*5)-10);

    pCroiseur->pCroiseurTexMirrored = GameSprite_new();
    initTex(pCroiseur->pCroiseurTexMirrored,"../img/croiseurMirrored.png",(40*5)-10,35);
    pCroiseur->len = 5;
    pCroiseur->canMove =1;

    pCroiseur->flammes = GameSprite_new();
    pCroiseur->flammes->init(pCroiseur->flammes,"../img/flammes.png",(40*5)-10,35);
    pCroiseur->flammes->color = D3DCOLOR_ARGB(100,255,255,255);
    pCroiseur->flammesRight = GameSprite_new();
    pCroiseur->flammesRight->init(pCroiseur->flammesRight,"../img/flammesRight.png",35,(40*5)-10);
    pCroiseur->flammesRight->color = D3DCOLOR_ARGB(100,255,255,255);
    return pCroiseur;
}
/// ce constructeur est utilisé par le constructeur player_boats_new et bots_boats_new pour initaliser les cases des tableaux
/// \return
destroyer_t* destroyer_new(){
    destroyer_t* pDestroyer = (destroyer_t*)(malloc(sizeof(destroyer_t)));

    pDestroyer->pDestroyerTex = GameSprite_new();
    initTex(pDestroyer->pDestroyerTex,"../img/destroyer.png",(40*3)-10,35);

    pDestroyer->pDestroyerTex90right = GameSprite_new();
    initTex(pDestroyer->pDestroyerTex90right,"../img/destroyer90right.png",35,(40*3)-10);

    pDestroyer->pDestroyerTex90rightMirrored = GameSprite_new();
    initTex(pDestroyer->pDestroyerTex90rightMirrored,"../img/destroyer90rightMirrored.png",35,(40*3)-10);

    pDestroyer->pDestroyerTexMirrored = GameSprite_new();
    initTex(pDestroyer->pDestroyerTexMirrored,"../img/destroyerMirrored.png",(40*3)-10,35);
    pDestroyer->len = 3;
    pDestroyer->canMove =1;

    pDestroyer->flammes = GameSprite_new();
    pDestroyer->flammes->init(pDestroyer->flammes,"../img/flammes.png",(40*3)-10,35);
    pDestroyer->flammes->color = D3DCOLOR_ARGB(100,255,255,255);
    pDestroyer->flammesRight = GameSprite_new();
    pDestroyer->flammesRight->init(pDestroyer->flammesRight,"../img/flammesRight.png",35,(40*3)-10);
    pDestroyer->flammesRight->color = D3DCOLOR_ARGB(100,255,255,255);

    return pDestroyer;
}
/// ce constructeur est utilisé par le constructeur player_boats_new et bots_boats_new pour initaliser les cases des tableaux
/// \return
sous_marin_t* sousMarin_new(){
    sous_marin_t* pSousMarin = (sous_marin_t*)(malloc(sizeof(sous_marin_t)));

    pSousMarin->pSousMarinTex = GameSprite_new();
    initTex(pSousMarin->pSousMarinTex,"../img/sousMarin.png",38,35);
    pSousMarin->pSousMarinTexMirrored = GameSprite_new();
    initTex(pSousMarin->pSousMarinTexMirrored,"../img/sousMarinMirrored.png",38,35);

    pSousMarin->len = 1;
    pSousMarin->canMove =1;
    pSousMarin->flammes = GameSprite_new();
    pSousMarin->flammes->init(pSousMarin->flammes,"../img/flammes.png",35,35);
    pSousMarin->flammes->color = D3DCOLOR_ARGB(100,255,255,255);
    return pSousMarin;
}
#pragma endregion
void initTex(GameSprite_t* pG,const char* str,int initSizeW,int initSizeH){
    if(pG != NULL){
        pG->init(pG,str,initSizeW,initSizeH);
        if(!pG->isInit(pG)){
            MessageBoxA(NULL,"creation de la tex failed",NULL,0);
            exit(1);
        }
    }else{
        MessageBoxA(NULL,"creation du ptr GameSprite failed",NULL,0);
        exit(1);
    }
}
int isGameFinished(player_boats_t* pP,bots_boats_t* pB){
    //si tout les bateau d'un coté sont a 0
    if(pP->pPorteAvion->canMove == 0 && pP->pCroiseurs[0]->canMove == 0 && pP->pCroiseurs[1]->canMove == 0 &&
        pP->pDestroyers[0]->canMove == 0 && pP->pDestroyers[1]->canMove == 0 && pP->pDestroyers[2]->canMove == 0 &&
        pP->pSousMarins[0]->canMove == 0 && pP->pSousMarins[1]->canMove == 0 && pP->pSousMarins[2]->canMove == 0 && pP->pSousMarins[3]->canMove == 0){

        system("cls");
        int returnVal = MessageBoxA(NULL,"BOT won ! replay ?",NULL,MB_YESNO | MB_ICONEXCLAMATION);
        if(returnVal == IDYES){
            return 1;
        }else if(returnVal == IDNO){
            exit(1);
        }

    }else if(pB->pPorteAvion->canMove == 0 && pB->pCroiseurs[0]->canMove == 0 && pB->pCroiseurs[1]->canMove == 0 &&
            pB->pDestroyers[0]->canMove == 0 && pB->pDestroyers[1]->canMove == 0 && pB->pDestroyers[2]->canMove == 0 &&
            pB->pSousMarins[0]->canMove == 0 && pB->pSousMarins[1]->canMove == 0 && pB->pSousMarins[2]->canMove == 0 && pB->pSousMarins[3]->canMove == 0){

        system("cls");
        int returnVal = MessageBoxA(NULL,"PLAYER won ! replay ?",NULL,MB_YESNO | MB_ICONEXCLAMATION);
        if(returnVal == IDYES){
            return 1;
        }else if(returnVal == IDNO){
            exit(1);
        }
    }

    return 0;
}
void cleanEverything()
{
    fclose(Game->saveFile);
    free(Game);
    cleanD3D();
}
