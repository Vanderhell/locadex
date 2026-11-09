/* Held-out cross-family validation source; dependency is outside this product. */
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

static int32_t oracle_axis(int32_t value, uint32_t extent)
{
    if (value < 0) return 0;
    if ((uint32_t)value >= extent) return (int32_t)(extent - 1u);
    return value;
}

int main(void)
{
    uint32_t width, height, x, y, seed = UINT32_C(0x519C1A);
    int32_t actual_x, actual_y;
    const uint32_t extents[] = {1u, 2u, (uint32_t)INT32_MAX,
                                (uint32_t)INT32_MAX + 1u, UINT32_MAX};
    size_t i;

    actual_x = 123;
    CHECK(!pc_control_output_clamp_i32(0, 0, -1, &actual_x));
    CHECK(actual_x == 123);
    CHECK(!pc_control_output_clamp_i32(0, 0, 1, NULL));

    for (width = 1u; width <= 16u; ++width) {
        for (height = 1u; height <= 16u; ++height) {
            for (x = 0u; x < width + 3u; ++x) {
                for (y = 0u; y < height + 3u; ++y) {
                    const int32_t ix = (int32_t)x - 3;
                    const int32_t iy = (int32_t)y - 3;
                    CHECK(pc_control_output_clamp_i32(ix, 0, (int32_t)width - 1, &actual_x));
                    CHECK(pc_control_output_clamp_i32(iy, 0, (int32_t)height - 1, &actual_y));
                    CHECK(actual_x == oracle_axis(ix, width));
                    CHECK(actual_y == oracle_axis(iy, height));
                }
            }
        }
    }
    for (i = 0u; i < sizeof(extents) / sizeof(extents[0]); ++i) {
        const int32_t values[] = {INT32_MIN, -1, 0, 1, INT32_MAX};
        size_t j;
        for (j = 0u; j < sizeof(values) / sizeof(values[0]); ++j) {
            const int32_t upper = extents[i] - 1u > (uint32_t)INT32_MAX
                                      ? INT32_MAX : (int32_t)(extents[i] - 1u);
            CHECK(pc_control_output_clamp_i32(values[j], 0, upper, &actual_x));
            CHECK(actual_x == oracle_axis(values[j], extents[i]));
        }
    }
    for (i = 0u; i < 100000u; ++i) {
        const int32_t ix = as_i32(next_u32(&seed));
        const int32_t iy = as_i32(next_u32(&seed));
        width = next_u32(&seed) | 1u;
        height = next_u32(&seed) | 1u;
        {
            const int32_t upper_x = width - 1u > (uint32_t)INT32_MAX
                                      ? INT32_MAX : (int32_t)(width - 1u);
            const int32_t upper_y = height - 1u > (uint32_t)INT32_MAX
                                      ? INT32_MAX : (int32_t)(height - 1u);
            CHECK(pc_control_output_clamp_i32(ix, 0, upper_x, &actual_x));
            CHECK(pc_control_output_clamp_i32(iy, 0, upper_y, &actual_y));
            CHECK(actual_x == oracle_axis(ix, width));
            CHECK(actual_y == oracle_axis(iy, height));
        }
    }
    return 0;
}