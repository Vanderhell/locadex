#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "pc_grid_direction8_i32.h"
#include "pc_morton3_decode_u32.h"
#include "pc_morton3_encode_u32.h"
#include "pc_voxel_coords_3d_u32.h"
#include "pc_voxel_index_3d_u32.h"

#define CHECK(expr) do { if (!(expr)) { \
    fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #expr); \
    return 1; \
} } while (0)

#define RANDOM_CASES UINT32_C(100000)
#define MORTON_MAX UINT32_C(0x3FFFFFFF)
#define VOLUME_LIMIT (UINT64_C(1) + (uint64_t)UINT32_MAX)

static uint32_t rng_state = UINT32_C(0x91E10DA5);

static uint32_t next_random(void)
{
    uint32_t x = rng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng_state = x;
    return x;
}

static int32_t as_i32(uint32_t bits)
{
    if (bits <= (uint32_t)INT32_MAX) return (int32_t)bits;
    return (int32_t)((int64_t)bits - INT64_C(4294967296));
}

/* Independent specification model: place/extract one source bit at a time. */
static uint32_t morton_reference(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t code = 0u;
    unsigned int bit;
    for (bit = 0u; bit < 10u; ++bit) {
        code |= ((x >> bit) & 1u) << (3u * bit);
        code |= ((y >> bit) & 1u) << (3u * bit + 1u);
        code |= ((z >> bit) & 1u) << (3u * bit + 2u);
    }
    return code;
}

static void morton_decode_reference(uint32_t code, uint32_t *x,
                                    uint32_t *y, uint32_t *z)
{
    unsigned int bit;
    *x = 0u; *y = 0u; *z = 0u;
    for (bit = 0u; bit < 10u; ++bit) {
        *x |= ((code >> (3u * bit)) & 1u) << bit;
        *y |= ((code >> (3u * bit + 1u)) & 1u) << bit;
        *z |= ((code >> (3u * bit + 2u)) & 1u) << bit;
    }
}

static uint8_t direction_reference(int32_t dx, int32_t dy)
{
    const double pi = 3.14159265358979323846264338327950288;
    double angle = atan2((double)dy, (double)dx);
    int sector;
    if (angle < 0.0) angle += 2.0 * pi;
    sector = (int)floor((angle + pi / 8.0) / (pi / 4.0));
    return (uint8_t)(sector & 7);
}

static uint64_t voxel_reference(uint32_t width, uint32_t height,
                                uint32_t x, uint32_t y, uint32_t z)
{
    return ((uint64_t)z * height + y) * width + x;
}

