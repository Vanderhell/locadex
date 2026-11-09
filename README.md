# locadex

Locadex is a standalone C99 spatial-indexing library for deterministic grid coordinates, neighborhoods, Morton-style mappings and bounded spatial transforms.

## Scope

The package contains 17 public headers and 5 implementation units. It is portable C99, uses no mandatory heap or operating-system service, and keeps caller-owned state explicit where applicable.

## Build and test

```sh
cmake -S . -B build -DLOCADEX_BUILD_TESTS=ON
cmake --build build --config Release
ctest --test-dir build --output-on-failure -C Release
```

## Validation status

Host validation is run during extraction. ESP32-S3 validation and isolated footprint measurements are pending unless explicitly recorded; no hardware result is claimed.

## Architecture and integration

Coordinate, grid and Morton operations are isolated C99 translation units with
fixed-width data and explicit outputs. Link `locadex` through CMake or compile
selected files from `src/` with headers from `include/`.

## API, configuration and dependencies

Public headers are under `include/locadex/spatial`. `LOCADEX_BUILD_TESTS`
controls host tests. No heap, OS, thread or third-party dependency is required;
coordinate bounds and invalid-input behavior are specified in each header.

## Resource, performance and limitations

The enabled host suite passes 2/2 tests. Embedded flash, RAM, stack and cycle
measurements are `PENDING`; HW NOT VERIFIED. Do not use coordinate encodings as
security mechanisms.

## Version, license and origin

The product is independently versioned with semantic-versioning intent before
1.0. Apache License 2.0, copyright Vanderhell. It is self-contained and was
maintained as a self-contained library.

## Name and origin

Locadex combines locus (place) with index, reflecting compact deterministic coordinate and grid indexing.
Its technical scope is spatial indexing, grids and coordinate transforms.

## License

Apache License 2.0, copyright Vanderhell. See LICENSE and NOTICE.
