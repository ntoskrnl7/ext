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

  using namespace ext::lang::ko_kr::syllable;

  letter lt = L'간';
  bool valid = lt.valid(); // true

  wchar_t first = lt.onset; // L'ㄱ'
  wchar_t middle = lt.nucleus; // L'ㅏ'
  wchar_t last = lt.coda; // L'ㄴ'

  letter consonant = L'ㄱ';
  bool consonant_is_syllable = consonant.valid(); // false
  wchar_t consonant_onset = consonant.onset; // L'ㄱ'
  ```

- ko_kr::postposition

  ```C++
  #include <ext/lang>

  using namespace ext::lang::ko_kr;

  std::wstring topic = postposition::topic(L"산"); // L"은"
  std::wstring topic_without_coda = postposition::topic(L"바다"); // L"는"

  std::wstring subject = postposition::identifier(L"산"); // L"이"
  std::wstring object = postposition::objective(L"바다"); // L"를"
  std::wstring destination = postposition::destination(L"산"); // L"으로"
  std::wstring conjunction = postposition::conjunction(L"바다"); // L"와"
  ```

- ko_kr::numeric

  ```C++
  #include <ext/lang>

  using namespace ext::lang::ko_kr;

  std::string nominal = numeric::nominal(3); // "삼"
  std::string ordinal = numeric::ordinal(3); // "셋째"
  std::string ordinal_with_suffix = numeric::ordinal(3, " 번째"); // "세 번째"
  std::string cardinal = numeric::cardinal(3); // "셋"
  std::string counted = numeric::cardinal(3, " 번"); // "세 번"

  std::wstring wide_nominal = numeric::wnominal(3); // L"삼"
  std::wstring wide_ordinal = numeric::wordinal(3); // L"셋째"
  std::wstring wide_cardinal = numeric::wcardinal(3); // L"셋"
  ```
