#include "pc_morton3_decode_u32.h"
#include "pc_morton3_encode_u32.h"

#include <assert.h>
#include <stdint.h>

int main(void)
{
    uint32_t x = 11u, y = 22u, z = 33u;
    uint32_t a, b, c;
    uint32_t state = UINT32_C(514);
    unsigned int i;
    assert(pc_morton3_decode_u32(0u, &x, &y, &z));
    assert(x == 0u && y == 0u && z == 0u);
    assert(pc_morton3_decode_u32(UINT32_C(0x3FFFFFFF), &x, &y, &z));
    assert(x == 1023u && y == 1023u && z == 1023u);
    x = 11u; y = 22u; z = 33u;
    assert(!pc_morton3_decode_u32(UINT32_C(0x40000000), &x, &y, &z));
    assert(!pc_morton3_decode_u32(UINT32_MAX, &x, &y, &z));
    assert(!pc_morton3_decode_u32(0u, &x, &x, &z));
    assert(!pc_morton3_decode_u32(0u, &x, &y, &y));
    assert(!pc_morton3_decode_u32(0u, 0, &y, &z));
    assert(x == 11u && y == 22u && z == 33u);

    for (a = 0u; a < 32u; ++a) {
        for (b = 0u; b < 32u; ++b) {
            for (c = 0u; c < 32u; ++c) {
                uint32_t code;
                assert(pc_morton3_encode_u32(a, b, c, &code));
                assert(pc_morton3_decode_u32(code, &x, &y, &z));
                assert(x == a && y == b && z == c);
            }
        }
    }
    for (i = 0u; i < 100000u; ++i) {
        uint32_t code;
        state = state * UINT32_C(1664525) + UINT32_C(1013904223);
        code = state & UINT32_C(0x3FFFFFFF);
        assert(pc_morton3_decode_u32(code, &x, &y, &z));
        assert(pc_morton3_encode_u32(x, y, z, &a));
        assert(a == code);
    }
    return 0;
}