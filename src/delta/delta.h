#ifndef DELTA_H
#define DELTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defines what is a win32 delta function
#define DELTA_WIN32_IMPL

#define DELTA_WINDOW_CENTERED -(0x01)

#define DELTA_KEY_UP 0
#define DELTA_KEY_DOWN 1

#if defined(_WIN32) || defined(WIN32)
    #define DELTA_WIN32 1
    #include <windows.h>
    struct DT_WINDOW {
        HWND win32_window_handle;
        int destroyed;
    } typedef dtWindow;
    #include "delta/delta_win32.h"
#endif

#if defined(__unix__)
    struct DT_WINDOW {
        int destroyed;
    } typedef dtWindow;
#endif

dtWindow* dtCreateWindow(const char* title, int x, int y, int w, int h) {
    #if DELTA_WIN32
        return create_win32_window(title, x, y, w, h);
    #endif
}
void dtUpdateWindow(dtWindow* window) {
    #if DELTA_WIN32
        poll_messages_win32(window);
        SwapBuffers(GetDC(window->win32_window_handle));
    #endif

    return;
}

int dtWindowShouldClose(dtWindow* window) {
    return window->destroyed;
}

void dtDestroyWindow(dtWindow* window) {
    #if DELTA_WIN32
        DestroyWindow(window->win32_window_handle);
    #endif
    free(window);
}

dtWindow* dtCopyWindow(dtWindow* window) {
    dtWindow* copy = malloc(sizeof(dtWindow));
    memcpy(copy, window, sizeof(dtWindow));
    return copy;
}

void dtSetWindowPos(dtWindow* window, int x, int y) {
    #if DELTA_WIN32
        set_window_pos_win32(window, x, y);
    #endif
    return;
}

void dtGetWindowPos(dtWindow* window, int* x, int* y) {
    #if DELTA_WIN32
        get_window_pos_win32(window, x, y);
    #endif
}

void dtSetWindowSize(dtWindow* window, int w, int h) {
    #if  DELTA_WIN32
        set_window_size_win32(window, w, h);
    #endif
    return;
}

void dtGetWindowSize(dtWindow* window, int* w, int* h) {
    #if DELTA_WIN32
        get_window_size_win32(window, w, h);
    #endif
}

#endif