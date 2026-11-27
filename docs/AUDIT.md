# Audit register

## API inventory and results

All five callable C99 APIs have a public header, a separate implementation
unit, and a direct enabled test. They were reviewed against the header
contract for integer ranges, overflow, pointer validation, aliasing,
determinism and output preservation.

| API | Result | Independent evidence |
|---|---|---|
| `locadex_grid_direction8_i32` | OK | `atan2`/`floor` sector reference; all directions, boundary neighborhoods, zero, null output, signed extrema and 100,000 seeded full-range vectors. |
| `locadex_morton3_encode_u32` | OK | Per-bit interleave reference; all coordinate edges and 100,000 seeded triples. |
| `locadex_morton3_decode_u32` | OK | Per-bit extraction reference; boundary codes, upper-bit rejection, aliased output rejection, 100,000 seeded codes and round trips. |
| `locadex_voxel_index_3d_u32` | OK | Independent widened row-major formula, exhaustive small grids, exact 2^32-cell capacity, overflow rejection and 100,000 seeded valid shapes. |
| `locadex_voxel_coords_3d_u32` | OK | Independent quotient/remainder model, exhaustive small grids, output-preservation checks, exact maximum volume and 100,000 seeded indices/shapes. |

`OK` means implementation inspection and recorded tests found no defect. It
does not imply exhaustive enumeration of the full integer domains.

## Findings

- Confirmed production algorithm defects: **0**. No production implementation
  changed in this namespace/build migration.
- The previous `assert`-dependent test issue was corrected before this
  migration; the two assertion-based test sources undefine `NDEBUG`, and the
  audit test uses explicit `CHECK` conditions.
- Non-CMake test files in the checkout referenced other spatial or signal
  primitives, not Locadex implementations. Their exact content and referenced
  symbols were hash-archived internally for ownership reconciliation; they
  are not presented as Locadex API coverage.
- `RISK`: seeded tests and finite-precision `atan2` references are not proofs
  across every possible input. No stronger global accuracy bound is claimed.

The migration changed public names and paths only. A normalized exact text
comparison against the original source files verified all five implementation
bodies unchanged.

## Hardware evidence

A historical ESP32-S3 firmware called all five pre-namespace APIs, checked
independent expected values and emitted `LOCADEX_ALL5_PASS`. Since the
implementation bodies are unchanged, this remains historical evidence; no
new firmware was flashed or executed for this revision. Historical timings
and linker-map data are in [PERFORMANCE.md](PERFORMANCE.md).

Current revision target execution is **NOT VERIFIED**. The 100,000-case host
tests are not full-domain enumeration, and sampled cycle measurements do not
establish worst-case latency.
