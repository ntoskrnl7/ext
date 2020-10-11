#include <ext/base64>
#include <gtest/gtest.h>

TEST(base64_test, simple_test) {
  auto encoded_data_a = ext::base64::encode("1234");
  auto encoded_data_w = ext::base64::encode<wchar_t>("1234");
  EXPECT_STREQ(encoded_data_a.c_str(), "MTIzNA==");
  EXPECT_STREQ(encoded_data_w.c_str(), L"MTIzNA==");

  auto decoded_data_a = ext::base64::decode(encoded_data_a);
  decoded_data_a.push_back(0);

  auto decoded_data_w = ext::base64::decode(encoded_data_w);
  decoded_data_w.push_back(0);

  EXPECT_STREQ((char *)&decoded_data_a[0], "1234");
  EXPECT_STREQ((char *)&decoded_data_w[0], "1234");

  encoded_data_a = ext::base64::encode(L"1234");
  encoded_data_w = ext::base64::encode<wchar_t>(L"1234");
  EXPECT_STREQ(encoded_data_a.c_str(), "MQAyADMANAA=");
  EXPECT_STREQ(encoded_data_w.c_str(), L"MQAyADMANAA=");

  decoded_data_a = ext::base64::decode(encoded_data_a);
  for (size_t i = 0; i < sizeof(L'\0'); ++i)
    decoded_data_a.push_back(0);

  decoded_data_w = ext::base64::decode(encoded_data_w);
  for (size_t i = 0; i < sizeof(L'\0'); ++i)
    decoded_data_w.push_back(0);

  EXPECT_STREQ((wchar_t *)&decoded_data_a[0], L"1234");
  EXPECT_STREQ((wchar_t *)&decoded_data_w[0], L"1234");

  encoded_data_a = ext::base64::encode(
      "Man is distinguished, not only by his reason, but by this "
      "singular passion from other animals, which is a lust of the "
      "mind, that by a perseverance of delight in the continued and "
      "indefatigable generation of knowledge, exceeds the short "
      "vehemence of any carnal pleasure.");

  encoded_data_w = ext::base64::encode<wchar_t>(
      "Man is distinguished, not only by his reason, but by this "
      "singular passion from other animals, which is a lust of the "
      "mind, that by a perseverance of delight in the continued and "
      "indefatigable generation of knowledge, exceeds the short "
      "vehemence of any carnal pleasure.");

  EXPECT_STREQ(encoded_data_a.c_str(),
               "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ"
               "1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLC"
               "B3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlc"
               "mFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdh"
               "YmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB"
               "2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=");
  EXPECT_STREQ(encoded_data_w.c_str(),
               L"TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIG"
               L"J1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxz"
               L"LCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZX"
               L"ZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0"
               L"aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG"
               L"9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=");

  decoded_data_a = ext::base64::decode(encoded_data_a);
  decoded_data_a.push_back(0);

  decoded_data_w = ext::base64::decode(encoded_data_w);
  decoded_data_w.push_back(0);

  EXPECT_STREQ((char *)&decoded_data_a[0],
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");

  EXPECT_STREQ((char *)&decoded_data_w[0],
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");

  decoded_data_a = ext::base64::decode(std::string(
      R"(TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz
IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg
dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu
dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo
ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=)"));
  decoded_data_a.push_back(0);

  decoded_data_w = ext::base64::decode(std::wstring(
      LR"(TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz
IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg
dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu
dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo
ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=)"));
  decoded_data_w.push_back(0);

  EXPECT_STREQ((char *)&decoded_data_a[0],
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");

  EXPECT_STREQ((char *)&decoded_data_w[0],
               "Man is distinguished, not only by his reason, but by this "
               "singular passion from other animals, which is a lust of the "
               "mind, that by a perseverance of delight in the continued and "
               "indefatigable generation of knowledge, exceeds the short "
               "vehemence of any carnal pleasure.");
}

TEST(base64_test, struct_test) {
  typedef struct {
    int a;
    int b;
    char c;
    double d;
  } data_s;

  data_s data;
  data.a = 10;
  data.b = 20;
  data.c = 'a';
  data.d = 30.30;

  auto encoded_data_a = ext::base64::encode(data);
  auto encoded_data_w = ext::base64::encode<wchar_t>(data);

  EXPECT_STREQ(encoded_data_a.c_str(), "CgAAABQAAABhzMzMzMzMzM3MzMzMTD5A");
  EXPECT_STREQ(encoded_data_w.c_str(), L"CgAAABQAAABhzMzMzMzMzM3MzMzMTD5A");

  auto decoded_data_a = ext::base64::decode<data_s>(encoded_data_a);
  auto decoded_data_w = ext::base64::decode<data_s>(encoded_data_w);

  EXPECT_EQ(decoded_data_a->a, 10);
  EXPECT_EQ(decoded_data_a->b, 20);
  EXPECT_EQ(decoded_data_a->c, 'a');
  EXPECT_EQ(decoded_data_a->d, 30.30);

  EXPECT_EQ(decoded_data_w->a, 10);
  EXPECT_EQ(decoded_data_w->b, 20);
  EXPECT_EQ(decoded_data_w->c, 'a');
  EXPECT_EQ(decoded_data_w->d, 30.30);
}