static int test_morton(void)
{
    static const uint32_t edge[] = {0u, 1u, 2u, 511u, 512u, 1022u, 1023u};
    uint32_t i, x, y, z, code, actual, expected;
    uint32_t decoded_x, decoded_y, decoded_z;
    size_t a, b, c;
    for (a = 0u; a < sizeof edge / sizeof edge[0]; ++a)
        for (b = 0u; b < sizeof edge / sizeof edge[0]; ++b)
            for (c = 0u; c < sizeof edge / sizeof edge[0]; ++c) {
                expected = morton_reference(edge[a], edge[b], edge[c]);
                CHECK(pc_morton3_encode_u32(edge[a], edge[b], edge[c], &actual));
                CHECK(actual == expected);
                CHECK(pc_morton3_decode_u32(expected, &x, &y, &z));
                CHECK(x == edge[a] && y == edge[b] && z == edge[c]);
            }
    for (i = 0u; i < 10u; ++i) {
        const uint32_t bit = UINT32_C(1) << i;
        CHECK(pc_morton3_encode_u32(bit, 0u, 0u, &code));
        CHECK(code == (UINT32_C(1) << (3u * i)));
        CHECK(pc_morton3_encode_u32(0u, bit, 0u, &code));
        CHECK(code == (UINT32_C(1) << (3u * i + 1u)));
        CHECK(pc_morton3_encode_u32(0u, 0u, bit, &code));
        CHECK(code == (UINT32_C(1) << (3u * i + 2u)));
    }
    CHECK(pc_morton3_encode_u32(1023u, 1023u, 1023u, &code));
    CHECK(code == MORTON_MAX);
    for (i = 0u; i < RANDOM_CASES; ++i) {
        x = next_random() & 1023u;
        y = next_random() & 1023u;
        z = next_random() & 1023u;
        expected = morton_reference(x, y, z);
        CHECK(pc_morton3_encode_u32(x, y, z, &actual) && actual == expected);
        CHECK(pc_morton3_decode_u32(expected, &decoded_x, &decoded_y, &decoded_z));
        CHECK(decoded_x == x && decoded_y == y && decoded_z == z);
    }
    /* A second random stream exercises decode for arbitrary legal codes. */
    for (i = 0u; i < RANDOM_CASES; ++i) {
        const uint32_t random_code = next_random() & MORTON_MAX;
        uint32_t rx, ry, rz;
        morton_decode_reference(random_code, &x, &y, &z);
        CHECK(pc_morton3_decode_u32(random_code, &rx, &ry, &rz));
        CHECK(rx == x && ry == y && rz == z);
        CHECK(morton_reference(rx, ry, rz) == random_code);
    }
    x = 11u; y = 22u; z = 33u;
    CHECK(!pc_morton3_decode_u32(UINT32_C(0x40000000), &x, &y, &z));
    CHECK(x == 11u && y == 22u && z == 33u);
    CHECK(!pc_morton3_decode_u32(UINT32_MAX, &x, &y, &z));
    CHECK(!pc_morton3_decode_u32(0u, &x, &x, &z));
    CHECK(!pc_morton3_decode_u32(0u, &x, &y, &x));
    CHECK(!pc_morton3_decode_u32(0u, &x, &y, &y));
    CHECK(!pc_morton3_decode_u32(0u, NULL, &y, &z));
    code = UINT32_C(0xA5A5A5A5);
    CHECK(!pc_morton3_encode_u32(1024u, 0u, 0u, &code));
    CHECK(code == UINT32_C(0xA5A5A5A5));
    CHECK(!pc_morton3_encode_u32(0u, 1024u, 0u, &code));
    CHECK(!pc_morton3_encode_u32(0u, 0u, 1024u, &code));
    CHECK(!pc_morton3_encode_u32(0u, 0u, 0u, NULL));
    return 0;
}

