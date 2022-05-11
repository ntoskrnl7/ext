#include <ext/lang>
#include <gtest/gtest.h>

TEST(lang_test, ko_kr_numeric_nominal) {
  using namespace ext::lang::ko_kr::numeric;

  EXPECT_STREQ(nominal(0).c_str(), "영");
  EXPECT_STREQ(nominal(1).c_str(), "일");
  EXPECT_STREQ(nominal(3).c_str(), "삼");
  EXPECT_STREQ(nominal(2).c_str(), "이");
  EXPECT_STREQ(nominal(10).c_str(), "십");
  EXPECT_STREQ(nominal(11).c_str(), "십일");
  EXPECT_STREQ(nominal(20).c_str(), "이십");
  EXPECT_STREQ(nominal(21).c_str(), "이십일");
  EXPECT_STREQ(nominal(99).c_str(), "구십구");
  EXPECT_STREQ(nominal(100).c_str(), "백");
  EXPECT_STREQ(nominal(101).c_str(), "백일");
  EXPECT_STREQ(nominal(110).c_str(), "백십");
  EXPECT_STREQ(nominal(1000).c_str(), "천");
  EXPECT_STREQ(nominal(1100).c_str(), "천백");
  EXPECT_STREQ(nominal(1111).c_str(), "천백십일");
  EXPECT_STREQ(nominal(100000).c_str(), "십만");
  EXPECT_STREQ(nominal(110000).c_str(), "십일만");
  EXPECT_STREQ(nominal(111111).c_str(), "십일만천백십일");
  EXPECT_STREQ(nominal(1111111111).c_str(), "십일억천백십일만천백십일");
  EXPECT_STREQ(nominal(11111111111111).c_str(),
               "십일조천백십일억천백십일만천백십일");
  EXPECT_STREQ(nominal(111111111111111111).c_str(),
               "십일경천백십일조천백십일억천백십일만천백십일");
  EXPECT_STREQ(nominal(222222222222222222).c_str(),
               "이십이경이천이백이십이조이천이백이십이억이천이백이십이만이천이"
               "백이십이");
}

TEST(lang_test, ko_kr_numeric_wnominal) {
  using namespace ext::lang::ko_kr::numeric;

  EXPECT_STREQ(wnominal(0).c_str(), L"영");
  EXPECT_STREQ(wnominal(1).c_str(), L"일");
  EXPECT_STREQ(wnominal(2).c_str(), L"이");
  EXPECT_STREQ(wnominal(3).c_str(), L"삼");
  EXPECT_STREQ(wnominal(10).c_str(), L"십");
  EXPECT_STREQ(wnominal(11).c_str(), L"십일");
  EXPECT_STREQ(wnominal(20).c_str(), L"이십");
  EXPECT_STREQ(wnominal(21).c_str(), L"이십일");
  EXPECT_STREQ(wnominal(99).c_str(), L"구십구");
  EXPECT_STREQ(wnominal(100).c_str(), L"백");
  EXPECT_STREQ(wnominal(101).c_str(), L"백일");
  EXPECT_STREQ(wnominal(110).c_str(), L"백십");
  EXPECT_STREQ(wnominal(1000).c_str(), L"천");
  EXPECT_STREQ(wnominal(1100).c_str(), L"천백");
  EXPECT_STREQ(wnominal(1111).c_str(), L"천백십일");
  EXPECT_STREQ(wnominal(100000).c_str(), L"십만");
  EXPECT_STREQ(wnominal(110000).c_str(), L"십일만");
  EXPECT_STREQ(wnominal(111111).c_str(), L"십일만천백십일");
  EXPECT_STREQ(wnominal(1111111111).c_str(), L"십일억천백십일만천백십일");
  EXPECT_STREQ(wnominal(11111111111111).c_str(),
               L"십일조천백십일억천백십일만천백십일");
  EXPECT_STREQ(wnominal(111111111111111111).c_str(),
               L"십일경천백십일조천백십일억천백십일만천백십일");
  EXPECT_STREQ(wnominal(222222222222222222).c_str(),
               L"이십이경이천이백이십이조이천이백이십이억이천이백이십이만이천이"
               L"백이십이");
}

