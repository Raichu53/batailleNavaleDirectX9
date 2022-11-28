//
// Created by matt0 on 11/27/2022.
//

#include "includes.h"
#include <time.h>

///pour faire spawn les bateau de maniere random on selectionne une case dans la grille et on check si c'est possible
///pour la taille du bateau que l'on veut mettre ET si il n'y a pas deja un bateau
///le ptr pC represente le bout du bateau
void spawnBoats(bots_boats_t* pB,player_boats_t* pP){
    //il a 15*15=225 cases par grille
    int randomCase,nextCase = -1;
    Case_t* usedCases;
    int bVertical = 0;
    srand(time(NULL));
    ///////////////////////////////////////////////player side///////////////////////////////////////////////////////////
#pragma region porteAvion
    bVertical = rand()%2;
    if(bVertical){
        while(1){
            randomCase = rand()%224;
            if(randomCase > 105){
                pP->pPorteAvion->caseId = randomCase;
                printf("l'id de la case choisi pour le porte avion du player est : %d et il est vertical\n",randomCase);
                break;
            }
        }
    }else{
        while(1){
            randomCase = rand()%224;
            if((randomCase%15) > 6){
                pP->pPorteAvion->caseId = randomCase;
                printf("l'id de la case choisi pour le porte avion du player est : %d et il est horizontal\n",randomCase);
                break;
            }
        }
    }

    pP->pPorteAvion->isVertical = bVertical;
    pP->pPorteAvion->pC = getCasePtrWithId(1,pP->pPorteAvion->caseId);

    //on rempli les cases utilisé par le bateau
    nextCase = randomCase;
    usedCases = pP->pPorteAvion->pC;
    printf("Les cases :");
    if(bVertical){
        for(int k = 0; k < 7; k++){
            pP->pPorteAvion->currentHealth[k] = usedCases;
            pP->pPorteAvion->currentHealth[k]->healthStatus = 1;
            pP->pPorteAvion->currentHealth[k]->isOccupied = 1;
            printf("%d, ",pP->pPorteAvion->currentHealth[k]->id);
            nextCase -= 15;
            usedCases = getCasePtrWithId(1,nextCase);
        }
    }else{
        for(int j = 0;j < 7;j++){
            pP->pPorteAvion->currentHealth[j] = usedCases;
            pP->pPorteAvion->currentHealth[j]->healthStatus = 1;
            pP->pPorteAvion->currentHealth[j]->isOccupied = 1;
            printf("%d, ",pP->pPorteAvion->currentHealth[j]->id);
            nextCase -= 1;
            usedCases = getCasePtrWithId(1,nextCase);
        }
    }
    printf("sont occupees par le porte avion.\n\n");
#pragma endregion
#pragma region Croiseur
    for(int i = 0;i < 2;i++){
        bVertical = rand()%2;
        if(bVertical){
            while(1){
                randomCase = rand()%224;
                if(randomCase > 75 && isGoingToFit(1,5,bVertical,randomCase,pB,pP)){
                    pP->pCroiseurs[i]->caseId = randomCase;
                    printf("l'id de la case choisi pour le croiseur %d du player est : %d et il est vertical\n",i,randomCase);
                    break;
                }
            }
        }else{
            while(1){
                randomCase = rand()%224;
                if((randomCase%15) > 4 && isGoingToFit(1,5,bVertical,randomCase,pB,pP)){
                    pP->pCroiseurs[i]->caseId = randomCase;
                    printf("l'id de la case choisi pour le croiseur %d du player est : %d et il est horizontal\n",i,randomCase);
                    break;
                }
            }
        }

        pP->pCroiseurs[i]->isVertical = bVertical;
        pP->pCroiseurs[i]->pC = getCasePtrWithId(1,pP->pCroiseurs[i]->caseId);
        nextCase = randomCase;
        usedCases = pP->pCroiseurs[i]->pC;
        printf("Les cases: ");
        if(bVertical){
            for(int k = 0; k < 5; k++){
                pP->pCroiseurs[i]->currentHealth[k] = usedCases;
                pP->pCroiseurs[i]->currentHealth[k]->healthStatus = 1;
                pP->pCroiseurs[i]->currentHealth[k]->isOccupied = 1;
                printf("%d, ",pP->pCroiseurs[i]->currentHealth[k]->id);
                nextCase -= 15;
                usedCases = getCasePtrWithId(1,nextCase);
            }
        }else{
            for(int j = 0;j < 5;j++){
                pP->pCroiseurs[i]->currentHealth[j] = usedCases;
                pP->pCroiseurs[i]->currentHealth[j]->healthStatus = 1;
                pP->pCroiseurs[i]->currentHealth[j]->isOccupied = 1;
                printf("%d, ",pP->pCroiseurs[i]->currentHealth[j]->id);
                nextCase -= 1;
                usedCases = getCasePtrWithId(1,nextCase);
            }
        }
        printf("sont occupees par le croiseur numero %d.\n",i);
    }
    printf("\n");
#pragma endregion
#pragma region destroyeur
    for(int o = 0;o < 3;o++){
        bVertical = rand()%2;
        if(bVertical){
            while(1){
                randomCase = rand()%224;
                if(randomCase > 45 && isGoingToFit(1,3,bVertical,randomCase,pB,pP)){
                    pP->pDestroyers[o]->caseId = randomCase;
                    printf("l'id de la case choisi pour le destroyer %d du player est : %d en vertical\n",o,randomCase);
                    break;
                }
            }
        }else{
            while(1){
                randomCase = rand()%224;
                if((randomCase%15) > 2 && isGoingToFit(1,3,bVertical,randomCase,pB,pP)){
                    pP->pDestroyers[o]->caseId = randomCase;
                    printf("l'id de la case choisi pour le destroyer %d du player est : %d en horizontal\n",o,randomCase);
                    break;
                }
            }
        }

        pP->pDestroyers[o]->isVertical = bVertical;
        pP->pDestroyers[o]->pC = getCasePtrWithId(1,pP->pDestroyers[o]->caseId);
        nextCase = randomCase;
        usedCases = pP->pDestroyers[o]->pC;
        printf("Les cases : ");
        if(bVertical){
            for(int k = 0; k < 3; k++){
                pP->pDestroyers[o]->currentHealth[k] = usedCases;
                pP->pDestroyers[o]->currentHealth[k]->healthStatus = 1;
                pP->pDestroyers[o]->currentHealth[k]->isOccupied = 1;
                printf("%d, ",pP->pDestroyers[o]->currentHealth[k]->id);
                nextCase -= 15;
                usedCases = getCasePtrWithId(1,nextCase);
            }
        }else{
            for(int j = 0;j < 3;j++){
                pP->pDestroyers[o]->currentHealth[j] = usedCases;
                pP->pDestroyers[o]->currentHealth[j]->healthStatus = 1;
                pP->pDestroyers[o]->currentHealth[j]->isOccupied = 1;
                printf("%d, ",pP->pDestroyers[o]->currentHealth[j]->id);
                nextCase -= 1;
                usedCases = getCasePtrWithId(1,nextCase);
            }
        }
        printf("sont occupees par le destroyeur numero %d.\n",o);
    }
    printf("\n");
#pragma endregion
#pragma region SousMarin
    for(int l = 0;l < 4;l++){

        while(1){
            randomCase = rand()%224;
            if(isGoingToFit(1,1,bVertical,randomCase,pB,pP)){
                pP->pSousMarins[l]->caseId = randomCase;
                printf("l'id de la case choisi pour le sous marin %d du player est : %d\n",l,randomCase);
                break;
            }
        }

        pP->pSousMarins[l]->isVertical = bVertical;
        pP->pSousMarins[l]->pC = getCasePtrWithId(1,pP->pSousMarins[l]->caseId);

        pP->pSousMarins[l]->currentHealth = pP->pSousMarins[l]->pC;
        pP->pSousMarins[l]->currentHealth->healthStatus = 1;
        pP->pSousMarins[l]->currentHealth->isOccupied = 1;


    }
#pragma endregion
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////bot side///////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bVertical = rand()%2;
    if(bVertical){
        while(1){
            randomCase = rand()%224;
            if(randomCase > 105){
                pB->pPorteAvion->caseId = randomCase;
                break;
            }
        }
    }else{
        while(1){
            randomCase = rand()%224;
            if((randomCase%15) > 6){
                pB->pPorteAvion->caseId = randomCase;
                break;
            }
        }
    }

    pB->pPorteAvion->isVertical = bVertical;
    pB->pPorteAvion->pC = getCasePtrWithId(0,pB->pPorteAvion->caseId);
    //printf("l'id de la case choisi pour le porte avion du bot est : %d\n",randomCase);
    for(int m = 0;m < 2;m++){

    }
    for(int n = 0;n < 3;n++){

    }
    for(int p = 0;p < 4;p++){

    }
}
int isGoingToFit(int isPlayer,int len,int isVertical,int caseId,bots_boats_t* pB,player_boats_t* pP){
    Case_t* bufferCase = NULL;
    int nextCase = caseId;
    if(isPlayer){
        if(isVertical){
            for(int i = 0;i < len;i++){
                bufferCase = getCasePtrWithId(1,nextCase);
                if(bufferCase->isOccupied) {return 0;}
                else{
                    nextCase -= 15;
                }
            }
            return 1;
        }else{
            for(int i = 0;i < len;i++){
                bufferCase = getCasePtrWithId(1,nextCase);
                if(bufferCase->isOccupied) {return 0;}
                else{
                    nextCase--;
                }
            }
            return 1;
        }
    }else{
        if(isVertical){
            for(int i = 0;i < len;i++){
                bufferCase = getCasePtrWithId(0,nextCase);
                if(bufferCase->isOccupied) {return 0;}
                else{
                    nextCase -= 15;
                }
            }
            return 1;
        }else{
            for(int i = 0;i < len;i++){
                bufferCase = getCasePtrWithId(0,nextCase);
                if(bufferCase->isOccupied) {return 0;}
                else{
                    nextCase--;
                }
            }
            return 1;
        }
    }
}
Case_t* getCasePtrWithId(int isPlayer,int id){
    for(int i = 0; i < GAME_DIMENSION;i++){
        for(int k = 0; k < GAME_DIMENSION; k++){
            if(isPlayer){
                if(Game->playerPlayground[i][k]->id == id){
                    return Game->playerPlayground[i][k];
                }
            }else{
                if(Game->botPlayground[i][k]->id == id){
                    return Game->botPlayground[i][k];
                }
            }
        }
    }
}