static int test_voxel(void)
{
    static const uint32_t dims[] = {1u, 2u, 3u, 7u, 16u, 255u};
    uint32_t i, x, y, z, index, encoded;
    size_t dw, dh, dd;
    for (dw = 0u; dw < sizeof dims / sizeof dims[0]; ++dw)
        for (dh = 0u; dh < sizeof dims / sizeof dims[0]; ++dh)
            for (dd = 0u; dd < sizeof dims / sizeof dims[0]; ++dd) {
                const uint32_t w = dims[dw], h = dims[dh], d = dims[dd];
                const uint64_t volume = (uint64_t)w * h * d;
                for (index = 0u; (uint64_t)index < volume; ++index) {
                    const uint32_t expected_x = index % w;
                    const uint32_t expected_y = (index / w) % h;
                    const uint32_t expected_z = index / (w * h);
                    CHECK(pc_voxel_coords_3d_u32(w, h, d, index, &x, &y, &z));
                    CHECK(x == expected_x && y == expected_y && z == expected_z);
                    CHECK(pc_voxel_index_3d_u32(w, h, d, x, y, z, &encoded));
                    CHECK((uint64_t)encoded == voxel_reference(w, h, x, y, z));
                    CHECK(encoded == index);
                }
            }
    /* Legal maximum representable volume (2^32 cells) and near-boundary shapes. */
    CHECK(pc_voxel_index_3d_u32(65536u, 65536u, 1u,
                                65535u, 65535u, 0u, &index));
    CHECK(index == UINT32_MAX);
    CHECK(pc_voxel_coords_3d_u32(65536u, 65536u, 1u, UINT32_MAX,
                                 &x, &y, &z));
    CHECK(x == 65535u && y == 65535u && z == 0u);
    CHECK(pc_voxel_index_3d_u32(UINT32_MAX, 1u, 1u,
                                UINT32_MAX - 1u, 0u, 0u, &index));
    CHECK(index == UINT32_MAX - 1u);
    CHECK(pc_voxel_coords_3d_u32(UINT32_MAX, 1u, 1u, UINT32_MAX - 1u,
                                 &x, &y, &z));
    CHECK(x == UINT32_MAX - 1u && y == 0u && z == 0u);
    for (i = 0u; i < RANDOM_CASES; ++i) {
        const uint32_t w = (next_random() % 100000u) + 1u;
        const uint32_t h = (next_random() % 40000u) + 1u;
        const uint64_t max_depth = VOLUME_LIMIT / ((uint64_t)w * h);
        const uint32_t depth_range = (uint32_t)(max_depth < 1000u ? max_depth : 1000u);
        const uint32_t d = (next_random() % depth_range) + 1u;
        const uint64_t volume = (uint64_t)w * h * d;
        const uint32_t rx = next_random() % w;
        const uint32_t ry = next_random() % h;
        const uint32_t rz = next_random() % d;
        const uint64_t ref = voxel_reference(w, h, rx, ry, rz);
        CHECK(volume <= VOLUME_LIMIT && ref < VOLUME_LIMIT);
        CHECK(pc_voxel_index_3d_u32(w, h, d, rx, ry, rz, &encoded));
        CHECK((uint64_t)encoded == ref);
        CHECK(pc_voxel_coords_3d_u32(w, h, d, encoded, &x, &y, &z));
        CHECK(x == rx && y == ry && z == rz);
    }
    /* Random inverse indices independently derived with quotient/remainder. */
    for (i = 0u; i < RANDOM_CASES; ++i) {
        const uint32_t w = 65536u, h = 65536u, d = 1u;
        const uint32_t test_index = next_random();
        const uint32_t rx = test_index % w;
        const uint32_t ry = (test_index / w) % h;
        const uint32_t rz = (uint32_t)((uint64_t)test_index /
                                      ((uint64_t)w * (uint64_t)h));
        CHECK(pc_voxel_coords_3d_u32(w, h, d, test_index, &x, &y, &z));
        CHECK(x == rx && y == ry && z == rz);
        CHECK(pc_voxel_index_3d_u32(w, h, d, rx, ry, rz, &encoded));
        CHECK(encoded == test_index);
    }
    x = 11u; y = 22u; z = 33u; index = 99u;
    CHECK(!pc_voxel_index_3d_u32(0u, 1u, 1u, 0u, 0u, 0u, &index));
    CHECK(index == 99u);
    CHECK(!pc_voxel_index_3d_u32(2u, 3u, 4u, 2u, 0u, 0u, &index));
    CHECK(!pc_voxel_index_3d_u32(2u, 3u, 4u, 0u, 3u, 0u, &index));
    CHECK(!pc_voxel_index_3d_u32(2u, 3u, 4u, 0u, 0u, 4u, &index));
    CHECK(!pc_voxel_index_3d_u32(UINT32_MAX, 2u, 1u, 0u, 0u, 0u, &index));
    CHECK(!pc_voxel_index_3d_u32(1u, 1u, 1u, 0u, 0u, 0u, NULL));
    CHECK(index == 99u);
    CHECK(!pc_voxel_coords_3d_u32(2u, 3u, 4u, 24u, &x, &y, &z));
    CHECK(!pc_voxel_coords_3d_u32(UINT32_MAX, 2u, 1u, 0u, &x, &y, &z));
    CHECK(!pc_voxel_coords_3d_u32(1u, 1u, 1u, 0u, &x, &x, &z));
    CHECK(!pc_voxel_coords_3d_u32(1u, 1u, 1u, 0u, &x, &y, &x));
    CHECK(!pc_voxel_coords_3d_u32(1u, 1u, 1u, 0u, &x, &y, &y));
    CHECK(!pc_voxel_coords_3d_u32(1u, 1u, 1u, 0u, NULL, &y, &z));
    CHECK(x == 11u && y == 22u && z == 33u);
    return 0;
}

