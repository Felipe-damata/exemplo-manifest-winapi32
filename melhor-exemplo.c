#define UNICODE
#define _UNICODE

#include <windows.h>
#include <commctrl.h>       // Needed for InitCommonControls()
#include "resource.h"       // Your button and icon IDs

const wchar_t g_szClassName[] = L"minha_janela";

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(
            L"BUTTON", L"Botão 1",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            50, 50, 120, 30,
            hwnd, (HMENU)ID_BUTTON1,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
        );

        CreateWindowW(
            L"BUTTON", L"Botão 2",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            200, 50, 120, 30,
            hwnd, (HMENU)ID_BUTTON2,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
        );
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BUTTON1:
            MessageBoxW(hwnd, L"Você clicou no Botão 1!", L"Info", MB_OK);
            break;
        case ID_BUTTON2:
            MessageBoxW(hwnd, L"Você clicou no Botão 2!", L"Info", MB_OK);
            break;
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        TextOutW(hdc, 10, 10, L"WinAPI Exemplo!", 16);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Entry Point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)lpCmdLine;

    // Enable themed controls (older but works)
    InitCommonControls();

    // Register window class
    WNDCLASSEXW wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIconW(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIconW(hInstance, MAKEINTRESOURCE(IDI_ICON1));

    if (!RegisterClassExW(&wc)) {
        MessageBoxW(NULL, L"Erro ao registrar a classe!", L"Erro", MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        L"Exemplo com dois botões",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        MessageBoxW(NULL, L"Erro ao criar a janela!", L"Erro", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}
