#include "game.h"

#include "../../engine/src/core/logger.h"
#include "../../engine/src/core/input.h"
#include "../../engine/src/core/cmemory.h"

b8 game_initialize(game* game_inst) {
    CDEBUG("game_initialize() called!");
    return true;
}

b8 game_update(game* game_inst, f32 delta_time) {

    static u64 alloc_count = 0;
    u64 prev_alloc_count = alloc_count;
    alloc_count = get_memory_alloc_count();
    if (input_is_key_up('M') && input_was_key_down('M')) {
        CDEBUG("Allocations: %llu (%llu this frame", alloc_count, alloc_count - prev_alloc_count);
    }

    return true;
}

b8 game_render(game* game_inst, f32 delta_time) {
    return true;
}

void game_on_resize(game* game_inst, u32 width, u32 height) {

}
