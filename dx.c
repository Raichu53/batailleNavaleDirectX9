//
// Created by matt0 on 11/19/2022.
//
#include "includes.h"
#include "./MicrosoftDirectXSDKJune2010/Include/d3d9.h"
#include "./MicrosoftDirectXSDKJune2010/Include/d3dx9.h"

IDirect3D9* d3d = NULL;
IDirect3DDevice9* d3ddev = NULL;

void initD3D()
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);    // crée l'interface direct3D
    D3DPRESENT_PARAMETERS d3dpp;    // crée les param pour la creation du device

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;    // pas fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = window;    //la fenetre sur laquelle on va utilisé direct3D


    // on crée la struct du device en utilisant les params d3dpp
    d3d->lpVtbl->CreateDevice(d3d,D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      window,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
}

void render_frame()
{
    // Clear rose
    d3ddev->lpVtbl->Clear(d3ddev,0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 255), 1.0f, 0);

    d3ddev->lpVtbl->BeginScene(d3ddev);    // demarre la scene 3D

    // do 3D rendering on the back buffer here

    d3ddev->lpVtbl->EndScene(d3ddev);    // ferme la scene 3D

    d3ddev->lpVtbl->Present(d3ddev,NULL, NULL, NULL, NULL);   // affiche la frame que l'on vien de crée
}
void cleanD3D()
{
    d3ddev->lpVtbl->Release(d3ddev);
    d3d->lpVtbl->Release(d3d);
}
