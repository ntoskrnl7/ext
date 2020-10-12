#include <ext/base64>
#include <gtest/gtest.h>

TEST(base64_test, mbcs_test) {
  auto encoded_mbcs_text_mbcs = ext::base64::encode("1234");
  EXPECT_STREQ(encoded_mbcs_text_mbcs.c_str(), "MTIzNA==");

  auto encoded_mbcs_text_wcs = ext::base64::encode<wchar_t>("1234");
  EXPECT_STREQ(encoded_mbcs_text_wcs.c_str(), L"MTIzNA==");

  // decode_vec
  auto decoded_mbcs_text_vec = ext::base64::decode(encoded_mbcs_text_mbcs);
  decoded_mbcs_text_vec.push_back((std::byte)0);
  EXPECT_STREQ((char *)&decoded_mbcs_text_vec[0], "1234");

  decoded_mbcs_text_vec = ext::base64::decode(encoded_mbcs_text_wcs);
  decoded_mbcs_text_vec.push_back((std::byte)0);
  EXPECT_STREQ((char *)&decoded_mbcs_text_vec[0], "1234");

  // decode_str
  auto decoded_mbcs_text_mbcs = ext::base64::decode_str(encoded_mbcs_text_mbcs);
  EXPECT_STREQ(decoded_mbcs_text_mbcs.c_str(), "1234");

  decoded_mbcs_text_mbcs = ext::base64::decode_str(encoded_mbcs_text_wcs);
  EXPECT_STREQ(decoded_mbcs_text_mbcs.c_str(), "1234");

  auto decoded_mbcs_text_wcs =
      ext::base64::decode_str<wchar_t>(encoded_mbcs_text_mbcs);
  EXPECT_STREQ((char *)decoded_mbcs_text_wcs.c_str(), "1234");

  decoded_mbcs_text_wcs =
      ext::base64::decode_str<wchar_t>(encoded_mbcs_text_wcs);
  EXPECT_STREQ((char *)decoded_mbcs_text_wcs.c_str(), "1234");
}

TEST(base64_test, wcs_test) {
  auto encoded_wcs_text_mbcs = ext::base64::encode(L"1234");
  auto encoded_wcs_text_wcs = ext::base64::encode<wchar_t>(L"1234");
  if (sizeof(wchar_t) == 2) {
    EXPECT_STREQ(encoded_wcs_text_mbcs.c_str(), "MQAyADMANAA=");
    EXPECT_STREQ(encoded_wcs_text_wcs.c_str(), L"MQAyADMANAA=");
  } else if (sizeof(wchar_t) == 4) {
    EXPECT_STREQ(encoded_wcs_text_mbcs.c_str(), "MQAAADIAAAAzAAAANAAAAA==");
    EXPECT_STREQ(encoded_wcs_text_wcs.c_str(), L"MQAAADIAAAAzAAAANAAAAA==");
  }

  // decode_vec
  auto decoded_wcs_text_vec = ext::base64::decode(encoded_wcs_text_mbcs);
  for (size_t i = 0; i < sizeof(L'\0'); ++i)
    decoded_wcs_text_vec.push_back((std::byte)0);
  EXPECT_STREQ((wchar_t *)&decoded_wcs_text_vec[0], L"1234");

  decoded_wcs_text_vec = ext::base64::decode(encoded_wcs_text_wcs);
  for (size_t i = 0; i < sizeof(L'\0'); ++i)
    decoded_wcs_text_vec.push_back((std::byte)0);
  EXPECT_STREQ((wchar_t *)&decoded_wcs_text_vec[0], L"1234");

  // decode_str
  auto decoded_wcs_text_wcs =
      ext::base64::decode_str<wchar_t>(encoded_wcs_text_mbcs);
  EXPECT_STREQ(decoded_wcs_text_wcs.c_str(), L"1234");

  decoded_wcs_text_wcs = ext::base64::decode_str<wchar_t>(encoded_wcs_text_wcs);
  EXPECT_STREQ(decoded_wcs_text_wcs.c_str(), L"1234");

  auto decoded_wcs_text_mbcs = ext::base64::decode_str(encoded_wcs_text_mbcs);
  decoded_wcs_text_mbcs.push_back(0);
  EXPECT_STREQ((wchar_t *)decoded_wcs_text_mbcs.c_str(), L"1234");

  decoded_wcs_text_mbcs = ext::base64::decode_str(encoded_wcs_text_wcs);
  decoded_wcs_text_mbcs.push_back(0);
  EXPECT_STREQ((wchar_t *)decoded_wcs_text_mbcs.c_str(), L"1234");
}