TEST(lang_test, ko_kr_numeric_ordinal) {
  using namespace ext::lang::ko_kr::numeric;

  EXPECT_STREQ(ordinal(1).c_str(), "첫째");
  EXPECT_STREQ(ordinal(2).c_str(), "둘째");
  EXPECT_STREQ(ordinal(3).c_str(), "셋째");
  EXPECT_STREQ(ordinal(10).c_str(), "열째");
  EXPECT_STREQ(ordinal(11).c_str(), "열한째");
  EXPECT_STREQ(ordinal(20).c_str(), "스무째");
  EXPECT_STREQ(ordinal(21).c_str(), "스물한째");
  EXPECT_STREQ(ordinal(99).c_str(), "아흔아홉째");
  EXPECT_STREQ(ordinal(100).c_str(), "백째");
  EXPECT_STREQ(ordinal(101).c_str(), "백한째");
  EXPECT_STREQ(ordinal(110).c_str(), "백열째");
  EXPECT_STREQ(ordinal(1000).c_str(), "천째");
  EXPECT_STREQ(ordinal(1100).c_str(), "천백째");
  EXPECT_STREQ(ordinal(1111).c_str(), "천백열한째");
  EXPECT_STREQ(ordinal(100000).c_str(), "십만째");
  EXPECT_STREQ(ordinal(110000).c_str(), "십일만째");
  EXPECT_STREQ(ordinal(111111).c_str(), "십일만천백열한째");
  EXPECT_STREQ(ordinal(1111111111).c_str(), "십일억천백십일만천백열한째");
  EXPECT_STREQ(ordinal(11111111111111).c_str(),
               "십일조천백십일억천백십일만천백열한째");
  EXPECT_STREQ(ordinal(111111111111111111).c_str(),
               "십일경천백십일조천백십일억천백십일만천백열한째");
  EXPECT_STREQ(ordinal(222222222222222222).c_str(),
               "이십이경이천이백이십이조이천이백이십이억이천이백이십이만이천이"
               "백스물둘째");

  EXPECT_STREQ(ordinal(1, "번째").c_str(), "첫 번째");
  EXPECT_STREQ(ordinal(2, "번째").c_str(), "두 번째");
  EXPECT_STREQ(ordinal(3, "번째").c_str(), "세 번째");
  EXPECT_STREQ(ordinal(10, "번째").c_str(), "열 번째");
  EXPECT_STREQ(ordinal(11, "번째").c_str(), "열한 번째");
  EXPECT_STREQ(ordinal(20, "번째").c_str(), "스무 번째");
  EXPECT_STREQ(ordinal(21, "번째").c_str(), "스물한 번째");
  EXPECT_STREQ(ordinal(99, "번째").c_str(), "아흔아홉 번째");
  EXPECT_STREQ(ordinal(100, "번째").c_str(), "백 번째");
  EXPECT_STREQ(ordinal(101, "번째").c_str(), "백한 번째");
  EXPECT_STREQ(ordinal(110, "번째").c_str(), "백열 번째");
  EXPECT_STREQ(ordinal(1000, "번째").c_str(), "천 번째");
  EXPECT_STREQ(ordinal(1100, "번째").c_str(), "천백 번째");
  EXPECT_STREQ(ordinal(1111, "번째").c_str(), "천백열한 번째");
  EXPECT_STREQ(ordinal(100000, "번째").c_str(), "십만 번째");
  EXPECT_STREQ(ordinal(110000, "번째").c_str(), "십일만 번째");
  EXPECT_STREQ(ordinal(111111, "번째").c_str(), "십일만천백열한 번째");
  EXPECT_STREQ(ordinal(1111111111, "번째").c_str(),
               "십일억천백십일만천백열한 번째");
  EXPECT_STREQ(ordinal(11111111111111, "번째").c_str(),
               "십일조천백십일억천백십일만천백열한 번째");
  EXPECT_STREQ(ordinal(111111111111111111, "번째").c_str(),
               "십일경천백십일조천백십일억천백십일만천백열한 번째");
  EXPECT_STREQ(ordinal(222222222222222222, "번째").c_str(),
               "이십이경이천이백이십이조이천이백이십이억이천이백이십이만이천이"
               "백스물두 번째");
}

