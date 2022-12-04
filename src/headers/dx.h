//
// Created by matt0 on 11/19/2022.
//

#ifndef PROJET_DX_H
#define PROJET_DX_H


void initD3D(HWND window);
void render_frame();
void cleanD3D();
GameSprite_t* GameSprite_new();
GameSprite_t* GameSprite_newWithPos(float x, float y);

void drawPlayerBoats(player_boats_t* pP);
void drawBotsBoats(bots_boats_t* pB);

void drawBoatHits();
int drawMenu();
int boatIsNotDead(int isPlayer,Case_t* caseptr);
void drawBotsDeadBoats(bots_boats_t* pB);

void drawPorteAvion(int mirrored,porte_avion_t* pA);
void drawCroiseurs(int mirrored,croiseur_t* pCr);
void drawFlammes(int index,porte_avion_t* pPorteAvion,croiseur_t* pCroiseurs,destroyer_t* pDestroyers,sous_marin_t* pSousMarins);
void drawIntero();
void menuInputs();
void writeInFile(FILE* f);
#endif //PROJET_DX_H
