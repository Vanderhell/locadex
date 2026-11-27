#include <locadex/spatial/morton3_decode_u32.h>
#include <locadex/spatial/morton3_encode_u32.h>

#include <stdint.h>

int main(void)
{
    uint32_t code = 0u;
    uint32_t x = 0u, y = 0u, z = 0u;

    if (!locadex_morton3_encode_u32(1u, 2u, 3u, &code) ||
        !locadex_morton3_decode_u32(code, &x, &y, &z)) {
        return 1;
    }
    return x == 1u && y == 2u && z == 3u ? 0 : 1;
}
