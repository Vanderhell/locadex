# Contributing

Keep changes focused on correctness, C99 portability, API contracts and
documentation accuracy. Preserve existing mathematical behavior unless a
defect can be independently reproduced.

Before submitting, build and run CTest in Debug and Release with strict
warnings enabled. Add deterministic boundary tests and an independent oracle
or invariant for behavior changes. Test checks must remain active in Release.

Production code must not require heap allocation, an operating system,
threads or external libraries. Keep build flags local to Locadex targets.
Record the target and method for hardware or performance evidence.