TEST(lang_test, ko_kr_numeric_wordinal) {
  using namespace ext::lang::ko_kr::numeric;

  EXPECT_STREQ(wordinal(1).c_str(), L"첫째");
  EXPECT_STREQ(wordinal(2).c_str(), L"둘째");
  EXPECT_STREQ(wordinal(3).c_str(), L"셋째");
  EXPECT_STREQ(wordinal(10).c_str(), L"열째");
  EXPECT_STREQ(wordinal(11).c_str(), L"열한째");
  EXPECT_STREQ(wordinal(20).c_str(), L"스무째");
  EXPECT_STREQ(wordinal(21).c_str(), L"스물한째");
  EXPECT_STREQ(wordinal(99).c_str(), L"아흔아홉째");
  EXPECT_STREQ(wordinal(100).c_str(), L"백째");
  EXPECT_STREQ(wordinal(101).c_str(), L"백한째");
  EXPECT_STREQ(wordinal(110).c_str(), L"백열째");
  EXPECT_STREQ(wordinal(1000).c_str(), L"천째");
  EXPECT_STREQ(wordinal(1100).c_str(), L"천백째");
  EXPECT_STREQ(wordinal(1111).c_str(), L"천백열한째");
  EXPECT_STREQ(wordinal(100000).c_str(), L"십만째");
  EXPECT_STREQ(wordinal(110000).c_str(), L"십일만째");
  EXPECT_STREQ(wordinal(111111).c_str(), L"십일만천백열한째");
  EXPECT_STREQ(wordinal(1111111111).c_str(), L"십일억천백십일만천백열한째");
  EXPECT_STREQ(wordinal(11111111111111).c_str(),
               L"십일조천백십일억천백십일만천백열한째");
  EXPECT_STREQ(wordinal(111111111111111111).c_str(),
               L"십일경천백십일조천백십일억천백십일만천백열한째");
  EXPECT_STREQ(wordinal(222222222222222222).c_str(),
               L"이십이경이천이백이십이조이천이백이십이억이천이백이십이만이천이"
               L"백스물둘째");

  EXPECT_STREQ(wordinal(1, L"번째").c_str(), L"첫 번째");
  EXPECT_STREQ(wordinal(2, L"번째").c_str(), L"두 번째");
  EXPECT_STREQ(wordinal(3, L"번째").c_str(), L"세 번째");
  EXPECT_STREQ(wordinal(10, L"번째").c_str(), L"열 번째");
  EXPECT_STREQ(wordinal(11, L"번째").c_str(), L"열한 번째");
  EXPECT_STREQ(wordinal(20, L"번째").c_str(), L"스무 번째");
  EXPECT_STREQ(wordinal(21, L"번째").c_str(), L"스물한 번째");
  EXPECT_STREQ(wordinal(99, L"번째").c_str(), L"아흔아홉 번째");
  EXPECT_STREQ(wordinal(100, L"번째").c_str(), L"백 번째");
  EXPECT_STREQ(wordinal(101, L"번째").c_str(), L"백한 번째");
  EXPECT_STREQ(wordinal(110, L"번째").c_str(), L"백열 번째");
  EXPECT_STREQ(wordinal(1000, L"번째").c_str(), L"천 번째");
  EXPECT_STREQ(wordinal(1100, L"번째").c_str(), L"천백 번째");
  EXPECT_STREQ(wordinal(1111, L"번째").c_str(), L"천백열한 번째");
  EXPECT_STREQ(wordinal(100000, L"번째").c_str(), L"십만 번째");
  EXPECT_STREQ(wordinal(110000, L"번째").c_str(), L"십일만 번째");
  EXPECT_STREQ(wordinal(111111, L"번째").c_str(), L"십일만천백열한 번째");
  EXPECT_STREQ(wordinal(1111111111, L"번째").c_str(),
               L"십일억천백십일만천백열한 번째");
  EXPECT_STREQ(wordinal(11111111111111, L"번째").c_str(),
               L"십일조천백십일억천백십일만천백열한 번째");
  EXPECT_STREQ(wordinal(111111111111111111, L"번째").c_str(),
               L"십일경천백십일조천백십일억천백십일만천백열한 번째");
  EXPECT_STREQ(wordinal(222222222222222222, L"번째").c_str(),
               L"이십이경이천이백이십이조이천이백이십이억이천이백이십이만이천이"
               L"백스물두 번째");
}

