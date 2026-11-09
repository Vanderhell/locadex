#include "roundmath/tile_neighbor6_3d_u32.h"

#include <assert.h>
#include <stdint.h>

static uint32_t next_random(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static void check(uint32_t w, uint32_t h, uint32_t d,
                  uint32_t x, uint32_t y, uint32_t z)
{
    pc_tile_neighbors6_3d_u32 n;
    uint64_t base = ((uint64_t)z * h + y) * w + x;
    uint32_t exp[6] = {
        x ? (uint32_t)(base - 1u) : UINT32_MAX,
        x + 1u < w ? (uint32_t)(base + 1u) : UINT32_MAX,
        y ? (uint32_t)(base - w) : UINT32_MAX,
        y + 1u < h ? (uint32_t)(base + w) : UINT32_MAX,
        z ? (uint32_t)(base - (uint64_t)w * h) : UINT32_MAX,
        z + 1u < d ? (uint32_t)(base + (uint64_t)w * h) : UINT32_MAX
    };
    uint8_t mask = 0u;
    assert(pc_tile_neighbor6_3d_u32(w,h,d,x,y,z,&n));
    for (unsigned int i=0; i<6; ++i) {
        assert(n.index[i] == exp[i]);
        if (exp[i] != UINT32_MAX) mask = (uint8_t)(mask | (uint8_t)(1u << i));
    }
    assert(n.valid_mask == mask);
}

int main(void)
{
    uint32_t seed = UINT32_C(0xA1776E);
    pc_tile_neighbors6_3d_u32 n = { UINT8_C(0xA5), {1u,2u,3u,4u,5u,6u} };
    pc_tile_neighbors6_3d_u32 before = n;
    for (uint32_t w=1; w<=8; ++w)
        for (uint32_t h=1; h<=7; ++h)
            for (uint32_t d=1; d<=6; ++d)
                for (uint32_t z=0; z<d; ++z)
                    for (uint32_t y=0; y<h; ++y)
                        for (uint32_t x=0; x<w; ++x) check(w,h,d,x,y,z);
    for (uint32_t i=0; i<100000u; ++i) {
        uint32_t w=1u+next_random(&seed)%1000u;
        uint32_t h=1u+next_random(&seed)%1000u;
        uint32_t d=1u+next_random(&seed)%100u;
        if ((uint64_t)w*h*d > (uint64_t)UINT32_MAX+1u) d=1u;
        check(w,h,d,next_random(&seed)%w,next_random(&seed)%h,next_random(&seed)%d);
    }
    assert(pc_tile_neighbor6_3d_u32(1,1,1,0,0,0,&n) && n.valid_mask==0u);
    assert(pc_tile_neighbor6_3d_u32(65536u,65536u,1u,65535u,65535u,0u,&n));
    assert(n.index[0]==UINT32_MAX-1u && n.index[2]==UINT32_MAX-65536u);
    n=before;
    assert(!pc_tile_neighbor6_3d_u32(0,1,1,0,0,0,&n));
    assert(n.valid_mask==before.valid_mask && n.index[5]==before.index[5]);
    assert(!pc_tile_neighbor6_3d_u32(65537u,65536u,1u,0,0,0,&n));
    assert(!pc_tile_neighbor6_3d_u32(1,1,1,1,0,0,&n));
    assert(!pc_tile_neighbor6_3d_u32(1,1,1,0,0,0,NULL));
    return 0;
}