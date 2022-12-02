//
// Created by matt0 on 12/1/2022.
//
#include "../headers/includes.h"
/// called in playerActions()
/// \param clickedCase la case qui a été clické sur le terrain enemi
void fire(Case_t* clickedCase)
{
    void* boatptr;
    int intBuffer;
    porte_avion_t* pA;
    croiseur_t* pC;
    destroyer_t* pD;
    sous_marin_t* pS;

    if(clickedCase->isOccupied){
        boatptr = findBoatPtrWithCase(0,clickedCase);
        switch (*(int*)boatptr) {
            case 1:
                pS = (sous_marin_t*)findBoatPtrWithCase(0,clickedCase);
                intBuffer = findIndexWithBox(clickedCase,4,pA,pC,pD,pS);
                updateSousMarinLife(intBuffer,pS);
                break;
            case 3:
                pD = (destroyer_t*)findBoatPtrWithCase(0,clickedCase);
                intBuffer = findIndexWithBox(clickedCase,3,pA,pC,pD,pS);
                updateDestroyerLife(intBuffer,pD);
                break;
            case 5:
                pC = (croiseur_t*)findBoatPtrWithCase(0,clickedCase);
                intBuffer = findIndexWithBox(clickedCase,2,pA,pC,pD,pS);
                updateCroiseurLife(intBuffer,pC);
                break;
            case 7:
                pA = (porte_avion_t*)findBoatPtrWithCase(0,clickedCase);
                intBuffer = findIndexWithBox(clickedCase,1,pA,pC,pD,pS);
                updatePorteAvionLife(intBuffer,pA);
                break;
            default:
                MessageBoxA(NULL,"Error in fire()",NULL,0);
                break;
        }
    }else{
        printf("you missed...\n");
    }
    Game->playerTurn = !Game->playerTurn;
}
void updatePorteAvionLife(int indexInArray,porte_avion_t* pA){
    pA->currentHealth[indexInArray]->healthStatus = 0;
}
void updateCroiseurLife(int indexInArray,croiseur_t* pC){
    pC->currentHealth[indexInArray]->healthStatus = 0;
}
void updateDestroyerLife(int indexInArray,destroyer_t* pD){
    pD->currentHealth[indexInArray]->healthStatus = 0;
}
void updateSousMarinLife(int indexInArray,sous_marin_t* pS){
    pS->currentHealth->healthStatus = 0;
}
int findIndexWithBox(Case_t* caseptr,int index,
                     porte_avion_t* pPorteAvion,croiseur_t* pCroiseurs,destroyer_t* pDestroyers,sous_marin_t* pSousMarins){
    switch (index) {
        case 1:
            for(int i = 0;i <= 6;i++){
                if(pPorteAvion->currentHealth[i]->id == caseptr->id){
                    return i;
                }
            }
            break;
        case 2:
            for(int i = 0;i <= 4;i++){
                if(pCroiseurs->currentHealth[i]->id == caseptr->id){
                    return i;
                }
            }
            break;
        case 3:
            for(int i = 0;i <= 2;i++){
                if(pDestroyers->currentHealth[i]->id == caseptr->id){
                    return i;
                }
            }
            break;
        case 4:
            if(pSousMarins->currentHealth->id == caseptr->id){
                return -1;
            }
            break;
        default:
            MessageBoxA(NULL,"Error in findIndexWithBox()",NULL,0);
            break;
    }
    return 0;
}