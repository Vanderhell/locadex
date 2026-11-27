# Changelog

## 0.2.0

- Public callable names and header paths now use the `locadex_` namespace and
  `locadex/spatial/` include path. This breaks source compatibility with
  0.1.0; update include paths and symbol names when migrating.
- Added a namespaced CMake target, install/export package, opt-in tests and
  examples, standalone C header checks, C++ header smoke test and strict GCC,
  Clang, sanitizer and MSVC CI jobs.
- No production algorithm changed during this migration.
