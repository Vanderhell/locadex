# Locadex API reference

Complete public-header inventory generated from the current source tree. Headers remain authoritative.

## include/locadex/spatial/pc_grid_direction8_i32.h

Public API: pc_grid_direction8_i32

Contract: Quantize a signed int32 displacement to its nearest compass direction. Codes are E, NE, N, NW, W, SW, S, SE = 0..7 counterclockwise. The zero vector fails; failure preserves *out.

Header path: include/locadex/spatial/pc_grid_direction8_i32.h

## include/locadex/spatial/pc_morton3_decode_u32.h

Public API: pc_morton3_decode_u32

Contract: Decode a 30-bit x/y/z-interleaved Morton code. Codes with either upper uint32 bit set are invalid. Outputs must be non-null and distinct; failure preserves all outputs.

Header path: include/locadex/spatial/pc_morton3_decode_u32.h

## include/locadex/spatial/pc_morton3_encode_u32.h

Public API: pc_morton3_encode_u32

Contract: Interleave three 10-bit coordinates into bits 0..29 in x,y,z order. Failure preserves code.

Header path: include/locadex/spatial/pc_morton3_encode_u32.h

## include/locadex/spatial/pc_voxel_coords_3d_u32.h

Public API: pc_voxel_coords_3d_u32

Contract: Checked inverse of pc_voxel_index_3d_u32. Dimensions are nonzero, volume <= UINT32_MAX+1, and output pointers are non-null and distinct. Failure preserves all outputs.

Header path: include/locadex/spatial/pc_voxel_coords_3d_u32.h

## include/locadex/spatial/pc_voxel_index_3d_u32.h

Public API: pc_voxel_index_3d_u32

Contract: Checked row-major voxel index ((z * height + y) * width + x). Dimensions must be nonzero, coordinates in range, and volume <= UINT32_MAX+1 cells. Failure preserves index.

Header path: include/locadex/spatial/pc_voxel_index_3d_u32.h
