#define CXX_USE_STD_U8STRING
#include <ext/uri>

#include <gtest/gtest.h>

TEST(uri_test, invalid_uri_test) {
  ext::uri u("");
  EXPECT_STREQ(u.scheme.c_str(), "");
  EXPECT_STREQ(u.host.c_str(), "");
  EXPECT_STREQ(u.path.c_str(), "");

  u = ext::uri("https://example.com:65536/path");
  EXPECT_FALSE(u.valid());

  u = ext::uri("https://example.com:12x/path");
  EXPECT_FALSE(u.valid());

  u = ext::uri("https://example.com:+80/path");
  EXPECT_FALSE(u.valid());

  u = ext::uri("https://[2001:db8::1/path");
  EXPECT_FALSE(u.valid());
}

TEST(uri_test, invalid_wuri_test) {
  ext::wuri u(L"");
  EXPECT_STREQ(u.scheme.c_str(), L"");
  EXPECT_STREQ(u.host.c_str(), L"");
  EXPECT_STREQ(u.path.c_str(), L"");

  u = ext::wuri(L"https://example.com:65536/path");
  EXPECT_FALSE(u.valid());

  u = ext::wuri(L"https://example.com:12x/path");
  EXPECT_FALSE(u.valid());

  u = ext::wuri(L"https://example.com:+80/path");
  EXPECT_FALSE(u.valid());

  u = ext::wuri(L"https://[2001:db8::1/path");
  EXPECT_FALSE(u.valid());
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

  u = ext::uri("https://User:Pass@EXAMPLE.com:8443/test");
  EXPECT_STREQ(u.scheme.c_str(), "https");
  EXPECT_STREQ(u.userinfo.c_str(), "User:Pass");
  EXPECT_STREQ(u.host.c_str(), "example.com");
  EXPECT_EQ(u.port, 8443);
  EXPECT_STREQ(u.path.c_str(), "/test");
  EXPECT_STREQ(u.scheme_host_port().c_str(),
               "https://User:Pass@EXAMPLE.com:8443");

  u = ext::uri("https://[2001:DB8::1]:443/test");
  EXPECT_STREQ(u.scheme.c_str(), "https");
  EXPECT_TRUE(u.userinfo.empty());
  EXPECT_STREQ(u.host.c_str(), "2001:db8::1");
  EXPECT_EQ(u.port, 443);
  EXPECT_STREQ(u.path.c_str(), "/test");
  EXPECT_STREQ(u.scheme_host_port().c_str(), "https://[2001:DB8::1]:443");

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

  u = ext::wuri(L"https://User:Pass@EXAMPLE.com:8443/test");
  EXPECT_STREQ(u.scheme.c_str(), L"https");
  EXPECT_STREQ(u.userinfo.c_str(), L"User:Pass");
  EXPECT_STREQ(u.host.c_str(), L"example.com");
  EXPECT_EQ(u.port, 8443);
  EXPECT_STREQ(u.path.c_str(), L"/test");
  EXPECT_STREQ(u.scheme_host_port().c_str(),
               L"https://User:Pass@EXAMPLE.com:8443");

  u = ext::wuri(L"https://[2001:DB8::1]:443/test");
  EXPECT_STREQ(u.scheme.c_str(), L"https");
  EXPECT_TRUE(u.userinfo.empty());
  EXPECT_STREQ(u.host.c_str(), L"2001:db8::1");
  EXPECT_EQ(u.port, 443);
  EXPECT_STREQ(u.path.c_str(), L"/test");
  EXPECT_STREQ(u.scheme_host_port().c_str(), L"https://[2001:DB8::1]:443");

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

  ext::uri::query_map query3;
  query3.insert(ext::uri::query_map::value_type("q", "hello world"));
  query3.insert(ext::uri::query_map::value_type("a+b", "c&d"));
  u = ext::uri("https://example.com/search#results", query3);
  EXPECT_STREQ(u.query.c_str(), "?a%2Bb=c%26d&q=hello%20world");
  EXPECT_STREQ(u.value.c_str(),
               "https://example.com/search?a%2Bb=c%26d&q=hello%20world#results");

  ext::uri parsed(
      "https://example.com/search?q=hello%20world&empty&a%2Bb=c%26d");
  ext::uri::query_map params = parsed.query_params();
  EXPECT_EQ(params.size(), 3u);
  EXPECT_STREQ(params["q"].c_str(), "hello world");
  EXPECT_STREQ(params["empty"].c_str(), "");
  EXPECT_STREQ(params["a+b"].c_str(), "c&d");
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

  ext::wuri::query_map query3;
  query3.insert(ext::wuri::query_map::value_type(L"q", L"hello world"));
  query3.insert(ext::wuri::query_map::value_type(L"a+b", L"c&d"));
  u = ext::wuri(L"https://example.com/search#results", query3);
  EXPECT_STREQ(u.query.c_str(), L"?a%2Bb=c%26d&q=hello%20world");
  EXPECT_STREQ(u.value.c_str(),
               L"https://example.com/search?a%2Bb=c%26d&q=hello%20world#results");

  ext::wuri parsed(
      L"https://example.com/search?q=hello%20world&empty&a%2Bb=c%26d");
  ext::wuri::query_map params = parsed.query_params();
  EXPECT_EQ(params.size(), 3u);
  EXPECT_STREQ(params[L"q"].c_str(), L"hello world");
  EXPECT_STREQ(params[L"empty"].c_str(), L"");
  EXPECT_STREQ(params[L"a+b"].c_str(), L"c&d");
}

