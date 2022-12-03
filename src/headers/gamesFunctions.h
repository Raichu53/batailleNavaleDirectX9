//
// Created by matt0 on 11/16/2022.
//

#ifndef PROJET_GAMESFUNCTIONS_H
#define PROJET_GAMESFUNCTIONS_H

#define GAME_DIMENSION 15
#include <d3d9.h>
#include <d3dx9.h>
typedef struct vec2{
    int x,y;
}vec2_t;

typedef struct GameSprite
{
    //ptr vers les fonctions, assignation dans la fonction qui sert de "constructeur" (GameSprite_new)
    //on ajoute des parenthese sinon ça revient a dire fonction qui renvoie un ptr de type void
    void (*GameSprite_delete)(struct GameSprite* pGS);

    int (*init)(struct GameSprite* pGS,const char* fileName, int w, int h);
    int (*isInit)(struct GameSprite* pGS);
    void (*update)(struct GameSprite* pGS);
    void (*draw)(struct GameSprite* pGS);

    //getters and setters
    D3DXVECTOR2 (*getPos)(struct GameSprite* pGS);
    void (*setPos)(struct GameSprite* pGS,float x, float y);

    int initialized;
    LPDIRECT3DTEXTURE9 tex;
    LPD3DXSPRITE sprite;

    D3DXVECTOR3 pos;
    D3DCOLOR color;
}GameSprite_t;
typedef struct Case{
    int id;
    vec2_t posInGrid;
    int isOccupied;
    int healthStatus;

    GameSprite_t* fireBall;
}Case_t;
typedef struct sous_marin{
    int len,canMove;
    Case_t* currentHealth; //array en partant de l'avant vers l'arriere du bateau pour savoir ou il y a des hits
    //il faut placer les images dans le meme dossier que l'exe
    GameSprite_t* pSousMarinTex;
    GameSprite_t* pSousMarinTexMirrored;

    GameSprite_t* flammes;
    int caseId;
    int isVertical;
    Case_t* pC;
}sous_marin_t;
typedef struct destroyer{
    int len,canMove;
    Case_t* currentHealth[3];

    GameSprite_t* pDestroyerTex;
    GameSprite_t* pDestroyerTex90right;
    GameSprite_t* pDestroyerTexMirrored;
    GameSprite_t* pDestroyerTex90rightMirrored;

    GameSprite_t* flammes;
    GameSprite_t* flammesRight;
    int caseId;
    int isVertical;
    Case_t* pC;
}destroyer_t;
typedef struct croiseur{
    int len,canMove;
    Case_t* currentHealth[5];

    GameSprite_t* pCroiseurTex;
    GameSprite_t* pCroiseurTex90right;
    GameSprite_t* pCroiseurTexMirrored;
    GameSprite_t* pCroiseurTex90rightMirrored;

    GameSprite_t* flammes;
    GameSprite_t* flammesRight;
    int caseId;
    int isVertical;
    Case_t* pC;
}croiseur_t;
typedef struct porte_avion{
    int len,canMove;
    Case_t* currentHealth[7];

    GameSprite_t* pPorteAvionTex;
    GameSprite_t* pPorteAvionTex90right;
    GameSprite_t* pPorteAvionTexMirrored;
    GameSprite_t* pPorteAvionTex90rightMirrored;

    GameSprite_t* flammes;
    GameSprite_t* flammesRight;
    int caseId;
    int isVertical;
    Case_t* pC;
}porte_avion_t;
typedef struct bots_boats{
    porte_avion_t* pPorteAvion;
    croiseur_t* pCroiseurs[2];
    destroyer_t* pDestroyers[3];
    sous_marin_t* pSousMarins[4];
}bots_boats_t;
typedef struct player_boats{
    porte_avion_t* pPorteAvion;
    croiseur_t* pCroiseurs[2];
    destroyer_t* pDestroyers[3];
    sous_marin_t* pSousMarins[4];
}player_boats_t;

typedef struct Game{
    int waitingInput,inputHasBeenSend,index,toggleMenu,playerTurn;
    HWND window;
    vec2_t windowPos;
    LPPOINT cursorPos;

    //le 1er index est la hauteur le 2eme est la largeur
    Case_t* botPlayground[GAME_DIMENSION][GAME_DIMENSION];
    Case_t* playerPlayground[GAME_DIMENSION][GAME_DIMENSION];
    bots_boats_t* pBots_boats;
    player_boats_t* pPlayer_boats;

    sous_marin_t* sousMarinPtr;
    destroyer_t* destroyerPtr;
    croiseur_t* croiseurPtr;
    porte_avion_t* porteAvionPtr;
    Case_t* pClickedCase;

    GameSprite_t* fireballBuffer; //optimization

    struct timeval tp;
}Game_t;

Case_t* case_new(GameSprite_t* fireballTex,int rowLen,int collumnlen,int bBot);
Game_t* game_new(HWND window);
bots_boats_t* bots_boats_new();
player_boats_t* player_boats_new();
porte_avion_t* porteAvion_new();
croiseur_t* croiseur_new();
destroyer_t* destroyer_new();
sous_marin_t* sousMarin_new();

void initTex(GameSprite_t* pG,const char* str,int initSizeW,int initSizeH);
void cleanEverything();
int isGameFinished();
#endif //PROJET_GAMESFUNCTIONS_H
