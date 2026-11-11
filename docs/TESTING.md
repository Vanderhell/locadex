# Testing and validation

## Automated coverage

CTest registers three executables: preserved Morton and voxel contract tests plus `test_api_audit.c`. The audit test uses explicit `CHECK` conditions, not `assert`, and is active in Release. Independent references are a bit-at-a-time Morton model, `atan2`/`floor` direction quantization, and widened formula/quotient-remainder voxel models.

Coverage includes all 8 direction codes, vectors on both sides of each angular boundary, zero/null/failure output preservation, `INT32_MIN`/`INT32_MAX`, every pair of aliased coordinate outputs, Morton coordinate edges 0/1/2/511/512/1022/1023, high-bit rejection, round trips, exhaustive small voxel grids, 2^32-cell maximum legal capacity, invalid dimensions/coordinates/indexes, and volume overflow.

Each API receives at least 100,000 fixed-seed generated cases: direction full-range vectors; Morton encode triples and decode codes; voxel index valid shapes/coordinates; voxel coords varied valid shapes and maximum-volume indices. Some operations receive additional generated or exhaustive-small-domain checks. Full input-space enumeration is not feasible for the 30-bit Morton and 32-bit voxel domains.

## Host results

| Toolchain/configuration | Result |
|---|---|
| GCC 13.3.0, C99 strict warnings, Debug | PASS, 3/3 |
| GCC 13.3.0, C99 strict warnings, Release | PASS, 3/3 |
| Clang 18.1.3, C99 strict warnings, Debug | PASS, 3/3 |
| Clang 18.1.3, C99 strict warnings, Release | PASS, 3/3 |
| MSVC 19.42.34444, `/W4 /WX`, Debug | PASS, 3/3 |
| MSVC 19.42.34444, `/W4 /WX`, Release | PASS, 3/3 |
| GCC AddressSanitizer | PASS, 3/3 |
| GCC UndefinedBehaviorSanitizer | PASS, 3/3 |
| GitHub Actions | NOT RUN until push |

Reproduce host tests with:

```sh
cmake -S . -B build -DLOCADEX_BUILD_TESTS=ON -DLOCADEX_STRICT_WARNINGS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure -C Release
```

Sanitizer configurations use GCC with `-fsanitize=address` or `-fsanitize=undefined -fno-sanitize-recover=all`, plus `-fno-omit-frame-pointer`.

## Hardware

ESP32-S3 v0.2 test on the Ozobot DRVKit profile (Arduino ESP32 core 3.3.10, 240 MHz): all five APIs passed the independent expected-value checks and the firmware emitted `LOCADEX_ALL5_PASS`. Per-operation cycle readings, build footprint and their limits are in `PERFORMANCE.md`.