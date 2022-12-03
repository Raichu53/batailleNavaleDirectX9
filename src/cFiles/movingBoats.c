//
// Created by matt0 on 11/29/2022.
//
#include "../headers/includes.h"
/*
 * 1 - on attend un clic
 * 2 - on cherche la case ou il a cliquer
 * 3 - on check si ya un bateau
 * 4 - ...
 */
void playerActions(){
    //either use this struct provided by windows api MOUSEINPUT or getASyncKeyState()

    int boatSize = 0;
    void* ptr = NULL;

    GetCursorPos(Game->cursorPos);
    Game->windowPos = GetWindowPos();
    if(cursorIsInWindow(-1,Game->cursorPos,Game->windowPos)){ //on check d'abord si on est dans la fenetre entiere
        //ça serait bien de faire un "custom windows pointer"
        if(GetAsyncKeyState(VK_LBUTTON)){
            if(cursorIsInWindow(1,Game->cursorPos,Game->windowPos)){ //on check ensuite si dequel coté de la map on est
                Game->pClickedCase = getCasePtrWithPxCoords(1,(vec2_t){Game->cursorPos->x - Game->windowPos.x,
                                                                 Game->cursorPos->y - Game->windowPos.y - 30});
                if(Game->pClickedCase != NULL){
                    if(Game->pClickedCase->isOccupied){
                        //trouver a quel bateau cette case apartient
                        ptr = findBoatPtrWithCase(1,Game->pClickedCase);
                        boatSize = *(int*)ptr; //la longeur d'un bateau est a l'offset 0 de la struct
                        switch (boatSize) {
                            case 1: //sous marin
                                Game->sousMarinPtr = (sous_marin_t*)findBoatPtrWithCase(1,Game->pClickedCase);
                                printf("sous marin selected, waiting for input...\n");
                                Game->waitingInput = 1;
                                Game->index = 4;
                                break;
                            case 3:
                                Game->destroyerPtr = (destroyer_t*)findBoatPtrWithCase(1,Game->pClickedCase);
                                printf("destroyer selected, waiting for input...\n");
                                Game->waitingInput = 1;
                                Game->index = 3;
                                break;
                            case 5:
                                Game->croiseurPtr = (croiseur_t *)findBoatPtrWithCase(1,Game->pClickedCase);
                                printf("croiseur selected, waiting for input...\n");
                                Game->waitingInput = 1;
                                Game->index = 2;
                                break;
                            case 7:
                                Game->porteAvionPtr = (porte_avion_t*)findBoatPtrWithCase(1,Game->pClickedCase);
                                printf("porteAvion selected, waiting for input...\n");
                                Game->waitingInput = 1;
                                Game->index = 1;
                                break;
                            default:
                                MessageBoxA(NULL,"fct : PlayerActions() failed",NULL,0);
                                break;
                        }
                    }else{
                        Game->waitingInput = 0;
                        Game->inputHasBeenSend = 0;
                        printf("you have no boats here\n");
                    }
                }else{
                    MessageBoxA(NULL,"clicked case is nullptr",NULL,0);
                }
            }
            else{
                fire(0,getCasePtrWithPxCoords(0,(vec2_t){Game->cursorPos->x - Game->windowPos.x,
                                                       Game->cursorPos->y - Game->windowPos.y - 30}));

            }
        }
    }
    inputs(Game->pClickedCase,Game->index,
           Game->porteAvionPtr,Game->croiseurPtr,Game->destroyerPtr,Game->sousMarinPtr);
}

