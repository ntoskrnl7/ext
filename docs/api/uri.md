# uri

[Back to API reference](README.md)

## Header

`#include <ext/uri>`

## Overview

Parses URI strings into scheme, host, port, path, query, and fragment fields and provides URI/component percent-encoding helpers. Tests cover invalid URIs, literals, query maps, and encoding.

## Key APIs

- `ext::basic_uri<CharT>` stores parsed URI components and the original value.
- `ext::uri` and `ext::wuri` are narrow and wide aliases.
- `encode_uri<CharT>(u8_string)` preserves reserved URI characters while escaping others.
- `encode_uri_component<CharT>(u8_string)` escapes reserved characters for component values.
- Constructors can append query maps to an existing URI.

## Behavior Notes

- A URI without `://` is considered invalid and clears `value`.
- Scheme and host are normalized to lowercase during parsing.
- Query strings are stored with the leading `?` when present.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- uri

  ```C++
  ext::uri u("https://localhost:8443/test");
  // u.scheme == "https"
  // u.host == "localhost"
  // u.port == 8443
  // u.path == "/test"
  // u.scheme_host_port() == "https://localhost:8443"

  u = ext::uri("foo://info.example.com?fred");
  // u.scheme == "foo"
  // u.host == "info.example.com"
  // u.path.empty() == true
  // u.query == "?fred"
  ```

- wuri

  ```C++
  ext::wuri u(L"https://localhost:8443/test");
  // u.scheme == L"https"
  // u.host == L"localhost"
  // u.port == 8443
  // u.path == L"/test"
  // u.scheme_host_port() == L"https://localhost:8443"

  u = ext::wuri(L"foo://info.example.com?fred");
  // u.scheme == L"foo"
  // u.host == L"info.example.com"
  // u.path.empty() == true
  // u.query == L"?fred"
  ```

- User-defined literals

  ```C++
  #include <ext/uri>

  using namespace ext::literals;

  ext::uri u = "http://test.com:1234/test?key=value&key1=value1"_uri;
  ext::wuri u = L"http://test.com:1234/test?key=value&key1=value1"_uri;
  ```

- encode

  ```C++
  #define CXX_USE_STD_U8STRING
  #include <ext/uri>

  #if defined(CXX_STD_U8STRING_NOT_SUPPORTED)
  #if defined(__cpp_user_defined_literals) &&                                    \
    (CXX_VER >= __cpp_user_defined_literals)
    const std::u8string uri_u8str = ext::from_u8(u8"https://www.google.com/search?q=한글+english");
  #else
    const std::u8string uri_u8str =ext::to_u8string(L"https://www.google.com/search?q=한글+english");
  #endif
  #else
    const std::u8string uri_u8str = u8"https://www.google.com/search?q=한글+english";
  #endif
    ext::uri u(uri_u8str);
    ext::wuri u(uri_u8str);
  ```
