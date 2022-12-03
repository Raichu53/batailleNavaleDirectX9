//
// Created by matt0 on 11/19/2022.
//
#include "../headers/includes.h"

IDirect3D9* d3d = NULL;
IDirect3DDevice9* d3ddev = NULL;

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
        pGS->sprite->lpVtbl->Begin(pGS->sprite,D3DXSPRITE_ALPHABLEND );

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
    //A is supposed to be the alpha
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
    d3ddev->lpVtbl->Clear(d3ddev,0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(37, 150, 190), 1.0f, 0);

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
    if(GetAsyncKeyState(0x56)){//v
        //version finale mettre drawBotsBoats dedans
        drawBotsBoats(Game->pBots_boats);
    }else{
        drawBotsDeadBoats(Game->pBots_boats);
    }

    drawBoatHits();
    if(GetAsyncKeyState(VK_ESCAPE) && Game->toggleMenu == 0){
        Game->toggleMenu = 1;
    }
    if(Game->toggleMenu){
        if(drawMenu() == 0){
            Game->toggleMenu = 0;
        }
    }
}
void drawPorteAvion(int mirrored,porte_avion_t* pA){
    if(mirrored){
        if (pA->isVertical) {
            pA->pPorteAvionTex90rightMirrored->setPos(pA->pPorteAvionTex90rightMirrored,
                                                                   pA->pC->posInGrid.x + 5,
                                                                   pA->pC->posInGrid.y - (40 * 6) + 5);
            pA->pPorteAvionTex90rightMirrored->draw(pA->pPorteAvionTex90rightMirrored);
        } else {
            pA->pPorteAvionTexMirrored->setPos(pA->pPorteAvionTexMirrored,
                                                            pA->pC->posInGrid.x + 10, //les textures partent de la fin et pas du debut
                                                            pA->pC->posInGrid.y + 5);
            pA->pPorteAvionTexMirrored->draw(pA->pPorteAvionTexMirrored);
        }
    }else{
        if(pA->isVertical){
            pA->pPorteAvionTex90right->setPos(pA->pPorteAvionTex90right,
                                              pA->pC->posInGrid.x + 5,
                                              pA->pC->posInGrid.y - (40*6) + 5);
            pA->pPorteAvionTex90right->draw(pA->pPorteAvionTex90right);
        }else{
            pA->pPorteAvionTex->setPos(pA->pPorteAvionTex,
                                       pA->pC->posInGrid.x - ((40*5)+30), //les textures partent de la fin et pas du debut
                                       pA->pC->posInGrid.y + 5);
            pA->pPorteAvionTex->draw(pA->pPorteAvionTex);
        }
    }
}
void drawCroiseurs(int mirrored,croiseur_t* pCr){
    if(mirrored){
        if(pCr->isVertical){
            pCr->pCroiseurTex90rightMirrored->setPos(pCr->pCroiseurTex90rightMirrored,
                                                     pCr->pC->posInGrid.x + 5,
                                                     pCr->pC->posInGrid.y - (40*4) + 5);
            pCr->pCroiseurTex90rightMirrored->draw(pCr->pCroiseurTex90rightMirrored);
        }else{
            pCr->pCroiseurTexMirrored->setPos(pCr->pCroiseurTexMirrored,
                                              pCr->pC->posInGrid.x + 10, //les textures partent de la fin et pas du debut
                                              pCr->pC->posInGrid.y + 5);
            pCr->pCroiseurTexMirrored->draw(pCr->pCroiseurTexMirrored);
        }
    }else{
        if(pCr->isVertical){
            pCr->pCroiseurTex90right->setPos(pCr->pCroiseurTex90right,
                                             pCr->pC->posInGrid.x + 5,
                                             pCr->pC->posInGrid.y - (40*4) + 5);
            pCr->pCroiseurTex90right->draw(pCr->pCroiseurTex90right);
        }else{
            pCr->pCroiseurTex->setPos(pCr->pCroiseurTex,
                                      pCr->pC->posInGrid.x - ((40*3)+30), //les textures partent de la fin et pas du debut
                                      pCr->pC->posInGrid.y + 5);
            pCr->pCroiseurTex->draw(pCr->pCroiseurTex);
        }
    }
}
void drawDestroyers(int mirrored,destroyer_t* pD){
    if(mirrored){
        if(pD->isVertical){
            pD->pDestroyerTex90rightMirrored->setPos(pD->pDestroyerTex90rightMirrored,
                                                     pD->pC->posInGrid.x + 5,
                                                     pD->pC->posInGrid.y - (40*2) + 5);
            pD->pDestroyerTex90rightMirrored->draw(pD->pDestroyerTex90rightMirrored);
        }else{
            pD->pDestroyerTexMirrored->setPos(pD->pDestroyerTexMirrored,
                                              pD->pC->posInGrid.x + 10, //les textures partent de la fin et pas du debut
                                              pD->pC->posInGrid.y + 5);
            pD->pDestroyerTexMirrored->draw(pD->pDestroyerTexMirrored);
        }
    }else{
        if(pD->isVertical){
            pD->pDestroyerTex90right->setPos(pD->pDestroyerTex90right,
                                             pD->pC->posInGrid.x + 5,
                                             pD->pC->posInGrid.y - (40*2) + 5);
            pD->pDestroyerTex90right->draw(pD->pDestroyerTex90right);
        }else{
            pD->pDestroyerTex->setPos(pD->pDestroyerTex,
                                      pD->pC->posInGrid.x - ((40*1)+30), //les textures partent de la fin et pas du debut
                                      pD->pC->posInGrid.y + 5);
            pD->pDestroyerTex->draw(pD->pDestroyerTex);
        }
    }
}
//index = 1 =>pA , index = 2 =>pC, index = 3 => pD, index = 4 => pS
void drawFlammes(int index,porte_avion_t* pPorteAvion,croiseur_t* pCroiseurs,destroyer_t* pDestroyers,sous_marin_t* pSousMarins){

    switch (index) {
        case 1:
            if(!pPorteAvion->isVertical){
                pPorteAvion->flammes->setPos(pPorteAvion->flammes,pPorteAvion->currentHealth[0]->posInGrid.x+20,pPorteAvion->currentHealth[0]->posInGrid.y+2);
                pPorteAvion->flammes->draw(pPorteAvion->flammes);
            }else{
                pPorteAvion->flammesRight->setPos(pPorteAvion->flammesRight,pPorteAvion->currentHealth[6]->posInGrid.x,pPorteAvion->currentHealth[6]->posInGrid.y);
                pPorteAvion->flammesRight->draw(pPorteAvion->flammesRight);
            }
            break;
        case 2:
            if(!pCroiseurs->isVertical){
                pCroiseurs->flammes->setPos(pCroiseurs->flammes,pCroiseurs->currentHealth[0]->posInGrid.x+20,pCroiseurs->currentHealth[0]->posInGrid.y+5);
                pCroiseurs->flammes->draw(pCroiseurs->flammes);
            }else{
                pCroiseurs->flammesRight->setPos(pCroiseurs->flammesRight,pCroiseurs->currentHealth[4]->posInGrid.x,pCroiseurs->currentHealth[4]->posInGrid.y);
                pCroiseurs->flammesRight->draw(pCroiseurs->flammesRight);
            }
            break;
        case 3:
            if(!pDestroyers->isVertical){
                pDestroyers->flammes->setPos(pDestroyers->flammes,pDestroyers->currentHealth[0]->posInGrid.x+12,pDestroyers->currentHealth[0]->posInGrid.y+3);
                pDestroyers->flammes->draw(pDestroyers->flammes);
            }else{
                pDestroyers->flammesRight->setPos(pDestroyers->flammesRight,pDestroyers->currentHealth[2]->posInGrid.x,pDestroyers->currentHealth[2]->posInGrid.y);
                pDestroyers->flammesRight->draw(pDestroyers->flammesRight);
            }
            break;
        case 4:
            pSousMarins->flammes->setPos(pSousMarins->flammes,pSousMarins->currentHealth->posInGrid.x+5,pSousMarins->currentHealth->posInGrid.y+1);
            pSousMarins->flammes->draw(pSousMarins->flammes);
            break;
        default:
            MessageBoxA(NULL,"Error in drawFlammes()",NULL,0);
            break;
    }
}
void drawBotsDeadBoats(bots_boats_t* pB){
    if(pB->pPorteAvion->canMove == 0){
        drawPorteAvion(1,pB->pPorteAvion);
        drawFlammes(1,pB->pPorteAvion,NULL,NULL,NULL);
    }
    for(int i = 0; i < 2;i++){
        if(pB->pCroiseurs[i]->canMove == 0){
            drawCroiseurs(1,pB->pCroiseurs[i]);
            drawFlammes(2,NULL,pB->pCroiseurs[i],NULL,NULL);
        }
    }
    for(int k = 0; k < 3; k++){
        if(pB->pDestroyers[k]->canMove == 0){
            drawDestroyers(1,pB->pDestroyers[k]);
            drawFlammes(3,pB->pPorteAvion,NULL,pB->pDestroyers[k],NULL);
        }
    }
    for(int j = 0; j < 4; j++){
        if(pB->pSousMarins[j]->canMove == 0){

            pB->pSousMarins[j]->pSousMarinTexMirrored->setPos(pB->pSousMarins[j]->pSousMarinTexMirrored, //multiplier par 6 ou 7 ?
                                                      pB->pSousMarins[j]->pC->posInGrid.x + 1, //les textures partent de la fin et pas du debut
                                                      pB->pSousMarins[j]->pC->posInGrid.y + 5);
            pB->pSousMarins[j]->pSousMarinTexMirrored->draw(pB->pSousMarins[j]->pSousMarinTexMirrored);

            drawFlammes(4,NULL,NULL,NULL,pB->pSousMarins[j]);
        }
    }
}
int drawMenu(){

    //il faut retourner 0 si le bouton resume est pressed pour enlever le menu

    RECT r= {0,0,100,50};
    d3ddev->lpVtbl->ColorFill(d3ddev,NULL,&r, D3DCOLOR_ARGB(255,255,255,255));
    if(GetAsyncKeyState(0x41)){//faire un bouton "resume" et check si il est pressed
        return 0;
    }
    return 1;
}

