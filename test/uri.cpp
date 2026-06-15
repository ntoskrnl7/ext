#define CXX_USE_STD_U8STRING
#include <ext/uri>

#include <gtest/gtest.h>

TEST(uri_test, invalid_uri_test) {
  ext::uri u("");
  EXPECT_STREQ(u.scheme.c_str(), "");
  EXPECT_STREQ(u.host.c_str(), "");
  EXPECT_STREQ(u.path.c_str(), "");
}

TEST(uri_test, invalid_wuri_test) {
  ext::wuri u(L"");
  EXPECT_STREQ(u.scheme.c_str(), L"");
  EXPECT_STREQ(u.host.c_str(), L"");
  EXPECT_STREQ(u.path.c_str(), L"");
}

#if defined(__cpp_user_defined_literals) &&                                    \
    (CXX_VER >= __cpp_user_defined_literals)
TEST(uri_test, uri_literal_test) {
  using namespace ext::literals;

  ext::uri u = "http://test.com:1234/test?key=value&key1=value1"_uri;
  EXPECT_TRUE(u.valid());
  EXPECT_STREQ(u.scheme.c_str(), "http");
  EXPECT_STREQ(u.host.c_str(), "test.com");
  EXPECT_EQ(u.port, 1234);
  EXPECT_STREQ(u.path.c_str(), "/test");
  EXPECT_STREQ(u.query.c_str(), "?key=value&key1=value1");
  EXPECT_STREQ(u.value.c_str(),
               "http://test.com:1234/test?key=value&key1=value1");
}

TEST(uri_test, wuri_literal_test) {
  using namespace ext::literals;

  ext::wuri u = L"http://test.com:1234/test?key=value&key1=value1"_uri;
  EXPECT_TRUE(u.valid());
  EXPECT_STREQ(u.scheme.c_str(), L"http");
  EXPECT_STREQ(u.host.c_str(), L"test.com");
  EXPECT_EQ(u.port, 1234);
  EXPECT_STREQ(u.path.c_str(), L"/test");
  EXPECT_STREQ(u.query.c_str(), L"?key=value&key1=value1");
  EXPECT_STREQ(u.value.c_str(),
               L"http://test.com:1234/test?key=value&key1=value1");
}
#endif // !defined(__cpp_user_defined_literals)

TEST(uri_test, uri_test) {
  ext::uri u("https://google.com/");
  EXPECT_STREQ(u.scheme.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "google.com");
  EXPECT_STREQ(u.path.c_str(), "/");

  u = ext::uri("https://google.com");
  EXPECT_STREQ(u.scheme.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "google.com");
  EXPECT_TRUE(u.path.empty());

  u = ext::uri("https://localhost:8443/test");
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

  u = ext::uri("https://localhost:8443#top");
  EXPECT_STREQ(u.scheme.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "localhost");
  EXPECT_EQ(u.port, 8443);
  EXPECT_TRUE(u.path.empty());
  EXPECT_TRUE(u.query.empty());
  EXPECT_STREQ(u.fragment.c_str(), "#top");
  EXPECT_STREQ(u.scheme_host_port().c_str(), "https://localhost:8443");

  u = ext::uri("https://example.com/path?key=value#section-1");
  EXPECT_STREQ(u.scheme.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "example.com");
  EXPECT_STREQ(u.path.c_str(), "/path");
  EXPECT_STREQ(u.query.c_str(), "?key=value");
  EXPECT_STREQ(u.fragment.c_str(), "#section-1");
  EXPECT_STREQ(u.scheme_host_port().c_str(), "https://example.com");

  u = ext::uri("https://example.com/path#section?not=query");
  EXPECT_STREQ(u.path.c_str(), "/path");
  EXPECT_TRUE(u.query.empty());
  EXPECT_STREQ(u.fragment.c_str(), "#section?not=query");
}