static int test_direction(void)
{
    static const int32_t vectors[8][2] = {
        {1, 0}, {1, 1}, {0, 1}, {-1, 1},
        {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
    };
    size_t i;
    uint32_t n;
    uint8_t direction = 99u;
    for (i = 0u; i < 8u; ++i) {
        CHECK(pc_grid_direction8_i32(vectors[i][0], vectors[i][1], &direction));
        CHECK(direction == i);
    }
    CHECK(pc_grid_direction8_i32(INT32_MIN, INT32_MIN, &direction) && direction == 5u);
    CHECK(pc_grid_direction8_i32(INT32_MAX, INT32_MIN, &direction) && direction == 7u);
    CHECK(pc_grid_direction8_i32(INT32_MIN, INT32_MAX, &direction) && direction == 3u);
    CHECK(pc_grid_direction8_i32(INT32_MAX, INT32_MAX, &direction) && direction == 1u);
    /* The irrational 22.5-degree boundary is bracketed by adjacent integer slopes. */
    CHECK(pc_grid_direction8_i32(INT32_C(1000000000), INT32_C(414213562), &direction) && direction == 0u);
    CHECK(pc_grid_direction8_i32(INT32_C(1000000000), INT32_C(414213563), &direction) && direction == 1u);
    CHECK(pc_grid_direction8_i32(INT32_C(414213562), INT32_C(1000000000), &direction) && direction == 2u);
    CHECK(pc_grid_direction8_i32(INT32_C(414213563), INT32_C(1000000000), &direction) && direction == 1u);
    CHECK(pc_grid_direction8_i32(-INT32_C(414213562), INT32_C(1000000000), &direction) && direction == 2u);
    CHECK(pc_grid_direction8_i32(-INT32_C(414213563), INT32_C(1000000000), &direction) && direction == 3u);
    CHECK(pc_grid_direction8_i32(-INT32_C(1000000000), INT32_C(414213562), &direction) && direction == 4u);
    CHECK(pc_grid_direction8_i32(-INT32_C(1000000000), INT32_C(414213563), &direction) && direction == 3u);
    CHECK(pc_grid_direction8_i32(-INT32_C(1000000000), -INT32_C(414213562), &direction) && direction == 4u);
    CHECK(pc_grid_direction8_i32(-INT32_C(1000000000), -INT32_C(414213563), &direction) && direction == 5u);
    CHECK(pc_grid_direction8_i32(-INT32_C(414213562), -INT32_C(1000000000), &direction) && direction == 6u);
    CHECK(pc_grid_direction8_i32(-INT32_C(414213563), -INT32_C(1000000000), &direction) && direction == 5u);
    CHECK(pc_grid_direction8_i32(INT32_C(414213562), -INT32_C(1000000000), &direction) && direction == 6u);
    CHECK(pc_grid_direction8_i32(INT32_C(414213563), -INT32_C(1000000000), &direction) && direction == 7u);
    CHECK(pc_grid_direction8_i32(INT32_C(1000000000), -INT32_C(414213562), &direction) && direction == 0u);
    CHECK(pc_grid_direction8_i32(INT32_C(1000000000), -INT32_C(414213563), &direction) && direction == 7u);
    direction = 77u;
    CHECK(!pc_grid_direction8_i32(0, 0, &direction) && direction == 77u);
    CHECK(!pc_grid_direction8_i32(1, 1, NULL));
    for (n = 0u; n < RANDOM_CASES; ++n) {
        const int32_t dx = as_i32(next_random());
        const int32_t dy = as_i32(next_random());
        uint8_t expected;
        if (dx == 0 && dy == 0) {
            direction = 91u;
            CHECK(!pc_grid_direction8_i32(dx, dy, &direction) && direction == 91u);
            continue;
        }
        expected = direction_reference(dx, dy);
        CHECK(pc_grid_direction8_i32(dx, dy, &direction));
        CHECK(direction == expected);
    }
    return 0;
}

int main(void)
{
    CHECK(test_morton() == 0);
    CHECK(test_voxel() == 0);
    CHECK(test_direction() == 0);
    puts("LOCADEX independent audit tests: 5/5 APIs, deterministic differential PASS");
    return 0;
}
