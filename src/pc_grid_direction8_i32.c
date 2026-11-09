#include "pc_grid_direction8_i32.h"
#include <stddef.h>

static uint32_t magnitude(int32_t value)
{
    const uint32_t bits = (uint32_t)value;
    return value < 0 ? 0u - bits : bits;
}

bool pc_grid_direction8_i32(int32_t dx, int32_t dy, uint8_t *out)
{
    const uint32_t ax = magnitude(dx), ay = magnitude(dy);
    const bool x_major = ax >= ay;
    const uint32_t major = x_major ? ax : ay;
    const uint32_t minor = x_major ? ay : ax;
    bool diagonal = false;
    uint8_t direction;

    if (out == NULL || (ax == 0u && ay == 0u)) return false;
    if (minor != 0u) {
        const uint32_t gap = major - minor;
        diagonal = (uint64_t)gap * gap <= UINT64_C(2) * minor * minor;
    }
    if (diagonal) {
        if ((dx < 0) == (dy < 0)) direction = dx < 0 ? 5u : 1u;
        else direction = dx < 0 ? 3u : 7u;
    } else if (x_major) {
        direction = dx < 0 ? 4u : 0u;
    } else {
        direction = dy < 0 ? 6u : 2u;
    }
    *out = direction;
    return true;
}