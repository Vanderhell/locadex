#ifndef PC_PC_GRID_DIRECTION8_I32_H
#define PC_PC_GRID_DIRECTION8_I32_H
#include <stdbool.h>
#include <stdint.h>
/* Quantize a signed int32 displacement to its nearest compass direction.
 * Codes are E, NE, N, NW, W, SW, S, SE = 0..7 counterclockwise. The zero
 * vector fails; failure preserves *out. */
bool pc_grid_direction8_i32(int32_t dx, int32_t dy, uint8_t *out);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_grid_direction8_i32
#define pc_grid_direction8_i32 pc_grid_direction8_i32
#endif
#ifndef pc_grid_direction8_i32
#define pc_grid_direction8_i32 pc_grid_direction8_i32
#endif
#ifndef PC_PC_PC_GRID_DIRECTION8_I32_H
#define PC_PC_PC_GRID_DIRECTION8_I32_H PC_PC_GRID_DIRECTION8_I32_H
#endif

