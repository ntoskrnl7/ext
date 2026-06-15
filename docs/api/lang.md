# lang

[Back to API reference](README.md)

## Header

`#include <ext/lang>`

## Overview

Provides `ext::lang::ko_kr` utilities for decomposing Hangul syllables, choosing Korean postpositions, and converting numeric values into Korean nominal, ordinal, and cardinal forms.

## Key APIs

- `ko_kr::numeric::{nominal, ordinal, cardinal}` return UTF-8 string forms.
- `ko_kr::numeric::{wnominal, wordinal, wcardinal}` return wide-string forms.
- `ko_kr::syllable::{onset, nucleus, coda}` decompose Hangul syllable characters.
- `ko_kr::postposition` selects topic, identifier, objective, destination, conjunction, vocative, and exclamation particles.

## Behavior Notes

- `syllable::letter` reports invalid input for non-syllables while retaining recognized jamo where possible.
- Syllable helpers validate the Unicode Hangul syllable range before decomposition.
- Postposition selection is based on whether the final syllable has a coda.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- ko_kr::syllable

  ```C++
  #include <ext/lang>

  ext::lang::ko_kr::syllable::letter lt = L'a';
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
  ```

- ko_kr::postposition

  ```C++
  #include <ext/lang>

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
  ```

- ko_kr::numeric

  ```C++
  #include <ext/lang>

  using namespace ext::lang::ko_kr;

  EXPECT_STREQ(numeric::nominal(1).c_str(), "일");
  EXPECT_STREQ(numeric::nominal(2).c_str(), "이");
  EXPECT_STREQ(numeric::nominal(3).c_str(), "삼");

  EXPECT_STREQ(numeric::ordinal(1).c_str(), "첫째");
  EXPECT_STREQ(numeric::ordinal(2).c_str(), "둘째");
  EXPECT_STREQ(numeric::ordinal(3).c_str(), "셋째");

  EXPECT_STREQ(numeric::ordinal(1, " 번째").c_str(), "첫 번째");
  EXPECT_STREQ(numeric::ordinal(2, " 번째").c_str(), "두 번째");
  EXPECT_STREQ(numeric::ordinal(3, " 번째").c_str(), "세 번째");

  EXPECT_STREQ(numeric::cardinal(1).c_str(), "하나");
  EXPECT_STREQ(numeric::cardinal(2).c_str(), "둘");
  EXPECT_STREQ(numeric::cardinal(3).c_str(), "셋");

  EXPECT_STREQ(numeric::cardinal(1, " 번").c_str(), "한 번");
  EXPECT_STREQ(numeric::cardinal(2, " 번").c_str(), "두 번");
  EXPECT_STREQ(numeric::cardinal(3, " 번").c_str(), "세 번");


  EXPECT_STREQ(numeric::wnominal(1).c_str(), L"일");
  EXPECT_STREQ(numeric::wnominal(2).c_str(), L"이");
  EXPECT_STREQ(numeric::wnominal(3).c_str(), L"삼");

  EXPECT_STREQ(numeric::wordinal(1).c_str(), L"첫째");
  EXPECT_STREQ(numeric::wordinal(2).c_str(), L"둘째");
  EXPECT_STREQ(numeric::wordinal(3).c_str(), L"셋째");

  EXPECT_STREQ(numeric::wordinal(1, L" 번째").c_str(), L"첫 번째");
  EXPECT_STREQ(numeric::wordinal(2, L" 번째").c_str(), L"두 번째");
  EXPECT_STREQ(numeric::wordinal(3, L" 번째").c_str(), L"세 번째");

  EXPECT_STREQ(numeric::wcardinal(1).c_str(), L"하나");
  EXPECT_STREQ(numeric::wcardinal(2).c_str(), L"둘");
  EXPECT_STREQ(numeric::wcardinal(3).c_str(), L"셋");

  EXPECT_STREQ(numeric::wcardinal(1, L" 번").c_str(), L"한 번");
  EXPECT_STREQ(numeric::wcardinal(2, L" 번").c_str(), L"두 번");
  EXPECT_STREQ(numeric::wcardinal(3, L" 번").c_str(), L"세 번");
  ```
