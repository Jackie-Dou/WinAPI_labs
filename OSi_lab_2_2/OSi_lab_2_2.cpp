// OSi_lab_2_2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "OSi_lab_2_2.h"
#include <string>

#define MAX_LOADSTRING 100
#define NUM_COLUMNS 5
#define NUM_STR 20

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OSILAB22, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OSILAB22));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OSILAB22));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OSILAB22);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

HWND hWnd;

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

int wdth = 0, xPos = 0, yPos = 0, index = 0, num = 0;
using namespace std;
wstring arrayStrings[NUM_STR] = 
{ L" hello world! here are some text for testing my small simple application ", 
L"Read a blogpost about the impact of social media influencers in the business world to practise and improve your reading skills. ", 
L"It is estimated that about 40 per cent of the world’s population use social media",
L"and many of these billions of social media users look up to influencers to help",   
L"them decide what to buy and what trends to follow ", 
L"An influencer is a person who can influence the decisions of their followers because of their relationship with their audience or technology.", 
L"Influencers often have a large following of people",
L"who pay close attention to their views. They have the power to persuade people to buy things, and influencers are now seen by many companies as a direct way to customers’ hearts. ", 
L"Brands are now asking powerful influencers to market their products. With some influencers charging up to $25,000 for one social media post ", 
L"it is no surprise that more and more people are keen to become ", 
L"influencers too. If you are one of them, then here are five tips on how to do it. ", 
L"What is the area that you know most about? What do you feel most excited talking about? Find the specific area that you’re most interested in and develop it. ", 
L"Most influencers these days are bloggers and micro-bloggers. Decide which medium – such as your own online ",
L"blog, Instagram or Snapchat – is the best way to connect with your followers and chat about your niche area. When you have done that, write an attention-grabbing ",
L"bio that describes you and your speciality area in an interesting and unique way. ",
L"Make sure that people who read your bio will want to follow you.",
L"Many influencers post daily on their social media accounts. The more you post, the more likely people will follow you. ",
L"Also, ensure that your posts are consistent and possibly follow a theme. ",
//L"Whether it is a photo or a comment that you are posting, use it to tell a story that will catch the attention of your followers and help them connect with you.",
L"Whether it is a photo or a comment that you are posting, use it to tell a story that will catch the attention of your followers and help them connect with you." };


BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
    HPEN hPen;
    hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, x1, y1, NULL);
    return LineTo(hdc, x2, y2);
}


int FillString(HDC hdc, int xPos, int yPos, int index) {
    RECT rcl;
    rcl.top = yPos+3;
    rcl.bottom = yPos + 10000;
    int hth, maxhth = 0;
    
    for (int i = 0; i < NUM_COLUMNS; i++) {
        rcl.left = wdth * i + 3;
        rcl.right = wdth * (i + 1) - 3;
        LPCWSTR temp = arrayStrings[index + i].c_str();
        try {
            hth = DrawText(hdc, temp, -1, &rcl, DT_NOCLIP | DT_CENTER | DT_WORDBREAK);
        }
        catch (exception) {
            temp = L"";
            hth = DrawText(hdc, temp, -1, &rcl, DT_NOCLIP | DT_CENTER | DT_WORDBREAK);
        }
        if (hth > maxhth) {
            maxhth = hth;
            rcl.bottom = yPos + maxhth + 3;
        }
    }
    Line(hdc, 0, yPos + maxhth, xPos, yPos + maxhth);
    return (yPos + maxhth);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {    
    case WM_CREATE:
        if (NUM_STR % 2 == 1)
            num = (NUM_STR / NUM_COLUMNS) + 1;
        else
            num = (NUM_STR / NUM_COLUMNS);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_SIZE:
    {
            xPos = (int)(short)LOWORD(lParam);   
            yPos = (int)(short)HIWORD(lParam);   
            wdth = xPos / NUM_COLUMNS;
            index = 0;
            InvalidateRect(hWnd, NULL, true);
        break;
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            for (int i = 0; i <= NUM_COLUMNS; i++)
                Line(hdc, 0 + i * wdth, 0, 0 + i * wdth, yPos);
            int ind, prevind = 0;
            for (int i = 0; i < num; i++) {
                ind = FillString(hdc, xPos, prevind, index);
                prevind = ind;
                index += NUM_COLUMNS;
            }            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
