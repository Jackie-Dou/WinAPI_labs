// OSi_lab_1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "OSi_lab_1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр (дескриптор экземпляра приложения)
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hWnd; //описатель окна, от которого GetMessage будет принимать сообщения - дескриптор окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance); //регистрация
BOOL                InitInstance(HINSTANCE, int); //поддержка нескольких экземпляров
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM); //обработка сообщений окна
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, //текущий экземпляр
                     _In_opt_ HINSTANCE hPrevInstance, //предыдущий
                     _In_ LPWSTR    lpCmdLine, //командная строка
                     _In_ int       nCmdShow) //тип отображения окна программы
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.


    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OSILAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OSILAB1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OSILAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OSILAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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

  // hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
  //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE,
           CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   //ShowWindow(hWnd, nCmdShow);
   ShowWindow(hWnd, SW_SHOWMAXIMIZED);
   UpdateWindow(hWnd);

   return TRUE;
}

//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться


int screenX = 750;
int screenY = 400;
int bias = 65;
int speed = 10;
int rebound = speed * 4;
int wheelDelta = 0;
int fwKeys = 0;
bool check = 0;
RECT rect;
RECT prevPos;
HANDLE hImage;


void UseSprite()
{
    PAINTSTRUCT ps;
    HDC hdc;

    hdc = BeginPaint(hWnd, &ps); 

    HBRUSH hBrush;
    hBrush = CreateSolidBrush(RGB(0, 195, 157)); 
    SelectObject(hdc, hBrush); 
    Rectangle(hdc, screenX - bias, screenY - bias, screenX + bias, screenY + bias); 
    EndPaint(hWnd, &ps);
    check = 0;
}

void UsePicture()
{
    
    PAINTSTRUCT ps;
    HDC hdc, hmdc;
    hdc = BeginPaint(hWnd, &ps);
    hmdc = CreateCompatibleDC(hdc);
    SelectObject(hmdc, hImage);
    BitBlt(hdc, screenX - bias, screenY - bias, screenX + bias, screenY + bias, hmdc, NULL, NULL, SRCAND); 
    DeleteDC(hmdc); 

    //Ellipse(hdc, screenX - bias, screenY - bias, screenX + bias, screenY + bias);

    EndPaint(hWnd, &ps);
    check = 1;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    GetClientRect(hWnd, &rect);

    switch (message)
    {
    case WM_CREATE:
        hImage = LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 2 * bias, 2 * bias, LR_COPYFROMRESOURCE);
        SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(219, 219, 219)));
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
    case WM_PAINT:
        { 
            if (check == 0)
                UseSprite();
            else
                UsePicture();
        }
        break;

    //Обработка нажатия клавиши
    case WM_KEYDOWN:
    {
        prevPos.top = screenY - bias-rebound;
        prevPos.bottom = screenY + bias+rebound;
        prevPos.left = screenX - bias-rebound;
        prevPos.right = screenX + bias+rebound;

        switch (wParam) {
        case VK_LEFT:
            screenX -= speed;
            if ((screenX-bias) < (&rect)->left)
                screenX += rebound;
            break;
        case VK_RIGHT:
            screenX += speed;
            if ((screenX+bias) > (&rect)->right)
                screenX -= rebound;           
            break;
        case VK_UP:
            screenY -= speed;
            if ((screenY-bias) < (&rect)->top)
                screenY += rebound;
            break;
        case VK_DOWN:
            screenY += speed;
            if ((screenY+bias) > (&rect)->bottom)
                screenY -= rebound;
            break;
        case VK_CONTROL:
            if (check == 0) {
                UsePicture();
                check = 1;
            }    
            else {
                UseSprite();
                check = 0;
            }
            break;
        default:
            break;
        }       
        InvalidateRect(hWnd, &prevPos, true);
        /*if (check == 0)
            UseSprite();
        else
            UsePicture();*/
        break;
    }
    case WM_MOUSEWHEEL: 
    {
        prevPos.top = screenY - bias - rebound;
        prevPos.bottom = screenY + bias + rebound;
        prevPos.left = screenX - bias - rebound;
        prevPos.right = screenX + bias + rebound;

        wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
        fwKeys = GET_KEYSTATE_WPARAM(wParam);
        for (; wheelDelta > WHEEL_DELTA; wheelDelta -= WHEEL_DELTA)
        {
            if (fwKeys == MK_SHIFT) {
                screenX -= speed;
                if ((screenX - bias) < (&rect)->left)
                    screenX += rebound;
            }
            else {
                screenY -= speed;
                if ((screenY - bias) < (&rect)->top)
                    screenY += rebound;
            }
        }
        for (; wheelDelta < 0; wheelDelta += WHEEL_DELTA)
        {
            if (fwKeys == MK_SHIFT) {  
                screenX += speed;
                if ((screenX + bias) > (&rect)->right)
                    screenX -= rebound;
            }
            else {
                screenY += speed;
                if ((screenY + bias) > (&rect)->bottom)
                    screenY -= rebound;
            }
        }
        InvalidateRect(hWnd, &prevPos, true);
        break;
    }
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

//InvalidateRect (false)
//LOADIMAGE вынести
//Сохранять координаты
//Забелять только старую область
//и перерисовывать тоже

//и это обновление поля загнать в область двойной буферизации??? (Мурашко)
