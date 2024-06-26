#include "game_commands.h"
#include "../../engine/src/core/console.h"

#include "../../engine/src/core/event.h"

void game_command_exit(console_command_context context) {
    CDEBUG("game exit called!");
    event_fire(EVENT_CODE_APPLICATION_QUIT, 0, (event_context){});
}

void game_setup_commands(game* game_inst) {
    console_register_command("exit", 0, game_command_exit);
    console_register_command("quit", 0, game_command_exit);
}