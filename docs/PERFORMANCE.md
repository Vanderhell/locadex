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

For the five production translation units, Xtensa ESP32-S3 `size` reported object `.text` sizes of 107, 149, 203, 141, and 239 bytes respectively (sum 839 bytes before final-link placement/relaxation). Each object had 0 bytes `.data` and `.bss`. This object-level accounting is not the same as isolated final linked flash. Stack high-water usage was not measured.