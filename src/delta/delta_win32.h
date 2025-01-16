#ifndef DELTA_WIN32_H
#define DELTA_WIN32_H

#if defined(_WIN32) || defined(WIN32)

#include "delta/delta.h"

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#include <strsafe.h>

void get_last_error_win32(LPCTSTR lpszFunction);

LRESULT CALLBACK get_window_proc_win32(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

DELTA_WIN32_IMPL dtWindow* create_win32_window(const char* title,int x, int y, int w, int h);

DELTA_WIN32_IMPL void poll_messages_win32(dtWindow* window);

DELTA_WIN32_IMPL void set_window_pos_win32(dtWindow* window, int x, int y);

DELTA_WIN32_IMPL void get_window_pos_win32(dtWindow* window, int* x, int* y);

DELTA_WIN32_IMPL void set_window_size_win32(dtWindow* window, int w, int h);

DELTA_WIN32_IMPL void get_window_size_win32(dtWindow* window, int* w, int* h);

DELTA_WIN32_IMPL int get_key_state_win32(dtWindow* window, int key, int action);

#endif
#endif