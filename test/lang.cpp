#include <ext/lang>
#include <gtest/gtest.h>

TEST(lang_test, syllable) {
  using namespace ext::lang::ko_kr;
  wchar_t onset = syllable::onset(L'간');
  syllable::letter lt = L'간';
  lt = L'a';
  EXPECT_FALSE(lt.valid());

  lt = L'ㄱ';
  EXPECT_FALSE(lt.valid());
  EXPECT_EQ(lt.onset, L'ㄱ');

  lt = L'ㅏ';
  EXPECT_FALSE(lt.valid());
  EXPECT_EQ(lt.nucleus, L'ㅏ');

  lt = L'가';
  EXPECT_TRUE(lt.valid());
  EXPECT_EQ(lt.onset, L'ㄱ');
  EXPECT_EQ(lt.nucleus, L'ㅏ');

  lt = L'간';
  EXPECT_TRUE(lt.valid());
  EXPECT_EQ(lt.onset, L'ㄱ');
  EXPECT_EQ(lt.nucleus, L'ㅏ');
  EXPECT_EQ(lt.coda, L'ㄴ');
}

TEST(lang_test, postposition) {
  using namespace ext::lang::ko_kr;
  EXPECT_STREQ(postposition::topic(L"산").c_str(), L"은");
  EXPECT_STREQ(postposition::topic(L"바다").c_str(), L"는");

  EXPECT_STREQ(postposition::identifier(L"산").c_str(), L"이");
  EXPECT_STREQ(postposition::identifier(L"바다").c_str(), L"가");

  EXPECT_STREQ(postposition::objective(L"산").c_str(), L"을");
  EXPECT_STREQ(postposition::objective(L"바다").c_str(), L"를");

  EXPECT_STREQ(postposition::destination(L"산").c_str(), L"으로");
  EXPECT_STREQ(postposition::destination(L"바다").c_str(), L"로");

  EXPECT_STREQ(postposition::destination(L"산").c_str(), L"으로");
  EXPECT_STREQ(postposition::destination(L"바다").c_str(), L"로");

  EXPECT_STREQ(postposition::conjunction(L"산").c_str(), L"과");
  EXPECT_STREQ(postposition::conjunction(L"바다").c_str(), L"와");

  EXPECT_STREQ(postposition::vocative(L"산").c_str(), L"아");
  EXPECT_STREQ(postposition::vocative(L"바다").c_str(), L"야");

  EXPECT_STREQ(postposition::exclamation(L"산").c_str(), L"이여");
  EXPECT_STREQ(postposition::exclamation(L"바다").c_str(), L"여");
}