TEST(lang_test, ko_kr_numeric_cardinal) {
  using namespace ext::lang::ko_kr::numeric;

  EXPECT_STREQ(cardinal(1).c_str(), "하나");
  EXPECT_STREQ(cardinal(2).c_str(), "둘");
  EXPECT_STREQ(cardinal(3).c_str(), "셋");
  EXPECT_STREQ(cardinal(10).c_str(), "열");
  EXPECT_STREQ(cardinal(11).c_str(), "열하나");
  EXPECT_STREQ(cardinal(20).c_str(), "스물");
  EXPECT_STREQ(cardinal(21).c_str(), "스물하나");
  EXPECT_STREQ(cardinal(99).c_str(), "아흔아홉");
  EXPECT_STREQ(cardinal(100).c_str(), "온");
  EXPECT_STREQ(cardinal(101).c_str(), "온하나");
  EXPECT_STREQ(cardinal(110).c_str(), "온열");
  EXPECT_STREQ(cardinal(1000).c_str(), "즈믄");
  EXPECT_STREQ(cardinal(1100).c_str(), "즈믄온");
  EXPECT_STREQ(cardinal(1111).c_str(), "즈믄온열하나");
  EXPECT_STREQ(cardinal(100000).c_str(), "열골");
  EXPECT_STREQ(cardinal(110000).c_str(), "열한골");
  EXPECT_STREQ(cardinal(111111).c_str(), "열한골즈믄온열하나");
  EXPECT_STREQ(cardinal(1111111111).c_str(), "열한잘즈믄온열한골즈믄온열하나");
  EXPECT_STREQ(cardinal(11111111111111).c_str(),
               "열한울즈믄온열한잘즈믄온열한골즈믄온열하나");
  EXPECT_STREQ(cardinal(111111111111111111).c_str(),
               "열한경즈믄온열한울즈믄온열한잘즈믄온열한골즈믄온열하나");
  EXPECT_STREQ(cardinal(222222222222222222).c_str(),
               "스물두경두즈믄두온스물두울두즈믄두온스물두잘두즈믄두온스물두골"
               "두즈믄두온스물둘");

  EXPECT_STREQ(cardinal(1, " 번").c_str(), "한 번");
  EXPECT_STREQ(cardinal(2, " 번").c_str(), "두 번");
  EXPECT_STREQ(cardinal(3, " 번").c_str(), "세 번");
  EXPECT_STREQ(cardinal(10, " 번").c_str(), "열 번");
  EXPECT_STREQ(cardinal(11, " 번").c_str(), "열한 번");
  EXPECT_STREQ(cardinal(20, " 번").c_str(), "스무 번");
  EXPECT_STREQ(cardinal(21, " 번").c_str(), "스물한 번");
  EXPECT_STREQ(cardinal(99, " 번").c_str(), "아흔아홉 번");
  EXPECT_STREQ(cardinal(100, " 번").c_str(), "온 번");
  EXPECT_STREQ(cardinal(101, " 번").c_str(), "온한 번");
  EXPECT_STREQ(cardinal(110, " 번").c_str(), "온열 번");
  EXPECT_STREQ(cardinal(1000, " 번").c_str(), "즈믄 번");
  EXPECT_STREQ(cardinal(1100, " 번").c_str(), "즈믄온 번");
  EXPECT_STREQ(cardinal(1111, " 번").c_str(), "즈믄온열한 번");
  EXPECT_STREQ(cardinal(100000, " 번").c_str(), "열골 번");
  EXPECT_STREQ(cardinal(110000, " 번").c_str(), "열한골 번");
  EXPECT_STREQ(cardinal(111111, " 번").c_str(), "열한골즈믄온열한 번");
  EXPECT_STREQ(cardinal(1111111111, " 번").c_str(),
               "열한잘즈믄온열한골즈믄온열한 번");
  EXPECT_STREQ(cardinal(11111111111111, " 번").c_str(),
               "열한울즈믄온열한잘즈믄온열한골즈믄온열한 번");
  EXPECT_STREQ(cardinal(111111111111111111, " 번").c_str(),
               "열한경즈믄온열한울즈믄온열한잘즈믄온열한골즈믄온열한 번");
  EXPECT_STREQ(cardinal(222222222222222222, " 번").c_str(),
               "스물두경두즈믄두온스물두울두즈믄두온스물두잘두즈믄두온스물두골"
               "두즈믄두온스물두 번");
}

