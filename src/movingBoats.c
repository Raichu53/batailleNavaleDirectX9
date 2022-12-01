//
// Created by matt0 on 11/29/2022.
//
#include "includes.h"
/*
 * 1 - on attend un clic
 * 2 - on cherche la case ou il a cliquer
 * 3 - on check si ya un bateau
 * 4 - ...
 */
void playerActions(){
    //either use this struct provided by windows api MOUSEINPUT or getASyncKeyState()

    int boatSize = 0;
    void* ptr = NULL;
    Case_t* pClickedCase = NULL;


    GetCursorPos(Game->cursorPos);
    Game->windowPos = GetWindowPos();
    if(cursorIsInWindow(-1,Game->cursorPos,Game->windowPos)){ //on check d'abord si on est dans la fenetre entiere
        //ça serait bien de faire un "custom windows pointer"
        if(GetAsyncKeyState(VK_LBUTTON)){
            if(cursorIsInWindow(1,Game->cursorPos,Game->windowPos)){ //on check ensuite si dequel coté de la map on est
                pClickedCase = getCasePtrWithPxCoords(1,(vec2_t){Game->cursorPos->x - Game->windowPos.x,
                                                                 Game->cursorPos->y - Game->windowPos.y - 30});
                if(pClickedCase != NULL){
                    if(pClickedCase->isOccupied){
                        //trouver a quel bateau cette case apartient
                        ptr = findBoatPtrWithCase(1,pClickedCase);
                        boatSize = *(int*)ptr; //la longeur d'un bateau est a l'offset 0 de la struct
                        switch (boatSize) {
                            case 1: //sous marin
                                Game->sousMarinPtr = (sous_marin_t*)findBoatPtrWithCase(1,pClickedCase);
                                printf("sous marin selected, waiting for input...\n");
                                Game->waitingInput = 1;
                                Game->index = 4;
                                break;
                            case 3:
                                Game->destroyerPtr = (destroyer_t*)findBoatPtrWithCase(1,pClickedCase);
                                printf("destroyer selected, waiting for input...\n");
                                Game->waitingInput = 1;
                                Game->index = 3;
                                break;
                            case 5:
                                Game->croiseurPtr = (croiseur_t *)findBoatPtrWithCase(1,pClickedCase);
                                printf("croiseur selected, waiting for input...\n");
                                Game->waitingInput = 1;
                                Game->index = 2;
                                break;
                            case 7:
                                Game->porteAvionPtr = (porte_avion_t*)findBoatPtrWithCase(1,pClickedCase);
                                printf("porteAvion selected, waiting for input...\n");
                                Game->waitingInput = 1;
                                Game->index = 1;
                                break;
                            default:
                                MessageBoxA(NULL,"fct : PlayerActions() failed",NULL,0);
                                break;
                        }
                    }else{
                        printf("you have no boats here\n");
                    }
                }
            }
            else{
                printf("bot side\n");
            }
        }
    }
}
int inputs(int index,porte_avion_t* pPorteAvion,croiseur_t* pCroiseurs,destroyer_t* pDestroyers,sous_marin_t* pSousMarins){
    if(Game->waitingInput){
        if(GetAsyncKeyState(90)){
            printf("z\n");
            Game->waitingInput = 0;
            Game->inputHasBeenSend = 1;
        }else if(GetAsyncKeyState(83)){
            printf("s\n");
            Game->waitingInput = 0;
            Game->inputHasBeenSend = -1;
        }
    }
    if(Game->inputHasBeenSend == 1){
        moveBoat(index,1,Game->porteAvionPtr,Game->croiseurPtr,Game->destroyerPtr,Game->sousMarinPtr);
        Game->inputHasBeenSend = 0;
    }
    else if(Game->inputHasBeenSend == -1){
        moveBoat(index,0,Game->porteAvionPtr,Game->croiseurPtr,Game->destroyerPtr,Game->sousMarinPtr);
        Game->inputHasBeenSend = 0;
    }
    return 0;
}
//index = 1 pour porte avion 2 croiseur 3 destroyer et 4 sous marin
int moveBoat(int index,int bForward,
             porte_avion_t* pPorteAvion,croiseur_t* pCroiseurs,destroyer_t* pDestroyers,sous_marin_t* pSousMarins)
{
    switch (index) {
        case 1:
            if(pPorteAvion->isVertical){
                if(bForward){
                    //printf("on avance\n");
                }else{
                    //printf("on recule\n");
                }
            }else{
                if(bForward){

                }else{

                }
            }
            break;
        case 2:
            if(pCroiseurs->isVertical){
                if(bForward){

                }else{

                }
            }else{
                if(bForward){

                }else{

                }
            }
            break;
        case 3:
            if(pDestroyers->isVertical){
                if(bForward){

                }else{

                }
            }else{
                if(bForward){

                }else{

                }
            }
            break;
        case 4:
            if(bForward){

            }else{

            }
            break;
        default:
            break;
    }
}
///
/// \param side = 1 pour le player 0 pour le bot
/// \param case_ptr
/// \return un ptr sur le bateau
void* findBoatPtrWithCase(int side,Case_t* case_ptr){
    if(side){
        for(int j = 0; j < 7;j++){
            if(Game->pPlayer_boats->pPorteAvion->currentHealth[j]->id == case_ptr->id){
                return Game->pPlayer_boats->pPorteAvion;
            }
        }
        for(int k = 0; k < 2;k++){
            for(int l = 0; l < 5;l++){
                if(Game->pPlayer_boats->pCroiseurs[k]->currentHealth[l]->id == case_ptr->id){
                    return Game->pPlayer_boats->pCroiseurs[k];
                }
            }
        }
        for(int p = 0; p < 3;p++){
            for(int f = 0; f < 3;f++){
                if(Game->pPlayer_boats->pDestroyers[p]->currentHealth[f]->id == case_ptr->id){
                    return Game->pPlayer_boats->pDestroyers[p];
                }
            }
        }
        for(int y = 0; y < 4;y++){
            if(Game->pPlayer_boats->pSousMarins[y]->currentHealth->id == case_ptr->id){
                return Game->pPlayer_boats->pSousMarins[y];
            }
        }
    }else{

    }
}
///
/// \param side le mettre a -1 si on veut juste savoir si on est dans la window, 0 si on veut le side du bot et 1 le side player
/// \param cursorPos
/// \param windowPos
/// \return
int cursorIsInWindow(int side,LPPOINT cursorPos,vec2_t windowPos)
{
    if(side == -1){
        if((cursorPos->x > windowPos.x) && (cursorPos->x < (windowPos.x + WINDOW_WIDTH))){
            if((cursorPos->y > (windowPos.y + 32)) && (cursorPos->y < (windowPos.y + WINDOW_HEIGHT))){ //32 is the window bar height
                return 1;
            }
        }
        return 0;
    }
    else if(side == 0){
        if((cursorPos->x > (windowPos.x + (WINDOW_WIDTH/2))) && (cursorPos->x < (windowPos.x + WINDOW_WIDTH))){
            if((cursorPos->y > (windowPos.y + 32)) && (cursorPos->y < (windowPos.y + WINDOW_HEIGHT))){
                return 1;
            }
        }
        return 0;
    }
    else if(side == 1){
        if((cursorPos->x > windowPos.x) && (cursorPos->x < (windowPos.x + (WINDOW_WIDTH/2)))){
            if((cursorPos->y > (windowPos.y + 32)) && (cursorPos->y < (windowPos.y + WINDOW_HEIGHT))){
                return 1;
            }
        }
        return 0;
    }
    else{
        MessageBoxA(NULL,"fct : cursorIsInWindow failed",NULL,0);
        return 0;
    }
}

