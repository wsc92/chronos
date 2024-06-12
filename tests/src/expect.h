#include "../../engine/src/core/logger.h"
#include "../../engine/src/math/cmath.h"

/**
 * @brief Expects expected to be equal to actual.
 */
#define expect_should_be(expected, actual)                                                              \
    if (actual != expected) {                                                                           \
        CERROR("--> Expected %lld, but got: %lld. File: %s:%d.", expected, actual, __FILE__, __LINE__); \
        return false;                                                                                   \
    }

/**
 * @brief Expects expected to NOT be equal to actual.
 */
#define expect_should_not_be(expected, actual)                                                                   \
    if (actual == expected) {                                                                                    \
        CERROR("--> Expected %d != %d, but they are equal. File: %s:%d.", expected, actual, __FILE__, __LINE__); \
        return false;                                                                                            \
    }

/**
 * @brief Expects expected to be actual given a tolerance of K_FLOAT_EPSILON.
 */
#define expect_float_to_be(expected, actual)                                                        \
    if (kabs(expected - actual) > 0.001f) {                                                         \
        CERROR("--> Expected %f, but got: %f. File: %s:%d.", expected, actual, __FILE__, __LINE__); \
        return false;                                                                               \
    }

/**
 * @brief Expects actual to be true.
 */
#define expect_to_be_true(actual)                                                      \
    if (actual != true) {                                                              \
        CERROR("--> Expected true, but got: false. File: %s:%d.", __FILE__, __LINE__); \
        return false;                                                                  \
    }

/**
 * @brief Expects actual to be false.
 */
#define expect_to_be_false(actual)                                                     \
    if (actual != false) {                                                             \
        CERROR("--> Expected false, but got: true. File: %s:%d.", __FILE__, __LINE__); \
        return false;                                                                  \
    }
