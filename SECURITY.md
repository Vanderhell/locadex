# Security policy

Report suspected vulnerabilities privately to the repository maintainers
through GitHub's security reporting feature. Include affected operations,
inputs, impact and a minimal reproducer where possible. Avoid publishing
exploit details before maintainers have had an opportunity to investigate.

Locadex validates bounded integer coordinate inputs but cannot validate the
meaning or trustworthiness of application data. Applications must check
boolean return values and preserve caller-owned buffer lifetimes.
