#pragma once

#include "../defines.h"

// Disable assertions by commenting out the below line.
#define CASSERTIONS_ENABLED

#ifdef CASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

CAPI void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

#define CASSERT(expr)                                                   \
    {                                                                   \
        if (expr) {                                                     \
        }else {                                                         \
            report_assertion_failure(#expr, "", __FILE__, __LINE__);    \
            debugBreak();                                               \
        }                                                               \
    }                          

#define CASSERT_MSG(expr, message)                                       \
    {                                                                    \
        if (expr) {                                                      \
        }else {                                                          \
            report_assertion_failure(#expr, message, __FILE__, __LINE__);\
            debugBreak();                                                \
        }                                                                \
    }                          

#ifdef _DEBUG
#define CASSERT_DEBUG(expr)                                              \
    {                                                                    \
        if (expr) {                                                      \
        }else {                                                          \
            report_assertion_failure(#expr, "", __FILE__, __LINE__);     \
            debugBreak();                                                \
        }                                                                \
    }  
#else 
#define CASSERT_DEBUG(expr) // DOES nothing
#endif

#else
#define CASSERT(expr) //does nothing
#define CASSERT_MSG(expr) //does nothing
#define CASSERTDEBU(expr) //does nothing
#endif
