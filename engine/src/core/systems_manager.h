#pragma once

#include "../defines.h"
#include "../memory/linear_allocator.h"

typedef b8 (*PFN_system_initialize)(u64* memory_requirement, void* memory, void* config);
typedef void (*PFN_system_shutdown)(void* state);
typedef b8 (*PFN_system_update)(void* state, f32 delta_time);

typedef struct c_system {
    u64 state_size;
    void* state;
    PFN_system_initialize initialize;
    PFN_system_shutdown shutdown;
    /** @brief A function pointer for the system's update routine, called every frame. Optional. */
    PFN_system_update update;
} c_system;

#define C_SYSTEM_TYPE_MAX_COUNT 512

typedef enum c_system_type {
    C_SYSTEM_TYPE_MEMORY = 0,
    C_SYSTEM_TYPE_CONSOLE,
    C_SYSTEM_TYPE_CVAR,
    C_SYSTEM_TYPE_EVENT,
    C_SYSTEM_TYPE_LOGGING,
    C_SYSTEM_TYPE_INPUT,
    C_SYSTEM_TYPE_PLATFORM,
    C_SYSTEM_TYPE_RESOURCE,
    C_SYSTEM_TYPE_SHADER,
    C_SYSTEM_TYPE_JOB,
    C_SYSTEM_TYPE_TEXTURE,
    C_SYSTEM_TYPE_FONT,
    C_SYSTEM_TYPE_CAMERA,
    C_SYSTEM_TYPE_RENDERER,
    C_SYSTEM_TYPE_RENDER_VIEW,
    C_SYSTEM_TYPE_MATERIAL,
    C_SYSTEM_TYPE_GEOMETRY,

    // NOTE: Anything beyond this is in user space.
    C_SYSTEM_TYPE_KNOWN_MAX = 255,

    // The user-space max
    C_SYSTEM_TYPE_USER_MAX = C_SYSTEM_TYPE_MAX_COUNT,
    // The max, including all user-space types.
    C_SYSTEM_TYPE_MAX = C_SYSTEM_TYPE_USER_MAX
} c_system_type;

typedef struct systems_manager_state {
    linear_allocator systems_allocator;
    c_system systems[C_SYSTEM_TYPE_MAX_COUNT];
} systems_manager_state;

struct application_config;

b8 systems_manager_initialize(systems_manager_state* state, struct application_config* app_config);
b8 systems_manager_post_boot_initialize(systems_manager_state* state, struct application_config* app_config);
void systems_manager_shutdown(systems_manager_state* state);

b8 systems_manager_update(systems_manager_state* state, u32 delta_time);

b8 systems_manager_register(
    systems_manager_state* state,
    u16 type,
    PFN_system_initialize initialize,
    PFN_system_shutdown shutdown,
    PFN_system_update update,
    void* config);
