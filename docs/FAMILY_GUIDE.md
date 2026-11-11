# Locadex family guide

## What this family solves

**Spatial indexing.** Grid, voxel, Morton and bounded spatial-index calculations.

This guide describes the complete public family as an independent embedded-C product. Each primitive remains separately linkable; select only the headers and source units required by the application.

## When to use this family

Use Locadex when the application needs the operations listed below and requires deterministic behavior, explicit caller-owned memory, and no mandatory operating-system services.

## Family at a glance

```mermaid
flowchart LR
    A[Application input] --> B[Validate representation and bounds]
    B --> C[Select one public primitive]
    C --> D[Check status or output contract]
    D --> E[Use result with documented units]
```

## Primitive map

| Public header | Symbol | Purpose and contract | Validation source |
|---|---|---|---|
| `include/locadex/spatial/pc_grid_direction8_i32.h` | `pc_grid_direction8_i32` | Quantize a signed int32 displacement to its nearest compass direction. Codes are E, NE, N, NW, W, SW, S, SE = 0..7 counterclockwise. The zero vector fails; failure preserves *out. | tests/test_api_audit.c and focused boundary tests |
| `include/locadex/spatial/pc_morton3_decode_u32.h` | `pc_morton3_decode_u32` | Decode a 30-bit x/y/z-interleaved Morton code. Codes with either upper uint32 bit set are invalid. Outputs must be non-null and distinct; failure preserves all outputs. | tests/test_morton.c |
| `include/locadex/spatial/pc_morton3_encode_u32.h` | `pc_morton3_encode_u32` | Interleave three 10-bit coordinates into bits 0..29 in x,y,z order. Failure preserves code. | tests/test_morton.c |
| `include/locadex/spatial/pc_voxel_coords_3d_u32.h` | `pc_voxel_coords_3d_u32` | Checked inverse of pc_voxel_index_3d_u32. Dimensions are nonzero, volume <= UINT32_MAX+1, and output pointers are non-null and distinct. Failure preserves all outputs. | tests/test_voxel.c |
| `include/locadex/spatial/pc_voxel_index_3d_u32.h` | `pc_voxel_index_3d_u32` | Checked row-major voxel index ((z * height + y) * width + x). Dimensions must be nonzero, coordinates in range, and volume <= UINT32_MAX+1 cells. Failure preserves index. | tests/test_voxel.c |

## Selection guidance

- Choose the primitive whose width, representation, rounding, saturation, wrapping, and error contract match the application.
- Do not substitute a similarly named function without checking the public header.
- Allocate state and buffers in the caller; respect documented aliasing and output-preservation rules.
- Refer to docs/AUDIT.md for per-operation evidence and remaining test limits.

## Integration checklist

1. Include only the required public header.
2. Compile the matching source translation unit or use the product CMake target.
3. Check every boolean/status return before consuming an output.
4. Add application-specific boundary tests for units, widths, invalid inputs, and overflow behavior.
5. Run the documented host tests before target integration.

## Complexity and footprint

The product is split into independent translation units. Exact flash, RAM, stack, and cycle costs depend on the selected functions, compiler, optimization, and MCU; unmeasured values are identified as not measured in the testing documentation.

## Validation boundary

The API reference links each public entry to its implementation and available validation source. Hardware status is reported only when reproducible target evidence exists.
