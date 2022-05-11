#include <ext/units>
#include <gtest/gtest.h>

#include <iostream>

TEST(units_test, SI) {
#if defined(__cpp_user_defined_literals)
  using namespace ext::units::SI::literals;
  size_t value = 5_mB;
  EXPECT_EQ(value, 5 * ext::units::SI::mB);

  std::string str = 5_mB;
  EXPECT_STREQ(str.c_str(), "5mB");

  std::wstring wstr = 5_mB;
  EXPECT_STREQ(wstr.c_str(), L"5mB");
#endif // defined(__cpp_user_defined_literals)
  EXPECT_STREQ(ext::units::SI::to_string(1000 * ext::units::SI::kB).c_str(),
               "1000kB");
  EXPECT_STREQ(ext::units::SI::to_wstring(1000 * ext::units::SI::kB).c_str(),
               L"1000kB");

  EXPECT_STREQ(ext::units::SI::to_string(10000 * ext::units::SI::kB).c_str(),
               "10mB");
  EXPECT_STREQ(ext::units::SI::to_wstring(10000 * ext::units::SI::kB).c_str(),
               L"10mB");

  EXPECT_EQ(ext::units::to_size_t("5gB"), 5 * ext::units::SI::gB);
  EXPECT_EQ(ext::units::to_size_t(L"5gB"), 5 * ext::units::SI::gB);
  EXPECT_STREQ(
      ext::units::to_string(5 * ext::units::SI::gB, ext::units::POLICY_SI)
          .c_str(),
      "5gB");
  EXPECT_STREQ(
      ext::units::to_wstring(5 * ext::units::SI::gB, ext::units::POLICY_SI)
          .c_str(),
      L"5gB");

  EXPECT_EQ(ext::units::to_size_t("2tB"), 2 * ext::units::SI::tB);
  EXPECT_EQ(ext::units::to_size_t(L"2tB"), 2 * ext::units::SI::tB);
  EXPECT_STREQ(
      ext::units::to_string(2 * ext::units::SI::tB, ext::units::POLICY_SI)
          .c_str(),
      "2tB");
  EXPECT_STREQ(
      ext::units::to_wstring(2 * ext::units::SI::tB, ext::units::POLICY_SI)
          .c_str(),
      L"2tB");

  EXPECT_STREQ(
      ext::units::SI::to_string(2 * ext::units::SI::tB, ext::units::SI::kB)
          .c_str(),
      "2000000000kB");
  EXPECT_STREQ(
      ext::units::SI::to_wstring(2 * ext::units::SI::tB, ext::units::SI::kB)
          .c_str(),
      L"2000000000kB");
}

TEST(units_test, IEC) {
#if defined(__cpp_user_defined_literals)
  using namespace ext::units::IEC::literals;
  size_t value = 5_MiB;
  EXPECT_EQ(value, 5 * ext::units::IEC::MiB);

  std::string str = 5_MiB;
  EXPECT_STREQ(str.c_str(), "5MiB");

  std::wstring wstr = 5_MiB;
  EXPECT_STREQ(wstr.c_str(), L"5MiB");
#endif // defined(__cpp_user_defined_literals)
  EXPECT_STREQ(ext::units::IEC::to_string(1000 * ext::units::IEC::KiB).c_str(),
               "1000KiB");
  EXPECT_STREQ(ext::units::IEC::to_wstring(1000 * ext::units::IEC::KiB).c_str(),
               L"1000KiB");

  EXPECT_STREQ(ext::units::IEC::to_string(10000 * ext::units::IEC::KiB).c_str(),
               "9MiB");
  EXPECT_STREQ(
      ext::units::IEC::to_wstring(10000 * ext::units::IEC::KiB).c_str(),
      L"9MiB");

  EXPECT_EQ(ext::units::to_size_t("5GiB"), 5 * ext::units::IEC::GiB);
  EXPECT_EQ(ext::units::to_size_t(L"5GiB"), 5 * ext::units::IEC::GiB);
  EXPECT_STREQ(
      ext::units::to_string(5 * ext::units::IEC::GiB, ext::units::POLICY_IEC)
          .c_str(),
      "5GiB");
  EXPECT_STREQ(
      ext::units::to_wstring(5 * ext::units::IEC::GiB, ext::units::POLICY_IEC)
          .c_str(),
      L"5GiB");

  EXPECT_EQ(ext::units::to_size_t("2TiB"), 2 * ext::units::IEC::TiB);
  EXPECT_EQ(ext::units::to_size_t(L"2TiB"), 2 * ext::units::IEC::TiB);
  EXPECT_STREQ(
      ext::units::to_string(2 * ext::units::IEC::TiB, ext::units::POLICY_IEC)
          .c_str(),
      "2TiB");
  EXPECT_STREQ(
      ext::units::to_wstring(2 * ext::units::IEC::TiB, ext::units::POLICY_IEC)
          .c_str(),
      L"2TiB");

  EXPECT_STREQ(
      ext::units::IEC::to_string(2 * ext::units::IEC::TiB, ext::units::IEC::KiB)
          .c_str(),
      "2147483648KiB");
  EXPECT_STREQ(ext::units::IEC::to_wstring(2 * ext::units::IEC::TiB,
                                           ext::units::IEC::KiB)
                   .c_str(),
               L"2147483648KiB");
}