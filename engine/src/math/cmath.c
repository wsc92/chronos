#include "cmath.h"
#include "../platform/platform.h"

#include <math.h>
#include <stdlib.h>

static b8 rand_seeded = FALSE;

/**
 * Note that these are here in order to prevent having to import the
 * entire <math.h> everywhere.
 */
f32 csin(f32 x) {
    return sinf(x);
}

f32 ccos(f32 x) {
    return cosf(x);
}

f32 ctan(f32 x) {
    return tanf(x);
}

f32 cacos(f32 x) {
    return acosf(x);
}

f32 csqrt(f32 x) {
    return sqrtf(x);
}

f32 cabs(f32 x) {
    return fabsf(x);
}

i32 crandom() {
    if (!rand_seeded) {
        srand((u32)platform_get_absolute_time());
        rand_seeded = TRUE;
    }
    return rand();
}

i32 crandom_in_range(i32 min, i32 max) {
    if (!rand_seeded) {
        srand((u32)platform_get_absolute_time());
        rand_seeded = TRUE;
    }
    return (rand() % (max - min + 1)) + min;
}

f32 fcrandom() {
    return (float)crandom() / (f32)RAND_MAX;
}

f32 fcrandom_in_range(f32 min, f32 max) {
    return min + ((float)crandom() / ((f32)RAND_MAX / (max - min)));
}
