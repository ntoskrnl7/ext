# uri

[Back to API reference](README.md)

## Header

`#include <ext/uri>`

## Overview

Parses hierarchical URI strings into scheme, user info, host, port, path, query,
and fragment fields and provides URI/component percent-encoding helpers. Tests
cover invalid URIs, literals, query maps, fragments, IPv6 literals, relative
resolution, and UTF-8 encoding.

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
- `query_params()` parses `query` into a decoded `query_map`.
- `resolve(base, reference)` resolves a relative reference against a base URI.
- `remove_dot_segments(path)` applies RFC 3986 dot-segment path cleanup.
- `valid()` reports whether parsing produced a non-empty value.
- `operator const string_type &()` exposes the stored URI string.
- `basic_uri::encode_component(u8_string)` is a static component-encoding
  convenience wrapper.
- `basic_uri::decode_component(encoded)` decodes percent escapes in a component.
- `ext::literals::operator"" _uri` creates `uri` or `wuri` from string
  literals when user-defined literals are supported.

## Behavior Notes

- A URI without `://` is considered invalid and clears `value`.
- Scheme and host are normalized to lowercase during parsing. User info, path,
  query, and fragment are kept as provided.
- `userinfo@host` is split into `userinfo` and `host`.
- IPv6 host literals must use bracket form such as `[2001:db8::1]`. The parsed
  `host` field stores the address without brackets.
- Ports must be decimal, fully consumed, and in the range `0..65535`; malformed
  ports make the URI invalid.
- Query strings are stored with the leading `?` when present. Query maps append
  percent-encoded `?key=value&...` pairs to the stored value before any
  fragment.
- `query_params()` decodes percent escapes and stores duplicate keys using
  `std::map` semantics, so later duplicate keys overwrite earlier ones.
- Fragment strings are stored with the leading `#` when present.
- Relative references are resolved with RFC 3986-style path merging and
  dot-segment cleanup. The constructor still requires a hierarchical absolute
  URI containing `://`; use `resolve()` for relative references.
- The parser validates common authority and port errors, but it does not enforce
  every RFC 3986 grammar rule and does not implement non-hierarchical schemes
  such as `mailto:`.
- `encode_uri` and `encode_uri_component` operate on bytes from the supplied
  UTF-8-like string. They emit uppercase percent escapes.
- `decode_component` reverses percent escapes byte-by-byte. It does not perform
  UTF-8 transcoding for wide strings.

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
  // u.userinfo.empty() == true
  // u.host == "localhost"
  // u.port == 8443
  // u.path == "/test"
  // u.scheme_host_port() == "https://localhost:8443"

  u = ext::uri("https://User:Pass@EXAMPLE.com:8443/test");
  // u.userinfo == "User:Pass"
  // u.host == "example.com"

  u = ext::uri("https://[2001:DB8::1]:443/test");
  // u.host == "2001:db8::1"
  // u.port == 443

  u = ext::uri("foo://info.example.com?fred");
  // u.scheme == "foo"
  // u.host == "info.example.com"
  // u.path.empty() == true
  // u.query == "?fred"

  u = ext::uri("https://example.com/path?key=value#section-1");
  // u.path == "/path"
  // u.query == "?key=value"
  // u.fragment == "#section-1"
  ```

- query map

  ```C++
  #include <ext/uri>

  ext::uri::query_map query = {
    {"q", "hello world"},
    {"a+b", "c&d"},
    {"page", "1"},
  };

  ext::uri u("https://example.com/search#results", query);
  // u.value == "https://example.com/search?a%2Bb=c%26d&page=1&q=hello%20world#results"

  ext::uri parsed("https://example.com/search?q=hello%20world&a%2Bb=c%26d");
  ext::uri::query_map params = parsed.query_params();
  // params["q"] == "hello world"
  // params["a+b"] == "c&d"
  ```

- relative references

  ```C++
  #include <ext/uri>

  ext::uri base("https://User@example.com/a/b/c?x=1#old");
  ext::uri resolved = base.resolve("../d/./e?y=2#new");
  // resolved.value == "https://User@example.com/a/d/e?y=2#new"

  ext::uri::remove_dot_segments("/a/b/../c/./");
  // "/a/c/"
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

    ext::uri::decode_component("a%20b%2Bc");
    // "a b+c"
  ```