int inputs(Case_t* clicked,int index,porte_avion_t* pPorteAvion,croiseur_t* pCroiseurs,destroyer_t* pDestroyers,sous_marin_t* pSousMarins){
    int currentBoatState;//1 vertical 0 horizontal
    switch (index) {
        case 1:
            if(pPorteAvion->isVertical){
                currentBoatState = 1;
            }else{
                currentBoatState = 0;
            }
            break;
        case 2:
            if(pCroiseurs->isVertical){
                currentBoatState = 1;
            }else{
                currentBoatState = 0;
            }
            break;
        case 3:
            if(pDestroyers->isVertical){
                currentBoatState = 1;
            }else{
                currentBoatState = 0;
            }
            break;
        case 4:
            currentBoatState = 0;
            break;
    }
    if(currentBoatState){
        if(GetAsyncKeyState(0x5A) && Game->waitingInput){//z
            Game->waitingInput = 0;
            Game->inputHasBeenSend = 1;
        }else if(GetAsyncKeyState(0x53) && Game->waitingInput){//s
            Game->waitingInput = 0;
            Game->inputHasBeenSend = -1;
        }
    }else{
        if(GetAsyncKeyState(0x44) && Game->waitingInput){//d
            Game->waitingInput = 0;
            Game->inputHasBeenSend = 2;
        }else if(GetAsyncKeyState(0x51) && Game->waitingInput){//q
            Game->waitingInput = 0;
            Game->inputHasBeenSend = -2;
        }
    }

    if(Game->inputHasBeenSend == 1){
        moveBoat(index,1,Game->porteAvionPtr,Game->croiseurPtr,Game->destroyerPtr,Game->sousMarinPtr);
        Game->inputHasBeenSend = 0;
    }else if(Game->inputHasBeenSend == -1){
        moveBoat(index,0,Game->porteAvionPtr,Game->croiseurPtr,Game->destroyerPtr,Game->sousMarinPtr);
        Game->inputHasBeenSend = 0;
    }else if(Game->inputHasBeenSend == 2){
        moveBoat(index,1,Game->porteAvionPtr,Game->croiseurPtr,Game->destroyerPtr,Game->sousMarinPtr);
        Game->inputHasBeenSend = 0;
    }else if(Game->inputHasBeenSend == -2){
        moveBoat(index,0,Game->porteAvionPtr,Game->croiseurPtr,Game->destroyerPtr,Game->sousMarinPtr);
        Game->inputHasBeenSend = 0;
    }
    return 0;
}
//index = 1 pour porte avion 2 croiseur 3 destroyer et 4 sous marin
int moveBoat(int index,int bForward,
             porte_avion_t* pPorteAvion,croiseur_t* pCroiseurs,destroyer_t* pDestroyers,sous_marin_t* pSousMarins) {
    Case_t *buffercase;
    int bufferint,hit;
    checkBoatLife();
    switch (index) {
        case 1:
            if(pPorteAvion->canMove){

                if (pPorteAvion->isVertical) {
                    if (bForward) {//on a appuyé sur z
                        //printf("on recule\n");
                        bufferint = pPorteAvion->currentHealth[6]->id - 15;
                        if (bufferint >= 0) {
                            buffercase = getCasePtrWithId(1, (pPorteAvion->currentHealth[6]->id - 15));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 6; i >= 0; i--) {
                                    if(pPorteAvion->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }

                                    pPorteAvion->currentHealth[i] = getCasePtrWithId(1, (pPorteAvion->currentHealth[i]->id -15));
                                    pPorteAvion->currentHealth[i]->isOccupied = 1;
                                    pPorteAvion->currentHealth[i]->healthStatus = hit;

                                }
                                printf("front du boat moved from %d", pPorteAvion->pC->id);
                                pPorteAvion->pC = pPorteAvion->currentHealth[0];
                                printf(" to %d\n\n", pPorteAvion->pC->id);
                                //on clean la caisse d'ou on vien de partir
                                buffercase = getCasePtrWithId(1, pPorteAvion->pC->id + 15);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }
                    } else {//on a appuyé sur s
                        //printf("on avance\n");
                        bufferint = pPorteAvion->pC->id + 15;
                        if (bufferint <= 224) {
                            buffercase = getCasePtrWithId(1, (pPorteAvion->pC->id + 15));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 0; i <= 6; i++) {
                                    if(pPorteAvion->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pPorteAvion->currentHealth[i] = getCasePtrWithId(1, (pPorteAvion->currentHealth[i]->id +15));
                                    pPorteAvion->currentHealth[i]->isOccupied = 1;
                                    pPorteAvion->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d", pPorteAvion->pC->id);
                                pPorteAvion->pC = pPorteAvion->currentHealth[0];
                                printf(" to %d\n\n", pPorteAvion->pC->id);
                                buffercase = getCasePtrWithId(1, pPorteAvion->currentHealth[6]->id - 15);
                                buffercase->isOccupied = 0;
                            }

                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }
                    }
                } else {
                    int row;
                    if (bForward) {//on a appuyé sur d
                        //printf("on avance\n");
                        bufferint = pPorteAvion->pC->id + 1;
                        if ((bufferint % 15) != 0) {
                            buffercase = getCasePtrWithId(1, (pPorteAvion->pC->id + 1));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 0; i <= 6; i++) {
                                    if(pPorteAvion->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pPorteAvion->currentHealth[i] = getCasePtrWithId(1, (pPorteAvion->currentHealth[i]->id +1));
                                    pPorteAvion->currentHealth[i]->isOccupied = 1;
                                    pPorteAvion->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d", pPorteAvion->pC->id);
                                pPorteAvion->pC = pPorteAvion->currentHealth[0];
                                printf(" to %d\n\n", pPorteAvion->pC->id);
                                buffercase = getCasePtrWithId(1, pPorteAvion->currentHealth[6]->id - 1);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }

                    } else {//on a appuyé sur q
                        //printf("on avance\n");
                        bufferint = pPorteAvion->currentHealth[6]->id;
                        if ((bufferint % 15) != 0) {
                            buffercase = getCasePtrWithId(1, (pPorteAvion->currentHealth[6]->id - 1));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...");
                            } else {
                                //on peut bouger
                                for (int i = 6; i >= 0; i--) {
                                    if(pPorteAvion->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pPorteAvion->currentHealth[i] = getCasePtrWithId(1, (pPorteAvion->currentHealth[i]->id -1));
                                    pPorteAvion->currentHealth[i]->isOccupied = 1;
                                    pPorteAvion->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d\n", pPorteAvion->pC->id);
                                pPorteAvion->pC = pPorteAvion->currentHealth[0];
                                printf(" to %d\n\n", pPorteAvion->pC->id);
                                buffercase = getCasePtrWithId(1, pPorteAvion->pC->id + 1);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }

                    }
                }
            }
            else{
                printf("Can't move this boat, its dead\n");
            }
            break;
        case 2:
            if(pCroiseurs->canMove){

                if (pCroiseurs->isVertical) {
                    if (bForward) {
                        //printf("on recule\n");
                        bufferint = pCroiseurs->currentHealth[4]->id - 15;
                        if (bufferint >= 0) {
                            buffercase = getCasePtrWithId(1, (pCroiseurs->currentHealth[4]->id - 15));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 4; i >= 0; i--) {
                                    if(pCroiseurs->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pCroiseurs->currentHealth[i] = getCasePtrWithId(1, (pCroiseurs->currentHealth[i]->id -15));
                                    pCroiseurs->currentHealth[i]->isOccupied = 1;
                                    pCroiseurs->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d", pCroiseurs->pC->id);
                                pCroiseurs->pC = pCroiseurs->currentHealth[0];
                                printf(" to %d\n\n", pCroiseurs->pC->id);
                                //on clean la caisse d'ou on vien de partir
                                buffercase = getCasePtrWithId(1, pCroiseurs->pC->id + 15);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }

                    } else {
                        //printf("on avance\n");
                        bufferint = pCroiseurs->pC->id + 15;
                        if (bufferint <= 224) {
                            buffercase = getCasePtrWithId(1, (pCroiseurs->pC->id + 15));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 0; i <= 4; i++) {
                                    if(pCroiseurs->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pCroiseurs->currentHealth[i] = getCasePtrWithId(1, (pCroiseurs->currentHealth[i]->id +15));
                                    pCroiseurs->currentHealth[i]->isOccupied = 1;
                                    pCroiseurs->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d", pCroiseurs->pC->id);
                                pCroiseurs->pC = pCroiseurs->currentHealth[0];
                                printf(" to %d\n\n", pCroiseurs->pC->id);
                                buffercase = getCasePtrWithId(1, pCroiseurs->currentHealth[4]->id - 15);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }

                    }
                }
                else {
                    int row;
                    if (bForward) {//on a appuyé sur d
                        //printf("on avance\n");
                        bufferint = pCroiseurs->pC->id + 1;
                        if ((bufferint % 15) != 0) {
                            buffercase = getCasePtrWithId(1, (pCroiseurs->pC->id + 1));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 0; i <= 4; i++) {
                                    if(pCroiseurs->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pCroiseurs->currentHealth[i] = getCasePtrWithId(1,(pCroiseurs->currentHealth[i]->id +1));
                                    pCroiseurs->currentHealth[i]->isOccupied = 1;
                                    pCroiseurs->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d", pCroiseurs->pC->id);
                                pCroiseurs->pC = pCroiseurs->currentHealth[0];
                                printf(" to %d\n\n", pCroiseurs->pC->id);
                                buffercase = getCasePtrWithId(1, pCroiseurs->currentHealth[4]->id - 1);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }

                    } else {
                        bufferint = pCroiseurs->currentHealth[4]->id;
                        if ((bufferint % 15) != 0) {
                            buffercase = getCasePtrWithId(1, (pCroiseurs->currentHealth[4]->id - 1));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 4; i >= 0; i--) {
                                    if(pCroiseurs->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pCroiseurs->currentHealth[i] = getCasePtrWithId(1,(pCroiseurs->currentHealth[i]->id -1));
                                    pCroiseurs->currentHealth[i]->isOccupied = 1;
                                    pCroiseurs->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d", pCroiseurs->pC->id);
                                pCroiseurs->pC = pCroiseurs->currentHealth[0];
                                printf(" to %d\n\n", pCroiseurs->pC->id);
                                buffercase = getCasePtrWithId(1, pCroiseurs->pC->id + 1);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }

                    }
                }
            }else{
                printf("Can't move this boat, its dead\n");
            }
            break;
        case 3:
            if(pDestroyers->canMove){
                if (pDestroyers->isVertical) {
                    if (bForward) {
                        //printf("on recule\n");
                        bufferint = pDestroyers->currentHealth[2]->id - 15;
                        if (bufferint >= 0) {
                            buffercase = getCasePtrWithId(1, (pDestroyers->currentHealth[2]->id - 15));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 2; i >= 0; i--) {
                                    if(pDestroyers->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pDestroyers->currentHealth[i] = getCasePtrWithId(1, (pDestroyers->currentHealth[i]->id -15));
                                    pDestroyers->currentHealth[i]->isOccupied = 1;
                                    pDestroyers->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d", pDestroyers->pC->id);
                                pDestroyers->pC = pDestroyers->currentHealth[0];
                                printf(" to %d\n\n", pDestroyers->pC->id);
                                //on clean la caisse d'ou on vien de partir
                                buffercase = getCasePtrWithId(1, pDestroyers->pC->id + 15);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }
                    } else {
                        //printf("on avance\n");
                        bufferint = pDestroyers->pC->id + 15;
                        if (bufferint <= 224) {
                            buffercase = getCasePtrWithId(1, (pDestroyers->pC->id + 15));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 0; i <= 2; i++) {
                                    if(pDestroyers->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pDestroyers->currentHealth[i] = getCasePtrWithId(1, (pDestroyers->currentHealth[i]->id +15));
                                    pDestroyers->currentHealth[i]->isOccupied = 1;
                                    pDestroyers->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d", pDestroyers->pC->id);
                                pDestroyers->pC = pDestroyers->currentHealth[0];
                                printf(" to %d\n\n", pDestroyers->pC->id);
                                buffercase = getCasePtrWithId(1, pDestroyers->currentHealth[2]->id - 15);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }
                    }
                } else {
                    int row;
                    if (bForward) {//on a appuyé sur d
                        //printf("on avance\n");
                        bufferint = pDestroyers->pC->id + 1;
                        if ((bufferint % 15) != 0) {
                            buffercase = getCasePtrWithId(1, (pDestroyers->pC->id + 1));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 0; i <= 2; i++) {
                                    if(pDestroyers->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pDestroyers->currentHealth[i] = getCasePtrWithId(1,(pDestroyers->currentHealth[i]->id +1));
                                    pDestroyers->currentHealth[i]->isOccupied = 1;
                                    pDestroyers->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d", pDestroyers->pC->id);
                                pDestroyers->pC = pDestroyers->currentHealth[0];
                                printf(" to %d\n\n", pDestroyers->pC->id);
                                buffercase = getCasePtrWithId(1, pDestroyers->currentHealth[2]->id - 1);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }
                    } else {
                        bufferint = pDestroyers->currentHealth[2]->id;
                        if ((bufferint % 15) != 0) {
                            buffercase = getCasePtrWithId(1, (pDestroyers->currentHealth[2]->id - 1));
                            if (buffercase->isOccupied) {
                                //la case est occupé
                                printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                            } else {
                                //on peut bouger
                                for (int i = 2; i >= 0; i--) {
                                    if(pDestroyers->currentHealth[i]->healthStatus == 0){
                                        hit = 0;
                                    }else{
                                        hit = 1;
                                    }
                                    pDestroyers->currentHealth[i] = getCasePtrWithId(1,(pDestroyers->currentHealth[i]->id -1));
                                    pDestroyers->currentHealth[i]->isOccupied = 1;
                                    pDestroyers->currentHealth[i]->healthStatus = hit;
                                }
                                printf("front du boat moved from %d", pDestroyers->pC->id);
                                pDestroyers->pC = pDestroyers->currentHealth[0];
                                printf(" to %d\n\n", pDestroyers->pC->id);
                                buffercase = getCasePtrWithId(1, pDestroyers->pC->id + 1);
                                buffercase->isOccupied = 0;
                            }
                        } else {
                            printf("on ne peut pas aller ici, raison: bord de la map...\n");
                        }
                    }
                }
            }
            else{
                printf("Can't move this boat, its dead\n");
            }
        break;
        case 4:
            if(pSousMarins->canMove){

                if (bForward) {//on a appuyé sur d
                    int row;
                    //printf("on avance\n");
                    bufferint = pSousMarins->pC->id + 1;
                    if ((bufferint % 15) != 0) {
                        buffercase = getCasePtrWithId(1, (pSousMarins->pC->id + 1));
                        if (buffercase->isOccupied) {
                            //la case est occupé
                            printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                        } else {
                            //on peut bouger
                            if(pSousMarins->currentHealth->healthStatus == 0){
                                hit = 0;
                            }else{
                                hit = 1;
                            }
                            pSousMarins->currentHealth = getCasePtrWithId(1,(pSousMarins->currentHealth->id +1));
                            pSousMarins->currentHealth->isOccupied = 1;
                            pSousMarins->currentHealth->healthStatus = hit;
                            printf("front du boat moved from %d", pSousMarins->pC->id);
                            pSousMarins->pC = pSousMarins->currentHealth;
                            printf(" to %d\n\n", pSousMarins->pC->id);
                            buffercase = getCasePtrWithId(1, pSousMarins->currentHealth->id - 1);
                            buffercase->isOccupied = 0;
                            buffercase->healthStatus = 1;
                        }
                    } else {
                        printf("on ne peut pas aller ici, raison: bord de la map...\n");
                    }
                } else {
                    bufferint = pSousMarins->currentHealth->id;
                    if ((bufferint % 15) != 0) {
                        buffercase = getCasePtrWithId(1, (pSousMarins->currentHealth->id - 1));
                        if (buffercase->isOccupied) {
                            //la case est occupé
                            printf("il n'est pas possible d'aller la, raison bateau allié ...\n");
                        } else {
                            //on peut bouger
                            if(pSousMarins->currentHealth->healthStatus == 0){
                                hit = 0;
                            }else{
                                hit = 1;
                            }
                            pSousMarins->currentHealth = getCasePtrWithId(1,(pSousMarins->currentHealth->id -1));
                            pSousMarins->currentHealth->isOccupied = 1;
                            pSousMarins->currentHealth->healthStatus = hit;

                            printf("front du boat moved from %d", pSousMarins->pC->id);
                            pSousMarins->pC = pSousMarins->currentHealth;
                            printf(" to %d\n\n", pSousMarins->pC->id);
                            buffercase = getCasePtrWithId(1, pSousMarins->pC->id + 1);
                            buffercase->isOccupied = 0;
                            buffercase->healthStatus = 1;
                        }
                    } else {
                        printf("on ne peut pas aller ici, raison: bord de la map...\n");
                    }
                }
            }else{
                printf("Can't move this boat, its dead\n");;
            }
        break;
        default:
            break;

    }
    Game->playerTurn = !Game->playerTurn;
}
///
/// \param side = 1 pour le player 0 pour le bot
/// \param case_ptr
/// \return un ptr sur le bateau
void *findBoatPtrWithCase(int side, Case_t *case_ptr)
{
    if (side) {
        for (int j = 0; j < 7; j++) {
            if (Game->pPlayer_boats->pPorteAvion->currentHealth[j]->id == case_ptr->id) {
                return Game->pPlayer_boats->pPorteAvion;
            }
        }
        for (int k = 0; k < 2; k++) {
            for (int l = 0; l < 5; l++) {
                if (Game->pPlayer_boats->pCroiseurs[k]->currentHealth[l]->id == case_ptr->id) {
                    return Game->pPlayer_boats->pCroiseurs[k];
                }
            }
        }
        for (int p = 0; p < 3; p++) {
            for (int f = 0; f < 3; f++) {
                if (Game->pPlayer_boats->pDestroyers[p]->currentHealth[f]->id == case_ptr->id) {
                    return Game->pPlayer_boats->pDestroyers[p];
                }
            }
        }
        for (int y = 0; y < 4; y++) {
            if (Game->pPlayer_boats->pSousMarins[y]->currentHealth->id == case_ptr->id) {
                return Game->pPlayer_boats->pSousMarins[y];
            }
        }
    } else {
        for (int j = 0; j < 7; j++) {
            if (Game->pBots_boats->pPorteAvion->currentHealth[j]->id == case_ptr->id) {
                return Game->pBots_boats->pPorteAvion;
            }
        }
        for (int k = 0; k < 2; k++) {
            for (int l = 0; l < 5; l++) {
                if (Game->pBots_boats->pCroiseurs[k]->currentHealth[l]->id == case_ptr->id) {
                    return Game->pBots_boats->pCroiseurs[k];
                }
            }
        }
        for (int p = 0; p < 3; p++) {
            for (int f = 0; f < 3; f++) {
                if (Game->pBots_boats->pDestroyers[p]->currentHealth[f]->id == case_ptr->id) {
                    return Game->pBots_boats->pDestroyers[p];
                }
            }
        }
        for (int y = 0; y < 4; y++) {
            if (Game->pBots_boats->pSousMarins[y]->currentHealth->id == case_ptr->id) {
                return Game->pBots_boats->pSousMarins[y];
            }
        }
    }
}
///
/// \param side le mettre a -1 si on veut juste savoir si on est dans la window, 0 si on veut le side du bot et 1 le side player
/// \param cursorPos
/// \param windowPos
/// \return
int cursorIsInWindow(int side, LPPOINT cursorPos, vec2_t windowPos) {
    if(GetActiveWindow() == Game->window){
        if (side == -1) {
            if ((cursorPos->x > windowPos.x) && (cursorPos->x < (windowPos.x + WINDOW_WIDTH))) {
                if ((cursorPos->y > (windowPos.y + 32)) &&
                    (cursorPos->y < (windowPos.y + WINDOW_HEIGHT + 25))) { //32 is the window bar height
                    return 1;
                }
            }
            return 0;
        } else if (side == 0) {
            if ((cursorPos->x > (windowPos.x + (WINDOW_WIDTH / 2))) && (cursorPos->x < (windowPos.x + WINDOW_WIDTH))) {
                if ((cursorPos->y > (windowPos.y + 32)) && (cursorPos->y < (windowPos.y + WINDOW_HEIGHT + 25))) {
                    return 1;
                }
            }
            return 0;
        } else if (side == 1) {
            if ((cursorPos->x > windowPos.x) && (cursorPos->x < (windowPos.x + (WINDOW_WIDTH / 2)))) {
                if ((cursorPos->y > (windowPos.y + 32)) && (cursorPos->y < (windowPos.y + WINDOW_HEIGHT + 25))) {
                    return 1;
                }
            }
            return 0;
        } else {
            MessageBoxA(NULL, "fct : cursorIsInWindow failed", NULL, 0);
            return 0;
        }
    }
    else{
        return 0;
    }
}
Case_t* getCasePtrWithPxCoords(int isPlayer, vec2_t relativeXY) {
    //printf("%d %d\n",relativeXY.x,relativeXY.y);
    vec2_t pV;
    for (int i = 0; i < GAME_DIMENSION; i++) {
        for (int j = 0; j < GAME_DIMENSION; j++) {
            if (isPlayer) {
                pV = Game->playerPlayground[i][j]->posInGrid;
                if ((pV.x <= relativeXY.x) && ((pV.x + 40) >= relativeXY.x)) {
                    if (pV.y <= relativeXY.y && ((pV.y + 40) >= relativeXY.y)) {
                        //printf("player %d",Game->botPlayground[i][j]->id);
                        return getCasePtrWithId(1, Game->playerPlayground[i][j]->id);
                    }
                }
            } else {
                pV = Game->botPlayground[i][j]->posInGrid;
                if ((pV.x <= relativeXY.x) && ((pV.x + 40) >= relativeXY.x)) {
                    if (pV.y <= relativeXY.y && ((pV.y + 40) >= relativeXY.y)) {
                        //printf("bot %d",Game->botPlayground[i][j]->id);
                        return getCasePtrWithId(0, Game->botPlayground[i][j]->id);
                    }
                }
            }
        }
    }
}

vec2_t GetWindowPos() {
    RECT rect = {};
    vec2_t pos;
    if( GetWindowRect( Game->window, &rect ) ) {
        pos.x = rect.left;
        pos.y = rect.top;
    }
    return pos;
}
