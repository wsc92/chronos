#include "stack.h"
#include "../core/logger.h"
#include "../core/cmemory.h"

static void stack_ensure_allocated(stack* s, u32 count) {
    if (s->allocated < s->element_size * count) {
        void* temp = callocate(count * s->element_size, MEMORY_TAG_ARRAY);
        if (s->memory) {
            ccopy_memory(temp, s->memory, s->allocated);
            cfree(s->memory, s->allocated, MEMORY_TAG_ARRAY);
        }
        s->memory = temp;
        s->allocated = count * s->element_size;
    }
}

b8 stack_create(stack* out_stack, u32 element_size) {
    if (!out_stack) {
        CERROR("stack_create requires a pointer to a valid stack.");
        return false;
    }

    czero_memory(out_stack, sizeof(stack));
    out_stack->element_size = element_size;
    out_stack->element_count = 0;
    stack_ensure_allocated(out_stack, 1);
    return true;
}

void stack_destroy(stack* s) {
    if (s) {
        if (s->memory) {
            cfree(s->memory, s->allocated, MEMORY_TAG_ARRAY);
        }
        czero_memory(s, sizeof(stack));
    }
}

b8 stack_push(stack* s, void* element_data) {
    if (!s) {
        CERROR("stack_push requires a pointer to a valid stack.");
        return false;
    }

    stack_ensure_allocated(s, s->element_count + 1);
    ccopy_memory((void*)((u64)s->memory + (s->element_count * s->element_size)), element_data, s->element_size);
    s->element_count++;
    return true;
}

b8 stack_pop(stack* s, void* out_element_data) {
    if (!s || out_element_data) {
        CERROR("stack_pop requires a pointer to a valid stack and to hold element data output.");
        return false;
    }

    if (s->element_count < 1) {
        CWARN("Cannot pop from an empty stack.");
        return false;
    }

    ccopy_memory(out_element_data, (void*)((u64)s->memory + ((s->element_count - 1) * s->element_size)), s->element_size);

    s->element_count--;

    return true;
}
