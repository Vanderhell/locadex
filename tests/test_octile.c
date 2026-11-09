#include "../include/pc_grid_octile_distance_q.h"

#include <assert.h>
#include <stdint.h>

static uint32_t next_random(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static uint64_t reference(uint32_t ax,uint32_t ay,uint32_t bx,uint32_t by)
{
    uint32_t dx=ax>=bx?ax-bx:bx-ax,dy=ay>=by?ay-by:by-ay;
    uint32_t major=dx>=dy?dx:dy,minor=dx>=dy?dy:dx;
    uint64_t product=(uint64_t)minor*UINT64_C(1779033704);
    uint64_t q=product>>16,rem=product&UINT64_C(0xFFFF);
    if(rem>UINT64_C(0x8000)||(rem==UINT64_C(0x8000)&&(q&1u)!=0u))++q;
    return (uint64_t)major*UINT64_C(65536)+q;
}

int main(void)
{
    uint32_t seed=UINT32_C(507);
    unsigned int i;
    assert(pc_grid_octile_distance_q(0u,0u,0u,0u)==0u);
    assert(pc_grid_octile_distance_q(0u,0u,3u,0u)==UINT64_C(196608));
    assert(pc_grid_octile_distance_q(0u,0u,1u,1u)==UINT64_C(92682));
    assert(pc_grid_octile_distance_q(0u,0u,UINT32_MAX,UINT32_MAX)<UINT64_MAX);
    for(i=0u;i<100000u;++i){
        uint32_t ax=next_random(&seed),ay=next_random(&seed);
        uint32_t bx=next_random(&seed),by=next_random(&seed);
        uint64_t d=pc_grid_octile_distance_q(ax,ay,bx,by);
        assert(d==reference(ax,ay,bx,by));
        assert(d==pc_grid_octile_distance_q(bx,by,ax,ay));
    }
    return 0;
}
