#include "pc_snap_to_grid_i32.h"
#include <limits.h>
#define CHECK(c) do { if (!(c)) return __LINE__; } while (0)
int main(void)
{
    int32_t out = 77;
    CHECK(pc_snap_to_grid_i32(2, 1, 2, &out) && out == 1);
    CHECK(pc_snap_to_grid_i32(4, 1, 2, &out) && out == 5);
    CHECK(pc_snap_to_grid_i32(-2, 1, 2, &out) && out == -3);
    CHECK(pc_snap_to_grid_i32(-4, 1, 2, &out) && out == -3);
    CHECK(pc_snap_to_grid_i32(10, 3, 4, &out) && out == 11);
    CHECK(pc_snap_to_grid_i32(INT32_MIN, INT32_MIN, 1, &out) && out == INT32_MIN);
    out = 77;
    CHECK(!pc_snap_to_grid_i32(INT32_MAX, INT32_MIN + 2, INT32_MAX, &out) && out == 77);
    CHECK(!pc_snap_to_grid_i32(1, 0, 0, &out) && out == 77);
    CHECK(!pc_snap_to_grid_i32(1, 0, 1, 0));
    return 0;
}