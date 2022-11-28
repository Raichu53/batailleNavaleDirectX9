//
// Created by matt0 on 11/19/2022.
//
#include "includes.h"


#pragma region functions/structs defs
void drawScene();
void drawGrid();
void drawLine(D3DXVECTOR2 pos1,D3DXVECTOR2 pos2,int thickness,D3DCOLOR color);
D3DXVECTOR2 getWindowDimension();
#pragma endregion

#pragma region GameSprite
int init(GameSprite_t* pGS,const char* fileName, int w, int h)
{
    if (d3ddev == NULL)
    {
        MessageBox(NULL, "d3ddev is nullptr", NULL, 0);
        return 1;
    }

    //version extended de D3DXCreateTextureFromFile, prend en plus la largeur et hauteur
    HRESULT resultTex = D3DXCreateTextureFromFileExA(d3ddev, fileName, w, h, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN,
                                                     D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &(pGS->tex));

    //debuging
    if (resultTex != D3D_OK)
    {
        if (resultTex == D3DERR_INVALIDCALL)
        {
            MessageBox(NULL, "D3DERR_INVALIDCALL", NULL, 0);
            return 0;
        }
        if (resultTex == D3DERR_NOTAVAILABLE)
        {
            MessageBox(NULL, "D3DERR_NOTAVAILABLE", NULL, 0);;
            return 0;
        }
        if (resultTex == D3DERR_INVALIDCALL)
        {
            MessageBox(NULL, "D3DERR_INVALIDCALL", NULL, 0);;
            return 0;
        }
        if (resultTex == D3DERR_OUTOFVIDEOMEMORY)
        {
            MessageBox(NULL, "D3DERR_OUTOFVIDEOMEMORY", NULL, 0);
            return 0;
        }
        if (resultTex == D3DXERR_INVALIDDATA)
        {
            MessageBox(NULL, "D3DXERR_INVALIDDATA", NULL, 0);
            return 0;
        }
        if (resultTex == E_OUTOFMEMORY)
        {
            MessageBox(NULL, "E_OUTOFMEMORY", NULL, 0);
            return 0;
        }

        MessageBox(NULL, "Erreur pendant la creation de la texture", NULL, 0);
        return 0;
    }

    if (!SUCCEEDED(D3DXCreateSprite(d3ddev, &pGS->sprite)))
    {
        MessageBox(NULL, "Erreur pendant la creation du sprite", NULL, 0);
        return 0;
    }
    pGS->initialized = 1;
    return 1;
}
int isInit(struct GameSprite* pGS)
{
    return pGS->initialized;
}
void update(struct GameSprite* pGS)
{

}
void draw(struct GameSprite* pGS)
{
    if (pGS->sprite && pGS->tex)
    {
        pGS->sprite->lpVtbl->Begin(pGS->sprite,D3DXSPRITE_ALPHABLEND);


        pGS->sprite->lpVtbl->Draw(pGS->sprite,pGS->tex, NULL, NULL, &pGS->pos, pGS->color);

        pGS->sprite->lpVtbl->End(pGS->sprite);

    }
}
D3DXVECTOR2 getPos(struct GameSprite* pGS)
{
    return (D3DXVECTOR2){ pGS->pos.x,pGS->pos.y };
}
void setPos(struct GameSprite* pGS,float x, float y)
{
    pGS->pos.x = x;
    pGS->pos.y = y;
}
void GameSprite_delete(struct GameSprite* pGS)
{
    if (pGS->sprite)
    {
        pGS->sprite->lpVtbl->Release(pGS->sprite);
        pGS->sprite = 0;
    }
    if (pGS->tex)
    {
        pGS->tex->lpVtbl->Release(pGS->tex);
        pGS->tex = 0;
    }
}

