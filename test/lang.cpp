#include <ext/lang>
#include <gtest/gtest.h>

TEST(lang_test, numeric) {
  using namespace ext::lang::ko_kr;

  EXPECT_STREQ(numeric::nominal(0).c_str(), L"영");
  EXPECT_STREQ(numeric::nominal(1).c_str(), L"일");
  EXPECT_STREQ(numeric::nominal(2).c_str(), L"이");
  EXPECT_STREQ(numeric::nominal(3).c_str(), L"삼");
  EXPECT_STREQ(numeric::nominal(10).c_str(), L"십");
  EXPECT_STREQ(numeric::nominal(11).c_str(), L"십일");
  EXPECT_STREQ(numeric::nominal(99).c_str(), L"구십구");
  EXPECT_STREQ(numeric::nominal(100).c_str(), L"백");
  EXPECT_STREQ(numeric::nominal(101).c_str(), L"백일");
  EXPECT_STREQ(numeric::nominal(110).c_str(), L"백십");
  EXPECT_STREQ(numeric::nominal(1000).c_str(), L"천");
  EXPECT_STREQ(numeric::nominal(1100).c_str(), L"천백");
  EXPECT_STREQ(numeric::nominal(1111).c_str(), L"천백십일");
  EXPECT_STREQ(numeric::nominal(100000).c_str(), L"십만");
  EXPECT_STREQ(numeric::nominal(110000).c_str(), L"십일만");
  EXPECT_STREQ(numeric::nominal(111111).c_str(), L"십일만천백십일");
  EXPECT_STREQ(numeric::nominal(1111111111).c_str(),
               L"십일억천백십일만천백십일");
  EXPECT_STREQ(numeric::nominal(11111111111111).c_str(),
               L"십일조천백십일억천백십일만천백십일");
  EXPECT_STREQ(numeric::nominal(111111111111111111).c_str(),
               L"십일경천백십일조천백십일억천백십일만천백십일");
  EXPECT_STREQ(numeric::nominal(222222222222222222).c_str(),
               L"이십이경이천이백이십이조이천이백이십이억이천이백이십이만이천이"
               L"백이십이");

  EXPECT_STREQ(numeric::ordinal(1).c_str(), L"첫째");
  EXPECT_STREQ(numeric::ordinal(2).c_str(), L"둘째");
  EXPECT_STREQ(numeric::ordinal(3).c_str(), L"셋째");
  EXPECT_STREQ(numeric::ordinal(10).c_str(), L"열째");
  EXPECT_STREQ(numeric::ordinal(11).c_str(), L"열한째");
  EXPECT_STREQ(numeric::ordinal(99).c_str(), L"아흔아홉째");
  EXPECT_STREQ(numeric::ordinal(100).c_str(), L"백째");
  EXPECT_STREQ(numeric::ordinal(101).c_str(), L"백한째");
  EXPECT_STREQ(numeric::ordinal(110).c_str(), L"백열째");
  EXPECT_STREQ(numeric::ordinal(1000).c_str(), L"천째");
  EXPECT_STREQ(numeric::ordinal(1100).c_str(), L"천백째");
  EXPECT_STREQ(numeric::ordinal(1111).c_str(), L"천백열한째");
  EXPECT_STREQ(numeric::ordinal(100000).c_str(), L"십만째");
  EXPECT_STREQ(numeric::ordinal(110000).c_str(), L"십일만째");
  EXPECT_STREQ(numeric::ordinal(111111).c_str(), L"십일만천백열한째");
  EXPECT_STREQ(numeric::ordinal(1111111111).c_str(),
               L"십일억천백십일만천백열한째");
  EXPECT_STREQ(numeric::ordinal(11111111111111).c_str(),
               L"십일조천백십일억천백십일만천백열한째");
  EXPECT_STREQ(numeric::ordinal(111111111111111111).c_str(),
               L"십일경천백십일조천백십일억천백십일만천백열한째");
  EXPECT_STREQ(numeric::ordinal(222222222222222222).c_str(),
               L"이십이경이천이백이십이조이천이백이십이억이천이백이십이만이천이"
               L"백스물둘째");

  EXPECT_STREQ(numeric::ordinal(1, L"번째").c_str(), L"첫 번째");
  EXPECT_STREQ(numeric::ordinal(2, L"번째").c_str(), L"두 번째");
  EXPECT_STREQ(numeric::ordinal(3, L"번째").c_str(), L"세 번째");
  EXPECT_STREQ(numeric::ordinal(10, L"번째").c_str(), L"열 번째");
  EXPECT_STREQ(numeric::ordinal(11, L"번째").c_str(), L"열한 번째");
  EXPECT_STREQ(numeric::ordinal(99, L"번째").c_str(), L"아흔아홉 번째");
  EXPECT_STREQ(numeric::ordinal(100, L"번째").c_str(), L"백 번째");
  EXPECT_STREQ(numeric::ordinal(101, L"번째").c_str(), L"백한 번째");
  EXPECT_STREQ(numeric::ordinal(110, L"번째").c_str(), L"백열 번째");
  EXPECT_STREQ(numeric::ordinal(1000, L"번째").c_str(), L"천 번째");
  EXPECT_STREQ(numeric::ordinal(1100, L"번째").c_str(), L"천백 번째");
  EXPECT_STREQ(numeric::ordinal(1111, L"번째").c_str(), L"천백열한 번째");
  EXPECT_STREQ(numeric::ordinal(100000, L"번째").c_str(), L"십만 번째");
  EXPECT_STREQ(numeric::ordinal(110000, L"번째").c_str(), L"십일만 번째");
  EXPECT_STREQ(numeric::ordinal(111111, L"번째").c_str(),
               L"십일만천백열한 번째");
  EXPECT_STREQ(numeric::ordinal(1111111111, L"번째").c_str(),
               L"십일억천백십일만천백열한 번째");
  EXPECT_STREQ(numeric::ordinal(11111111111111, L"번째").c_str(),
               L"십일조천백십일억천백십일만천백열한 번째");
  EXPECT_STREQ(numeric::ordinal(111111111111111111, L"번째").c_str(),
               L"십일경천백십일조천백십일억천백십일만천백열한 번째");
  EXPECT_STREQ(numeric::ordinal(222222222222222222, L"번째").c_str(),
               L"이십이경이천이백이십이조이천이백이십이억이천이백이십이만이천이"
               L"백스물두 번째");

  EXPECT_STREQ(numeric::cardinal(1).c_str(), L"하나");
  EXPECT_STREQ(numeric::cardinal(2).c_str(), L"둘");
  EXPECT_STREQ(numeric::cardinal(3).c_str(), L"셋");
  EXPECT_STREQ(numeric::cardinal(10).c_str(), L"열");
  EXPECT_STREQ(numeric::cardinal(11).c_str(), L"열하나");
  EXPECT_STREQ(numeric::cardinal(99).c_str(), L"아흔아홉");
  EXPECT_STREQ(numeric::cardinal(100).c_str(), L"온");
  EXPECT_STREQ(numeric::cardinal(101).c_str(), L"온하나");
  EXPECT_STREQ(numeric::cardinal(110).c_str(), L"온열");
  EXPECT_STREQ(numeric::cardinal(1000).c_str(), L"즈믄");
  EXPECT_STREQ(numeric::cardinal(1100).c_str(), L"즈믄온");
  EXPECT_STREQ(numeric::cardinal(1111).c_str(), L"즈믄온열하나");
  EXPECT_STREQ(numeric::cardinal(100000).c_str(), L"열골");
  EXPECT_STREQ(numeric::cardinal(110000).c_str(), L"열한골");
  EXPECT_STREQ(numeric::cardinal(111111).c_str(), L"열한골즈믄온열하나");
  EXPECT_STREQ(numeric::cardinal(1111111111).c_str(),
               L"열한잘즈믄온열한골즈믄온열하나");
  EXPECT_STREQ(numeric::cardinal(11111111111111).c_str(),
               L"열한울즈믄온열한잘즈믄온열한골즈믄온열하나");
  EXPECT_STREQ(numeric::cardinal(111111111111111111).c_str(),
               L"열한경즈믄온열한울즈믄온열한잘즈믄온열한골즈믄온열하나");
  EXPECT_STREQ(numeric::cardinal(222222222222222222).c_str(),
               L"스물두경두즈믄두온스물두울두즈믄두온스물두잘두즈믄두온스물두골"
               L"두즈믄두온스물둘");

  EXPECT_STREQ(numeric::cardinal(1, L" 번").c_str(), L"한 번");
  EXPECT_STREQ(numeric::cardinal(2, L" 번").c_str(), L"두 번");
  EXPECT_STREQ(numeric::cardinal(3, L" 번").c_str(), L"세 번");
  EXPECT_STREQ(numeric::cardinal(10, L" 번").c_str(), L"열 번");
  EXPECT_STREQ(numeric::cardinal(11, L" 번").c_str(), L"열한 번");
  EXPECT_STREQ(numeric::cardinal(99, L" 번").c_str(), L"아흔아홉 번");
  EXPECT_STREQ(numeric::cardinal(100, L" 번").c_str(), L"온 번");
  EXPECT_STREQ(numeric::cardinal(101, L" 번").c_str(), L"온한 번");
  EXPECT_STREQ(numeric::cardinal(110, L" 번").c_str(), L"온열 번");
  EXPECT_STREQ(numeric::cardinal(1000, L" 번").c_str(), L"즈믄 번");
  EXPECT_STREQ(numeric::cardinal(1100, L" 번").c_str(), L"즈믄온 번");
  EXPECT_STREQ(numeric::cardinal(1111, L" 번").c_str(), L"즈믄온열한 번");
  EXPECT_STREQ(numeric::cardinal(100000, L" 번").c_str(), L"열골 번");
  EXPECT_STREQ(numeric::cardinal(110000, L" 번").c_str(), L"열한골 번");
  EXPECT_STREQ(numeric::cardinal(111111, L" 번").c_str(),
               L"열한골즈믄온열한 번");
  EXPECT_STREQ(numeric::cardinal(1111111111, L" 번").c_str(),
               L"열한잘즈믄온열한골즈믄온열한 번");
  EXPECT_STREQ(numeric::cardinal(11111111111111, L" 번").c_str(),
               L"열한울즈믄온열한잘즈믄온열한골즈믄온열한 번");
  EXPECT_STREQ(numeric::cardinal(111111111111111111, L" 번").c_str(),
               L"열한경즈믄온열한울즈믄온열한잘즈믄온열한골즈믄온열한 번");
  EXPECT_STREQ(numeric::cardinal(222222222222222222, L" 번").c_str(),
               L"스물두경두즈믄두온스물두울두즈믄두온스물두잘두즈믄두온스물두골"
               L"두즈믄두온스물두 번");
}

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