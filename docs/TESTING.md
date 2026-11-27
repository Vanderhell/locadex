# Testing and validation

## Coverage

All five public functions have direct enabled tests. CTest registers three
behavior programs (`test_api_audit`, `test_morton`, `test_voxel`), five
independent C public-header builds and one C++ aggregate-header/link smoke
test: nine entries total. Test checks remain active in Release; the API audit
uses explicit `CHECK` conditions; the two retained assertion-based test
sources undefine `NDEBUG` themselves.

The API audit executes at least 100,000 deterministic cases for every
operation. Its references use per-bit Morton placement/extraction,
`atan2`/`floor` direction quantization and independently expressed widened
row-major/quotient-remainder voxel formulas. It also includes boundary tests,
round trips, output preservation, alias rejection and exhaustive small-grid
checks. These finite tests do not enumerate the full integer domains.

## Reproduce

```sh
cmake -S . -B build -DLOCADEX_BUILD_TESTS=ON -DLOCADEX_STRICT_WARNINGS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure

cmake -S . -B build-release -DLOCADEX_BUILD_TESTS=ON -DLOCADEX_STRICT_WARNINGS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build-release --parallel
ctest --test-dir build-release --output-on-failure
```

GitHub Actions runs GCC and Clang in Debug and Release, separate GCC ASan and
UBSan jobs, and MSVC Debug and Release. Current-commit remote results must be
checked after push.

## Current local results

Executed on 2026-11-28 against the namespaced tree with strict warnings:

| Toolchain/configuration | Result |
|---|---|
| GCC 16.1.0 MinGW UCRT Debug | PASS, 9/9 |
| GCC 16.1.0 MinGW UCRT Release | PASS, 9/9 |
| MSVC 19.42.34444 Debug | PASS, 9/9 |
| MSVC 19.42.34444 Release | PASS, 9/9 |
| ClangCL 19.1.5 Debug | PASS, 9/9 |
| ClangCL 19.1.5 Release | PASS, 9/9 |
| Linux GCC/Clang, ASan and UBSan on this revision | Pending remote CI |

Earlier CI run `42978119057` passed eight jobs for the pre-productization
revision. It is historical and does not substitute for the current commit's
workflow.

## ESP32-S3

Historical ESP32-S3 firmware called all five pre-namespace functions, checked
independent expected values and emitted `LOCADEX_ALL5_PASS`. The normalized
implementation comparison found that namespacing changed no algorithm body.
No new current-revision firmware was flashed or executed. Current hardware
status is **HW NOT VERIFIED**. Historical cycle and size measurements are
summarized in [PERFORMANCE.md](PERFORMANCE.md).