GameSprite_t* GameSprite_new()
{
    GameSprite_t* pGS = malloc(sizeof(GameSprite_t));
    pGS->pos.x = 0;
    pGS->pos.y = 0;
    pGS->pos.z = 0;

    pGS->color = D3DCOLOR_ARGB(255, 255, 255, 255);

    pGS->initialized = 0;
    pGS->tex = NULL;
    pGS->sprite = NULL;

    pGS->init = &init;
    pGS->isInit = &isInit;
    pGS->draw = &draw;
    pGS->update = &update;
    pGS->setPos = &setPos;
    pGS->getPos = &getPos;
    pGS->GameSprite_delete = &GameSprite_delete;
    return pGS;
}
GameSprite_t* GameSprite_newWithPos(float x, float y)
{
    GameSprite_t* pGS = malloc(sizeof(GameSprite_t));
    pGS->pos.x = x;
    pGS->pos.y = y;
    pGS->pos.z = 0;

    pGS->color = D3DCOLOR_ARGB(255, 255, 255, 255);

    pGS->initialized = 0;
    pGS->tex = NULL;
    pGS->sprite = NULL;

    pGS->init = &init;
    pGS->isInit = &isInit;
    pGS->draw = &draw;
    pGS->update = &update;
    pGS->setPos = &setPos;
    pGS->getPos = &getPos;
    pGS->GameSprite_delete = &GameSprite_delete;
    return pGS;
}

#pragma endregion

