#include "delta/delta.h"
#include "delta/delta_win32.h"

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

DELTA_WIN32_IMPL deltaWindow* create_win32_window(const char* title,int x, int y, int w, int h) {

    deltaWindow* window = malloc(sizeof(deltaWindow));
    memset(window, 0, sizeof(deltaWindow));

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

    HWND hwnd = CreateWindowEx(
        0, 
        class_name,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        w,
        h,
        NULL,
        NULL, 
        instance,
        NULL
    );

    if (hwnd == NULL) {
        printf("Failed to create win32 window\n");
        get_last_error_win32("Create Win32 Window");
    }

    window->win32_window_handle = hwnd;

    ShowWindow(hwnd, 1);

    return window;
}

DELTA_WIN32_IMPL void poll_messages_win32(deltaWindow* window) {
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