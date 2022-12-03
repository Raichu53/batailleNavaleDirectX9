//
// Created by matt0 on 12/2/2022.
//
#include "../headers/includes.h"

void botAction(){
    int randomInt = rand()%224;
    printf("bot shot at %d\n",randomInt);
    fire(1, getCasePtrWithId(1,randomInt));

}