TEST(uri_test, uri_resolve) {
  ext::uri base("https://User@example.com/a/b/c?x=1#old");

  ext::uri u = base.resolve("../d/./e?y=2#new");
  EXPECT_STREQ(u.value.c_str(), "https://User@example.com/a/d/e?y=2#new");
  EXPECT_STREQ(u.userinfo.c_str(), "User");
  EXPECT_STREQ(u.host.c_str(), "example.com");
  EXPECT_STREQ(u.path.c_str(), "/a/d/e");
  EXPECT_STREQ(u.query.c_str(), "?y=2");
  EXPECT_STREQ(u.fragment.c_str(), "#new");

  u = base.resolve("?q=2");
  EXPECT_STREQ(u.value.c_str(), "https://User@example.com/a/b/c?q=2");
  EXPECT_STREQ(u.path.c_str(), "/a/b/c");
  EXPECT_STREQ(u.query.c_str(), "?q=2");
  EXPECT_TRUE(u.fragment.empty());

  u = base.resolve("#frag");
  EXPECT_STREQ(u.value.c_str(), "https://User@example.com/a/b/c?x=1#frag");
  EXPECT_STREQ(u.query.c_str(), "?x=1");
  EXPECT_STREQ(u.fragment.c_str(), "#frag");

  u = base.resolve("//[2001:db8::1]:9443/v");
  EXPECT_STREQ(u.value.c_str(), "https://[2001:db8::1]:9443/v");
  EXPECT_STREQ(u.host.c_str(), "2001:db8::1");
  EXPECT_EQ(u.port, 9443);

  EXPECT_STREQ(ext::uri::remove_dot_segments("/a/b/../c/./").c_str(),
               "/a/c/");
}

TEST(uri_test, wuri_resolve) {
  ext::wuri base(L"https://User@example.com/a/b/c?x=1#old");

  ext::wuri u = base.resolve(L"../d/./e?y=2#new");
  EXPECT_STREQ(u.value.c_str(), L"https://User@example.com/a/d/e?y=2#new");
  EXPECT_STREQ(u.userinfo.c_str(), L"User");
  EXPECT_STREQ(u.host.c_str(), L"example.com");
  EXPECT_STREQ(u.path.c_str(), L"/a/d/e");
  EXPECT_STREQ(u.query.c_str(), L"?y=2");
  EXPECT_STREQ(u.fragment.c_str(), L"#new");

  u = base.resolve(L"//[2001:db8::1]:9443/v");
  EXPECT_STREQ(u.value.c_str(), L"https://[2001:db8::1]:9443/v");
  EXPECT_STREQ(u.host.c_str(), L"2001:db8::1");
  EXPECT_EQ(u.port, 9443);

  EXPECT_STREQ(ext::wuri::remove_dot_segments(L"/a/b/../c/./").c_str(),
               L"/a/c/");
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
  EXPECT_STREQ(ext::uri::decode_component("a%20b%2Bc").c_str(), "a b+c");
  EXPECT_THROW(ext::uri::decode_component("bad%2"), std::invalid_argument);
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
  EXPECT_STREQ(ext::wuri::decode_component(L"a%20b%2Bc").c_str(), L"a b+c");
  EXPECT_THROW(ext::wuri::decode_component(L"bad%2"), std::invalid_argument);
}
