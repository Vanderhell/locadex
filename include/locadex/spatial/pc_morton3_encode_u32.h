#ifndef PC_MORTON3_ENCODE_U32_H
#define PC_MORTON3_ENCODE_U32_H
#include <stdbool.h>
#include <stdint.h>

/* Interleave three 10-bit coordinates into bits 0..29 in x,y,z order.
 * Failure preserves code. */
bool pc_morton3_encode_u32(uint32_t x, uint32_t y, uint32_t z,
                           uint32_t *code);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_morton3_encode_u32
#define pc_morton3_encode_u32 pc_morton3_encode_u32
#endif
#ifndef pc_morton3_encode_u32
#define pc_morton3_encode_u32 pc_morton3_encode_u32
#endif
#ifndef PC_PC_MORTON3_ENCODE_U32_H
#define PC_PC_MORTON3_ENCODE_U32_H PC_MORTON3_ENCODE_U32_H
#endif

