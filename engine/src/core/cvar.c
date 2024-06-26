#include "cvar.h"

#include "cmemory.h"
#include "logger.h"
#include "cstring.h"
#include "event.h"

#include "console.h"

typedef struct cvar_int_entry {
    const char* name;
    i32 value;
} cvar_int_entry;

#define CVAR_INT_MAX_COUNT 200

typedef struct cvar_system_state {
    // Integer cvars.
    cvar_int_entry ints[CVAR_INT_MAX_COUNT];
} cvar_system_state;

static cvar_system_state* state_ptr;

void cvar_register_console_commands();

b8 cvar_initialize(u64* memory_requirement, void* memory, void* config) {
    *memory_requirement = sizeof(cvar_system_state);

    if (!memory) {
        return true;
    }

    state_ptr = memory;

    czero_memory(state_ptr, sizeof(cvar_system_state));

    cvar_register_console_commands();

    return true;
}
void cvar_shutdown(void* state) {
    if (state_ptr) {
        czero_memory(state_ptr, sizeof(cvar_system_state));
    }
}

b8 cvar_create_int(const char* name, i32 value) {
    if (!state_ptr || !name) {
        return false;
    }

    for (u32 i = 0; i < CVAR_INT_MAX_COUNT; ++i) {
        cvar_int_entry* entry = &state_ptr->ints[i];
        if (entry->name && strings_equali(entry->name, name)) {
            CERROR("A int kvar named '%s' already exists.", name);
            return false;
        }
    }

    for (u32 i = 0; i < CVAR_INT_MAX_COUNT; ++i) {
        cvar_int_entry* entry = &state_ptr->ints[i];
        if (!entry->name) {
            entry->name = string_duplicate(name);
            entry->value = value;
            return true;
        }
    }

    CERROR("cvar_create_int could not find a free slot to store an entry in.");
    return false;
}

b8 cvar_get_int(const char* name, i32* out_value) {
    if (!state_ptr || !name) {
        return false;
    }

    for (u32 i = 0; i < CVAR_INT_MAX_COUNT; ++i) {
        cvar_int_entry* entry = &state_ptr->ints[i];
        if (entry->name && strings_equali(name, entry->name)) {
            *out_value = entry->value;
            return true;
        }
    }

    CERROR("cvar_get_int could not find a cvar named '%s'.", name);
    return false;
}

b8 cvar_set_int(const char* name, i32 value) {
    if (!state_ptr || !name) {
        return false;
    }

    for (u32 i = 0; i < CVAR_INT_MAX_COUNT; ++i) {
        cvar_int_entry* entry = &state_ptr->ints[i];
        if (entry->name && strings_equali(name, entry->name)) {
            entry->value = value;
            // TODO: also pass type?
            event_context context = {0};
            string_ncopy(context.data.c, name, 16);
            event_fire(EVENT_CODE_CVAR_CHANGED, 0, context);
            return true;
        }
    }

    CERROR("cvar_set_int could not find a cvar named '%s'.", name);
    return false;
}

void cvar_console_command_create_int(console_command_context context) {
    if (context.argument_count != 2) {
        CERROR("cvar_console_command_create_int requires a context arg count of 2.");
        return;
    }

    const char* name = context.arguments[0].value;
    const char* val_str = context.arguments[1].value;
    i32 value = 0;
    if (!string_to_i32(val_str, &value)) {
        CERROR("Failed to convert argument 1 to i32: '%s'.", val_str);
        return;
    }

    if (!cvar_create_int(name, value)) {
        CERROR("Failed to create int cvar.");
    }
}

void cvar_console_command_print_int(console_command_context context) {
    if (context.argument_count != 1) {
        CERROR("cvar_console_command_print_int requires a context arg count of 1.");
        return;
    }

    const char* name = context.arguments[0].value;
    i32 value = 0;
    if (!cvar_get_int(name, &value)) {
        CERROR("Failed to find cvar called '%s'.", name);
        return;
    }

    char val_str[50] = {0};
    string_format(val_str, "%i", value);

    console_write_line(LOG_LEVEL_INFO, val_str);
}

void cvar_console_command_set_int(console_command_context context) {
    if (context.argument_count != 2) {
        CERROR("cvar_console_command_set_int requires a context arg count of 2.");
        return;
    }

    const char* name = context.arguments[0].value;
    const char* val_str = context.arguments[1].value;
    i32 value = 0;
    if (!string_to_i32(val_str, &value)) {
        CERROR("Failed to convert argument 1 to i32: '%s'.", val_str);
        return;
    }

    if (!cvar_set_int(name, value)) {
        CERROR("Failed to set int cvar called '%s' because it doesn't exist.", name);
    }

    char out_str[500] = {0};
    string_format(out_str, "%s = %i", name, value);
    console_write_line(LOG_LEVEL_INFO, val_str);
}

void cvar_console_command_print_all(console_command_context context) {
    // Int cvars
    for (u32 i = 0; i < CVAR_INT_MAX_COUNT; ++i) {
        cvar_int_entry* entry = &state_ptr->ints[i];
        if (entry->name) {
            char val_str[500] = {0};
            string_format(val_str, "%s = %i", entry->name, entry->value);
            console_write_line(LOG_LEVEL_INFO, val_str);
        }
    }

    // TODO: Other variable types.
}

void cvar_register_console_commands() {
    console_register_command("cvar_create_int", 2, cvar_console_command_create_int);
    console_register_command("cvar_print_int", 1, cvar_console_command_print_int);
    console_register_command("cvar_set_int", 2, cvar_console_command_set_int);
    console_register_command("cvar_print_all", 0, cvar_console_command_print_all);
}
