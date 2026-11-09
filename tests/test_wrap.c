#include "pc_grid_wrap_coords_i32.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#define CHECK(c) do { if (!(c)) { fprintf(stderr, "check failed at %d\n", __LINE__); return 1; } } while (0)

static uint32_t next_u32(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static int32_t as_i32(uint32_t value)
{
    return value <= (uint32_t)INT32_MAX
               ? (int32_t)value
               : (int32_t)((int64_t)value - INT64_C(4294967296));
}

static uint32_t oracle_axis(int32_t coordinate, uint32_t extent)
{
    int64_t remainder = (int64_t)coordinate % (int64_t)extent;
    if (remainder < 0) remainder += (int64_t)extent;
    return (uint32_t)remainder;
}

int main(void)
{
    uint32_t xout = 77u, yout = 88u, seed = UINT32_C(0x520A11);
    const uint32_t extents[] = {1u, 2u, 3u, 7u, 16u, 31u,
                                (uint32_t)INT32_MAX, (uint32_t)INT32_MAX + 1u, UINT32_MAX};
    const int32_t endpoints[] = {INT32_MIN, -1, 0, 1, INT32_MAX};
    size_t i, j, k, l;

    CHECK(!pc_grid_wrap_coords_i32(1, 2, 0u, 3u, &xout, &yout));
    CHECK(xout == 77u && yout == 88u);
    CHECK(!pc_grid_wrap_coords_i32(1, 2, 3u, 0u, &xout, &yout));
    CHECK(xout == 77u && yout == 88u);
    CHECK(!pc_grid_wrap_coords_i32(1, 2, 3u, 4u, NULL, &yout));
    CHECK(!pc_grid_wrap_coords_i32(1, 2, 3u, 4u, &xout, NULL));
    CHECK(!pc_grid_wrap_coords_i32(1, 2, 3u, 4u, &xout, &xout));
    CHECK(xout == 77u && yout == 88u);

    for (i = 1u; i <= 16u; ++i) {
        for (j = 1u; j <= 16u; ++j) {
            int32_t x, y;
            for (x = -64; x <= 64; ++x) {
                for (y = -64; y <= 64; ++y) {
                    CHECK(pc_grid_wrap_coords_i32(x, y, (uint32_t)i, (uint32_t)j, &xout, &yout));
                    CHECK(xout == oracle_axis(x, (uint32_t)i));
                    CHECK(yout == oracle_axis(y, (uint32_t)j));
                    CHECK(pc_grid_wrap_coords_i32(x + (int32_t)i, y - (int32_t)j,
                                                  (uint32_t)i, (uint32_t)j, &xout, &yout));
                    CHECK(xout == oracle_axis(x, (uint32_t)i));
                    CHECK(yout == oracle_axis(y, (uint32_t)j));
                }
            }
        }
    }
    for (i = 0u; i < sizeof(extents) / sizeof(extents[0]); ++i) {
        for (j = 0u; j < sizeof(endpoints) / sizeof(endpoints[0]); ++j) {
            for (k = 0u; k < sizeof(extents) / sizeof(extents[0]); ++k) {
                for (l = 0u; l < sizeof(endpoints) / sizeof(endpoints[0]); ++l) {
                    CHECK(pc_grid_wrap_coords_i32(endpoints[j], endpoints[l],
                                                  extents[i], extents[k], &xout, &yout));
                    CHECK(xout == oracle_axis(endpoints[j], extents[i]));
                    CHECK(yout == oracle_axis(endpoints[l], extents[k]));
                }
            }
        }
    }
    for (i = 0u; i < 200000u; ++i) {
        const int32_t x = as_i32(next_u32(&seed));
        const int32_t y = as_i32(next_u32(&seed));
        const uint32_t width = next_u32(&seed) | 1u;
        const uint32_t height = next_u32(&seed) | 1u;
        CHECK(pc_grid_wrap_coords_i32(x, y, width, height, &xout, &yout));
        CHECK(xout == oracle_axis(x, width));
        CHECK(yout == oracle_axis(y, height));
    }
    return 0;
}