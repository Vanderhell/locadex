# LOCADEX API reference

Each symbol has one public C99 header and one independently compilable implementation unit. The public headers define the authoritative signatures and failure contracts. All five symbols have direct automated coverage in `tests/test_api_audit.c`; focused legacy tests remain in `tests/test_morton.c` and `tests/test_voxel.c`.

| Header | Symbol | Contract summary | Additional validation |
|---|---|---|---|
| `include/locadex/spatial/pc_grid_direction8_i32.h` | `pc_grid_direction8_i32` | Quantize nonzero signed displacement to E/NE/N/NW/W/SW/S/SE codes 0..7; null output or zero vector fails without writing. | `atan2`/`floor` reference, all sectors and transition neighborhoods, signed extremes, 100,000 seeded vectors. |
| `include/locadex/spatial/pc_morton3_encode_u32.h` | `pc_morton3_encode_u32` | Interleave three coordinates in 0..1023 into 30-bit x/y/z order; invalid coordinate or null output fails without changing code. | Independent bit placement, boundary values, 100,000 seeded triples. |
| `include/locadex/spatial/pc_morton3_decode_u32.h` | `pc_morton3_decode_u32` | Decode codes through `0x3fffffff`; rejects upper bits, null or aliased outputs atomically. | Independent bit extraction, boundary codes, 100,000 seeded codes and round trips. |
| `include/locadex/spatial/pc_voxel_index_3d_u32.h` | `pc_voxel_index_3d_u32` | Checked row-major `((z * height + y) * width + x)`; nonzero dimensions, in-range coordinates, volume <= 2^32; failure preserves index. | Independent widened formula, exhaustive small grids, maximum volume and 100,000 seeded valid points. |
| `include/locadex/spatial/pc_voxel_coords_3d_u32.h` | `pc_voxel_coords_3d_u32` | Checked inverse; volume <= 2^32, index in volume, outputs non-null/distinct; failure preserves outputs. | Quotient/remainder reference, exhaustive small grids, maximum volume and 200,000 seeded indices/shapes. |

Detailed inspection findings and proof boundaries are recorded in [AUDIT.md](AUDIT.md). Compiler and sanitizer commands are in [TESTING.md](TESTING.md); hardware timing and size results are in [PERFORMANCE.md](PERFORMANCE.md).