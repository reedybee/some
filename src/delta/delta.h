#ifndef DELTA_H
#define DELTA_H

#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
#endif

// defines what is a win32 delta function
#define DELTA_WIN32_IMPL

struct DELTA_WINDOW {
    HWND win32_window_handle;
    int destroyed;
} typedef deltaWindow;

#include "delta/delta_win32.h"

deltaWindow* deltaCreateWindow(const char* title,
                       int width, int height) {
    #if defined(_WIN32) || defined(WIN32)
        return delta_create_win32_window(title, width, height);
    #endif
}
void deltaUpdateWindow(deltaWindow* window) {
    #if defined(_WIN32) || defined(WIN32)
        delta_poll_messages_win32(window);
        SwapBuffers(GetDC(window->win32_window_handle));
    #endif
}

int deltaWindowShouldClose(deltaWindow* window) {
    return window->destroyed;
}

#endif