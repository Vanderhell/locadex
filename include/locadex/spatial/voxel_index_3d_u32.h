#ifndef LOCADEX_SPATIAL_VOXEL_INDEX_3D_U32_H
#define LOCADEX_SPATIAL_VOXEL_INDEX_3D_U32_H
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Checked row-major voxel index ((z * height + y) * width + x). Dimensions
 * must be nonzero, coordinates in range, and volume <= UINT32_MAX+1 cells.
 * Failure preserves index. */
bool locadex_voxel_index_3d_u32(uint32_t width, uint32_t height, uint32_t depth,
                           uint32_t x, uint32_t y, uint32_t z,
                           uint32_t *index);


#ifdef __cplusplus
}
#endif

#endif /* LOCADEX_SPATIAL_VOXEL_INDEX_3D_U32_H */