TEST(uri_test, wuri_test) {
  ext::wuri u(L"https://google.com/");
  EXPECT_STREQ(u.scheme.c_str(), L"https");
  EXPECT_STREQ(u.host.c_str(), L"google.com");
  EXPECT_STREQ(u.path.c_str(), L"/");

  u = ext::wuri(L"https://google.com");
  EXPECT_STREQ(u.scheme.c_str(), L"https");
  EXPECT_STREQ(u.host.c_str(), L"google.com");
  EXPECT_TRUE(u.path.empty());

  u = ext::wuri(L"https://localhost:8443/test");
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

  u = ext::wuri(L"https://localhost:8443#top");
  EXPECT_STREQ(u.scheme.c_str(), L"https");
  EXPECT_STREQ(u.host.c_str(), L"localhost");
  EXPECT_EQ(u.port, 8443);
  EXPECT_TRUE(u.path.empty());
  EXPECT_TRUE(u.query.empty());
  EXPECT_STREQ(u.fragment.c_str(), L"#top");
  EXPECT_STREQ(u.scheme_host_port().c_str(), L"https://localhost:8443");

  u = ext::wuri(L"https://example.com/path?key=value#section-1");
  EXPECT_STREQ(u.scheme.c_str(), L"https");
  EXPECT_STREQ(u.host.c_str(), L"example.com");
  EXPECT_STREQ(u.path.c_str(), L"/path");
  EXPECT_STREQ(u.query.c_str(), L"?key=value");
  EXPECT_STREQ(u.fragment.c_str(), L"#section-1");
  EXPECT_STREQ(u.scheme_host_port().c_str(), L"https://example.com");

  u = ext::wuri(L"https://example.com/path#section?not=query");
  EXPECT_STREQ(u.path.c_str(), L"/path");
  EXPECT_TRUE(u.query.empty());
  EXPECT_STREQ(u.fragment.c_str(), L"#section?not=query");
}

TEST(uri_test, uri_query_map) {
#if defined(__cpp_initializer_lists) && (CXX_VER >= __cpp_initializer_lists)
  ext::uri u("http://test.com:1234/test",
             {{"key", "value"}, {"key1", "value1"}});
#else
  ext::uri::query_map query;
  query.insert(ext::uri::query_map::value_type("key", "value"));
  query.insert(ext::uri::query_map::value_type("key1", "value1"));
  ext::uri u("http://test.com:1234/test", query);
#endif
  EXPECT_STREQ(u.scheme.c_str(), "http");
  EXPECT_STREQ(u.host.c_str(), "test.com");
  EXPECT_EQ(u.port, 1234);
  EXPECT_STREQ(u.path.c_str(), "/test");
  EXPECT_STREQ(u.query.c_str(), "?key=value&key1=value1");
  EXPECT_STREQ(u.value.c_str(),
               "http://test.com:1234/test?key=value&key1=value1");

  ext::uri::query_map query2;
  query2.insert(ext::uri::query_map::value_type("key2", "value2"));
  u = ext::uri("http://test.com:1234/test?key=value#frag", query2);
  EXPECT_STREQ(u.query.c_str(), "?key=value&key2=value2");
  EXPECT_STREQ(u.fragment.c_str(), "#frag");
  EXPECT_STREQ(u.value.c_str(),
               "http://test.com:1234/test?key=value&key2=value2#frag");
}

TEST(uri_test, wuri_query_map) {
#if defined(__cpp_initializer_lists) && (CXX_VER >= __cpp_initializer_lists)
  ext::wuri u(L"http://test.com:1234/test",
              {{L"key", L"value"}, {L"key1", L"value1"}});
#else
  ext::wuri::query_map query;
  query.insert(ext::wuri::query_map::value_type(L"key", L"value"));
  query.insert(ext::wuri::query_map::value_type(L"key1", L"value1"));
  ext::wuri u(L"http://test.com:1234/test", query);
#endif
  EXPECT_STREQ(u.scheme.c_str(), L"http");
  EXPECT_STREQ(u.host.c_str(), L"test.com");
  EXPECT_EQ(u.port, 1234);
  EXPECT_STREQ(u.path.c_str(), L"/test");
  EXPECT_STREQ(u.query.c_str(), L"?key=value&key1=value1");
  EXPECT_STREQ(u.value.c_str(),
               L"http://test.com:1234/test?key=value&key1=value1");

  ext::wuri::query_map query2;
  query2.insert(ext::wuri::query_map::value_type(L"key2", L"value2"));
  u = ext::wuri(L"http://test.com:1234/test?key=value#frag", query2);
  EXPECT_STREQ(u.query.c_str(), L"?key=value&key2=value2");
  EXPECT_STREQ(u.fragment.c_str(), L"#frag");
  EXPECT_STREQ(u.value.c_str(),
               L"http://test.com:1234/test?key=value&key2=value2#frag");
}

