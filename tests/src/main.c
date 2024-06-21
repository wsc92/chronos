#include "test_manager.h"

#include "memory/linear_allocator_tests.h"
#include "memory/dynamic_allocator_tests.h"
#include "containers/hashtable_tests.h"
#include "containers/freelist_tests.h"

#include "../../engine/src/core/logger.h"

int main() {
    // Always initalize the test manager first.
    test_manager_init();

    // TODO: add test registrations here.
    linear_allocator_register_tests();
    hashtable_register_tests();
    freelist_register_tests();
    dynamic_allocator_register_tests();

    CDEBUG("Starting tests...");

    // Execute tests
    test_manager_run_tests();

    return 0;
}
