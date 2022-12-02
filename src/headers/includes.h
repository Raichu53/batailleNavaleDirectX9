//
// Created by matt0 on 11/16/2022.
//
#ifndef PROJET_INCLUDES_H
#define PROJET_INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

#include "gamesFunctions.h"
#include "dx.h"
#include "spawningBoats.h"
#include "movingBoats.h"
#include "shooting.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


extern Game_t* Game;


#endif //PROJET_INCLUDES_H
