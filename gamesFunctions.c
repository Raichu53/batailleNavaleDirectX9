//
// Created by matt0 on 11/16/2022.
//
#include "includes.h"

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
        if(bBot){
            //on assigne la pos du coin hut gauche en px
            pCase->posInGrid.x = collumnIndex*((WINDOW_WIDTH/2)/15);
            pCase->posInGrid.y = rowIndex*((WINDOW_WIDTH/2)/15);
        }
        else{
            pCase->posInGrid.x = (WINDOW_WIDTH/2) + collumnIndex*((WINDOW_WIDTH/2)/15);
            pCase->posInGrid.y = rowIndex*((WINDOW_WIDTH/2)/15);
        }
        return pCase;
    }else{
        MessageBoxA(NULL,"Case_t* is NULL",NULL,0);
        exit(1);
    }
}