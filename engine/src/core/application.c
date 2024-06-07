#include "application.h"
#include "../game_types.h"

#include "logger.h"
#include "../platform/platform.h"
#include "cmemory.h"
#include "event.h"
#include "input.h"

typedef struct application_state {
    game* game_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initialized = FALSE;
static application_state app_state;

// Event handlers
b8 application_on_event(u16 code, void* sender, void* listener_inst, event_context context);
b8 application_on_key(u16 code, void* sender, void* listener_inst, event_context context);

b8 application_create(game* game_inst) {
    if (initialized) {
        CERROR("application_create called more than once.");
        return FALSE;
    }

    app_state.game_inst = game_inst;

    // initialize subsystems.
    initialize_logging();
    input_initialize();

    // TODO: Remove this later
    CFATAL("A test message: %f", 3.14f);
    CERROR("A test message: %f", 3.14f);
    CWARN("A test message: %f", 3.14f);
    CINFO("A test message: %f", 3.14f);
    CDEBUG("A test message: %f", 3.14f);
    CTRACE("A test message: %f", 3.14f);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    // check event System
    if (!event_initialize()) {
        CERROR("Event system failed initialization. Application cannot continue.");
        return FALSE;
    }

    // Register Events
    event_register(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_register(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
    event_register(EVENT_CODE_KEY_RELEASED, 0, application_on_key);

    if(!platform_startup(
                &app_state.platform,
                game_inst->app_config.name,
                game_inst->app_config.start_pos_x,
                game_inst->app_config.start_pos_y,
                game_inst->app_config.start_width,
                game_inst->app_config.start_height)) {
        return FALSE;
    }

    // initialize the game.
    if (!app_state.game_inst->initialize(app_state.game_inst)) {
        CFATAL("Game failed to initialize.");
        return FALSE;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialized = TRUE;

    return TRUE;
}

b8 application_run() {
    CINFO(get_memory_usage_str());

    // GAME LOOP
    while(app_state.is_running) 
    {
        if(!platform_pump_messages(&app_state.platform)) {
            app_state.is_running = FALSE;
        }

        if (!app_state.is_suspended) {
            // call the update routine
            if (!app_state.game_inst->update(app_state.game_inst, (f32)0)) {
                CFATAL("Game update failed,. shuttding down");
                app_state.is_running = FALSE;
                break;
            }

            // Call the games render routine.
            if (!app_state.game_inst->render(app_state.game_inst, (f32)0)) {
                CFATAL("Game Render failed, shutting down.");
                app_state.is_running = FALSE;
                break;
            }

            // NOTE: Input update/state copying should always be handled
            // after any input should be recorded; I.E. before this line.
            // As a safety, input is the last thing to be updated before
            // this frame ends.
            input_update(0);
        }
    }

    app_state.is_running = FALSE;


    //Unregister events
    event_unregister(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_unregister(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
    event_unregister(EVENT_CODE_KEY_RELEASED, 0, application_on_key);

    event_shutdown();
    input_shutdown();

    platform_shutdown(&app_state.platform);

    return TRUE;
}

b8 application_on_event(u16 code, void* sender, void* listener_inst, event_context context) {
    switch (code) {
        case EVENT_CODE_APPLICATION_QUIT: {
            CINFO("EVENT_CODE_APPLICATION_QUIT recieved, shutting down.\n");
            app_state.is_running = FALSE;
            return TRUE;
        }
    }

    return FALSE;
}

b8 application_on_key(u16 code, void* sender, void* listener_inst, event_context context) {
    if (code == EVENT_CODE_KEY_PRESSED) {
        u16 key_code = context.data.u16[0];
        if (key_code == KEY_ESCAPE) {
            // NOTE: Technically firing an event to itself, but there may be other listeners.
            event_context data = {};
            event_fire(EVENT_CODE_APPLICATION_QUIT, 0, data);

            // Block anything else from processing this.
            return TRUE;
        } else if (key_code == KEY_A) {
            //Example for checking a key_code
            CDEBUG("Explicit - A key pressed!");
        } else {
            CDEBUG("'%c' key pressed in window.", key_code);
        }
    } else if (code == EVENT_CODE_KEY_RELEASED) {
        u16 key_code = context.data.u16[0];
        if (key_code == KEY_B) {
            // Example on checking for a key
            CDEBUG("Explicit - B key released!");
        } else {
            CDEBUG("'%c' key released in window.", key_code)
        }
    }
    return FALSE;
}
