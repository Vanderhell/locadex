#ifndef LOCADEX_SPATIAL_MORTON3_DECODE_U32_H
#define LOCADEX_SPATIAL_MORTON3_DECODE_U32_H
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Decode a 30-bit x/y/z-interleaved Morton code. Codes with either upper
 * uint32 bit set are invalid. Outputs must be non-null and distinct; failure
 * preserves all outputs. */
bool locadex_morton3_decode_u32(uint32_t code, uint32_t *x, uint32_t *y,
                           uint32_t *z);


#ifdef __cplusplus
}
#endif

#endif /* LOCADEX_SPATIAL_MORTON3_DECODE_U32_H */
