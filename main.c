#include "includes.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    //pour le debug decommenter les 3 lignes commenté au debut et les 2 a la fin de ce fichier
    /*
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    */

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
    HWND window = CreateWindowEx(NULL, wcx.lpszClassName, "bataile navale", WS_OVERLAPPEDWINDOW,
                             100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, wcx.hInstance, NULL);

    // montrer la fenetre
    ShowWindow(window, nShowCmd);
    //gestion des interactions avec la fenetre (fonction WindowProc)
    MSG msg;

    while (1)
    {
        //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea
        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        if (msg.message == WM_QUIT || GetAsyncKeyState(VK_ESCAPE))//la croix ou echap
            break;

        Sleep(1);
    }
    /*
    fclose(f);
    FreeConsole();
     */
    return 0;
}
