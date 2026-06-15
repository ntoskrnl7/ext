# version

[Back to API reference](README.md)

## Header

`#include <ext/version>`

[Semantic Versioning](https://semver.org/)

## Overview

Represents SemVer-style version numbers with major, minor, patch, prerelease, and build metadata fields. Tests cover invalid parsing, hashing, comparisons, updates, and formatting.

## Key APIs

- `ext::version` parses version strings and exposes numeric components.
- Comparison operators order versions by major, minor, patch, and SemVer
  prerelease precedence.
- Hash support allows use in hashed containers.
- `major()`, `minor()`, `patch()`, `prerelease()`, `build_metadata()`, `release()`, and `str()` expose or mutate version state.

## Behavior Notes

- Invalid version strings throw `std::invalid_argument`.
- Build metadata is intentionally excluded from precedence, equality, and hash
  semantics through `str(false)`.
- Prerelease comparison follows SemVer item 11: dot-separated numeric
  identifiers compare numerically, numeric identifiers sort before non-numeric
  identifiers, and a release version has higher precedence than a prerelease
  version with the same major, minor, and patch.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2010+
- **std::regex** required

## Examples

- Basic

  ```C++
  try {
    ext::version invalid("a.b.c");
  } catch (const std::invalid_argument &) {
    // Invalid version strings throw.
  }

  ext::version stable("0.0.4");
  stable.major(); // 0
  stable.minor(); // 0
  stable.patch(); // 4
  stable.released(); // true
  stable.prerelease(); // ""
  stable.build_metadata(); // ""

  ext::version prerelease("1.1.2-prerelease+meta");
  prerelease.major(); // 1
  prerelease.minor(); // 1
  prerelease.patch(); // 2
  prerelease.released(); // false
  prerelease.prerelease(); // "prerelease"
  prerelease.build_metadata(); // "meta"
  ```

- std::hash

  ```C++
  std::unordered_map<ext::version, std::string> map = {
    {ext::version("1.2.3"), "abc"},
    {ext::version("5.0.0"), "def"},
    {ext::version("1.2.3-prerelease"), "ghi"},
  };

  auto it = map.find(ext::version("1.2.3"));
  // it->second == "abc"

  it = map.find(ext::version("5.0.0"));
  // it != map.end()
  // it->second == "def"

  it = map.find(ext::version("1.2.0"));
  // it == map.end()

  it = map.find(ext::version("1.2.3-prerelease"));
  // it != map.end()
  // it->second == "ghi"

  it = map.find(ext::version("1.2.3-prerelease+meta"));
  // it != map.end()
  // it->second == "ghi"

  it = map.find(ext::version("1.2.3-test+meta"));
  // it == map.end()
  ```
