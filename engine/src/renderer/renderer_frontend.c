#include "renderer_frontend.h"
#include "renderer_backend.h"

#include "../core/logger.h"
#include "../core/cmemory.h"

// Backend render context.
static renderer_backend* backend = 0;

b8 renderer_initialize(const char* application_name, struct platform_state* plat_state) {
    backend = kallocate(sizeof(renderer_backend), MEMORY_TAG_RENDERER);

    // TODO: make this configurable.
    renderer_backend_create(RENDERER_BACKEND_TYPE_VULKAN, plat_state, backend);
    backend->frame_number = 0;

    if (!backend->initialize(backend, application_name, plat_state)) {
        CFATAL("Renderer backend failed to initialize. Shutting down.");
        return FALSE;
    }

    return TRUE;
}

void renderer_shutdown() {
    backend->shutdown(backend);
    kfree(backend, sizeof(renderer_backend), MEMORY_TAG_RENDERER);
}

b8 renderer_begin_frame(f32 delta_time) {
    return backend->begin_frame(backend, delta_time);
}

b8 renderer_end_frame(f32 delta_time) {
    b8 result = backend->end_frame(backend, delta_time);
    backend->frame_number++;
    return result;
}

b8 renderer_draw_frame(render_packet* packet) {
    // If the begin frame returned successfully, mid-frame operations may continue.
    if (renderer_begin_frame(packet->delta_time)) {

        // End the frame. If this fails, it is likely unrecoverable.
        b8 result = renderer_end_frame(packet->delta_time);

        if (!result) {
            CERROR("renderer_end_frame failed. Shutting Down...");
            return FALSE;
        }

    }
    return TRUE;
}



