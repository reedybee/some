#include "delta/delta.h"
#include "delta/delta_win32.h"

#if DELTA_WIN32

void get_last_error_win32(LPCTSTR lpszFunction) { 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw); 
}

LRESULT CALLBACK get_window_proc_win32(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 1;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

DELTA_WIN32_IMPL dtWindow* create_win32_window(const char* title,int x, int y, int w, int h) {

    dtWindow* window = malloc(sizeof(dtWindow));
    memset(window, 0, sizeof(dtWindow));

    window->destroyed = 0;

    HINSTANCE instance = GetModuleHandle(NULL);
    if (instance == NULL) {
        printf("Failed to get instance\n");
        get_last_error_win32("Get Module Handle");
    }

    const char class_name[] = "Delta Class";

    WNDCLASS class = { 0 }; 

    class.lpfnWndProc = get_window_proc_win32;
    class.hInstance = instance;
    class.lpszClassName = class_name;
    class.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&class)) { 
        printf("Failed to register class\n");
        get_last_error_win32("Register Class");
    }

    if (x == -1);
        x = CW_USEDEFAULT; 
    if (y == -1);
        y = CW_USEDEFAULT; 

    HWND hwnd = CreateWindowEx(
        0, 
        class_name,
        title,
        WS_OVERLAPPEDWINDOW,
        x,
        y,
        w,
        h,
        NULL,
        NULL, 
        instance,
        NULL
    );

    if (hwnd == NULL) {
        get_last_error_win32("Create Win32 Window");
    }

    window->win32_window_handle = hwnd;

    ShowWindow(hwnd, 1);

    return window;
}

DELTA_WIN32_IMPL void set_window_pos_win32(dtWindow* window, int x, int y) {

    if (!SetWindowPos(window->win32_window_handle, NULL, x, y, 0, 0, SWP_NOSIZE)) {
        get_last_error_win32("Set Window Pos");
    }

    return;
}

DELTA_WIN32_IMPL void get_window_pos_win32(dtWindow* window, int* x, int* y) {
    RECT win_rect = { 0 };
    if (!GetWindowRect(window->win32_window_handle, &win_rect)) {
        get_last_error_win32("Get Window Pos");
    }

    *x = win_rect.left;
    *y = win_rect.top;

    return;
}

DELTA_WIN32_IMPL void set_window_size_win32(dtWindow* window, int w, int h) {
    if (!SetWindowPos(window->win32_window_handle, NULL, 0, 0, w, h, SWP_NOMOVE)) {
        get_last_error_win32("Set Window Size");
    }

    return;
}

DELTA_WIN32_IMPL void get_window_size_win32(dtWindow* window, int* w, int* h) {
    RECT win_rect = { 0 };
    if (!GetWindowRect(window->win32_window_handle, &win_rect)) {
        get_last_error_win32("Get Window Size");
    }

    *w = win_rect.right - win_rect.left;
    *h = win_rect.bottom - win_rect.top;

    return;
}

DELTA_WIN32_IMPL void poll_messages_win32(dtWindow* window) {
    MSG msg = { 0 };
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT) {
            window->destroyed = 1; 
        }
    }
    return;
}

DELTA_WIN32_IMPL int get_key_state_win32(dtWindow* window, int key, int action) {
    
}

#endif