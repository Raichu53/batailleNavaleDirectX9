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
    HWND window = CreateWindowEx(0, wcx.lpszClassName, "bataille navale", WS_OVERLAPPEDWINDOW,
                             100, 100, WINDOW_WIDTH+20, WINDOW_HEIGHT+40, NULL, NULL, wcx.hInstance, NULL);
                                                    //pour counter l'app bar
    // montrer la fenetre
    ShowWindow(window, nShowCmd);
    //gestion des interactions avec la fenetre (fonction WindowProc)
    MSG msg;

    initD3D(window);
    printf("Voulez vous charger la derniere save ? press Y / N\n");
    /*
    while(1){
        if(GetAsyncKeyState(0x59)){//y

            Game = game_load(window);
            if(Game->saveFile != NULL){
                loadBoats(Game->saveFile,Game->pBots_boats,Game->pPlayer_boats);
            }else{
                MessageBoxA(NULL,"fichier pas trouvé",NULL,0);
                exit(1);
            }
            break;
        }else if(GetAsyncKeyState(0x4E)){//n
            Game = game_new(window);
            spawnBoats(Game->pBots_boats,Game->pPlayer_boats);
            break;
        }
    }

     */
    Game = game_new(window);
    spawnBoats(Game->pBots_boats,Game->pPlayer_boats);
    printf("Press escape to show Menu\n");
    while (1)
    {
        //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea
        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        render_frame();
        if(Game->playerTurn && ((Game->ms - Game->oldms) > 200)){//on met playerTurn = 0 si il y a eu tir ou mouvement
            playerActions();
            Game->oldms = Game->ms;
        }else if(!Game->playerTurn && ((Game->ms - Game->oldms) > 200)){
            botAction();
            Game->oldms = Game->ms;
        }

        mingw_gettimeofday(&Game->tp, NULL);
        Game->ms = Game->tp.tv_sec * 1000 + Game->tp.tv_usec / 1000;

        if(isGameFinished(Game->pPlayer_boats,Game->pBots_boats)){
            system("cls");
            Game = game_new(window);
            spawnBoats(Game->pBots_boats,Game->pPlayer_boats);
        }
        if (msg.message == WM_QUIT )//la croix
            break;


        Sleep(10);
    }

    cleanEverything();
    fclose(f);
    FreeConsole();

    return 0;
}
