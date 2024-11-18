#include <windows.h>
#include <iostream>
#include <cstdlib>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);

    int msgResponse = MessageBox(NULL, "If you have epilepsy, I recommend closing this window!", "Warning", MB_OKCANCEL | MB_ICONWARNING);
    if (msgResponse == IDCANCEL) return 0; 
    else if (msgResponse == IDOK) {
        msgResponse = MessageBox(NULL, "You sure?", "Warning", MB_OKCANCEL | MB_ICONWARNING); 
        if (msgResponse == IDCANCEL) return 0;
    }

    const char CLASS_NAME[] = "Window Class";
    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "PepeGdiVirus",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) return 0;
    
    ShowWindow(hwnd, SW_HIDE);

    MSG msg = {};
    while (true) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) return 0;
        }

        HDC hdc = GetDC(0);

        POINT p[4] = { {rand() % sw, rand() % sh}, {rand() % sw, rand() % sh}, {rand() % sw, rand() % sh}, {rand() % sw, rand() % sh} };
        HPEN hPen = CreatePen(PS_SOLID, 5, RGB((rand() % 256), (rand() % 256), (rand() % 256)));
        SelectObject(hdc, hPen);
        PolyBezier(hdc, p, 4);
        DeleteObject(hPen);

        PatBlt(hdc, 0, 0, sw, sh, PATINVERT);

        StretchBlt(hdc, 0, -20, sw, sh + 40, hdc, 0, 0, sw, sh, SRCCOPY);

        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        BitBlt(hdc, 0, 0, sw, sh, hdc, -30, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, sw, sh, hdc, sw - 30, 0, SRCCOPY);
        DeleteObject(brush);

        BitBlt(hdc, rand() % 2, rand() % 2, sw, sh, hdc, rand() % 2, rand() % 2, SRCCOPY);

        BitBlt(hdc, rand() % sw, 10, 100, sh, hdc, rand() % sw, 0, SRCCOPY);

        ReleaseDC(0, hdc);
    }

    return 0;
}
