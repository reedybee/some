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

deltaWindow* deltaCreateWindow(const char* title, int x, int y, int w, int h) {
    #if defined(_WIN32) || defined(WIN32)
        return create_win32_window(title, x, y, w, h);
    #endif
}
void deltaUpdateWindow(deltaWindow* window) {
    #if defined(_WIN32) || defined(WIN32)
        poll_messages_win32(window);
        SwapBuffers(GetDC(window->win32_window_handle));
    #endif

    return;
}

int deltaWindowShouldClose(deltaWindow* window) {
    return window->destroyed;
}

void deltaDestroyWindow(deltaWindow* window) {
    DestroyWindow(window->win32_window_handle);
    free(window);
}

deltaWindow* deltaCopyWindow(deltaWindow* window) {
    deltaWindow* copy = malloc(sizeof(deltaWindow));
    memcpy(copy, window, sizeof(deltaWindow));
    return copy;
}

#endif