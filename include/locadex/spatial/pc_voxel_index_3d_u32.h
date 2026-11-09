#ifndef PC_VOXEL_INDEX_3D_U32_H
#define PC_VOXEL_INDEX_3D_U32_H
#include <stdbool.h>
#include <stdint.h>

/* Checked row-major voxel index ((z * height + y) * width + x). Dimensions
 * must be nonzero, coordinates in range, and volume <= UINT32_MAX+1 cells.
 * Failure preserves index. */
bool pc_voxel_index_3d_u32(uint32_t width, uint32_t height, uint32_t depth,
                           uint32_t x, uint32_t y, uint32_t z,
                           uint32_t *index);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_voxel_index_3d_u32
#define pc_voxel_index_3d_u32 pc_voxel_index_3d_u32
#endif
#ifndef pc_voxel_index_3d_u32
#define pc_voxel_index_3d_u32 pc_voxel_index_3d_u32
#endif
#ifndef PC_PC_VOXEL_INDEX_3D_U32_H
#define PC_PC_VOXEL_INDEX_3D_U32_H PC_VOXEL_INDEX_3D_U32_H
#endif

