#include <ext/units>
#include <gtest/gtest.h>

TEST(units_test, SI) {
  EXPECT_EQ(ext::units::to_size_t("5mB"), 5 * ext::units::SI::mB);
  EXPECT_STRCASEEQ(
      ext::units::to_string(5 * ext::units::SI::mB, ext::units::POLICY_SI)
          .c_str(),
      "5mB");

  EXPECT_EQ(ext::units::to_size_t("2tB"), 2 * ext::units::SI::tB);
  EXPECT_STRCASEEQ(
      ext::units::to_string(2 * ext::units::SI::tB, ext::units::POLICY_SI)
          .c_str(),
      "2tB");
}

TEST(units_test, IEC) {
  EXPECT_EQ(ext::units::to_size_t("5MiB"), 5 * ext::units::IEC::MiB);
  EXPECT_STRCASEEQ(
      ext::units::to_string(5 * ext::units::IEC::MiB, ext::units::POLICY_IEC)
          .c_str(),
      "5MiB");

  EXPECT_EQ(ext::units::to_size_t("2TiB"), 2 * ext::units::IEC::TiB);
  EXPECT_STRCASEEQ(
      ext::units::to_string(2 * ext::units::IEC::TiB, ext::units::POLICY_IEC)
          .c_str(),
      "2TiB");
}
