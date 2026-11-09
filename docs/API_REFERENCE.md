# Locadex API reference

This reference explains every public header in the Locadex product. It is generated from the current headers and test sources; the header remains authoritative when a detail conflicts.

## Reading the entries
Each entry states the public symbol, implementation unit, contract, edge/failure behavior and a call extracted from the validating test source. The examples are evidence-oriented; adapt buffer ownership and numeric units to the application.

## include/locadex/spatial/pc_grid_direction8_i32.h

**Public symbol:** pc_grid_direction8_i32

**Implementation unit:** src/pc_grid_direction8_i32.c

**Purpose and contract:** Quantize a signed int32 displacement to its nearest compass direction. Codes are E, NE, N, NW, W, SW, S, SE = 0..7 counterclockwise. The zero vector fails; failure preserves *out.

**Validation source:** No enabled test source was found by symbol search.

**Test-derived call:**
```c
No test-derived call was found.;
```

**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/locadex/spatial/pc_morton3_decode_u32.h

**Public symbol:** pc_morton3_decode_u32

**Implementation unit:** src/pc_morton3_decode_u32.c

**Purpose and contract:** Decode a 30-bit x/y/z-interleaved Morton code. Codes with either upper uint32 bit set are invalid. Outputs must be non-null and distinct; failure preserves all outputs.

**Validation source:** tests/test_morton.c

**Test-derived call:**
```c
pc_morton3_decode_u32(0u, &x, &y, &z\);
```

**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/locadex/spatial/pc_morton3_encode_u32.h

**Public symbol:** pc_morton3_encode_u32

**Implementation unit:** src/pc_morton3_encode_u32.c

**Purpose and contract:** Interleave three 10-bit coordinates into bits 0..29 in x,y,z order. Failure preserves code.

**Validation source:** tests/test_morton.c

**Test-derived call:**
```c
pc_morton3_encode_u32(a, b, c, &code\);
```

**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/locadex/spatial/pc_voxel_coords_3d_u32.h

**Public symbol:** pc_voxel_coords_3d_u32

**Implementation unit:** src/pc_voxel_coords_3d_u32.c

**Purpose and contract:** Checked inverse of pc_voxel_index_3d_u32. Dimensions are nonzero, volume <= UINT32_MAX+1, and output pointers are non-null and distinct. Failure preserves all outputs.

**Validation source:** tests/test_voxel.c

**Test-derived call:**
```c
pc_voxel_coords_3d_u32(1u, 1u, 1u, 0u, &x, &y, &z\);
```

**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/locadex/spatial/pc_voxel_index_3d_u32.h

**Public symbol:** pc_voxel_index_3d_u32

**Implementation unit:** src/pc_voxel_index_3d_u32.c

**Purpose and contract:** Checked row-major voxel index ((z * height + y) * width + x). Dimensions must be nonzero, coordinates in range, and volume <= UINT32_MAX+1 cells. Failure preserves index.

**Validation source:** tests/test_voxel.c

**Test-derived call:**
```c
pc_voxel_index_3d_u32(w, h, d, x, y, z, &encoded\);
```

**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