TEST(uri_test, uri_encode) {
  const std::u8string uri_u8str =
#if defined(CXX_STD_U8STRING_NOT_SUPPORTED)
#if defined(__cpp_user_defined_literals) &&                                    \
    (CXX_VER >= __cpp_user_defined_literals)
      ext::from_u8(u8"https://www.google.com/search?q=한글+english");
#else
      ext::to_u8string(L"https://www.google.com/search?q=한글+english");
#endif
#else
      u8"https://www.google.com/search?q=한글+english";
#endif
  EXPECT_STREQ(ext::encode_uri<char>(uri_u8str).c_str(),
               "https://www.google.com/search?q=%ED%95%9C%EA%B8%80+english");

  ext::uri u(uri_u8str);
  EXPECT_STREQ(u.scheme.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "www.google.com");
  EXPECT_EQ(u.port, 0);
  EXPECT_STREQ(u.path.c_str(), "/search");
  EXPECT_STREQ(u.query.c_str(), "?q=%ED%95%9C%EA%B8%80+english");
  EXPECT_STREQ(u.value.c_str(),
               "https://www.google.com/search?q=%ED%95%9C%EA%B8%80+english");
}

TEST(uri_test, wuri_encode) {
  const std::u8string uri_u8str =
#if defined(CXX_STD_U8STRING_NOT_SUPPORTED)
#if defined(__cpp_user_defined_literals) &&                                    \
    (CXX_VER >= __cpp_user_defined_literals)
      ext::from_u8(u8"https://www.google.com/search?q=한글+english");
#else
      ext::to_u8string(L"https://www.google.com/search?q=한글+english");
#endif
#else
      u8"https://www.google.com/search?q=한글+english";
#endif
  EXPECT_STREQ(ext::encode_uri<char>(uri_u8str).c_str(),
               "https://www.google.com/search?q=%ED%95%9C%EA%B8%80+english");

  ext::wuri u(uri_u8str);
  EXPECT_STREQ(u.scheme.c_str(), L"https");
  EXPECT_STREQ(u.host.c_str(), L"www.google.com");
  EXPECT_EQ(u.port, 0);
  EXPECT_STREQ(u.path.c_str(), L"/search");
  EXPECT_STREQ(u.query.c_str(), L"?q=%ED%95%9C%EA%B8%80+english");
  EXPECT_STREQ(u.value.c_str(),
               L"https://www.google.com/search?q=%ED%95%9C%EA%B8%80+english");
}

TEST(uri_test, uri_encode_component) {
#if defined(__cpp_user_defined_literals) &&                                    \
    (CXX_VER >= __cpp_user_defined_literals)
  EXPECT_STREQ(ext::uri::encode_component(u8"한글-english").c_str(),
               "%ED%95%9C%EA%B8%80-english");
#else
  EXPECT_STREQ(
      ext::uri::encode_component("\xED\x95\x9C\xEA\xB8\x80-english").c_str(),
      "%ED%95%9C%EA%B8%80-english");
#endif
}

TEST(uri_test, wuri_encode_component) {
#if defined(__cpp_user_defined_literals) &&                                    \
    (CXX_VER >= __cpp_user_defined_literals)
  EXPECT_STREQ(ext::wuri::encode_component(u8"한글-english").c_str(),
               L"%ED%95%9C%EA%B8%80-english");
#else
  EXPECT_STREQ(
      ext::wuri::encode_component("\xED\x95\x9C\xEA\xB8\x80-english").c_str(),
      L"%ED%95%9C%EA%B8%80-english");
#endif
}
