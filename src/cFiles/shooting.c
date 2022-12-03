//
// Created by matt0 on 12/1/2022.
//
#include "../headers/includes.h"
/// called in playerActions()
/// \param clickedCase la case qui a été clické sur le terrain enemi
void fire(int dest,Case_t* clickedCase)
{
    void* boatptr;
    int intBuffer;
    porte_avion_t* pA;
    croiseur_t* pC;
    destroyer_t* pD;
    sous_marin_t* pS;

    if(clickedCase->isOccupied){
        if(dest == 0){
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
            printf("player hit ! \n");
        }
        else{
            boatptr = findBoatPtrWithCase(1,clickedCase);
            switch (*(int*)boatptr) {
                case 1:
                    pS = (sous_marin_t*)findBoatPtrWithCase(1,clickedCase);
                    intBuffer = findIndexWithBox(clickedCase,4,pA,pC,pD,pS);
                    updateSousMarinLife(intBuffer,pS);
                    break;
                case 3:
                    pD = (destroyer_t*)findBoatPtrWithCase(1,clickedCase);
                    intBuffer = findIndexWithBox(clickedCase,3,pA,pC,pD,pS);
                    updateDestroyerLife(intBuffer,pD);
                    break;
                case 5:
                    pC = (croiseur_t*)findBoatPtrWithCase(1,clickedCase);
                    intBuffer = findIndexWithBox(clickedCase,2,pA,pC,pD,pS);
                    updateCroiseurLife(intBuffer,pC);
                    break;
                case 7:
                    pA = (porte_avion_t*)findBoatPtrWithCase(1,clickedCase);
                    intBuffer = findIndexWithBox(clickedCase,1,pA,pC,pD,pS);
                    updatePorteAvionLife(intBuffer,pA);
                    break;
                default:
                    MessageBoxA(NULL,"Error in fire()",NULL,0);
                    break;
            }
            printf("bot hit ! \n");
        }
        Game->playerTurn = !Game->playerTurn;
    }else{
        if(dest){
            printf("bot missed...\n");
        }else{
            printf("you missed...\n");
        }
        Game->playerTurn = !Game->playerTurn;
    }
    printf("\n");
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
    pS->canMove = 0;
    pS->currentHealth->isOccupied = 0;
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
void checkBoatLife(){
    //player
    porte_avion_t* pA;
    croiseur_t* pCr;
    destroyer_t* pD;

    int count = 0;
    pA = Game->pPlayer_boats->pPorteAvion;
    for(int i = 0; i < pA->len;i++){
        if(pA->currentHealth[i]->healthStatus == 0){
            count++;
        }
    }
    if(count == pA->len){//boat is dead
        if(pA->canMove == 1){
            //on clean la caisse
            for(int p = 0; p < pA->len;p++) {
                pA->currentHealth[p]->isOccupied = 0;
            }
        }
        pA->canMove = 0;
    }

    for(int j = 0; j < 2;j++){
        count = 0;
        pCr = Game->pPlayer_boats->pCroiseurs[j];
        for(int k = 0; k < pCr->len;k++){
            if(pCr->currentHealth[k]->healthStatus == 0){
                count++;
            }
        }
        if(count == pCr->len){
            if(pCr->canMove == 1){
                //on clean la caisse
                for(int h = 0; h < pCr->len;h++) {
                    pCr->currentHealth[h]->isOccupied = 0;
                }
            }
            pCr->canMove = 0;
        }
    }

    for(int l = 0; l < 3;l++){
        count = 0;
        pD = Game->pPlayer_boats->pDestroyers[l];
        for(int m = 0; m < pD->len;m++){
            if(pD->currentHealth[m]->healthStatus == 0){
                count++;
            }
        }
        if(count == pD->len){
            if(pD->canMove == 1){
                //on clean la caisse
                for(int y = 0; y < pA->len;y++) {
                    pD->currentHealth[y]->isOccupied = 0;
                }
            }
            pD->canMove = 0;
        }
    }
    //bot
    count = 0;
    pA = Game->pBots_boats->pPorteAvion;
    for(int i = 0; i < pA->len;i++){
        if(pA->currentHealth[i]->healthStatus == 0){
            count++;
        }
    }
    if(count == pA->len){//boat is dead
        if(pA->canMove == 1){
            //on clean la caisse
            for(int p = 0; p < pA->len;p++) {
                pA->currentHealth[p]->isOccupied = 0;
            }
        }
        pA->canMove = 0;
    }

    for(int j = 0; j < 2;j++){
        count = 0;
        pCr = Game->pBots_boats->pCroiseurs[j];
        for(int k = 0; k < pCr->len;k++){
            if(pCr->currentHealth[k]->healthStatus == 0){
                count++;
            }
        }
        if(count == pCr->len){
            if(pCr->canMove == 1){
                for(int r = 0; r < pA->len;r++) {
                    pCr->currentHealth[r]->isOccupied = 0;
                }
            }
            pCr->canMove = 0;
        }
    }

    for(int l = 0; l < 3;l++){
        count = 0;
        pD = Game->pBots_boats->pDestroyers[l];
        for(int m = 0; m < pD->len;m++){
            if(pD->currentHealth[m]->healthStatus == 0){
                count++;
            }
        }
        if(count == pD->len){
            if(pD->canMove == 1){
                for(int a = 0; a < pA->len;a++) {
                    pD->currentHealth[a]->isOccupied = 0;
                }
            }
            pD->canMove = 0;
        }
    }
}