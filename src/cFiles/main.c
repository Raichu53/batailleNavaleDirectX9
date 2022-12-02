#include "../headers/includes.h"

Game_t* Game = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    //pour le debug decommenter ces 3 lignes et les 2 a la fin du main

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);


    WNDCLASSEX wcx = {};
    ZeroMemory(&wcx,sizeof(WNDCLASSEX));

    //element obligatoire a definir
    wcx.cbSize = sizeof(wcx);
    wcx.hInstance = hInstance;
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpszClassName = "window1";
    wcx.lpfnWndProc = WndProc; //fonction qui gere les evenements

    //on "enregistre" la classe
    RegisterClassEx(&wcx);
    //on crée la fenetre
    HWND window = CreateWindowEx(0, wcx.lpszClassName, "bataile navale", WS_OVERLAPPEDWINDOW,
                             100, 100, WINDOW_WIDTH+20, WINDOW_HEIGHT+40, NULL, NULL, wcx.hInstance, NULL);
                                                    //pour counter l'app bar
    // montrer la fenetre
    ShowWindow(window, nShowCmd);
    //gestion des interactions avec la fenetre (fonction WindowProc)
    MSG msg;

    initD3D(window);

    while (1)
    {
        //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea
        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        render_frame();
        playerActions();


        if (msg.message == WM_QUIT || GetAsyncKeyState(VK_ESCAPE))//la croix ou echap
            break;

        Sleep(10);
    }
    cleanD3D();

    fclose(f);
    FreeConsole();

    return 0;
}
