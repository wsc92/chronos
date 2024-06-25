#include "loader_utils.h"

#include "../../core/cmemory.h"
#include "../../core/logger.h"
#include "../../core/cstring.h"

b8 resource_unload(struct resource_loader* self, resource* resource, memory_tag tag) {
    if (!self || !resource) {
        CWARN("resource_unload called with nullptr for self or resource.");
        return false;
    }

    if (resource->full_path) {
        u32 path_length = string_length(resource->full_path);
        if (path_length) {
            cfree(resource->full_path, sizeof(char) * path_length + 1, MEMORY_TAG_STRING);
        }
    }

    if (resource->data) {
        cfree(resource->data, resource->data_size, tag);
        resource->data = 0;
        resource->data_size = 0;
        resource->loader_id = INVALID_ID;
    }

    return true;
}
