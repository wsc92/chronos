#pragma once

#include "core/engine.h"
#include "core/logger.h"
#include "application_types.h"

/** @brief Externally-defined function to create a application, provided by the consumer
 * of this library.
 * @param out_app A pointer which holds the created application object as provided by the consumer.
 * @returns True on successful creation; otherwise false.
 */
extern b8 create_application(application* out_app);

/**
 * @brief The main entry point of the application.
 * @returns 0 on successful execution; nonzero on error.
 */
int main(void) {
    // Request the application instance from the application.
    application app_inst;
    if (!create_application(&app_inst)) {
        CFATAL("Could not create application!");
        return -1;
    }

    // Ensure the function pointers exist.
    if (!app_inst.render || !app_inst.update || !app_inst.initialize || !app_inst.on_resize) {
        CFATAL("The application's function pointers must be assigned!");
        return -2;
    }

    // Initialization.
    if (!engine_create(&app_inst)) {
        CFATAL("Application failed to create!.");
        return 1;
    }

    // Begin the engine loop.
    if (!engine_run()) {
        CINFO("Application did not shutdown gracefully.");
        return 2;
    }

    return 0;
}
