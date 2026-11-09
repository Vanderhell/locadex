# locadex

Locadex is a standalone C99 spatial-indexing library for deterministic grid coordinates, neighborhoods, Morton-style mappings and bounded spatial transforms.

## Scope

This first extraction contains 17 family headers, 5 implementation units and 11 migrated test sources. It is portable C99, uses no mandatory heap or operating-system service, and keeps caller-owned state explicit where applicable.

## Build and test

```sh
cmake -S . -B build -DLOCADEX_BUILD_TESTS=ON
cmake --build build --config Release
ctest --test-dir build --output-on-failure -C Release
```

## Validation status

Host validation is run during extraction. ESP32-S3 validation and isolated footprint measurements are pending unless explicitly recorded; no hardware result is claimed.

## Name and origin

Locadex combines locus (place) with index, reflecting compact deterministic coordinate and grid indexing.
It originates from PrimitiveCore's spatial/indexing_and_grids family.

## License

Apache License 2.0, copyright Vanderhell. See LICENSE and NOTICE.
