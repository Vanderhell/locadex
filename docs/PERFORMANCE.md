# Performance and footprint

## Historical ESP32-S3 measurements

The figures below are from the pre-namespace implementation on ESP32-S3 v0.2
at 240 MHz, Arduino ESP32 core 3.3.10, Ozobot DRVKit profile. The benchmark
made 20,000 successful calls with varying inputs. Cycle values are integer
averages for that run and include loop and call overhead; they are not
isolated function costs, medians, portable guarantees or WCET bounds.

| Operation | Historical cycles/call |
|---|---:|
| `locadex_grid_direction8_i32` | 54 |
| `locadex_morton3_encode_u32` | 123 |
| `locadex_morton3_decode_u32` | 161 |
| `locadex_voxel_index_3d_u32` | 154 |
| `locadex_voxel_coords_3d_u32` | 409 |

The source migration changed public identifiers and paths only. A normalized
comparison found the five implementation bodies unchanged. These timings
therefore remain useful historical measurements, but were not remeasured on
the current revision.

## Flash and RAM

Historical linker-map and firmware results:

- Five Locadex translation units contributed **644 bytes** of `.text` and
  **8 bytes** of `.literal` (652 bytes total) in the recorded build.
- Their objects had **0 bytes** of `.data` and `.bss`; this excludes caller
  stack and application-owned buffers.
- The complete test firmware used **290,529 bytes** of program storage and
  **21,756 bytes** of global variables. These whole-firmware totals include
  Arduino runtime and harness; they are not library footprint.
- The 64-bit division/remainder helpers used by voxel decoding resolved to
  ESP32-S3 ROM addresses in that build, adding no application flash there.
- Stack high-water usage was not measured.

Current-revision cycle counts, isolated footprint and stack usage are **NOT
MEASURED**. Results depend on selected operations, compiler, optimization,
target and workload; remeasure for deployment decisions.
