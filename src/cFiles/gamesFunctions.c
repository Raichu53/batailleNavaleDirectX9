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