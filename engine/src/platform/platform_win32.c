#include "platform.h"

//Windows Platform layer.
#if KPLATFORM_WINDOWS

#include <windows.h>
#include <windowsx.h>

typedef struct internal_state {
    HINSTANCE h_instance;
    HWND hwnd;
} internal_state;

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

b8 platform_startup(
        platform_state *plat_state,
        const char *application_name,
        i32 x,
        i32 y,
        i32 width,
        i32 height){

    plat_state->internal_state = malloc(sizeof(internal_state));
    internal_state *state = (internal_state *)plat_state->internal_state;

    state->h_instance = GetModuleHandleA(0);

    //Setup and register window class.
    HICON icon = LoadIcon(state->h_instance, IDI_APPPLICATION);
    WNDCLASSA wc;
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_DBLCLKS; //get double clicks
    wc.lpfnWndProc = win32_process_message;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = state->h_instance;
    wc.hICon = icon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // NULL; // Manage the cursor manually.
    wc.hbrBackground = NULL; //transparent
    wc.lpszClassName = "chronos_window_class";

    if (!RegisterClassA(&wc)) {
        MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return FALSE;
    }

    //create window
    u32 client_x = x;
    u32 client-y = y;
    u32 client_width = width;
    u32 client_height = height;

    u32 window_x = client_x;
    u32 window_y = client_y;
    u32 window_width = client_width;
    u32 window_height = client_height;

    u32 window_style = WS_OVERLAPPED | ws_SYSMENU | WS_CAPTION;
    u32 window_ex_style = WS_EX_APPWINDOW;

    window_style != WS_MAXIMIZEBOX;
    window_style != WS_MINIMIZEBOX;
    window_style != WS_THICKFRAME;

    //Obtaine the size of border.
    RECT border_rect = {0, 0, 0, 0};
    AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);

    // In this case, the border rectangle is negative.
    window_x += border_rect.left;
    window_y += border_rect.top;

    // Grow by the size of the OS border.
    window_width += boder_rect.right - border_rect.left;
    window_height += boder_rect.bottom - border_rect.top;
    
    HWND handle = CreateWindowExA(
            window_ex_style, "chronos_window_class", application_name,
            window_style, window_x, window_y, window_width, window_height,
            0, 0, state->h_instance, 0);

    if (handle == 0 ) {
        MessageBoxA(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

        CFATAL("Window creation failed!");
        return FALSE;
    } else {
        state->hwnd = handle;
    }
}



#endif
