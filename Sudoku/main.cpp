#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include "resource.h"
#include "sudoku.h"

const char g_szClassName[] = "myWindowClass";

static int npuzzle[81];

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case WM_INITDIALOG:

        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        //
        case IDD_OK:
        {            
            for (int outer = 0; outer < 9; outer++) {
                for (int inner = 0; inner < 9; inner++) {
                    int testeroni = GetDlgItemInt(hwnd, IDC_EDIT2 + outer * 9 + inner, 0, 0);
                    npuzzle[outer * 9 + inner] = testeroni;
                }
            }
            setpuzzle(npuzzle);
            itersolve(0, findstartcol());
            int* solved = getpuzzle();

            HWND solvedDialog = CreateDialog((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, AboutDlgProc);
            ShowWindow(solvedDialog, SW_SHOW);

            for (int a = 0; a < 81; a++) {
                HWND iter = GetDlgItem(hwnd, IDC_EDIT2 + a);
                std::string temp = std::to_string(*(solved + a));
                LPCSTR test = temp.c_str();
                SetDlgItemText(solvedDialog, IDC_EDIT2 + a, test);
            }
            UpdateWindow(hwnd);
            //EndDialog(hwnd, IDOK);
        }           
            break;
        //
        case IDD_CLEARPUZZLE:
        {
            for (int a = 0; a < 81; a++) {
                std::string blank = "";
                LPCSTR lpcstring = blank.c_str();
                SetDlgItemText(hwnd, IDC_EDIT2 + a, lpcstring);
            }
        }
            break;
        case IDD_CANCEL:
            EndDialog(hwnd, IDCANCEL);
            break;
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, IDCANCEL);
        break;
    default:
        return FALSE;
    }
    return TRUE;
}



// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) 
        {
            case IDC_MAIN_BUTTON:
            {
                HWND dialog = CreateDialog((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutDlgProc);
                ShowWindow(dialog, SW_SHOW);
            }
                break;
            case IDC_EXIT_BUTTON:
                DestroyWindow(hwnd);
                break;
        }
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    
    

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Sudoku",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 240,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    HWND button = CreateWindowEx(NULL, "button", "Solve a Sudoku Puzzle",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, 40,
        200, 30,
        hwnd, (HMENU)IDC_MAIN_BUTTON,
        GetModuleHandle(NULL), NULL);

    HWND exitbutton = CreateWindowEx(NULL, "button", "Exit the program",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, 100,
        200, 30,
        hwnd, (HMENU)IDC_EXIT_BUTTON,
        GetModuleHandle(NULL), NULL);

    HFONT hFont = CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma"));

    SendMessage(button, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(exitbutton, WM_SETFONT, (WPARAM)hFont, TRUE);
    

    UpdateWindow(hwnd);

    //HWND dialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutDlgProc);


    // Step 3: The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}


/*
case IDC_MAIN_BUTTON:
{
    HWND dialog = CreateDialog((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutDlgProc);
}
break;
*/