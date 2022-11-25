//
// Created by matt0 on 11/16/2022.
//

#ifndef PROJET_GAMESFUNCTIONS_H
#define PROJET_GAMESFUNCTIONS_H

#define GAME_DIMENSION 15
typedef struct vec2{
    int x,y;
}vec2_t;
typedef struct Case{
    vec2_t posInGrid;
    int id;

}Case_t;
typedef struct Game{
    HWND window;
    //le 1er index est la hauteur le 2eme est la largeur
    Case_t* botPlayground[GAME_DIMENSION][GAME_DIMENSION];
    Case_t* playerPlayground[GAME_DIMENSION][GAME_DIMENSION];
}Game_t;

Case_t* case_new(int rowLen,int collumnlen,int bBot);
Game_t* game_new(HWND window);
#endif //PROJET_GAMESFUNCTIONS_H
