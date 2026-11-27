# Locadex API reference

The five public APIs are listed with exact C declarations, contract text from their headers and enabled direct test sources. Public headers are authoritative for complete parameter and failure rules.

## API index

| Function | Declared behavior | Header | Direct tests |
|---|---|---|---|
| [`locadex_grid_direction8_i32`](#locadex_grid_direction8_i32) | Quantize a signed int32 displacement to its nearest compass direction. Codes are E, NE, N, NW, W, SW, S, SE = 0..7 counterclockwise. The zero vector fails; failure preserves *out. | [`grid_direction8_i32.h`](../include/locadex/spatial/grid_direction8_i32.h) | [`test_api_audit.c`](../tests/test_api_audit.c) |
| [`locadex_morton3_decode_u32`](#locadex_morton3_decode_u32) | Decode a 30-bit x/y/z-interleaved Morton code. Codes with either upper uint32 bit set are invalid. Outputs must be non-null and distinct; failure preserves all outputs. | [`morton3_decode_u32.h`](../include/locadex/spatial/morton3_decode_u32.h) | [`test_api_audit.c`](../tests/test_api_audit.c), [`test_morton.c`](../tests/test_morton.c) |
| [`locadex_morton3_encode_u32`](#locadex_morton3_encode_u32) | Interleave three 10-bit coordinates into bits 0..29 in x,y,z order. Failure preserves code. | [`morton3_encode_u32.h`](../include/locadex/spatial/morton3_encode_u32.h) | [`test_api_audit.c`](../tests/test_api_audit.c), [`test_morton.c`](../tests/test_morton.c) |
| [`locadex_voxel_coords_3d_u32`](#locadex_voxel_coords_3d_u32) | Checked inverse of locadex_voxel_index_3d_u32. Dimensions are nonzero, volume <= UINT32_MAX+1, and output pointers are non-null and distinct. Failure preserves all outputs. | [`voxel_coords_3d_u32.h`](../include/locadex/spatial/voxel_coords_3d_u32.h) | [`test_api_audit.c`](../tests/test_api_audit.c), [`test_voxel.c`](../tests/test_voxel.c) |
| [`locadex_voxel_index_3d_u32`](#locadex_voxel_index_3d_u32) | Checked row-major voxel index ((z * height + y) * width + x). Dimensions must be nonzero, coordinates in range, and volume <= UINT32_MAX+1 cells. Failure preserves index. | [`voxel_index_3d_u32.h`](../include/locadex/spatial/voxel_index_3d_u32.h) | [`test_api_audit.c`](../tests/test_api_audit.c), [`test_voxel.c`](../tests/test_voxel.c) |

## Integration

For CMake integration, use `find_package(Locadex CONFIG REQUIRED)` and link `Locadex::Locadex`, or add the project with `add_subdirectory()`. Compile a matching implementation unit for direct source integration.

```c
#include <stdint.h>
#include <locadex/spatial/morton3_encode_u32.h>
int main(void) { uint32_t code=0; return locadex_morton3_encode_u32(1u,2u,3u,&code) && code==53u ? 0 : 1; }
```

## API details

### locadex_grid_direction8_i32

Header: [`grid_direction8_i32.h`](../include/locadex/spatial/grid_direction8_i32.h)

**Purpose and declared contract:** Quantize a signed int32 displacement to its nearest compass direction. Codes are E, NE, N, NW, W, SW, S, SE = 0..7 counterclockwise. The zero vector fails; failure preserves *out.

**C99 declaration:**

```c
bool locadex_grid_direction8_i32(int32_t dx, int32_t dy, uint8_t *out);
```

**Direct tests:** [`test_api_audit.c`](../tests/test_api_audit.c)

### locadex_morton3_decode_u32

Header: [`morton3_decode_u32.h`](../include/locadex/spatial/morton3_decode_u32.h)

**Purpose and declared contract:** Decode a 30-bit x/y/z-interleaved Morton code. Codes with either upper uint32 bit set are invalid. Outputs must be non-null and distinct; failure preserves all outputs.

**C99 declaration:**

```c
bool locadex_morton3_decode_u32(uint32_t code, uint32_t *x, uint32_t *y,
                           uint32_t *z);
```

**Direct tests:** [`test_api_audit.c`](../tests/test_api_audit.c), [`test_morton.c`](../tests/test_morton.c)

### locadex_morton3_encode_u32

Header: [`morton3_encode_u32.h`](../include/locadex/spatial/morton3_encode_u32.h)

**Purpose and declared contract:** Interleave three 10-bit coordinates into bits 0..29 in x,y,z order. Failure preserves code.

**C99 declaration:**

```c
bool locadex_morton3_encode_u32(uint32_t x, uint32_t y, uint32_t z,
                           uint32_t *code);
```

**Direct tests:** [`test_api_audit.c`](../tests/test_api_audit.c), [`test_morton.c`](../tests/test_morton.c)

### locadex_voxel_coords_3d_u32

Header: [`voxel_coords_3d_u32.h`](../include/locadex/spatial/voxel_coords_3d_u32.h)

**Purpose and declared contract:** Checked inverse of locadex_voxel_index_3d_u32. Dimensions are nonzero, volume <= UINT32_MAX+1, and output pointers are non-null and distinct. Failure preserves all outputs.

**C99 declaration:**

```c
bool locadex_voxel_coords_3d_u32(uint32_t width, uint32_t height, uint32_t depth,
                           uint32_t index, uint32_t *x, uint32_t *y,
                           uint32_t *z);
```

**Direct tests:** [`test_api_audit.c`](../tests/test_api_audit.c), [`test_voxel.c`](../tests/test_voxel.c)

### locadex_voxel_index_3d_u32

Header: [`voxel_index_3d_u32.h`](../include/locadex/spatial/voxel_index_3d_u32.h)

**Purpose and declared contract:** Checked row-major voxel index ((z * height + y) * width + x). Dimensions must be nonzero, coordinates in range, and volume <= UINT32_MAX+1 cells. Failure preserves index.

**C99 declaration:**

```c
bool locadex_voxel_index_3d_u32(uint32_t width, uint32_t height, uint32_t depth,
                           uint32_t x, uint32_t y, uint32_t z,
                           uint32_t *index);
```

**Direct tests:** [`test_api_audit.c`](../tests/test_api_audit.c), [`test_voxel.c`](../tests/test_voxel.c)
