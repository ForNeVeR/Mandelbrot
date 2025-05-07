<!--
SPDX-FileCopyrightText: 2024-2025 Friedrich von Never <friedrich@fornever.me>

SPDX-License-Identifier: MIT
-->

Maintainer Guide
================

Release
-------
To release a new version:
1. Update the project status in the `README.md`, if required.
2. Choose a new version according to [Semantic Versioning][semver]. It should consist of three numbers (i.e. `1.0.0`).
3. Make sure there's a properly formed version entry in the `CHANGELOG.md`.
4. Update the `version` field in the `cargo.toml` file.
5. Merge the aforementioned changes via a pull request.
6. Push a tag named `v<VERSION>` to GitHub.

The new release for all three supported operating systems will be published automatically.

[semver]: https://semver.org/spec/v2.0.0.html
