# uri

[Back to API reference](README.md)

## Header

`#include <ext/uri>`

## Overview

Parses simple absolute URI strings into scheme, host, port, path, and query
fields and provides URI/component percent-encoding helpers. Tests cover invalid
URIs, literals, query maps, and UTF-8 encoding.

## Key APIs

- `ext::basic_uri<CharT>` stores parsed URI components and the original value.
- `ext::uri` and `ext::wuri` are narrow and wide aliases.
- `ext::encode_uri<CharT>(u8_string)` preserves RFC 3986 reserved characters
  while escaping other bytes.
- `ext::encode_uri_component<CharT>(u8_string)` escapes reserved characters for
  component values.
- `basic_uri(uri_string)` parses a string containing `://`.
- `basic_uri(uri_string, query_map)` appends query parameters to the value.
- `basic_uri(std::u8string)` and `basic_uri(std::u8string, u8query_map)` are
  available when UTF-8 string support is enabled.
- `scheme_host_port()` returns the URI prefix through the authority/port section.
- `valid()` reports whether parsing produced a non-empty value.
- `operator const string_type &()` exposes the stored URI string.
- `basic_uri::encode_component(u8_string)` is a static component-encoding
  convenience wrapper.
- `ext::literals::operator"" _uri` creates `uri` or `wuri` from string
  literals when user-defined literals are supported.

## Behavior Notes

- A URI without `://` is considered invalid and clears `value`.
- Scheme and host are normalized to lowercase during parsing. Path and query are
  kept as provided.
- The parser recognizes a port only when the authority contains `:port`.
- Query strings are stored with the leading `?` when present. Query maps append
  `?key=value&...` to the stored value.
- The `fragment` field exists but the parser does not currently split `#...`
  into it.
- The parser is intentionally lightweight. It does not validate every RFC 3986
  grammar rule, does not decode percent-encoded input, and does not parse user
  info or IPv6 authority forms as separate fields.
- `encode_uri` and `encode_uri_component` operate on bytes from the supplied
  UTF-8-like string. They emit uppercase percent escapes.
- Query map constructors append keys and values as provided for `std::string`
  and `std::wstring` maps. Encode keys and values first when component escaping
  is required.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- uri

  ```C++
  #include <ext/uri>

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

- query map

  ```C++
  #include <ext/uri>

  ext::uri::query_map query = {
    {"q", ext::uri::encode_component("hello world")},
    {"page", "1"},
  };

  ext::uri u("https://example.com/search", query);
  // u.value == "https://example.com/search?page=1&q=hello%20world"
  ```

- wuri

  ```C++
  #include <ext/uri>

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

  ext::uri narrow = "http://test.com:1234/test?key=value&key1=value1"_uri;
  ext::wuri wide = L"http://test.com:1234/test?key=value&key1=value1"_uri;
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
    const std::u8string uri_u8str =
        ext::to_u8string(L"https://www.google.com/search?q=한글+english");
  #endif
  #else
    const std::u8string uri_u8str = u8"https://www.google.com/search?q=한글+english";
  #endif
    ext::uri narrow(uri_u8str);
    ext::wuri wide(uri_u8str);

    ext::uri::encode_component("a b+c");
    // "a%20b%2Bc"
  ```