TEST(lang_test, ko_kr_numeric_wcardinal) {
  using namespace ext::lang::ko_kr::numeric;

  EXPECT_STREQ(wcardinal(1).c_str(), L"하나");
  EXPECT_STREQ(wcardinal(2).c_str(), L"둘");
  EXPECT_STREQ(wcardinal(3).c_str(), L"셋");
  EXPECT_STREQ(wcardinal(10).c_str(), L"열");
  EXPECT_STREQ(wcardinal(11).c_str(), L"열하나");
  EXPECT_STREQ(wcardinal(20).c_str(), L"스물");
  EXPECT_STREQ(wcardinal(21).c_str(), L"스물하나");
  EXPECT_STREQ(wcardinal(99).c_str(), L"아흔아홉");
  EXPECT_STREQ(wcardinal(100).c_str(), L"온");
  EXPECT_STREQ(wcardinal(101).c_str(), L"온하나");
  EXPECT_STREQ(wcardinal(110).c_str(), L"온열");
  EXPECT_STREQ(wcardinal(1000).c_str(), L"즈믄");
  EXPECT_STREQ(wcardinal(1100).c_str(), L"즈믄온");
  EXPECT_STREQ(wcardinal(1111).c_str(), L"즈믄온열하나");
  EXPECT_STREQ(wcardinal(100000).c_str(), L"열골");
  EXPECT_STREQ(wcardinal(110000).c_str(), L"열한골");
  EXPECT_STREQ(wcardinal(111111).c_str(), L"열한골즈믄온열하나");
  EXPECT_STREQ(wcardinal(1111111111).c_str(),
               L"열한잘즈믄온열한골즈믄온열하나");
  EXPECT_STREQ(wcardinal(11111111111111).c_str(),
               L"열한울즈믄온열한잘즈믄온열한골즈믄온열하나");
  EXPECT_STREQ(wcardinal(111111111111111111).c_str(),
               L"열한경즈믄온열한울즈믄온열한잘즈믄온열한골즈믄온열하나");
  EXPECT_STREQ(wcardinal(222222222222222222).c_str(),
               L"스물두경두즈믄두온스물두울두즈믄두온스물두잘두즈믄두온스물두골"
               L"두즈믄두온스물둘");

  EXPECT_STREQ(wcardinal(1, L" 번").c_str(), L"한 번");
  EXPECT_STREQ(wcardinal(2, L" 번").c_str(), L"두 번");
  EXPECT_STREQ(wcardinal(3, L" 번").c_str(), L"세 번");
  EXPECT_STREQ(wcardinal(10, L" 번").c_str(), L"열 번");
  EXPECT_STREQ(wcardinal(11, L" 번").c_str(), L"열한 번");
  EXPECT_STREQ(wcardinal(20, L" 번").c_str(), L"스무 번");
  EXPECT_STREQ(wcardinal(21, L" 번").c_str(), L"스물한 번");
  EXPECT_STREQ(wcardinal(99, L" 번").c_str(), L"아흔아홉 번");
  EXPECT_STREQ(wcardinal(100, L" 번").c_str(), L"온 번");
  EXPECT_STREQ(wcardinal(101, L" 번").c_str(), L"온한 번");
  EXPECT_STREQ(wcardinal(110, L" 번").c_str(), L"온열 번");
  EXPECT_STREQ(wcardinal(1000, L" 번").c_str(), L"즈믄 번");
  EXPECT_STREQ(wcardinal(1100, L" 번").c_str(), L"즈믄온 번");
  EXPECT_STREQ(wcardinal(1111, L" 번").c_str(), L"즈믄온열한 번");
  EXPECT_STREQ(wcardinal(100000, L" 번").c_str(), L"열골 번");
  EXPECT_STREQ(wcardinal(110000, L" 번").c_str(), L"열한골 번");
  EXPECT_STREQ(wcardinal(111111, L" 번").c_str(), L"열한골즈믄온열한 번");
  EXPECT_STREQ(wcardinal(1111111111, L" 번").c_str(),
               L"열한잘즈믄온열한골즈믄온열한 번");
  EXPECT_STREQ(wcardinal(11111111111111, L" 번").c_str(),
               L"열한울즈믄온열한잘즈믄온열한골즈믄온열한 번");
  EXPECT_STREQ(wcardinal(111111111111111111, L" 번").c_str(),
               L"열한경즈믄온열한울즈믄온열한잘즈믄온열한골즈믄온열한 번");
  EXPECT_STREQ(wcardinal(222222222222222222, L" 번").c_str(),
               L"스물두경두즈믄두온스물두울두즈믄두온스물두잘두즈믄두온스물두골"
               L"두즈믄두온스물두 번");
}

