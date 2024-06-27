#pragma once

#include "../../engine/src/renderer/renderer_types.inl"

/**
 * @brief Creates a new renderer plugin of the given type.
 * 
 * @param out_renderer_backend A pointer to hold the newly-created renderer plugin.
 * @return True if successful; otherwise false.
 */
CAPI b8 vulkan_renderer_plugin_create(renderer_plugin* out_plugin);

/**
 * @brief Destroys the given renderer backend.
 * 
 * @param renderer_backend A pointer to the plugin to be destroyed.
 */
CAPI void vulkan_renderer_plugin_destroy(renderer_plugin* plugin);