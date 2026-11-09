#include "../include/pc_voxel_coords_3d_u32.h"
#include "../../0511_rm_voxel_index_3d_u32/implementation/pc_voxel_index_3d_u32.h"

#include <assert.h>
#include <stdint.h>

int main(void)
{
    uint32_t x = 11u, y = 22u, z = 33u;
    uint32_t w, h, d;
    uint32_t state = UINT32_C(512);
    unsigned int i;
    assert(pc_voxel_coords_3d_u32(1u, 1u, 1u, 0u, &x, &y, &z));
    assert(x == 0u && y == 0u && z == 0u);
    assert(pc_voxel_coords_3d_u32(65536u, 65536u, 1u,
                                 UINT32_MAX, &x, &y, &z));
    assert(x == 65535u && y == 65535u && z == 0u);
    x = 11u; y = 22u; z = 33u;
    assert(!pc_voxel_coords_3d_u32(2u, 3u, 4u, 24u, &x, &y, &z));
    assert(!pc_voxel_coords_3d_u32(65537u, 65536u, 1u, 0u, &x, &y, &z));
    assert(!pc_voxel_coords_3d_u32(0u, 1u, 1u, 0u, &x, &y, &z));
    assert(!pc_voxel_coords_3d_u32(1u, 1u, 1u, 0u, &x, &x, &z));
    assert(!pc_voxel_coords_3d_u32(1u, 1u, 1u, 0u, &x, &y, &y));
    assert(!pc_voxel_coords_3d_u32(1u, 1u, 1u, 0u, 0, &y, &z));
    assert(x == 11u && y == 22u && z == 33u);

    for (w = 1u; w <= 8u; ++w) {
        for (h = 1u; h <= 8u; ++h) {
            for (d = 1u; d <= 8u; ++d) {
                uint32_t index;
                for (index = 0u; index < w * h * d; ++index) {
                    uint32_t encoded;
                    assert(pc_voxel_coords_3d_u32(w, h, d, index, &x, &y, &z));
                    assert(pc_voxel_index_3d_u32(w, h, d, x, y, z, &encoded));
                    assert(encoded == index);
                }
            }
        }
    }
    for (i = 0u; i < 100000u; ++i) {
        uint32_t index;
        state = state * UINT32_C(1664525) + UINT32_C(1013904223);
        index = state;
        assert(pc_voxel_coords_3d_u32(65536u, 65536u, 1u, index, &x, &y, &z));
        assert(pc_voxel_index_3d_u32(65536u, 65536u, 1u, x, y, z, &state));
        assert(state == index);
    }
    return 0;
}