TEST(lang_test, ko_kr_syllable) {
  using namespace ext::lang::ko_kr::syllable;

  EXPECT_EQ(onset(L'간'), L'ㄱ');
  EXPECT_EQ(nucleus(L'간'), L'ㅏ');
  EXPECT_EQ(coda(L'간'), L'ㄴ');

  letter lt = L'간';
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

TEST(lang_test, ko_kr_postposition) {
  using namespace ext::lang::ko_kr::postposition;

  EXPECT_STREQ(topic(L"산").c_str(), L"은");
  EXPECT_STREQ(topic(L"바다").c_str(), L"는");

  EXPECT_STREQ(identifier(L"산").c_str(), L"이");
  EXPECT_STREQ(identifier(L"바다").c_str(), L"가");

  EXPECT_STREQ(objective(L"산").c_str(), L"을");
  EXPECT_STREQ(objective(L"바다").c_str(), L"를");

  EXPECT_STREQ(destination(L"산").c_str(), L"으로");
  EXPECT_STREQ(destination(L"바다").c_str(), L"로");

  EXPECT_STREQ(destination(L"산").c_str(), L"으로");
  EXPECT_STREQ(destination(L"바다").c_str(), L"로");

  EXPECT_STREQ(conjunction(L"산").c_str(), L"과");
  EXPECT_STREQ(conjunction(L"바다").c_str(), L"와");

  EXPECT_STREQ(vocative(L"산").c_str(), L"아");
  EXPECT_STREQ(vocative(L"바다").c_str(), L"야");

  EXPECT_STREQ(exclamation(L"산").c_str(), L"이여");
  EXPECT_STREQ(exclamation(L"바다").c_str(), L"여");
}
