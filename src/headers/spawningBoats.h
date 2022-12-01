//
// Created by matt0 on 11/27/2022.
//

#ifndef PROJET_SPAWNINGBOATS_H
#define PROJET_SPAWNINGBOATS_H

void spawnBoats(bots_boats_t* pB,player_boats_t* pP);
Case_t* getCasePtrWithId(int isPlayer,int id);
int isGoingToFit(int isPlayer,int len,int isVertical,int caseId,bots_boats_t* pB,player_boats_t* pP);

#endif //PROJET_SPAWNINGBOATS_H
