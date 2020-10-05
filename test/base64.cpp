#include <ext/base64>
#include <gtest/gtest.h>

TEST(base64_test, simple_test) {
  auto a = ext::base64::encode("1234");
  EXPECT_STREQ(a.c_str(), "MTIzNA==");

  auto b = ext::base64::decode(a);
  EXPECT_STREQ(b.c_str(), "1234");
  
  auto aw = ext::base64::encode(L"1234");
  EXPECT_STREQ(aw.c_str(), L"MTIzNA==");
  
  auto bw = ext::base64::decode(aw);
  EXPECT_STREQ(bw.c_str(), L"1234");
}
