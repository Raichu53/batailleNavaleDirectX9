//
// Created by matt0 on 12/3/2022.
//
#include "../headers/includes.h"
///show case arround a click case
void scout(int dest,Case_t* caseCliked){
    //tableau qui contient les case autour, l index 0 etant la case clické
    Case_t* tab[9] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    tab[0] = caseCliked;
    //on commence par en haut puis dans le sens horaire
    if((caseCliked->id - 15) > 0 || (caseCliked->id == 15)){//au Nord
        tab[1] = getCasePtrWithId(0,caseCliked->id - 15);
    }
    if((((caseCliked->id - 15) + 1) > 0) && ((((caseCliked->id - 15) + 1)%15) != 0)){//au Nord Est
        tab[2] = getCasePtrWithId(0,(caseCliked->id - 15) + 1);
    }
    if(((caseCliked->id + 1)%15) != 0 ){//a l'est
        tab[3] = getCasePtrWithId(0,caseCliked->id + 1);
    }
    if(((caseCliked->id + (15+1))%15) != 0){ //au sud est
        tab[4] = getCasePtrWithId(0,caseCliked->id + (15+1));
    }
    if((caseCliked->id + 15) < 225){//au sud
        tab[5] = getCasePtrWithId(0,caseCliked->id + 15);
    }
    if(((caseCliked->id+15)%15) != 0){ // au sud ouest
        tab[6] = getCasePtrWithId(0,caseCliked->id + (15-1));
    }
    if((caseCliked->id%15) != 0){//a l'ouest
        tab[7] = getCasePtrWithId(0,caseCliked->id -1);
    }
    if(((caseCliked->id - 15)%15) != 0){//au nord ouest
        tab[8] = getCasePtrWithId(0,(caseCliked->id - 15)-1);
    }

    for(int i = 0; i < 9;i++){
        if(tab[i] != NULL){
            //printf("case id : %d \n",tab[i]->id);
            if(tab[i]->isOccupied){
                Game->intero[i]->setPos(Game->intero[i],tab[i]->posInGrid.x,tab[i]->posInGrid.y);
                Game->intero[i]->color = D3DCOLOR_ARGB(255,255,255,255);
            }else{
                Game->intero[i]->setPos(Game->intero[i],tab[i]->posInGrid.x,tab[i]->posInGrid.y);
                Game->intero[i]->color = D3DCOLOR_ARGB(0,255,255,255);
            }
        }else{
            Game->intero[i]->color = D3DCOLOR_ARGB(0,255,255,255);
        }
    }

    printf("\n");
    Game->playerTurn = !Game->playerTurn;
    Game->toggleIntero = 1;
}