void drawPlayerBoats(player_boats_t* pP)
{

    if(pP->pPorteAvion->canMove == 1){ //on affiche pas si un bateau est coulé
        drawPorteAvion(0,pP->pPorteAvion);

    }

    for(int i = 0;i < 2;i++){
        if(pP->pCroiseurs[i]->canMove == 1){
            drawCroiseurs(0,pP->pCroiseurs[i]);
        }
    }


    for(int i = 0;i < 3;i++){
        if(pP->pDestroyers[i]->canMove == 1){
            drawDestroyers(0,pP->pDestroyers[i]);
        }
    }


    for(int i = 0;i < 4;i++){
        if(pP->pSousMarins[i]->canMove == 1){
            pP->pSousMarins[i]->pSousMarinTex->setPos(pP->pSousMarins[i]->pSousMarinTex, //multiplier par 6 ou 7 ?
                                                      pP->pSousMarins[i]->pC->posInGrid.x + 1, //les textures partent de la fin et pas du debut
                                                      pP->pSousMarins[i]->pC->posInGrid.y + 5);
            pP->pSousMarins[i]->pSousMarinTex->draw(pP->pSousMarins[i]->pSousMarinTex);
        }
    }
}
void drawBotsBoats(bots_boats_t* pB){

    drawPorteAvion(1,pB->pPorteAvion);
    if(pB->pPorteAvion->canMove == 0){
        drawFlammes(1,pB->pPorteAvion,NULL,NULL,NULL);
    }

    for(int i = 0;i < 2;i++){
        drawCroiseurs(1,pB->pCroiseurs[i]);
        if(pB->pCroiseurs[i]->canMove == 0){
            drawFlammes(2,NULL,pB->pCroiseurs[i],NULL,NULL);
        }
    }


    for(int i = 0;i < 3;i++){
        drawDestroyers(1,pB->pDestroyers[i]);
        if(pB->pDestroyers[i]->canMove == 0){
            drawFlammes(3,NULL,NULL,pB->pDestroyers[i],NULL);
        }
    }


    for(int i = 0;i < 4;i++){
        pB->pSousMarins[i]->pSousMarinTexMirrored->setPos(pB->pSousMarins[i]->pSousMarinTexMirrored, //multiplier par 6 ou 7 ?
                                                  pB->pSousMarins[i]->pC->posInGrid.x + 1, //les textures partent de la fin et pas du debut
                                                  pB->pSousMarins[i]->pC->posInGrid.y + 5);
        pB->pSousMarins[i]->pSousMarinTexMirrored->draw(pB->pSousMarins[i]->pSousMarinTexMirrored);
        if(pB->pSousMarins[i]->canMove == 0){
            drawFlammes(4,NULL,NULL,NULL,pB->pSousMarins[i]);
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
                     1, D3DCOLOR_XRGB(255,255,255));
            drawLine((D3DXVECTOR2){Game->botPlayground[i][k]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->botPlayground[i][k]->posInGrid.y  },
                     (D3DXVECTOR2){Game->botPlayground[i][k]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->botPlayground[i][k]->posInGrid.y + ((WINDOW_WIDTH/2)/15) },
                     1, D3DCOLOR_XRGB(255,255,255));
        }
    }
    //player
    for(int j = 0; j < GAME_DIMENSION;j++){
        for(int l = 0; l < GAME_DIMENSION;l++){
            //la bare en haut et le coté droit
            drawLine((D3DXVECTOR2){Game->playerPlayground[j][l]->posInGrid.x,Game->playerPlayground[j][l]->posInGrid.y},
                     (D3DXVECTOR2){Game->playerPlayground[j][l]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->playerPlayground[j][l]->posInGrid.y},
                     1, D3DCOLOR_XRGB(255,255,255));
            drawLine((D3DXVECTOR2){Game->playerPlayground[j][l]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->playerPlayground[j][l]->posInGrid.y  },
                     (D3DXVECTOR2){Game->playerPlayground[j][l]->posInGrid.x + ((WINDOW_WIDTH/2)/15),Game->playerPlayground[j][l]->posInGrid.y + ((WINDOW_WIDTH/2)/15) },
                     1, D3DCOLOR_XRGB(255,255,255));
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
void drawBoatHits(){
    //player
    Case_t* buffer;
    for(int i = 0; i < GAME_DIMENSION;i++){
        for(int j = 0;j < GAME_DIMENSION;j++){
            buffer = Game->playerPlayground[i][j];
            if(buffer->healthStatus == 0 && buffer->isOccupied && boatIsNotDead(1,buffer)){
                buffer->fireBall->draw(buffer->fireBall);
            }
        }
    }
    //bot
    for(int k = 0;k<GAME_DIMENSION;k++){
        for(int l = 0;l < GAME_DIMENSION;l++){
            buffer = Game->botPlayground[k][l];
            if(buffer->healthStatus == 0 ){
                if(buffer->isOccupied || boatIsNotDead(0,buffer) == 0){
                    buffer->fireBall->draw(buffer->fireBall);
                }
            }
        }
    }
}
int boatIsNotDead(int isPlayer,Case_t* caseptr){
    int boatSize;
    void* ptr = NULL;
    porte_avion_t* pA= NULL;
    croiseur_t* pC= NULL;
    destroyer_t* pD= NULL;
    sous_marin_t * pS= NULL;

    if(isPlayer){
        ptr = findBoatPtrWithCase(isPlayer,caseptr);
        boatSize = *(int*)ptr;
        switch (boatSize) {
            case 1:
                pS = (sous_marin_t*)ptr;
                if(pS->canMove == 0){
                    return 0;
                }
                break;
            case 3:
                pD = (destroyer_t*)ptr;
                if(pD->canMove == 0){
                    return 0;
                }
                break;
            case 5:
                pC = (croiseur_t*)ptr;
                if(pC->canMove == 0){
                    return 0;
                }
                break;
            case 7:
                pA = (porte_avion_t*)ptr;
                if(pA->canMove == 0){
                    return 0;
                }
                break;
            default:
                MessageBoxA(NULL,"Error in boatIsNotDead()",NULL,0);
                break;
        }
    }else{
        //not used
        return 1;
    }
    return 1;
}
