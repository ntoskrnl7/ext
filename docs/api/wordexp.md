# wordexp

[Back to API reference](README.md)

## Header

`#include <ext/wordexp>`

Expands environment-variable strings and replaces them with the values defined for the current user.

## Overview

Provides a small helper for expanding a string through platform facilities. On Windows it uses `ExpandEnvironmentStringsA`; on POSIX it uses `wordexp` and returns the first expanded word.

## Key APIs

- `ext::wordexp(input)` returns the expanded string.
- Windows expands environment-variable expressions supported by `ExpandEnvironmentStringsA`.
- POSIX uses `::wordexp` and returns an empty string if expansion fails.

## Behavior Notes

- Expansion rules are platform-dependent.
- Avoid passing untrusted input to POSIX shell-style expansion workflows.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

```C++
#if defined(_WIN32)
  std::string system_drive = ext::wordexp("%SYSTEMDRIVE%");
  std::string windir = ext::wordexp("%WINDIR%");
  std::string user_profile = ext::wordexp("%USERPROFILE%");
  std::string user_name = ext::wordexp("%USERNAME%");
#else
  std::string home_path = ext::wordexp("$HOME");
  std::string user = ext::wordexp("$USER");
#endif
```

---
