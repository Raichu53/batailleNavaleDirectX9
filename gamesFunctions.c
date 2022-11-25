//
// Created by matt0 on 11/16/2022.
//
#include "includes.h"

Game_t* game_new(HWND window)
{
    Game_t* pGame = malloc(sizeof(Game_t));
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
}
Case_t* case_new(int rowIndex,int collumnIndex,int bBot)
{
    Case_t* pCase = malloc(sizeof(Game_t));
    pCase->id = ((rowIndex*15) + collumnIndex);
    if(bBot){
        //on assigne la pos du coin hut gauche en px
    }
    else{

    }
    return pCase;
}