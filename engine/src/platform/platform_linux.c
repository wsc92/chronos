#include "platform.h"
#include <xcb/xproto.h>

// Linux platform layer.
#if KPLATFORM_LINUX

#include "../core/logger.h"

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <sys/time.h>

#if _POSIX_C_SOURCE >= 199309L
#include <time.h> // nanosleep
#else
#include <unistd.h> // usleep
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct internal_state {
    Display *display;
    xcb_connection_t *connection;
    xcb_window_t window;
    xcb_screen_t *screen;
    xcb_atom_t wm_protocols;
    xcb_atom_t wm_delete_wm;
} internal_state;

b8 platform_startup(platform_state* plat_state, const char* application_name, i32 x, i32 y, i32 width, i32 height)
{
    // Create the internal state.
    plat_state->internal_state = malloc(sizeof(internal_state));
    internal_state *state = (internal_state *)plat_state->internal_state;

    // connect to X11
    state->display = XOpenDisplay(NULL);

    // Turn off key repeasts.
    XAutoRepeatOff(state->display);

    // Retrieve the connection from the display
    state->connection = XGetXCBConnection(state->display);

    if (xcb_connection_has_error(state->connection)) {
        KFATAL("Failed to connect to X server via XCB.");
        return FALSE;
    }

    // Get data from the X server
    const struct xcb_setup_t *setup = xcb_get_setup(state->connection);

    // Loop through screens using iterator
    xcb_screen_iterator_t it = xcb_setup_roots_iterator(setup);
    int screen_p = 0;
    for (i32 s = screen_p; s > 0; s--) {
        xcb_screen_next(&it);
    }

    // After screens have been looped through, assign it.
    state->screen = it.data;

    // allocate a XID for the window to be created.
    state->window = xcb_generate_id(state->connection);

    // Register Event Types
    // XCB_CW_BACK_PIXEL = filling the window bg with a single colour
    // XCB_CW_EVENT_MASK is required.
    u32 event_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

    // Listen for keyboard and mouse buttons
    u32 event_values = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
                        XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
                        XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
                        XCB_EVENT_MASK_STRUCTURE_NOTIFY;

    // Values to be sent over to XCB (bg colour, events)
    u32 value_list[] = {state->screen->black_pixel, event_values};

    //create the window
    xcb_void_cookie_t cookie = xcb_create_window(
            state->connection,
            XCB_COPY_FROM_PARENT, // depth
            state->window,
            state->screen->root,
            x,
            y,
            width,
            height,
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            state->screen->root_visual,
            event_mask,
            value_list);

    // change the title
    xcb_change_property(
            state->connection,
            XCB_PROP_MODE_REPLACE,
            state->window,
            XCB_ATOM_WM_NAME,
            XCB_ATOM_STRING,
            8, // data should be viewed 8 bits at a time
            strlen(application_name),
            application_name);

    // Tell the server to notify when the window manager
    // attempts to destroy the window.
    xcb_intern_atom_cookie_t wm_delete_cookie = xcb_intern_atom(
            state->connection,
            0,
            strlen("WM_DELETE_WINDOW"),
            "WM_DELETE_WINDOW");
    xcb_intern_atom_cookie_t wm_protocols_cookie = xcb_intern_atom(
            state->connection,
            0,
            strlen("WM_PROTOCOLS"),
            "WM_PROTOCOLS");
    xcb_intern_atom_reply_t *wm_delete_reply = xcb_intern_atom_reply(
            state->connection,
            wm_delete_cookie,
            NULL);
    xcb_intern_atom_reply_t *wm_protocols_reply = xcb_intern_atom_reply(
            state->connection,
            wm_protocols_cookie,
            NULL);
    state->wm_delete_wm = wm_delete_reply->atom;
    state->wm_protocols = wm_protocols_reply->atom;

    xcb_change_property(
            state->connection,
            XCB_PROP_MODE_REPLACE,
            state->window,
            wm_protocols_reply->atom,
            4,
            32,
            1,
            &wm_delete_reply->atom);

    // Map the window to the screen
    xcb_map_window(state->connection, state->window);

    // Flush the stream
    i32 stream_result = xcb_flush(state->connection);
    if (stream_result <= 0) {
        KFATAL("An error occured when flushing the stream: %d", stream_result);
        return FALSE;
    }

    return TRUE;
}

// TODO: KOHI #5 20:14 timestamp 
// complete all these methods
// 
void platform_shutdown(platform_state* plat_state) {

}

b8 platform_pump_messages(platform_state* plat_state) {

}

void* platform_allocate(u64 size, b8 alligned){}
void platform_free(void* block, b8 alligned){}
void* platform_zero_memory(void* block, u64 size){}
void* platform_copy_memory(void* dest, const void* source, u64 size){}
void* platform_set_memory(void* dest, i32 value, u64 size){}

void platform_console_write(const char* message, u8 colour){}
void platform_console_write_error(const char* message, u8 colour){}

f64 platform_get_absolute_time() {

}

// Sleep on the thread for the provided ms. This blocks the main thread.
// Should only be used for giving time back to the OS for unused update power.
// Therefore it is not exported.
void platform_sleep(u64 ms) {

}
#endif
