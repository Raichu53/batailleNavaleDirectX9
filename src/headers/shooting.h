//
// Created by matt0 on 12/1/2022.
//

#ifndef PROJET_SHOOTING_H
#define PROJET_SHOOTING_H
void fire(Case_t* clickedCase);
int findIndexWithBox(Case_t* caseptr,int index,
                     porte_avion_t* pPorteAvion,croiseur_t* pCroiseurs,destroyer_t* pDestroyers,sous_marin_t* pSousMarins);

void updatePorteAvionLife(int indexInArray,porte_avion_t* pA);
void updateCroiseurLife(int indexInArray,croiseur_t* pC);
void updateDestroyerLife(int indexInArray,destroyer_t* pD);
void updateSousMarinLife(int indexInArray,sous_marin_t* pS);

#endif //PROJET_SHOOTING_H
