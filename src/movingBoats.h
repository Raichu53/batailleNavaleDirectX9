//
// Created by matt0 on 11/29/2022.
//

#ifndef PROJET_MOVINGBOATS_H
#define PROJET_MOVINGBOATS_H

void playerActions();
vec2_t GetWindowPos();
Case_t* getCasePtrWithPxCoords(int isPlayer,vec2_t relativeXY);
int cursorIsInWindow(int side,LPPOINT cursorPos,vec2_t windowPos);
void* findBoatPtrWithCase(int side,Case_t* case_ptr);
int inputs(int index,porte_avion_t* pPorteAvion,croiseur_t* pCroiseurs,destroyer_t* pDestroyers,sous_marin_t* pSousMarins);
int moveBoat(int index,int bForward,porte_avion_t* pPorteAvion,croiseur_t* pCroiseurs,destroyer_t* pDestroyers,sous_marin_t* pSousMarins);

#endif //PROJET_MOVINGBOATS_H
