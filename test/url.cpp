#include <ext/url>
#include <gtest/gtest.h>


TEST(url_test, invalid_url_test) {
  ext::url u("");
  EXPECT_STREQ(u.protocol.c_str(), "");
  EXPECT_STREQ(u.host.c_str(), "");
  EXPECT_STREQ(u.path.c_str(), "");

  u = std::wstring(L"");
  EXPECT_STREQ(u.protocol.c_str(), "");
  EXPECT_STREQ(u.host.c_str(), "");
  EXPECT_STREQ(u.path.c_str(), "");
}

TEST(url_test, string_url_test) {
  ext::url u("https://google.com/");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "google.com");
  EXPECT_STREQ(u.path.c_str(), "/");

  u = ext::url("https://NAVER.com/");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "naver.com");
  EXPECT_STREQ(u.path.c_str(), "/");

  u = ext::url("https://localhost:8443/test");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "localhost");
  EXPECT_EQ(u.port, 8443);
  EXPECT_STREQ(u.path.c_str(), "/test");
  EXPECT_STREQ(u.protocol_host_port().c_str(), "https://localhost:8443");
}

TEST(url_test, wstring_url_test) {
  ext::url u(L"https://google.com/");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "google.com");
  EXPECT_STREQ(u.path.c_str(), "/");

  u = ext::url(L"https://NAVER.com/");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "naver.com");
  EXPECT_STREQ(u.path.c_str(), "/");

  u = ext::url(L"https://localhost:8443/test");
  EXPECT_STREQ(u.protocol.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "localhost");
  EXPECT_EQ(u.port, 8443);
  EXPECT_STREQ(u.path.c_str(), "/test");
  EXPECT_STREQ(u.protocol_host_port().c_str(), "https://localhost:8443");
}
