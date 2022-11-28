//
// Created by matt0 on 11/16/2022.
//
#include "includes.h"
#pragma region constructeurs
Game_t* game_new(HWND window)
{
    Game_t* pGame = (Game_t*)(malloc(sizeof(Game_t)));
    if(pGame != NULL){

        pGame->window = window;
        //bot side
        for(int i = 0; i < GAME_DIMENSION;i++){
            for(int j = 0; j < GAME_DIMENSION;j++){
                pGame->botPlayground[i][j] = case_new(i,j,1);
            }
        }
        //player side
        for(int k = 0; k < GAME_DIMENSION;k++){
            for(int l = 0; l < GAME_DIMENSION;l++){
                pGame->playerPlayground[k][l] = case_new(k,l,0);
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


        return pGame;
    }else{
        MessageBoxA(NULL,"Game* is NULL",NULL,0);
        exit(1);
    }
}
Case_t* case_new(int rowIndex,int collumnIndex,int bBot)
{
    Case_t* pCase = (Case_t*)(malloc(sizeof(Case_t)));
    if(pCase != NULL){
        pCase->id = ((rowIndex*15) + collumnIndex);
        pCase->isOccupied = 0;
        if(bBot){
            //on assigne la pos du coin hut gauche en px
            pCase->posInGrid.x = (WINDOW_WIDTH/2) +collumnIndex*((WINDOW_WIDTH/2)/15);
            pCase->posInGrid.y = rowIndex*((WINDOW_WIDTH/2)/15);
        }
        else{
            pCase->posInGrid.x =  collumnIndex*((WINDOW_WIDTH/2)/15);
            pCase->posInGrid.y = rowIndex*((WINDOW_WIDTH/2)/15);
        }
        return pCase;
    }else{
        MessageBoxA(NULL,"Case_t* is NULL",NULL,0);
        exit(1);
    }
}
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
porte_avion_t* porteAvion_new(){
    porte_avion_t* pPorteAvion = (porte_avion_t*)(malloc(sizeof(porte_avion_t)));
    pPorteAvion->pPorteAvionTex = NULL;
    pPorteAvion->pPorteAvionTex = GameSprite_new();
    if(pPorteAvion->pPorteAvionTex != NULL){
        pPorteAvion->pPorteAvionTex->init(pPorteAvion->pPorteAvionTex,"../img/porteAvion.png",(40*7)-10,35);//param w multiplié par la longeur du bateau
        if(!pPorteAvion->pPorteAvionTex->isInit(pPorteAvion->pPorteAvionTex)){
            MessageBoxA(NULL,"creatiobn de la tex du porte avion failed",NULL,0);
            exit(1);
        }
    }else{
        MessageBoxA(NULL,"creation du ptr GameSprite pour le porte avion failed",NULL,0);
        exit(1);
    }
    pPorteAvion->pPorteAvionTex90right = NULL;
    pPorteAvion->pPorteAvionTex90right = GameSprite_new();
    if(pPorteAvion->pPorteAvionTex90right != NULL){
        pPorteAvion->pPorteAvionTex90right->init(pPorteAvion->pPorteAvionTex90right,"../img/porteAvion90right.png",35,(40*7)-10);//param w multiplié par la longeur du bateau
        if(!pPorteAvion->pPorteAvionTex90right->isInit(pPorteAvion->pPorteAvionTex90right)){
            MessageBoxA(NULL,"creatiobn de la tex du porte avion 90 right failed",NULL,0);
            exit(1);
        }
    }else{
        MessageBoxA(NULL,"creation du ptr GameSprite pour le porte avion failed",NULL,0);
        exit(1);
    }
    pPorteAvion->len = 7;

    return pPorteAvion;
}
croiseur_t* croiseur_new(){
    croiseur_t* pCroiseur = (croiseur_t*)(malloc(sizeof(croiseur_t)));
    pCroiseur->pCroiseurTex = NULL;
    pCroiseur->pCroiseurTex = GameSprite_new();
    if(pCroiseur->pCroiseurTex != NULL){
        pCroiseur->pCroiseurTex->init(pCroiseur->pCroiseurTex,"../img/croiseur.png",(40*5)-10,35);
        if(!pCroiseur->pCroiseurTex->isInit(pCroiseur->pCroiseurTex)){
            MessageBoxA(NULL,"creatiobn de la tex du croiseur failed",NULL,0);
            exit(1);
        }
    }else{
        MessageBoxA(NULL,"creation du ptr GameSprite pour le croiseur failed",NULL,0);
        exit(1);
    }
    pCroiseur->pCroiseurTex90right = NULL;
    pCroiseur->pCroiseurTex90right = GameSprite_new();
    if(pCroiseur->pCroiseurTex90right != NULL){
        pCroiseur->pCroiseurTex90right->init(pCroiseur->pCroiseurTex90right,"../img/croiseur90right.png",35 ,(40*5)-10);
        if(!pCroiseur->pCroiseurTex90right->isInit(pCroiseur->pCroiseurTex90right)){
            MessageBoxA(NULL,"creatiobn de la tex du croiseur failed",NULL,0);
            exit(1);
        }
    }else{
        MessageBoxA(NULL,"creation du ptr GameSprite pour le croiseur failed",NULL,0);
        exit(1);
    }
    pCroiseur->len = 5;

    return pCroiseur;
}
destroyer_t* destroyer_new(){
    destroyer_t* pDestroyer = (destroyer_t*)(malloc(sizeof(destroyer_t)));
    pDestroyer->pDestroyerTex = NULL;
    pDestroyer->pDestroyerTex = GameSprite_new();
    if(pDestroyer->pDestroyerTex != NULL){
        pDestroyer->pDestroyerTex->init(pDestroyer->pDestroyerTex,"../img/destroyer.png",(40*3)-10,35);
        if(!pDestroyer->pDestroyerTex->isInit(pDestroyer->pDestroyerTex)){
            MessageBoxA(NULL,"creatiobn de la tex du destroyer failed",NULL,0);
            exit(1);
        }
    }else{
        MessageBoxA(NULL,"creation du ptr GameSprite pour le destroyer failed",NULL,0);
        exit(1);
    }
    pDestroyer->pDestroyerTex90right = NULL;
    pDestroyer->pDestroyerTex90right = GameSprite_new();
    if(pDestroyer->pDestroyerTex90right != NULL){
        pDestroyer->pDestroyerTex90right->init(pDestroyer->pDestroyerTex90right,"../img/destroyer90right.png",35,(40*3)-10);
        if(!pDestroyer->pDestroyerTex90right->isInit(pDestroyer->pDestroyerTex90right)){
            MessageBoxA(NULL,"creatiobn de la tex du destroyer failed",NULL,0);
            exit(1);
        }
    }else{
        MessageBoxA(NULL,"creation du ptr GameSprite pour le destroyer failed",NULL,0);
        exit(1);
    }
    pDestroyer->len = 3;

    return pDestroyer;
}
sous_marin_t* sousMarin_new(){
    sous_marin_t* pSousMarin = (sous_marin_t*)(malloc(sizeof(sous_marin_t)));
    pSousMarin->pSousMarinTex = NULL;

    pSousMarin->pSousMarinTex = GameSprite_new();
    if(pSousMarin->pSousMarinTex != NULL){
        pSousMarin->pSousMarinTex->init(pSousMarin->pSousMarinTex,"../img/sousMarin.png",38,35);
        if(!pSousMarin->pSousMarinTex->isInit(pSousMarin->pSousMarinTex)){
            MessageBoxA(NULL,"creatiobn de la tex du sous marin failed",NULL,0);
            exit(1);
        }
    }else{
        MessageBoxA(NULL,"creation du ptr GameSprite pour le sous marin failed",NULL,0);
        exit(1);
    }

    pSousMarin->len = 1;

    return pSousMarin;
}
#pragma endregion