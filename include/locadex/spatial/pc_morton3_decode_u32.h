#ifndef PRIMITIVECORE_MORTON3_DECODE_U32_H
#define PRIMITIVECORE_MORTON3_DECODE_U32_H
#include <stdbool.h>
#include <stdint.h>

/* Decode a 30-bit x/y/z-interleaved Morton code. Codes with either upper
 * uint32 bit set are invalid. Outputs must be non-null and distinct; failure
 * preserves all outputs. */
bool rm_morton3_decode_u32(uint32_t code, uint32_t *x, uint32_t *y,
                           uint32_t *z);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_morton3_decode_u32
#define pc_morton3_decode_u32 rm_morton3_decode_u32
#endif
#ifndef pc_morton3_decode_u32
#define pc_morton3_decode_u32 rm_morton3_decode_u32
#endif
#ifndef PC_PRIMITIVECORE_MORTON3_DECODE_U32_H
#define PC_PRIMITIVECORE_MORTON3_DECODE_U32_H PRIMITIVECORE_MORTON3_DECODE_U32_H
#endif

