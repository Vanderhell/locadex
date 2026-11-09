#include "../include/pc_hilbert2_coords_u32.h"
#include "../../0515_rm_hilbert2_index_u32/implementation/pc_hilbert2_index_u32.h"

#include <assert.h>
#include <stdint.h>

int main(void)
{
    uint32_t x = 11u, y = 22u;
    uint32_t index;
    uint32_t state = UINT32_C(516);
    uint32_t prev_x = 0u, prev_y = 0u;
    unsigned int i;
    assert(pc_hilbert2_coords_u32(0u, &x, &y) && x == 0u && y == 0u);
    assert(pc_hilbert2_coords_u32(1u, &x, &y) && x == 1u && y == 0u);
    assert(pc_hilbert2_coords_u32(2u, &x, &y) && x == 1u && y == 1u);
    assert(pc_hilbert2_coords_u32(3u, &x, &y) && x == 0u && y == 1u);
    assert(pc_hilbert2_coords_u32(UINT32_MAX, &x, &y));
    assert(x == 65535u && y == 0u);
    x = 11u; y = 22u;
    assert(!pc_hilbert2_coords_u32(0u, &x, &x) && x == 11u && y == 22u);
    assert(!pc_hilbert2_coords_u32(0u, NULL, &y) && x == 11u && y == 22u);

    for (index = 0u; index < 100000u; ++index) {
        uint32_t encoded;
        assert(pc_hilbert2_coords_u32(index, &x, &y));
        assert(pc_hilbert2_index_u32(x, y, &encoded));
        assert(encoded == index);
        if (index != 0u) {
            uint32_t distance = (x >= prev_x ? x - prev_x : prev_x - x) +
                                (y >= prev_y ? y - prev_y : prev_y - y);
            assert(distance == 1u);
        }
        prev_x = x; prev_y = y;
    }
    for (i = 0u; i < 100000u; ++i) {
        uint32_t encoded;
        state = state * UINT32_C(1664525) + UINT32_C(1013904223);
        assert(pc_hilbert2_coords_u32(state, &x, &y));
        assert(x < 65536u && y < 65536u);
        assert(pc_hilbert2_index_u32(x, y, &encoded) && encoded == state);
    }
    return 0;
}
