#ifndef LOCADEX_SPATIAL_VOXEL_COORDS_3D_U32_H
#define LOCADEX_SPATIAL_VOXEL_COORDS_3D_U32_H
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Checked inverse of locadex_voxel_index_3d_u32. Dimensions are nonzero, volume
 * <= UINT32_MAX+1, and output pointers are non-null and distinct. Failure
 * preserves all outputs. */
bool locadex_voxel_coords_3d_u32(uint32_t width, uint32_t height, uint32_t depth,
                           uint32_t index, uint32_t *x, uint32_t *y,
                           uint32_t *z);


#ifdef __cplusplus
}
#endif

#endif /* LOCADEX_SPATIAL_VOXEL_COORDS_3D_U32_H */
