# Performance and footprint

Measured on an ESP32-S3 v0.2 (240 MHz), Arduino ESP32 core 3.3.10, `esp32:esp32:ozobot_drvkit`. Each cycle figure is the integer average of 20,000 successful calls using varying inputs. The cycle counter wraps using unsigned subtraction. Figures include loop and call overhead and are one measurement on this build, not portable guarantees.

| Operation | Observed cycles/call |
|---|---:|
| `pc_grid_direction8_i32` | 54 |
| `pc_morton3_encode_u32` | 123 |
| `pc_morton3_decode_u32` | 161 |
| `pc_voxel_index_3d_u32` | 154 |
| `pc_voxel_coords_3d_u32` | 409 |

Arduino CLI reported 290,529 bytes program storage (9% of 3,145,728 bytes) and 21,756 bytes global variables (6% of 327,680 bytes). These are whole test-firmware values and include Arduino runtime and harness, not isolated library footprint.

The final linker map attributes 644 bytes of `.text` and 8 bytes of `.literal` (652 bytes total) to the five LOCADEX translation units. Their objects contain 0 bytes `.data` and `.bss`, so the isolated static RAM contribution is 0 bytes; this excludes caller stack. The 64-bit divide/remainder helpers used by voxel coordinate decoding resolve to ESP32-S3 ROM addresses (`0x40002544`, `0x40002574`), not additional application flash. These are measurements from this test firmware/profile, not universal guarantees. Stack high-water usage was not measured.