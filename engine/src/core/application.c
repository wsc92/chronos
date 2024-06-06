#include "application.h"
#include "../game_types.h"

#include "../core/logger.h"
#include "../platform/platform.h"
#include "../core/cmemory.h"

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

b8 application_create(game* game_inst) {
    if (initialized) {
        CERROR("application_create called more than once.");
        return FALSE;
    }

    app_state.game_inst = game_inst;

    // initialize subsystems.
    initialize_logging();

    // TODO: Remove this later
    CFATAL("A test message: %f", 3.14f);
    CERROR("A test message: %f", 3.14f);
    CWARN("A test message: %f", 3.14f);
    CINFO("A test message: %f", 3.14f);
    CDEBUG("A test message: %f", 3.14f);
    CTRACE("A test message: %f", 3.14f);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

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
        }
    }

    app_state.is_running = FALSE;

    platform_shutdown(&app_state.platform);

    return TRUE;
}