TEST(base64_test, long_mbcs_test) {
  auto encoded_mbcs_text_mbcs = ext::base64::encode(
      "Man is distinguished, not only by his reason, but by this "
      "singular passion from other animals, which is a lust of the "
      "mind, that by a perseverance of delight in the continued and "
      "indefatigable generation of knowledge, exceeds the short "
      "vehemence of any carnal pleasure.");

  EXPECT_STREQ(encoded_mbcs_text_mbcs.c_str(),
               "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ"
               "1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLC"
               "B3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlc"
               "mFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdh"
               "YmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB"
               "2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=");

  auto encoded_mbcs_text_wcs = ext::base64::encode<wchar_t>(
      "Man is distinguished, not only by his reason, but by this "
      "singular passion from other animals, which is a lust of the "
      "mind, that by a perseverance of delight in the continued and "
      "indefatigable generation of knowledge, exceeds the short "
      "vehemence of any carnal pleasure.");

  EXPECT_STREQ(encoded_mbcs_text_wcs.c_str(),
               L"TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIG"
               L"J1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxz"
               L"LCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZX"
               L"ZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0"
               L"aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG"
               L"9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=");

  // decode_vec
  auto decoded_mbcs_text_vec = ext::base64::decode(encoded_mbcs_text_mbcs);
  decoded_mbcs_text_vec.push_back((std::byte)0);
  EXPECT_STREQ((char *)&decoded_mbcs_text_vec[0],
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");

  decoded_mbcs_text_vec = ext::base64::decode(encoded_mbcs_text_wcs);
  decoded_mbcs_text_vec.push_back((std::byte)0);
  EXPECT_STREQ((char *)&decoded_mbcs_text_vec[0],
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");

  // decode_str
  auto decoded_mbcs_text_mbcs = ext::base64::decode_str(encoded_mbcs_text_mbcs);
  EXPECT_STREQ(decoded_mbcs_text_mbcs.c_str(),
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");

  decoded_mbcs_text_mbcs = ext::base64::decode_str(encoded_mbcs_text_wcs);
  EXPECT_STREQ(decoded_mbcs_text_mbcs.c_str(),
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");

  auto decoded_mbcs_text_wcs =
      ext::base64::decode_str<wchar_t>(encoded_mbcs_text_mbcs);
  EXPECT_STREQ((char *)decoded_mbcs_text_wcs.c_str(),
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");

  decoded_mbcs_text_wcs =
      ext::base64::decode_str<wchar_t>(encoded_mbcs_text_wcs);
  EXPECT_STREQ((char *)decoded_mbcs_text_wcs.c_str(),
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");
}

TEST(base64_test, long_wcs_test) {
  auto encoded_wcs_text_mbcs = ext::base64::encode(
      L"Man is distinguished, not only by his reason, but by this "
      L"singular passion from other animals, which is a lust of the "
      L"mind, that by a perseverance of delight in the continued and "
      L"indefatigable generation of knowledge, exceeds the short "
      L"vehemence of any carnal pleasure.");

  if (sizeof(wchar_t) == 2)
    EXPECT_STREQ(encoded_wcs_text_mbcs.c_str(),
                 "TQBhAG4AIABpAHMAIABkAGkAcwB0AGkAbgBnAHUAaQBzAGgAZQBkACwAIABuA"
                 "G8AdAAgAG8A"
                 "bgBsAHkAIABiAHkAIABoAGkAcwAgAHIAZQBhAHMAbwBuACwAIABiAHUAdAAgA"
                 "GIAeQAgAHQA"
                 "aABpAHMAIABzAGkAbgBnAHUAbABhAHIAIABwAGEAcwBzAGkAbwBuACAAZgByA"
                 "G8AbQAgAG8A"
                 "dABoAGUAcgAgAGEAbgBpAG0AYQBsAHMALAAgAHcAaABpAGMAaAAgAGkAcwAgA"
                 "GEAIABsAHUA"
                 "cwB0ACAAbwBmACAAdABoAGUAIABtAGkAbgBkACwAIAB0AGgAYQB0ACAAYgB5A"
                 "CAAYQAgAHAA"
                 "ZQByAHMAZQB2AGUAcgBhAG4AYwBlACAAbwBmACAAZABlAGwAaQBnAGgAdAAgA"
                 "GkAbgAgAHQA"
                 "aABlACAAYwBvAG4AdABpAG4AdQBlAGQAIABhAG4AZAAgAGkAbgBkAGUAZgBhA"
                 "HQAaQBnAGEA"
                 "YgBsAGUAIABnAGUAbgBlAHIAYQB0AGkAbwBuACAAbwBmACAAawBuAG8AdwBsA"
                 "GUAZABnAGUA"
                 "LAAgAGUAeABjAGUAZQBkAHMAIAB0AGgAZQAgAHMAaABvAHIAdAAgAHYAZQBoA"
                 "GUAbQBlAG4A"
                 "YwBlACAAbwBmACAAYQBuAHkAIABjAGEAcgBuAGEAbAAgAHAAbABlAGEAcwB1A"
                 "HIAZQAuAA="
                 "=");
  else if (sizeof(wchar_t) == 4)
    EXPECT_STREQ(
        encoded_wcs_text_mbcs.c_str(),
        "TQAAAGEAAABuAAAAIAAAAGkAAABzAAAAIAAAAGQAAABpAAAAcwAAAHQAAABpAAAAbgAAAG"
        "cAAAB1AAAAaQAAAHMAAABoAAAAZQAAAGQAAAAsAAAAIAAAAG4AAABvAAAAdAAAACAAAABv"
        "AAAAbgAAAGwAAAB5AAAAIAAAAGIAAAB5AAAAIAAAAGgAAABpAAAAcwAAACAAAAByAAAAZQ"
        "AAAGEAAABzAAAAbwAAAG4AAAAsAAAAIAAAAGIAAAB1AAAAdAAAACAAAABiAAAAeQAAACAA"
        "AAB0AAAAaAAAAGkAAABzAAAAIAAAAHMAAABpAAAAbgAAAGcAAAB1AAAAbAAAAGEAAAByAA"
        "AAIAAAAHAAAABhAAAAcwAAAHMAAABpAAAAbwAAAG4AAAAgAAAAZgAAAHIAAABvAAAAbQAA"
        "ACAAAABvAAAAdAAAAGgAAABlAAAAcgAAACAAAABhAAAAbgAAAGkAAABtAAAAYQAAAGwAAA"
        "BzAAAALAAAACAAAAB3AAAAaAAAAGkAAABjAAAAaAAAACAAAABpAAAAcwAAACAAAABhAAAA"
        "IAAAAGwAAAB1AAAAcwAAAHQAAAAgAAAAbwAAAGYAAAAgAAAAdAAAAGgAAABlAAAAIAAAAG"
        "0AAABpAAAAbgAAAGQAAAAsAAAAIAAAAHQAAABoAAAAYQAAAHQAAAAgAAAAYgAAAHkAAAAg"
        "AAAAYQAAACAAAABwAAAAZQAAAHIAAABzAAAAZQAAAHYAAABlAAAAcgAAAGEAAABuAAAAYw"
        "AAAGUAAAAgAAAAbwAAAGYAAAAgAAAAZAAAAGUAAABsAAAAaQAAAGcAAABoAAAAdAAAACAA"
        "AABpAAAAbgAAACAAAAB0AAAAaAAAAGUAAAAgAAAAYwAAAG8AAABuAAAAdAAAAGkAAABuAA"
        "AAdQAAAGUAAABkAAAAIAAAAGEAAABuAAAAZAAAACAAAABpAAAAbgAAAGQAAABlAAAAZgAA"
        "AGEAAAB0AAAAaQAAAGcAAABhAAAAYgAAAGwAAABlAAAAIAAAAGcAAABlAAAAbgAAAGUAAA"
        "ByAAAAYQAAAHQAAABpAAAAbwAAAG4AAAAgAAAAbwAAAGYAAAAgAAAAawAAAG4AAABvAAAA"
        "dwAAAGwAAABlAAAAZAAAAGcAAABlAAAALAAAACAAAABlAAAAeAAAAGMAAABlAAAAZQAAAG"
        "QAAABzAAAAIAAAAHQAAABoAAAAZQAAACAAAABzAAAAaAAAAG8AAAByAAAAdAAAACAAAAB2"
        "AAAAZQAAAGgAAABlAAAAbQAAAGUAAABuAAAAYwAAAGUAAAAgAAAAbwAAAGYAAAAgAAAAYQ"
        "AAAG4AAAB5AAAAIAAAAGMAAABhAAAAcgAAAG4AAABhAAAAbAAAACAAAABwAAAAbAAAAGUA"
        "AABhAAAAcwAAAHUAAAByAAAAZQAAAC4AAAA=");

  auto encoded_wcs_text_wcs = ext::base64::encode<wchar_t>(
      L"Man is distinguished, not only by his reason, but by this "
      L"singular passion from other animals, which is a lust of the "
      L"mind, that by a perseverance of delight in the continued and "
      L"indefatigable generation of knowledge, exceeds the short "
      L"vehemence of any carnal pleasure.");
  if (sizeof(wchar_t) == 2)
    EXPECT_STREQ(encoded_wcs_text_wcs.c_str(),
                 L"TQBhAG4AIABpAHMAIABkAGkAcwB0AGkAbgBnAHUAaQBzAGgAZQBkACwAIABu"
                 L"AG8AdAAgAG8"
                 L"AbgBsAHkAIABiAHkAIABoAGkAcwAgAHIAZQBhAHMAbwBuACwAIABiAHUAdAA"
                 L"gAGIAeQAgAH"
                 L"QAaABpAHMAIABzAGkAbgBnAHUAbABhAHIAIABwAGEAcwBzAGkAbwBuACAAZg"
                 L"ByAG8AbQAgA"
                 L"G8AdABoAGUAcgAgAGEAbgBpAG0AYQBsAHMALAAgAHcAaABpAGMAaAAgAGkAc"
                 L"wAgAGEAIABs"
                 L"AHUAcwB0ACAAbwBmACAAdABoAGUAIABtAGkAbgBkACwAIAB0AGgAYQB0ACAA"
                 L"YgB5ACAAYQA"
                 L"gAHAAZQByAHMAZQB2AGUAcgBhAG4AYwBlACAAbwBmACAAZABlAGwAaQBnAGg"
                 L"AdAAgAGkAbg"
                 L"AgAHQAaABlACAAYwBvAG4AdABpAG4AdQBlAGQAIABhAG4AZAAgAGkAbgBkAG"
                 L"UAZgBhAHQAa"
                 L"QBnAGEAYgBsAGUAIABnAGUAbgBlAHIAYQB0AGkAbwBuACAAbwBmACAAawBuA"
                 L"G8AdwBsAGUA"
                 L"ZABnAGUALAAgAGUAeABjAGUAZQBkAHMAIAB0AGgAZQAgAHMAaABvAHIAdAAg"
                 L"AHYAZQBoAGU"
                 L"AbQBlAG4AYwBlACAAbwBmACAAYQBuAHkAIABjAGEAcgBuAGEAbAAgAHAAbAB"
                 L"lAGEAcwB1AH"
                 L"IAZQAuAA==");
  else if (sizeof(wchar_t) == 4)
    EXPECT_STREQ(
        encoded_wcs_text_wcs.c_str(),
        L"TQAAAGEAAABuAAAAIAAAAGkAAABzAAAAIAAAAGQAAABpAAAAcwAAAHQAAABpAAAAbgAAA"
        L"GcAAAB1AAAAaQAAAHMAAABoAAAAZQAAAGQAAAAsAAAAIAAAAG4AAABvAAAAdAAAACAAAA"
        L"BvAAAAbgAAAGwAAAB5AAAAIAAAAGIAAAB5AAAAIAAAAGgAAABpAAAAcwAAACAAAAByAAA"
        L"AZQAAAGEAAABzAAAAbwAAAG4AAAAsAAAAIAAAAGIAAAB1AAAAdAAAACAAAABiAAAAeQAA"
        L"ACAAAAB0AAAAaAAAAGkAAABzAAAAIAAAAHMAAABpAAAAbgAAAGcAAAB1AAAAbAAAAGEAA"
        L"AByAAAAIAAAAHAAAABhAAAAcwAAAHMAAABpAAAAbwAAAG4AAAAgAAAAZgAAAHIAAABvAA"
        L"AAbQAAACAAAABvAAAAdAAAAGgAAABlAAAAcgAAACAAAABhAAAAbgAAAGkAAABtAAAAYQA"
        L"AAGwAAABzAAAALAAAACAAAAB3AAAAaAAAAGkAAABjAAAAaAAAACAAAABpAAAAcwAAACAA"
        L"AABhAAAAIAAAAGwAAAB1AAAAcwAAAHQAAAAgAAAAbwAAAGYAAAAgAAAAdAAAAGgAAABlA"
        L"AAAIAAAAG0AAABpAAAAbgAAAGQAAAAsAAAAIAAAAHQAAABoAAAAYQAAAHQAAAAgAAAAYg"
        L"AAAHkAAAAgAAAAYQAAACAAAABwAAAAZQAAAHIAAABzAAAAZQAAAHYAAABlAAAAcgAAAGE"
        L"AAABuAAAAYwAAAGUAAAAgAAAAbwAAAGYAAAAgAAAAZAAAAGUAAABsAAAAaQAAAGcAAABo"
        L"AAAAdAAAACAAAABpAAAAbgAAACAAAAB0AAAAaAAAAGUAAAAgAAAAYwAAAG8AAABuAAAAd"
        L"AAAAGkAAABuAAAAdQAAAGUAAABkAAAAIAAAAGEAAABuAAAAZAAAACAAAABpAAAAbgAAAG"
        L"QAAABlAAAAZgAAAGEAAAB0AAAAaQAAAGcAAABhAAAAYgAAAGwAAABlAAAAIAAAAGcAAAB"
        L"lAAAAbgAAAGUAAAByAAAAYQAAAHQAAABpAAAAbwAAAG4AAAAgAAAAbwAAAGYAAAAgAAAA"
        L"awAAAG4AAABvAAAAdwAAAGwAAABlAAAAZAAAAGcAAABlAAAALAAAACAAAABlAAAAeAAAA"
        L"GMAAABlAAAAZQAAAGQAAABzAAAAIAAAAHQAAABoAAAAZQAAACAAAABzAAAAaAAAAG8AAA"
        L"ByAAAAdAAAACAAAAB2AAAAZQAAAGgAAABlAAAAbQAAAGUAAABuAAAAYwAAAGUAAAAgAAA"
        L"AbwAAAGYAAAAgAAAAYQAAAG4AAAB5AAAAIAAAAGMAAABhAAAAcgAAAG4AAABhAAAAbAAA"
        L"ACAAAABwAAAAbAAAAGUAAABhAAAAcwAAAHUAAAByAAAAZQAAAC4AAAA=");

  // decode_vec
  auto decoded_wcs_text_vec = ext::base64::decode(encoded_wcs_text_mbcs);
  for (size_t i = 0; i < sizeof(L'\0'); ++i)
    decoded_wcs_text_vec.push_back((std::byte)0);
  EXPECT_STREQ((wchar_t *)&decoded_wcs_text_vec[0],
               L"Man is distinguished, not only by his reason, but by this "
               L"singular passion from other animals, which is a lust of the "
               L"mind, that by a perseverance of delight in the continued and "
               L"indefatigable generation of knowledge, exceeds the short "
               L"vehemence of any carnal pleasure.");

  decoded_wcs_text_vec = ext::base64::decode(encoded_wcs_text_wcs);
  for (size_t i = 0; i < sizeof(L'\0'); ++i)
    decoded_wcs_text_vec.push_back((std::byte)0);
  EXPECT_STREQ((wchar_t *)&decoded_wcs_text_vec[0],
               L"Man is distinguished, not only by his reason, but by this "
               L"singular passion from other animals, which is a lust of the "
               L"mind, that by a perseverance of delight in the continued and "
               L"indefatigable generation of knowledge, exceeds the short "
               L"vehemence of any carnal pleasure.");

  // decode_str
  auto decoded_wcs_text_wcs =
      ext::base64::decode_str<wchar_t>(encoded_wcs_text_mbcs);
  EXPECT_STREQ(decoded_wcs_text_wcs.c_str(),
               L"Man is distinguished, not only by his reason, but by this "
               L"singular passion from other animals, which is a lust of the "
               L"mind, that by a perseverance of delight in the continued and "
               L"indefatigable generation of knowledge, exceeds the short "
               L"vehemence of any carnal pleasure.");

  decoded_wcs_text_wcs = ext::base64::decode_str<wchar_t>(encoded_wcs_text_wcs);
  EXPECT_STREQ(decoded_wcs_text_wcs.c_str(),
               L"Man is distinguished, not only by his reason, but by this "
               L"singular passion from other animals, which is a lust of the "
               L"mind, that by a perseverance of delight in the continued and "
               L"indefatigable generation of knowledge, exceeds the short "
               L"vehemence of any carnal pleasure.");

  auto decoded_wcs_text_mbcs = ext::base64::decode_str(encoded_wcs_text_mbcs);
  decoded_wcs_text_mbcs.push_back(0);
  EXPECT_STREQ((wchar_t *)decoded_wcs_text_mbcs.c_str(),
               L"Man is distinguished, not only by his reason, but by this "
               L"singular passion from other animals, which is a lust of the "
               L"mind, that by a perseverance of delight in the continued and "
               L"indefatigable generation of knowledge, exceeds the short "
               L"vehemence of any carnal pleasure.");

  decoded_wcs_text_mbcs = ext::base64::decode_str(encoded_wcs_text_wcs);
  decoded_wcs_text_mbcs.push_back(0);
  EXPECT_STREQ((wchar_t *)decoded_wcs_text_mbcs.c_str(),
               L"Man is distinguished, not only by his reason, but by this "
               L"singular passion from other animals, which is a lust of the "
               L"mind, that by a perseverance of delight in the continued and "
               L"indefatigable generation of knowledge, exceeds the short "
               L"vehemence of any carnal pleasure.");
}

TEST(base64_text, rfc_2045) {

  auto decoded_mbcs_text_mbcs = ext::base64::decode_str(
      R"(TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz
IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg
dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu
dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo
ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=)");

  EXPECT_STREQ(decoded_mbcs_text_mbcs.c_str(),
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");
  if (sizeof(wchar_t) == 2) {
    auto decoded_wcs_text_wcs = ext::base64::decode_str<wchar_t>(
        R"(TQBhAG4AIABpAHMAIABkAGkAcwB0AGkAbgBnAHUAaQBzAGgAZQBkACwAIABuAG8AdAAgAG8AbgBs
AHkAIABiAHkAIABoAGkAcwAgAHIAZQBhAHMAbwBuACwAIABiAHUAdAAgAGIAeQAgAHQAaABpAHMA
IABzAGkAbgBnAHUAbABhAHIAIABwAGEAcwBzAGkAbwBuACAAZgByAG8AbQAgAG8AdABoAGUAcgAg
AGEAbgBpAG0AYQBsAHMALAAgAHcAaABpAGMAaAAgAGkAcwAgAGEAIABsAHUAcwB0ACAAbwBmACAA
dABoAGUAIABtAGkAbgBkACwAIAB0AGgAYQB0ACAAYgB5ACAAYQAgAHAAZQByAHMAZQB2AGUAcgBh
AG4AYwBlACAAbwBmACAAZABlAGwAaQBnAGgAdAAgAGkAbgAgAHQAaABlACAAYwBvAG4AdABpAG4A
dQBlAGQAIABhAG4AZAAgAGkAbgBkAGUAZgBhAHQAaQBnAGEAYgBsAGUAIABnAGUAbgBlAHIAYQB0
AGkAbwBuACAAbwBmACAAawBuAG8AdwBsAGUAZABnAGUALAAgAGUAeABjAGUAZQBkAHMAIAB0AGgA
ZQAgAHMAaABvAHIAdAAgAHYAZQBoAGUAbQBlAG4AYwBlACAAbwBmACAAYQBuAHkAIABjAGEAcgBu
AGEAbAAgAHAAbABlAGEAcwB1AHIAZQAuAA==)");
    EXPECT_STREQ(
        decoded_wcs_text_wcs.c_str(),
        L"Man is distinguished, not only by his reason, but by this "
        L"singular passion from other animals, which is a lust of the "
        L"mind, that by a perseverance of delight in the continued and "
        L"indefatigable generation of knowledge, exceeds the short "
        L"vehemence of any carnal pleasure.");
  } else if (sizeof(wchar_t) == 4) {
    auto decoded_wcs_text_wcs = ext::base64::decode_str<wchar_t>(
        R"(TQAAAGEAAABuAAAAIAAAAGkAAABzAAAAIAAAAGQAAABpAAAAcwAAAHQAAABpAAAAbgAAAGcAAAB1
AAAAaQAAAHMAAABoAAAAZQAAAGQAAAAsAAAAIAAAAG4AAABvAAAAdAAAACAAAABvAAAAbgAAAGwA
AAB5AAAAIAAAAGIAAAB5AAAAIAAAAGgAAABpAAAAcwAAACAAAAByAAAAZQAAAGEAAABzAAAAbwAA
AG4AAAAsAAAAIAAAAGIAAAB1AAAAdAAAACAAAABiAAAAeQAAACAAAAB0AAAAaAAAAGkAAABzAAAA
IAAAAHMAAABpAAAAbgAAAGcAAAB1AAAAbAAAAGEAAAByAAAAIAAAAHAAAABhAAAAcwAAAHMAAABp
AAAAbwAAAG4AAAAgAAAAZgAAAHIAAABvAAAAbQAAACAAAABvAAAAdAAAAGgAAABlAAAAcgAAACAA
AABhAAAAbgAAAGkAAABtAAAAYQAAAGwAAABzAAAALAAAACAAAAB3AAAAaAAAAGkAAABjAAAAaAAA
ACAAAABpAAAAcwAAACAAAABhAAAAIAAAAGwAAAB1AAAAcwAAAHQAAAAgAAAAbwAAAGYAAAAgAAAA
dAAAAGgAAABlAAAAIAAAAG0AAABpAAAAbgAAAGQAAAAsAAAAIAAAAHQAAABoAAAAYQAAAHQAAAAg
AAAAYgAAAHkAAAAgAAAAYQAAACAAAABwAAAAZQAAAHIAAABzAAAAZQAAAHYAAABlAAAAcgAAAGEA
AABuAAAAYwAAAGUAAAAgAAAAbwAAAGYAAAAgAAAAZAAAAGUAAABsAAAAaQAAAGcAAABoAAAAdAAA
ACAAAABpAAAAbgAAACAAAAB0AAAAaAAAAGUAAAAgAAAAYwAAAG8AAABuAAAAdAAAAGkAAABuAAAA
dQAAAGUAAABkAAAAIAAAAGEAAABuAAAAZAAAACAAAABpAAAAbgAAAGQAAABlAAAAZgAAAGEAAAB0
AAAAaQAAAGcAAABhAAAAYgAAAGwAAABlAAAAIAAAAGcAAABlAAAAbgAAAGUAAAByAAAAYQAAAHQA
AABpAAAAbwAAAG4AAAAgAAAAbwAAAGYAAAAgAAAAawAAAG4AAABvAAAAdwAAAGwAAABlAAAAZAAA
AGcAAABlAAAALAAAACAAAABlAAAAeAAAAGMAAABlAAAAZQAAAGQAAABzAAAAIAAAAHQAAABoAAAA
ZQAAACAAAABzAAAAaAAAAG8AAAByAAAAdAAAACAAAAB2AAAAZQAAAGgAAABlAAAAbQAAAGUAAABu
AAAAYwAAAGUAAAAgAAAAbwAAAGYAAAAgAAAAYQAAAG4AAAB5AAAAIAAAAGMAAABhAAAAcgAAAG4A
AABhAAAAbAAAACAAAABwAAAAbAAAAGUAAABhAAAAcwAAAHUAAAByAAAAZQAAAC4AAAA=
)");
    EXPECT_STREQ(
        decoded_wcs_text_wcs.c_str(),
        L"Man is distinguished, not only by his reason, but by this "
        L"singular passion from other animals, which is a lust of the "
        L"mind, that by a perseverance of delight in the continued and "
        L"indefatigable generation of knowledge, exceeds the short "
        L"vehemence of any carnal pleasure.");
  }
}

TEST(base64_test, byte_vector_test) {
  std::vector<std::byte> vec = {(std::byte)1, (std::byte)2, (std::byte)3,
                                (std::byte)4, (std::byte)5};

  auto encoded_data_a = ext::base64::encode(vec);
  auto encoded_data_w = ext::base64::encode<wchar_t>(vec);
  EXPECT_STREQ(encoded_data_a.c_str(), "AQIDBAU=");
  EXPECT_STREQ(encoded_data_w.c_str(), L"AQIDBAU=");

  auto decoded_data_a = ext::base64::decode(encoded_data_a);
  EXPECT_EQ(decoded_data_a[0], 1);
  EXPECT_EQ(decoded_data_a[1], 2);
  EXPECT_EQ(decoded_data_a[2], 3);
  EXPECT_EQ(decoded_data_a[3], 4);
  EXPECT_EQ(decoded_data_a[4], 5);

  auto decoded_data_w = ext::base64::decode(encoded_data_w);
  EXPECT_EQ(decoded_data_w[0], 1);
  EXPECT_EQ(decoded_data_w[1], 2);
  EXPECT_EQ(decoded_data_w[2], 3);
  EXPECT_EQ(decoded_data_w[3], 4);
  EXPECT_EQ(decoded_data_w[4], 5);
}

template <typename T> class struct_wrapper {
public:
  struct_wrapper(std::vector<std::byte> data) { data_ = std::move(data); }

  T *operator->() { return reinterpret_cast<T *>(&data_[0]); }

private:
  std::vector<std::byte> data_;
};

TEST(base64_test, struct_test) {
  typedef struct {
    int a;
    int b;
    char c;
    double d;
  } data_s;

  data_s data = {
      0,
  };
  data.a = 10;
  data.b = 20;
  data.c = 'a';
  data.d = 30.30;

  auto encoded_data_a = ext::base64::encode(data);
  auto encoded_data_w = ext::base64::encode<wchar_t>(data);

  EXPECT_STREQ(encoded_data_a.c_str(), "CgAAABQAAABhAAAAAAAAAM3MzMzMTD5A");
  EXPECT_STREQ(encoded_data_w.c_str(), L"CgAAABQAAABhAAAAAAAAAM3MzMzMTD5A");

  auto decoded_data_a = ext::base64::decode_shared_ptr<data_s>(encoded_data_a);
  auto decoded_data_w = ext::base64::decode_shared_ptr<data_s>(encoded_data_w);

  EXPECT_EQ(decoded_data_a->a, 10);
  EXPECT_EQ(decoded_data_a->b, 20);
  EXPECT_EQ(decoded_data_a->c, 'a');
  EXPECT_EQ(decoded_data_a->d, 30.30);

  EXPECT_EQ(decoded_data_w->a, 10);
  EXPECT_EQ(decoded_data_w->b, 20);
  EXPECT_EQ(decoded_data_w->c, 'a');
  EXPECT_EQ(decoded_data_w->d, 30.30);

  struct_wrapper<data_s> result(ext::base64::decode(encoded_data_a));
  EXPECT_EQ(result->a, 10);
  EXPECT_EQ(result->b, 20);
  EXPECT_EQ(result->c, 'a');
  EXPECT_EQ(result->d, 30.30);
}