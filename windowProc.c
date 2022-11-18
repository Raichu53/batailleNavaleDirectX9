//
// Created by matt0 on 11/18/2022.
//
#include "includes.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch (message)
    {
        case WM_COMMAND:

        case WM_DESTROY:
            // close the application entirely
            PostQuitMessage(0);
            return 0;
            break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}