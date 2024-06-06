#pragma once

#include "../defines.h"

struct game;

// Application Configuration
typedef struct application_config {
    //Window starting postion x axis, if applicable.
    i16 start_pos_x;

    // Window starting position y axis, if applicable.
    i16 start_pos_y;

    //Window starting width, if applicable
    i16 start_width;

    // Window starting height, if applicable
    i16 start_height;

    // The Application name used in windowing, of applicable
    char* name;
} application_config;

CAPI b8 application_create(struct game* game_inst);

CAPI b8 application_run();
