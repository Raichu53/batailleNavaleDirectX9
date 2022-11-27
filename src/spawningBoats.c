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
    int randomCase = -1;
    int bVertical = 0;
    srand(time(NULL));
    ///////////////////////////////////////////////player side///////////////////////////////////////////////////////////
    bVertical = rand()%2;
    if(bVertical){
        while(1){
            randomCase = rand()%224;
            if(randomCase > 105){
                pP->pPorteAvion->caseId = randomCase;
                break;
            }
        }
    }else{
        while(1){
            randomCase = rand()%224;
            if((randomCase%15) > 6){
                pP->pPorteAvion->caseId = randomCase;
                break;
            }
        }
    }

    pP->pPorteAvion->isVertical = bVertical;
    pP->pPorteAvion->pC = getCasePtrWithId(1,pP->pPorteAvion->caseId);
    printf("l'id de la case choisi pour le porte avion du player est : %d\n",randomCase);
    for(int i = 0;i < 2;i++){

    }
    for(int k = 0;k < 3;k++){

    }
    for(int l = 0;l < 4;l++){

    }

    ///////////////////////////////////////////////bot side///////////////////////////////////////////////////////////
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
    printf("l'id de la case choisi pour le porte avion du bot est : %d\n",randomCase);
    for(int m = 0;m < 2;m++){

    }
    for(int n = 0;n < 3;n++){

    }
    for(int p = 0;p < 4;p++){

    }
}
Case_t* getCasePtrWithId(int isPlayer,int id){
    for(int i = 0; i < GAME_DIMENSION;i++){
        for(int k = 0; k < GAME_DIMENSION; k++){
            if(isPlayer){
                if(Game->botPlayground[i][k]->id == id){
                    return Game->botPlayground[i][k];
                }
            }else{
                if(Game->playerPlayground[i][k]->id == id){
                    return Game->playerPlayground[i][k];
                }
            }
        }
    }
}
