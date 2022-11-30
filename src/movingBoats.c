//
// Created by matt0 on 11/29/2022.
//
#include "includes.h"
/*
 * 1 - on attend un clic
 * 2 - on cherche la case ou il a cliquer
 * 3 - on check si ya un bateau
 * 4 - ...
 */
void movePlayer(){
    //either use this struct provided by windows api or getASyncKeyState()
    //MOUSEINPUT mice;


    if(GetAsyncKeyState(VK_LBUTTON)){
        GetCursorPos(Game->cursorPos);

    }

}
///
/// \param boatLen la longeur du bateau a bouger
/// \param bForward si il faut avancer ou reculer
void decaleBateau(int boatLen,int bForward)
{

}
