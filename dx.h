//
// Created by matt0 on 11/19/2022.
//

#ifndef PROJET_DX_H
#define PROJET_DX_H


void initD3D(HWND window);
void render_frame();
void cleanD3D();
GameSprite_t* GameSprite_new();
GameSprite_t* GameSprite_newWithPos(float x, float y);
#endif //PROJET_DX_H
