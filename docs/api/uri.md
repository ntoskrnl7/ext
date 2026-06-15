# uri

[Back to API reference](README.md)

## Header

`#include <ext/uri>`

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- uri

  ```C++
  ext::uri u("https://localhost:8443/test");
  EXPECT_STREQ(u.scheme.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "localhost");
  EXPECT_EQ(u.port, 8443);
  EXPECT_STREQ(u.path.c_str(), "/test");
  EXPECT_STREQ(u.scheme_host_port().c_str(), "https://localhost:8443");

  u = ext::uri("foo://info.example.com?fred");
  EXPECT_STREQ(u.scheme.c_str(), "foo");
  EXPECT_STREQ(u.host.c_str(), "info.example.com");
  EXPECT_TRUE(u.path.empty());
  EXPECT_STREQ(u.query.c_str(), "?fred");
  ```

- wuri

  ```C++
  ext::wuri u(L"https://localhost:8443/test");
  EXPECT_STREQ(u.scheme.c_str(), L"https");
  EXPECT_STREQ(u.host.c_str(), L"localhost");
  EXPECT_EQ(u.port, 8443);
  EXPECT_STREQ(u.path.c_str(), L"/test");
  EXPECT_STREQ(u.scheme_host_port().c_str(), L"https://localhost:8443");

  u = ext::wuri(L"foo://info.example.com?fred");
  EXPECT_STREQ(u.scheme.c_str(), L"foo");
  EXPECT_STREQ(u.host.c_str(), L"info.example.com");
  EXPECT_TRUE(u.path.empty());
  EXPECT_STREQ(u.query.c_str(), L"?fred");
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
