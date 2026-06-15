# string

[Back to API reference](README.md)

## Header

`#include <ext/string>`

## Overview

Collects helpers under `ext::string` for common string transformations and compatibility behavior. It also provides optional movable string aliases and a `u8string` fallback for compilers without native `char8_t` support.

## Key APIs

- `printable`, `lprintable`, and `rprintable` remove non-printable characters.
- `trim`, `ltrim`, and `rtrim` remove whitespace from strings.
- `replace_all`, `split`, `starts_with`, `equal`, and search helpers cover common text operations.
- `stoul` and `stoull` provide unsigned numeric parsing compatibility.
- `to_u8string`, `from_u8`, and `from_u8string` bridge UTF-8 string types.

## Behavior Notes

- Most helpers are templated for `char` and `wchar_t` string types.
- In-place overloads mutate the supplied string and const/input overloads return transformed copies.
- The `ext::u8string` fallback uses `unsigned char` storage when native `std::u8string` is unavailable.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- split

  ```C++
  std::vector<std::string> list = ext::split("a,b,c,d", ",");
  // list == {"a", "b", "c", "d"}
  ```

- u8string

  ```C++
  #define CXX_USE_STD_U8STRING
  #include <ext/string>

  #if defined(CXX_STD_U8STRING_NOT_SUPPORTED)
  #if defined(__cpp_user_defined_literals) &&                                    \
      (CXX_VER >= __cpp_user_defined_literals)
    std::u8string str = ext::from_u8(u8"한글+english");
    // str contains UTF-8 bytes for "한글+english".
  #else
    std::u8string str = ext::from_u8(ext::to_u8string(L"한글+english"));
    // str contains UTF-8 bytes for "한글+english".
  #endif
  #else
    std::u8string str = u8"한글+english";
    // str contains UTF-8 bytes for "한글+english".
  #endif
  ```
