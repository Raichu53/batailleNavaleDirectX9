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
#endif //PROJET_MOVINGBOATS_H
