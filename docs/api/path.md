# path

[Back to API reference](README.md)

## Header

`#include <ext/path>`

## Overview

Adds cross-platform string and wide-string path helpers. Tests cover Windows-style and POSIX-style relative markers, existence checks, dirname/basename behavior, and multiple join cases.

## Key APIs

- `ext::path::seperator<char>()` and `seperator<wchar_t>()` return the platform
  path separator. The misspelled name is the current public API.
- `ext::path::basename(path)` and `dirname(path)` split the final component from its parent directory.
- `ext::path::exists(path)` checks whether a path exists.
- `ext::path::is_relative(path)` recognizes `./name`, `../name`, `.\name`, and `..\name` as relative path forms.
- `ext::path::join(base, child, ...)` joins path components while applying
  `./` and `../` segments.
- Overloads exist for `const CharT *` and `std::basic_string<CharT>`.
- Variadic `join` is used when the compiler supports variadic templates and
  `std::index_sequence`; otherwise overloads are provided up to four child
  arguments.

## Behavior Notes

- Both `std::string` and `std::wstring` path overloads are supported where the platform API allows it.
- A bare `.` or `..` is not considered a relative path by `is_relative`; the tests require an actual child component.
- `basename` and `dirname` return an empty string when the input has no platform
  separator.
- `join` treats `./` as current-directory noise and `../` as a request to move
  the accumulated path to its dirname before appending the remaining child path.
- `join` does not perform filesystem canonicalization, symlink resolution, or
  absolute-path security checks. It is string manipulation.
- On non-Windows platforms, wide-path `exists` converts through the string
  conversion helper before calling `stat`.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

```C++
#include <ext/path>

ext::path::seperator<char>(); // '/' on POSIX, '\\' on Windows

ext::path::basename("/aaa/bbb/file.txt"); // "file.txt"
ext::path::dirname("/aaa/bbb/file.txt"); // "/aaa/bbb"

ext::path::join("aaa", "bbb", "ccc"); // "aaa/bbb/ccc" on POSIX
ext::path::join("aaa/bbb", "../ccc"); // "aaa/ccc" on POSIX

ext::path::is_relative("./test"); // true
ext::path::is_relative("../test"); // true
ext::path::is_relative("/test"); // false
ext::path::exists("/test"); // platform filesystem check
```
