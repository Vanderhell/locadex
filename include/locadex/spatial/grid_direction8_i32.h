#ifndef LOCADEX_SPATIAL_GRID_DIRECTION8_I32_H
#define LOCADEX_SPATIAL_GRID_DIRECTION8_I32_H
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Quantize a signed int32 displacement to its nearest compass direction.
 * Codes are E, NE, N, NW, W, SW, S, SE = 0..7 counterclockwise. The zero
 * vector fails; failure preserves *out. */
bool locadex_grid_direction8_i32(int32_t dx, int32_t dy, uint8_t *out);


#ifdef __cplusplus
}
#endif

#endif /* LOCADEX_SPATIAL_GRID_DIRECTION8_I32_H */
