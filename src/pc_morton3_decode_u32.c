#include <primitivecore/spatial/indexing/morton/pc_morton3_decode_u32.h>

#include <stddef.h>

static uint32_t compact3(uint32_t value)
{
    value &= UINT32_C(0x09249249);
    value = (value ^ (value >> 2)) & UINT32_C(0x030C30C3);
    value = (value ^ (value >> 4)) & UINT32_C(0x0300F00F);
    value = (value ^ (value >> 8)) & UINT32_C(0x030000FF);
    value = (value ^ (value >> 16)) & UINT32_C(0x000003FF);
    return value;
}

bool rm_morton3_decode_u32(uint32_t code, uint32_t *x, uint32_t *y,
                           uint32_t *z)
{
    uint32_t result_x, result_y, result_z;
    if (code > UINT32_C(0x3FFFFFFF) || x == NULL || y == NULL || z == NULL ||
        x == y || x == z || y == z) {
        return false;
    }
    result_x = compact3(code);
    result_y = compact3(code >> 1);
    result_z = compact3(code >> 2);
    *x = result_x;
    *y = result_y;
    *z = result_z;
    return true;
}
