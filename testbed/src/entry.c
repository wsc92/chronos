#include "game.h"

#include "../../engine/src/entry.h"
#include "../../engine/src/core/cmemory.h"

// Define the function to create a game
b8 create_game(game* out_game) {

    //application configuration
    out_game->app_config.start_pos_x = 100;
    out_game->app_config.start_pos_y = 100;
    out_game->app_config.start_width = 1280;
    out_game->app_config.start_height = 720;
    out_game->app_config.name = "Chronos Engine Testbed";
    out_game->update = game_update;
    out_game->render = game_render;
    out_game->initialize = game_initialize;
    out_game->on_resize = game_on_resize;

    // create the game state.
    out_game->state_memory_requirement = sizeof(game_state);
    out_game->state = 0;

    out_game->application_state = 0;

    return true;
}