Case_t* getCasePtrWithPxCoords(int isPlayer,vec2_t relativeXY)
{
    //printf("%d %d\n",relativeXY.x,relativeXY.y);
    vec2_t pV;
    for(int i = 0; i < GAME_DIMENSION;i++){
        for(int j = 0; j  < GAME_DIMENSION;j++){
            if(isPlayer){
                pV = Game->playerPlayground[i][j]->posInGrid;
                if((pV.x < relativeXY.x) && ((pV.x + 40) > relativeXY.x)){
                    if(pV.y < relativeXY.y && ((pV.y + 40) > relativeXY.y)){
                        //printf("player %d",Game->botPlayground[i][j]->id);
                        return getCasePtrWithId(1,Game->playerPlayground[i][j]->id);
                    }
                }
            }else{
                pV = Game->botPlayground[i][j]->posInGrid;
                if((pV.x < relativeXY.x) && ((pV.x + 40) > relativeXY.x)){
                    if(pV.y < relativeXY.y && ((pV.y + 40) > relativeXY.y)){
                        //printf("bot %d",Game->botPlayground[i][j]->id);
                        return getCasePtrWithId(0,Game->botPlayground[i][j]->id);
                    }
                }
            }
        }
    }
}

vec2_t GetWindowPos() {
    RECT rect = {};
    vec2_t pos;
    if( GetWindowRect( Game->window, &rect ) ) {
        pos.x = rect.left;
        pos.y = rect.top;
    }
    return pos;
}
