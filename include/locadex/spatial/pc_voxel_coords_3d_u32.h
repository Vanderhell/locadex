#ifndef PC_VOXEL_COORDS_3D_U32_H
#define PC_VOXEL_COORDS_3D_U32_H
#include <stdbool.h>
#include <stdint.h>

/* Checked inverse of pc_voxel_index_3d_u32. Dimensions are nonzero, volume
 * <= UINT32_MAX+1, and output pointers are non-null and distinct. Failure
 * preserves all outputs. */
bool pc_voxel_coords_3d_u32(uint32_t width, uint32_t height, uint32_t depth,
                           uint32_t index, uint32_t *x, uint32_t *y,
                           uint32_t *z);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_voxel_coords_3d_u32
#define pc_voxel_coords_3d_u32 pc_voxel_coords_3d_u32
#endif
#ifndef pc_voxel_coords_3d_u32
#define pc_voxel_coords_3d_u32 pc_voxel_coords_3d_u32
#endif
#ifndef pc_voxel_index_3d_u32
#define pc_voxel_index_3d_u32 pc_voxel_index_3d_u32
#endif
#ifndef PC_PC_VOXEL_COORDS_3D_U32_H
#define PC_PC_VOXEL_COORDS_3D_U32_H PC_VOXEL_COORDS_3D_U32_H
#endif

