#include "octree_path_encode_u32.h"
#include <assert.h>
#include <stdint.h>

static uint32_t next_random(uint32_t *s)
{ *s=*s*UINT32_C(1664525)+UINT32_C(1013904223); return *s; }

static uint32_t oracle(uint32_t x,uint32_t y,uint32_t z,uint32_t d)
{
    uint32_t p=0u;
    for (uint32_t i=d;i>0u;--i) {
        uint32_t q=((x>>(i-1u))&1u)|(((y>>(i-1u))&1u)<<1)|(((z>>(i-1u))&1u)<<2);
        p=p*8u+q;
    }
    return p;
}

int main(void)
{
    uint32_t p=77u,seed=UINT32_C(0x1897);
    assert(pc_octree_path_encode_u32(0,0,0,0,&p) && p==0u);
    assert(pc_octree_path_encode_u32(3,2,5,3,&p) && p==UINT32_C(285));
    assert(pc_octree_path_encode_u32(1023u,1023u,1023u,10u,&p) && p==UINT32_C(0x3FFFFFFF));
    for (uint32_t d=0;d<=5u;++d)
        for (uint32_t z=0;z<(1u<<d);++z)
            for (uint32_t y=0;y<(1u<<d);++y)
                for (uint32_t x=0;x<(1u<<d);++x) {
                    assert(pc_octree_path_encode_u32(x,y,z,d,&p));
                    assert(p==oracle(x,y,z,d));
                }
    for (uint32_t i=0;i<100000u;++i) {
        uint32_t d=next_random(&seed)%11u, mask=(1u<<d)-1u;
        uint32_t x=next_random(&seed)&mask,y=next_random(&seed)&mask,z=next_random(&seed)&mask;
        assert(pc_octree_path_encode_u32(x,y,z,d,&p));
        assert(p==oracle(x,y,z,d));
    }
    p=77u;
    assert(!pc_octree_path_encode_u32(0,0,0,11u,&p) && p==77u);
    assert(!pc_octree_path_encode_u32(1024u,0,0,10u,&p) && p==77u);
    assert(!pc_octree_path_encode_u32(0,0,0,0,NULL));
    return 0;
}
