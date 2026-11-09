#include <primitivecore/spatial/indexing/grids/pc_voxel_index_3d_u32.h>

#include <stddef.h>

bool rm_voxel_index_3d_u32(uint32_t width, uint32_t height, uint32_t depth,
                           uint32_t x, uint32_t y, uint32_t z,
                           uint32_t *index)
{
    uint64_t plane;
    uint64_t capacity_limit = (uint64_t)UINT32_MAX + UINT64_C(1);
    uint64_t value;
    if (index == NULL || width == 0u || height == 0u || depth == 0u ||
        x >= width || y >= height || z >= depth) {
        return false;
    }
    plane = (uint64_t)width * (uint64_t)height;
    if (plane > capacity_limit || (uint64_t)depth > capacity_limit / plane) {
        return false;
    }
    value = (uint64_t)z * plane + (uint64_t)y * (uint64_t)width + (uint64_t)x;
    *index = (uint32_t)value;
    return true;
}
