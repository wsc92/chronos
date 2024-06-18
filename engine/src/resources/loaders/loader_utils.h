#pragma once

#include "../../defines.h"
#include "../../core/cmemory.h"
#include "../resource_types.h"

struct resource_loader;

b8 resource_unload(struct resource_loader* self, resource* resource, memory_tag tag);
