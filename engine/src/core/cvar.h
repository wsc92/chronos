#pragma once

#include "../defines.h"

b8 cvar_initialize(u64* memory_requirement, void* memory);
void cvar_shutdown(void* state);

CAPI b8 cvar_create_int(const char* name, i32 value);
CAPI b8 cvar_get_int(const char* name, i32* out_value);
CAPI b8 cvar_set_int(const char* name, i32 value);
