#include "pc_morton3_encode_u32.h"

#include <stddef.h>

static uint32_t spread3(uint32_t value)
{
    value &= UINT32_C(0x000003FF);
    value = (value | (value << 16)) & UINT32_C(0x030000FF);
    value = (value | (value << 8)) & UINT32_C(0x0300F00F);
    value = (value | (value << 4)) & UINT32_C(0x030C30C3);
    value = (value | (value << 2)) & UINT32_C(0x09249249);
    return value;
}

bool rm_morton3_encode_u32(uint32_t x, uint32_t y, uint32_t z,
                           uint32_t *code)
{
    uint32_t result;
    if (code == NULL || x > UINT32_C(1023) || y > UINT32_C(1023) ||
        z > UINT32_C(1023)) {
        return false;
    }
    result = spread3(x) | (spread3(y) << 1) | (spread3(z) << 2);
    *code = result;
    return true;
}