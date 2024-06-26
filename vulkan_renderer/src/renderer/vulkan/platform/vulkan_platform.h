#pragma once

#include "../../../../../engine/src/defines.h"

struct platform_state;
struct vulkan_context;

/**
 * @brief Creates and assigns a surface to the given context.
 * 
 * @param context A pointer to the Vulkan context.
 * @return True on success; otherwise false.
 */
b8 platform_create_vulkan_surface(struct vulkan_context* context);

/**
 * @brief Appends the names of required extensions for this platform to
 * the names_darray, which should be created and passed in.
 * @param names_darray A pointer to the array names of required extension names. Must be a darray
 * as this function adds names to the array.
 */
void platform_get_required_extension_names(const char*** names_darray);
