#include "../include/pc_grid_spiral_coords_i32.h"
#include "../../0509_rm_grid_spiral_index_u32/implementation/pc_grid_spiral_index_u32.h"

#include <assert.h>
#include <stdint.h>

int main(void)
{
    int32_t x = 123, y = 456;
    uint32_t radius;
    uint32_t state = UINT32_C(510);
    unsigned int i;
    assert(pc_grid_spiral_coords_i32(0u, &x, &y) && x == 0 && y == 0);

    for (radius = 0u; radius <= 512u; ++radius) {
        uint64_t first = radius == 0u ? 0u :
                         (UINT64_C(2) * radius - 1u) *
                         (UINT64_C(2) * radius - 1u);
        uint64_t count = radius == 0u ? 1u : UINT64_C(8) * radius;
        uint64_t n;
        for (n = first; n < first + count; ++n) {
            uint32_t encoded;
            assert(pc_grid_spiral_coords_i32((uint32_t)n, &x, &y));
            assert(pc_grid_spiral_index_u32(x, y, &encoded));
            assert(encoded == (uint32_t)n);
        }
    }

    for (i = 0u; i < 100000u; ++i) {
        uint32_t index;
        state = state * UINT32_C(1664525) + UINT32_C(1013904223);
        index = state;
        assert(pc_grid_spiral_coords_i32(index, &x, &y));
        assert(pc_grid_spiral_index_u32(x, y, &index));
        assert(index == state);
    }

    x = 123;
    y = 456;
    assert(!pc_grid_spiral_coords_i32(UINT32_MAX, &x, &x));
    assert(x == 123 && y == 456);
    assert(!pc_grid_spiral_coords_i32(1u, 0, &y));
    assert(!pc_grid_spiral_coords_i32(1u, &x, 0));
    assert(x == 123 && y == 456);
    return 0;
}
