# Architecture

Locadex is a standalone C99 static library of five bounded spatial
operations. Each callable operation has one self-contained public header in
`include/locadex/spatial/` and a separate implementation in `src/`. The
CMake source list is explicit, and the exported target is
`Locadex::Locadex`.

The production library uses fixed-width integer types and does not require
heap allocation, operating-system services, mutable global state or external
libraries. Callers own all input/output storage. Tests and examples are
disabled by default for consumers and use unique Locadex-specific options.

Public contracts specify valid coordinate/code ranges, output preservation,
pointer aliasing and error returns. The validation status and measured limits
are recorded in [TESTING.md](TESTING.md) and [PERFORMANCE.md](PERFORMANCE.md).
