#pragma once

#include "../defines.h"

/**
 * Represents a process thread in the system to be used for work.
 * Generally should not be created directly in user code.
 * This calls to the platform-specific thread implementation.
 */
typedef struct cthread {
    void *internal_data;
    u64 thread_id;
} cthread;

// A function pointer to be invoked when the thread starts.
typedef u32 (*pfn_thread_start)(void *);

/**
 * Creates a new thread, immediately calling the function pointed to.
 * @param start_function_ptr The pointer to the function to be invoked immediately. Required.
 * @param params A pointer to any data to be passed to the start_function_ptr. Optional. Pass 0/NULL if not used.
 * @param auto_detach Indicates if the thread should immediately release its resources when the work is complete. If true, out_thread is not set.
 * @param out_thread A pointer to hold the created thread, if auto_detach is false.
 * @returns true if successfully created; otherwise false.
 */
b8 cthread_create(pfn_thread_start start_function_ptr, void *params, b8 auto_detach, cthread *out_thread);

/**
 * Destroys the given thread.
 */
void cthread_destroy(cthread *thread);

/**
 * Detaches the thread, automatically releasing resources when work is complete.
 */
void cthread_detach(cthread *thread);

/**
 * Cancels work on the thread, if possible, and releases resources when possible.
 */
void cthread_cancel(cthread *thread);

/**
 * Indicates if the thread is currently active.
 * @returns True if active; otherwise false.
 */
b8 cthread_is_active(cthread* thread);

/**
 * Sleeps on the given thread for a given number of milliseconds. Should be called from the
 * thread requiring the sleep.
 */
void cthread_sleep(cthread* thread, u64 ms);

u64 get_thread_id();
