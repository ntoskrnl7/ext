# version

[Back to API reference](README.md)

## Header

`#include <ext/version>`

[Semantic Versioning](https://semver.org/)

## Overview

Represents SemVer-style version numbers with major, minor, patch, prerelease, and build metadata fields. Tests cover invalid parsing, hashing, comparisons, updates, and formatting.

## Key APIs

- `ext::version` parses version strings and exposes numeric components.
- Comparison operators order versions by their parsed fields.
- Hash support allows use in hashed containers.
- `major()`, `minor()`, `patch()`, `prerelease()`, `build_metadata()`, `release()`, and `str()` expose or mutate version state.

## Behavior Notes

- Invalid version strings throw `std::invalid_argument`.
- Build metadata is intentionally excluded from equality/hash semantics through `str(false)`.
- Full prerelease ordering is not implemented; comparison only distinguishes prerelease from released versions when major/minor/patch match.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2010+
- **std::regex** required

## Examples

- Basic

  ```C++
  ext::version v("a.b.c"); // std::invalid_argument

  ext::version v("0.0.4");
  v.major(); // 0
  v.minor(); // 0
  v.patch(); // 4
  v.released(); // true
  v.prerelease(); // ""
  v.build_metadata(); // ""

  ext::version v("1.1.2-prerelease+meta");
  v.major(); // 1
  v.minor(); // 1
  v.patch(); // 2
  v.released(); // false
  v.prerelease(); // "prerelease"
  v.build_metadata(); // "meta"
  ```

- std::hash

  ```C++
  std::unordered_map<ext::version, std::string> map = {
    {ext::version("1.2.3"), "abc"},
    {ext::version("5.0.0"), "def"},
    {ext::version("1.2.3-prerelease"), "ghi"},
  };

  auto it = map.find(ext::version("1.2.3"));
  EXPECT_EQ(it->second, "abc");

  it = map.find(ext::version("5.0.0"));
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->second, "def");

  it = map.find(ext::version("1.2.0"));
  EXPECT_EQ(it, map.end());

  it = map.find(ext::version("1.2.3-prerelease"));
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->second, "ghi");

  it = map.find(ext::version("1.2.3-prerelease+meta"));
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->second, "ghi");

  it = map.find(ext::version("1.2.3-test+meta"));
  EXPECT_EQ(it, map.end());
  ```
