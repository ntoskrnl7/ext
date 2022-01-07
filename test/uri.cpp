#include <ext/uri>
#include <gtest/gtest.h>

TEST(uri_test, invalid_uri_test) {
  ext::uri u("");
  EXPECT_STREQ(u.protocol.c_str(), "");
  EXPECT_STREQ(u.host.c_str(), "");
  EXPECT_STREQ(u.path.c_str(), "");

  u = std::wstring(L"");
  EXPECT_STREQ(u.protocol.c_str(), "");
  EXPECT_STREQ(u.host.c_str(), "");
  EXPECT_STREQ(u.path.c_str(), "");
}

TEST(uri_test, string_uri_test) {
  ext::uri u("https://google.com/");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "google.com");
  EXPECT_STREQ(u.path.c_str(), "/");

  u = ext::uri("https://NAVER.com/");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "naver.com");
  EXPECT_STREQ(u.path.c_str(), "/");

  u = ext::uri("https://localhost:8443/test");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "localhost");
  EXPECT_EQ(u.port, 8443);
  EXPECT_STREQ(u.path.c_str(), "/test");
  EXPECT_STREQ(u.protocol_host_port().c_str(), "https://localhost:8443");
}

TEST(uri_test, wstring_uri_test) {
  ext::uri u(L"https://google.com/");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "google.com");
  EXPECT_STREQ(u.path.c_str(), "/");

  u = ext::uri(L"https://NAVER.com/");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "naver.com");
  EXPECT_STREQ(u.path.c_str(), "/");

  u = ext::uri(L"https://localhost:8443/test");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "localhost");
  EXPECT_EQ(u.port, 8443);
  EXPECT_STREQ(u.path.c_str(), "/test");
  EXPECT_STREQ(u.protocol_host_port().c_str(), "https://localhost:8443");
}

TEST(uri_test, query_map) {
#ifdef __cpp_initializer_lists
  ext::uri u("http://test.com/test", {{"key", "value"}, {"key1", "value1"}});
#else
  ext::uri::query_map query;
  query.insert(ext::uri::query_map::value_type("key", "value"));
  query.insert(ext::uri::query_map::value_type("key1", "value1"));
  ext::uri u("http://test.com/test", query);
#endif // __cpp_initializer_lists
  EXPECT_STREQ(u.query.c_str(), "?key=value&key1=value1");
  EXPECT_STREQ(u.value.c_str(), "http://test.com/test?key=value&key1=value1");
}

TEST(uri_test, wquery_map) {
#ifdef __cpp_initializer_lists
  ext::uri u(L"http://test.com/test",
             {{L"key", L"value"}, {L"key1", L"value1"}});
#else
  ext::uri::wquery_map query;
  query.insert(ext::uri::wquery_map::value_type(L"key", L"value"));
  query.insert(ext::uri::wquery_map::value_type(L"key1", L"value1"));
  ext::uri u(L"http://test.com/test", query);
#endif // __cpp_initializer_lists
  EXPECT_STREQ(u.query.c_str(), "?key=value&key1=value1");
  EXPECT_STREQ(u.value.c_str(), "http://test.com/test?key=value&key1=value1");
}