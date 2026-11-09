# Testing

| Test category | Count | Platform | Result | Evidence |
|---|---:|---|---|---|
| Self-contained CTest tests | 2 | MSVC host | PASS | `test_morton`, `test_voxel`. |
| Preserved test sources | 11 | Repository | PRESERVED | Non-product dependencies are not enabled. |
| Hardware tests | 0 | ESP32-S3 | NOT TESTED | HW NOT VERIFIED. |

Reproduce with `cmake -S . -B build -DLOCADEX_BUILD_TESTS=ON`,
`cmake --build build --config Release`, and
`ctest --test-dir build --output-on-failure -C Release`.

Known gap: MCU footprint, stack use and execution-cycle measurements are not
available.
