# LOCADEX technical audit register

Audit scope: all five public headers and implementations in `include/locadex/spatial/` and `src/`, reviewed against the documented contracts. No public declaration or production algorithm was changed.

## API results

| Public API | Result | Evidence |
|---|---|---|
| `pc_grid_direction8_i32` | OK | Magnitudes use defined signed-to-unsigned conversion and modular negation. The sector test compares `gap^2` with `2*minor^2`; both fit in `uint64_t` for magnitudes <= 2^31. Independent `atan2`/`floor` reference, all 8 sectors, integer slopes on both sides of every octant boundary, zero, null output, signed extremes, and 100,000 seeded full-range vectors pass. |
| `pc_morton3_encode_u32` | OK | Rejects coordinates above 1023 and null output before writing. The spread operations shift unsigned values and mask to 30 bits. Checked against a per-bit interleave reference for boundary combinations and 100,000 seeded triples. |
| `pc_morton3_decode_u32` | OK | Rejects codes above `0x3fffffff`, null outputs, and every output-pointer alias pair before writing. The compact operations use unsigned shifts. Checked against a per-bit extraction reference for boundaries and 100,000 seeded legal codes, plus round trips. |
| `pc_voxel_index_3d_u32` | OK | Checks nonzero dimensions, coordinate bounds and volume <= 2^32 before index calculation. Products/sums are widened to `uint64_t`; accepted result is <= `UINT32_MAX`. Compared to an independent widened row-major formula, small exhaustive grids, 100,000 seeded valid shapes, exact 2^32-cell capacity and invalid overflow cases. |
| `pc_voxel_coords_3d_u32` | OK | Checks dimensions, capacity, index range, null and aliased outputs before publishing local results. The plane and volume products are bounded before use. Compared with independent quotient/remainder coordinate extraction, exhaustive small grids, 100,000 seeded shapes and 100,000 indices in a 2^32-cell domain. |

`OK` means source inspection and the listed test coverage found no defect; it does not claim exhaustive enumeration of every 32-bit input combination.

## Confirmed findings and limitations

- Confirmed production defects: **0**. No implementation fix was indicated by the audit.
- Test infrastructure defect fixed: previous Morton/voxel tests used `assert`, which Release can disable. Assertions are now forced active in those tests; the new audit suite uses explicit checks in every build type.
- A test-oracle overflow was caught and fixed before validation: a test computed `65536 * 65536` in `uint32_t`, producing zero. The oracle now widens before multiplication.
- The hardware harness initially contained an incorrect hand-computed expected voxel index (`14605`); it was corrected to `70605` and then passed on hardware. This was not a library defect.
- Morton's complete 30-bit code space and all valid voxel dimension tuples are too large for exhaustive enumeration; deterministic boundary matrices, exhaustive small grids and seeded 100,000-case samples are used.
- Hardware cycle measurements include loop/control overhead. Stack high-water and isolated linked flash/RAM were not measured; object-level production text sizes are reported separately in `PERFORMANCE.md`.