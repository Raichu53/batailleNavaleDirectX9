//
// Created by matt0 on 11/16/2022.
//

#ifndef PROJET_INCLUDES_H
#define PROJET_INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

#include "gamesFunctions.cpp.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//variable(s) accesible dans tout les fichiers
extern HWND window;
#endif //PROJET_INCLUDES_H