void initD3D(HWND window)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);    // crée l'interface direct3D
    D3DPRESENT_PARAMETERS d3dpp;    // crée les param pour la creation du device

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;    // pas fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = window;    //la fenetre sur laquelle on va utilisé direct3D


    // on crée la struct du device en utilisant les params d3dpp
    d3d->lpVtbl->CreateDevice(d3d,D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      window,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
    //init main struct
    Game = game_new(window);
    spawnBoats(Game->pBots_boats,Game->pPlayer_boats);
}
void render_frame()
{
    // Clear rose
    d3ddev->lpVtbl->Clear(d3ddev,0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

    d3ddev->lpVtbl->BeginScene(d3ddev);    // demarre la scene 3D

    // do 3D rendering here
    drawScene();

    d3ddev->lpVtbl->EndScene(d3ddev);    // ferme la scene 3D

    d3ddev->lpVtbl->Present(d3ddev,NULL, NULL, NULL, NULL);   // affiche la frame que l'on vien de crée
}
void cleanD3D()
{
    d3ddev->lpVtbl->Release(d3ddev);
    d3d->lpVtbl->Release(d3d);
}

void drawScene()
{
    drawGrid();
    drawPlayerBoats(Game->pPlayer_boats);
    drawBotsBoats(Game->pBots_boats);

}
void drawPlayerBoats(player_boats_t* pP)
{
    {
        if(pP->pPorteAvion->isVertical){
            pP->pPorteAvion->pPorteAvionTex90right->setPos(pP->pPorteAvion->pPorteAvionTex90right,
                                                           pP->pPorteAvion->pC->posInGrid.x + 5,
                                                           pP->pPorteAvion->pC->posInGrid.y - (40*6) + 5);
            pP->pPorteAvion->pPorteAvionTex90right->draw(pP->pPorteAvion->pPorteAvionTex90right);
        }else{
            pP->pPorteAvion->pPorteAvionTex->setPos(pP->pPorteAvion->pPorteAvionTex, //multiplier par 6 ou 7 ?
                                                    pP->pPorteAvion->pC->posInGrid.x - ((40*5)+30), //les textures partent de la fin et pas du debut
                                                    pP->pPorteAvion->pC->posInGrid.y + 5);
            pP->pPorteAvion->pPorteAvionTex->draw(pP->pPorteAvion->pPorteAvionTex);
        }
    }
    {
        for(int i = 0;i < 2;i++){
            if(pP->pCroiseurs[i]->isVertical){
                pP->pCroiseurs[i]->pCroiseurTex90right->setPos(pP->pCroiseurs[i]->pCroiseurTex90right,
                                                               pP->pCroiseurs[i]->pC->posInGrid.x + 5,
                                                               pP->pCroiseurs[i]->pC->posInGrid.y - (40*4) + 5);
                pP->pCroiseurs[i]->pCroiseurTex90right->draw(pP->pCroiseurs[i]->pCroiseurTex90right);
            }else{
                pP->pCroiseurs[i]->pCroiseurTex->setPos(pP->pCroiseurs[i]->pCroiseurTex,
                                                        pP->pCroiseurs[i]->pC->posInGrid.x - ((40*3)+30), //les textures partent de la fin et pas du debut
                                                        pP->pCroiseurs[i]->pC->posInGrid.y + 5);
                pP->pCroiseurs[i]->pCroiseurTex->draw(pP->pCroiseurs[i]->pCroiseurTex);
            }
        }
    }

    {
        for(int i = 0;i < 3;i++){
            if(pP->pDestroyers[i]->isVertical){
                pP->pDestroyers[i]->pDestroyerTex90right->setPos(pP->pDestroyers[i]->pDestroyerTex90right,
                                                                 pP->pDestroyers[i]->pC->posInGrid.x + 5,
                                                                 pP->pDestroyers[i]->pC->posInGrid.y - (40*2) + 5);
                pP->pDestroyers[i]->pDestroyerTex90right->draw(pP->pDestroyers[i]->pDestroyerTex90right);
            }else{
                pP->pDestroyers[i]->pDestroyerTex->setPos(pP->pDestroyers[i]->pDestroyerTex,
                                                        pP->pDestroyers[i]->pC->posInGrid.x - ((40*1)+30), //les textures partent de la fin et pas du debut
                                                        pP->pDestroyers[i]->pC->posInGrid.y + 5);
                pP->pDestroyers[i]->pDestroyerTex->draw(pP->pDestroyers[i]->pDestroyerTex);
            }
        }
    }
    {
        for(int i = 0;i < 4;i++){
            pP->pSousMarins[i]->pSousMarinTex->setPos(pP->pSousMarins[i]->pSousMarinTex, //multiplier par 6 ou 7 ?
                                                      pP->pSousMarins[i]->pC->posInGrid.x + 1, //les textures partent de la fin et pas du debut
                                                      pP->pSousMarins[i]->pC->posInGrid.y + 5);
            pP->pSousMarins[i]->pSousMarinTex->draw(pP->pSousMarins[i]->pSousMarinTex);
        }
    }

}
void drawBotsBoats(bots_boats_t* pB){
    {
        if (pB->pPorteAvion->isVertical) {
            pB->pPorteAvion->pPorteAvionTex90right->setPos(pB->pPorteAvion->pPorteAvionTex90right,
                                                           pB->pPorteAvion->pC->posInGrid.x + 5,
                                                           pB->pPorteAvion->pC->posInGrid.y - (40 * 6) + 5);
            pB->pPorteAvion->pPorteAvionTex90right->draw(pB->pPorteAvion->pPorteAvionTex90right);
        } else {
            pB->pPorteAvion->pPorteAvionTex->setPos(pB->pPorteAvion->pPorteAvionTex,
                                                    pB->pPorteAvion->pC->posInGrid.x -
                                                    ((40 * 5) + 30), //les textures partent de la fin et pas du debut
                                                    pB->pPorteAvion->pC->posInGrid.y + 5);
            pB->pPorteAvion->pPorteAvionTex->draw(pB->pPorteAvion->pPorteAvionTex);
        }
    }
    {
        for(int i = 0;i < 2;i++){
            if(pB->pCroiseurs[i]->isVertical){
                pB->pCroiseurs[i]->pCroiseurTex90right->setPos(pB->pCroiseurs[i]->pCroiseurTex90right,
                                                               pB->pCroiseurs[i]->pC->posInGrid.x + 5,
                                                               pB->pCroiseurs[i]->pC->posInGrid.y - (40*4) + 5);
                pB->pCroiseurs[i]->pCroiseurTex90right->draw(pB->pCroiseurs[i]->pCroiseurTex90right);
            }else{
                pB->pCroiseurs[i]->pCroiseurTex->setPos(pB->pCroiseurs[i]->pCroiseurTex,
                                                        pB->pCroiseurs[i]->pC->posInGrid.x - ((40*3)+30), //les textures partent de la fin et pas du debut
                                                        pB->pCroiseurs[i]->pC->posInGrid.y + 5);
                pB->pCroiseurs[i]->pCroiseurTex->draw(pB->pCroiseurs[i]->pCroiseurTex);
            }
        }
    }

    {
        for(int i = 0;i < 3;i++){
            if(pB->pDestroyers[i]->isVertical){
                pB->pDestroyers[i]->pDestroyerTex90right->setPos(pB->pDestroyers[i]->pDestroyerTex90right,
                                                                 pB->pDestroyers[i]->pC->posInGrid.x + 5,
                                                                 pB->pDestroyers[i]->pC->posInGrid.y - (40*2) + 5);
                pB->pDestroyers[i]->pDestroyerTex90right->draw(pB->pDestroyers[i]->pDestroyerTex90right);
            }else{
                pB->pDestroyers[i]->pDestroyerTex->setPos(pB->pDestroyers[i]->pDestroyerTex,
                                                          pB->pDestroyers[i]->pC->posInGrid.x - ((40*1)+30), //les textures partent de la fin et pas du debut
                                                          pB->pDestroyers[i]->pC->posInGrid.y + 5);
                pB->pDestroyers[i]->pDestroyerTex->draw(pB->pDestroyers[i]->pDestroyerTex);
            }
        }
    }
    {
        for(int i = 0;i < 4;i++){
            pB->pSousMarins[i]->pSousMarinTex->setPos(pB->pSousMarins[i]->pSousMarinTex, //multiplier par 6 ou 7 ?
                                                      pB->pSousMarins[i]->pC->posInGrid.x + 1, //les textures partent de la fin et pas du debut
                                                      pB->pSousMarins[i]->pC->posInGrid.y + 5);
            pB->pSousMarins[i]->pSousMarinTex->draw(pB->pSousMarins[i]->pSousMarinTex);
        }
    }
}
void drawGrid() {

    //bot
    for(int i = 0; i < GAME_DIMENSION;i++){
        for(int k = 0; k < GAME_DIMENSION;k++){
            //la bare en haut et le coté droit
            drawLine((D3DXVECTOR2){Game->botPlayground[i][k]->posInGrid.x,Game->botPlayground[i][k]->posInGrid.y},
                     (D3DXVECTOR2){Game->botPlayground[i][k]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->botPlayground[i][k]->posInGrid.y},
                     1, D3DCOLOR_XRGB(0,0,0));
            drawLine((D3DXVECTOR2){Game->botPlayground[i][k]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->botPlayground[i][k]->posInGrid.y  },
                     (D3DXVECTOR2){Game->botPlayground[i][k]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->botPlayground[i][k]->posInGrid.y + ((WINDOW_WIDTH/2)/15) },
                     1, D3DCOLOR_XRGB(0,0,0));
        }
    }
    //player
    for(int j = 0; j < GAME_DIMENSION;j++){
        for(int l = 0; l < GAME_DIMENSION;l++){
            //la bare en haut et le coté droit
            drawLine((D3DXVECTOR2){Game->playerPlayground[j][l]->posInGrid.x,Game->playerPlayground[j][l]->posInGrid.y},
                     (D3DXVECTOR2){Game->playerPlayground[j][l]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->playerPlayground[j][l]->posInGrid.y},
                     1, D3DCOLOR_XRGB(0,0,0));
            drawLine((D3DXVECTOR2){Game->playerPlayground[j][l]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->playerPlayground[j][l]->posInGrid.y  },
                     (D3DXVECTOR2){Game->playerPlayground[j][l]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->playerPlayground[j][l]->posInGrid.y + ((WINDOW_WIDTH/2)/15) },
                     1, D3DCOLOR_XRGB(0,0,0));
        }
    }
    drawLine((D3DXVECTOR2){WINDOW_WIDTH/2,0},(D3DXVECTOR2){WINDOW_WIDTH/2,WINDOW_HEIGHT},1,D3DCOLOR_XRGB(255,0,0));
}
void drawLine(D3DXVECTOR2 pos1,D3DXVECTOR2 pos2,int thickness,D3DCOLOR color)
{
    LPD3DXLINE LineL;
    D3DXCreateLine(d3ddev, &LineL);

    D3DXVECTOR2 Line[2];
    Line[0] = pos1;
    Line[1] = pos2;

    LineL->lpVtbl->SetWidth(LineL,thickness);
    LineL->lpVtbl->Draw(LineL,Line, 2, color);
    LineL->lpVtbl->Release(LineL);
}
D3DXVECTOR2 getWindowDimension()
{
    RECT rect;
    int width,height;
    if(GetWindowRect(Game->window, &rect))
    {
         width = rect.right - rect.left;
         height = rect.bottom - rect.top;
    }
    return (D3DXVECTOR2){width,height};
}
