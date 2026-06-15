# path

[Back to API reference](README.md)

## Header

`#include <ext/path>`

## Overview

Adds cross-platform string and wide-string path helpers. Tests cover Windows-style and POSIX-style relative markers, existence checks, dirname/basename behavior, and multiple join cases.

## Key APIs

- `ext::path::basename(path)` and `dirname(path)` split the final component from its parent directory.
- `ext::path::exists(path)` checks whether a path exists.
- `ext::path::is_relative(path)` recognizes `./name`, `../name`, `.\name`, and `..\name` as relative path forms.
- `ext::path::join(base, child, ...)` joins path components while preserving platform-style separators.

## Behavior Notes

- Both `std::string` and `std::wstring` path overloads are supported where the platform API allows it.
- A bare `.` or `..` is not considered a relative path by `is_relative`; the tests require an actual child component.
- Absolute child paths replace earlier base components in join behavior.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

```C++
#include <ext/path>

ext::path::join("aaa", "bbb", "ccc"); // aaa/bbb/ccc
ext::path::is_relative("./test"); // true
ext::path::is_relative("/test"); // false
ext::path::exists("/test");
```
