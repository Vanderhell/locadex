#include "octree_path_decode_u32.h"
#include <assert.h>
#include <stdint.h>

static uint32_t next_random(uint32_t *s)
{ *s=*s*UINT32_C(1664525)+UINT32_C(1013904223); return *s; }

static void oracle(uint32_t p,uint32_t d,uint32_t *x,uint32_t *y,uint32_t *z)
{
    *x=0u; *y=0u; *z=0u;
    for (uint32_t i=d;i>0u;--i) {
        uint32_t q=(p>>(3u*(i-1u)))&7u;
        *x=*x*2u+(q&1u); *y=*y*2u+((q>>1)&1u); *z=*z*2u+((q>>2)&1u);
    }
}

int main(void)
{
    uint32_t x=77u,y=88u,z=99u,seed=UINT32_C(0x1898);
    assert(pc_octree_path_decode_u32(0,0,&x,&y,&z) && x==0 && y==0 && z==0);
    assert(pc_octree_path_decode_u32(285u,3,&x,&y,&z) && x==3 && y==2 && z==5);
    assert(pc_octree_path_decode_u32(0x3FFFFFFFu,10,&x,&y,&z) && x==1023 && y==1023 && z==1023);
    for (uint32_t d=0;d<=5u;++d)
        for (uint32_t p=0;p<(1u<<(3u*d));++p) {
            uint32_t ex,ey,ez; oracle(p,d,&ex,&ey,&ez);
            assert(pc_octree_path_decode_u32(p,d,&x,&y,&z));
            assert(x==ex && y==ey && z==ez);
        }
    for (uint32_t i=0;i<100000u;++i) {
        uint32_t d=next_random(&seed)%11u;
        uint32_t p=next_random(&seed)&((1u<<(3u*d))-1u),ex,ey,ez;
        oracle(p,d,&ex,&ey,&ez);
        assert(pc_octree_path_decode_u32(p,d,&x,&y,&z));
        assert(x==ex && y==ey && z==ez);
    }
    x=77u;y=88u;z=99u;
    assert(!pc_octree_path_decode_u32(8u,1u,&x,&y,&z) && x==77u && y==88u && z==99u);
    assert(!pc_octree_path_decode_u32(0u,11u,&x,&y,&z) && x==77u && y==88u && z==99u);
    assert(!pc_octree_path_decode_u32(0u,0u,NULL,&y,&z) && y==88u && z==99u);
    assert(!pc_octree_path_decode_u32(0u,0u,&x,&x,&z) && x==77u && z==99u);
    return 0;
}
