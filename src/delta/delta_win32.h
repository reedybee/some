#ifndef DELTA_WIN32_H
#define DELTA_WIN32_H

#include "delta/delta.h"

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND wind, UINT msg, WPARAM wparam, LPARAM lparam) {
    return DefWindowProc(wind, msg, wparam, lparam);
}

DELTA_WIN32_IMPL deltaWindow* delta_create_win32_window(const char* title, int width, int height) {

    WNDCLASS win_class = { 0 }; 

    win_class.lpfnWndProc = WindowProc;
    win_class.hInstance = GetModuleHandle(NULL);
    win_class.lpszClassName = _T("Window Class");

    RegisterClass(&win_class);

    HWND hwnd = CreateWindowEx(
        0, 
        _T("Window Class"),
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        NULL,
        NULL, 
        GetModuleHandle(NULL),
        NULL
    );

    if (hwnd == NULL) {
        // failed to create window
    }

    ShowWindow(hwnd, 1);

    deltaWindow* window = malloc(sizeof(deltaWindow));

    window->win32_window_handle = hwnd;
    window->destroyed = 0;

    return window;
}  

DELTA_WIN32_IMPL void delta_poll_messages_win32(deltaWindow* window) {
    MSG msg = { 0 };
    while (GetMessage(&msg, window->win32_window_handle, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_CLOSE)
            DestroyWindow(window->win32_window_handle);
        if (msg.message == WM_DESTROY) 
            window->destroyed = 1;
    }
}

#endif