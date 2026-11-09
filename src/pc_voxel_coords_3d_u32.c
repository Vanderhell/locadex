#include <primitivecore/spatial/indexing/grids/pc_voxel_coords_3d_u32.h>

#include <stddef.h>

bool rm_voxel_coords_3d_u32(uint32_t width, uint32_t height, uint32_t depth,
                           uint32_t index, uint32_t *x, uint32_t *y,
                           uint32_t *z)
{
    uint64_t plane;
    uint64_t capacity_limit = (uint64_t)UINT32_MAX + UINT64_C(1);
    uint64_t remainder;
    uint32_t result_x, result_y, result_z;
    if (width == 0u || height == 0u || depth == 0u ||
        x == NULL || y == NULL || z == NULL || x == y || x == z || y == z) {
        return false;
    }
    plane = (uint64_t)width * (uint64_t)height;
    if (plane > capacity_limit || (uint64_t)depth > capacity_limit / plane) {
        return false;
    }
    if ((uint64_t)index >= plane * (uint64_t)depth) {
        return false;
    }
    result_z = (uint32_t)((uint64_t)index / plane);
    remainder = (uint64_t)index - (uint64_t)result_z * plane;
    result_y = (uint32_t)(remainder / (uint64_t)width);
    result_x = (uint32_t)(remainder - (uint64_t)result_y * width);
    *x = result_x;
    *y = result_y;
    *z = result_z;
    return true;
}
