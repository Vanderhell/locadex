#ifndef LOCADEX_SPATIAL_MORTON3_ENCODE_U32_H
#define LOCADEX_SPATIAL_MORTON3_ENCODE_U32_H
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Interleave three 10-bit coordinates into bits 0..29 in x,y,z order.
 * Failure preserves code. */
bool locadex_morton3_encode_u32(uint32_t x, uint32_t y, uint32_t z,
                           uint32_t *code);


#ifdef __cplusplus
}
#endif

#endif /* LOCADEX_SPATIAL_MORTON3_ENCODE_U32_H */
