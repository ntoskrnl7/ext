# string

[Back to API reference](README.md)

## Header

`#include <ext/string>`

## Overview

Collects helpers under `ext::string` for common string transformations and compatibility behavior. It also provides optional movable string aliases and a `u8string` fallback for compilers without native `char8_t` support.

## Key APIs

- `ext::string::printable`, `lprintable`, and `rprintable` remove
  non-printable characters from the whole string, left edge, or right edge.
- `ext::string::trim`, `ltrim`, and `rtrim` remove whitespace from the whole
  string, left edge, or right edge.
- `ext::string::search(text, needle, case_sensitive)` returns whether a needle
  appears in text. Matching is ASCII case-insensitive by default.
- `ext::string::starts_with(text, prefix, case_sensitive)` checks a prefix.
- `ext::string::equal(lhs, rhs, case_sensitive)` compares full strings.
- `ext::string::replace_all(text, old, replacement, case_sensitive)` replaces
  every occurrence of a string.
- `ext::string::split(text, delimiter)` returns non-empty string tokens.
- `ext::string::split<T>(text, delimiter, converter)` maps non-empty tokens
  through a converter callback.
- `ext::string::back(text)` returns the last character or zero for an empty
  string.
- `ext::string::convert(src, dst, locale)` converts between `std::string` and
  `std::wstring`.
- `ext::string::convert<DstChar>(src, locale)` returns a converted string or
  throws when exceptions are enabled.
- `operator!(std::string)` and `operator!(std::wstring)` are shorthand
  conversions between narrow and wide strings.
- `ext::from_u8`, `from_u8string`, and `to_u8string` bridge UTF-8 string types
  when `CXX_USE_STD_U8STRING` or native `std::u8string` support is available.
- `ext::string::basic_string<T>` derives from `std::basic_string<T>` for legacy
  movable-string compatibility when that compatibility path is enabled.

## Behavior Notes

- Most helpers are templated for `char` and `wchar_t` string types.
- In-place overloads mutate the supplied string and return a reference to it.
  `const std::basic_string<T>`, pointer, and rvalue overloads return
  transformed copies where supported by the compiler.
- The `ext::u8string` fallback uses `unsigned char` storage when native `std::u8string` is unavailable.
- `search`, `starts_with`, `equal`, and `replace_all` are ASCII
  case-insensitive by default. Pass `true` for case-sensitive matching.
- `split` skips empty tokens. For example, splitting `"a,,b"` by `","` returns
  `{"a", "b"}`.
- `convert` uses `std::codecvt` with the provided locale. Conversion behavior
  therefore depends on the platform locale and standard-library support.
- `from_u8string(..., ignore_errors)` currently substitutes invalid UTF-8
  sequences with a replacement character in the wide conversion path.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- Text cleanup and matching

  ```C++
  #include <ext/string>

  std::string text = "\tHello\n";
  ext::trim(text); // "Hello"

  ext::search("Hello world", "WORLD"); // true
  ext::search("Hello world", "WORLD", true); // false
  ext::starts_with("Hello", "he"); // true
  ext::equal("Value", "value"); // true
  ```

- replace and split

  ```C++
  #include <ext/string>

  std::string text = "one two one";
  ext::replace_all(text, "one", "1");
  // text == "1 two 1"

  std::vector<std::string> list = ext::split("a,b,,c,d", ",");
  // list == {"a", "b", "c", "d"}

  std::vector<int> numbers =
      ext::split<int>("1|2|3", "|", [](const std::string &s) {
        return std::stoi(s);
      });
  ```

- narrow/wide conversion

  ```C++
  #include <ext/string>

  std::wstring wide = ext::string::convert<wchar_t>(std::string("text"));
  std::string narrow = ext::string::convert<char>(wide);

  std::wstring wide2 = !std::string("text");
  std::string narrow2 = !wide2;
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
