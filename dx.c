//
// Created by matt0 on 11/19/2022.
//
#include "includes.h"
#include "./MicrosoftDirectXSDKJune2010/Include/d3d9.h"
#include "./MicrosoftDirectXSDKJune2010/Include/d3dx9.h"
IDirect3D9* d3d = NULL;
IDirect3DDevice9* d3ddev = NULL;

#pragma region functions/structs defs
void drawScene();
void drawGrid();
void drawLine(D3DXVECTOR2 pos1,D3DXVECTOR2 pos2,int thickness,D3DCOLOR color);

#pragma endregion

#pragma region GameSprite
//il faut placer les images dans le meme dossier que l'exe
typedef struct GameSprite
{
    //ptr vers les fonctions, assignation dans la fonction qui sert de "constructeur" (GameSprite_new)
    void (*GameSprite_delete)(struct GameSprite* pGS);

    int (*init)(struct GameSprite* pGS,const char* fileName, int w, int h);
    int (*isInit)(struct GameSprite* pGS);
    void (*update)(struct GameSprite* pGS);
    void (*draw)(struct GameSprite* pGS);

    //getters and setters
    D3DXVECTOR2 (*getPos)(struct GameSprite* pGS);
    void (*setPos)(struct GameSprite* pGS,int x, int y);

    int initialized;
    LPDIRECT3DTEXTURE9 tex;
    LPD3DXSPRITE sprite;

    D3DXVECTOR3 pos;
    D3DCOLOR color;
}GameSprite_t;
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
void setPos(struct GameSprite* pGS,int x, int y)
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
GameSprite_t* GameSprite_newWithPos(int x, int y)
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

void initD3D()
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

}
void render_frame()
{
    // Clear rose
    d3ddev->lpVtbl->Clear(d3ddev,0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 80, 127), 1.0f, 0);

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

}
void drawGrid()
{

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
