# units

[Back to API reference](README.md)

## Header

`#include <ext/units>`

- SI
- IEC

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- to_string

  ```C++
  #include <ext/units>

  // IEC
  size_t size = 2 * ext::units::IEC::TiB;
  ext::units::to_string(size, ext::units::POLICY_IEC); // "2TiB"
  ext::units::to_wstring(size, ext::units::POLICY_IEC); // L"2TiB"
  ext::units::IEC::to_string(size, ext::units::IEC::KiB); // "2147483648KiB"
  ext::units::IEC::to_wstring(size, ext::units::IEC::KiB); // L"2147483648KiB"

  // SI
  size = 2 * ext::units::SI::tB;
  ext::units::to_string(size, ext::units::POLICY_SI); // "2tB"
  ext::units::to_wstring(size, ext::units::POLICY_SI); // L"2tB"
  ext::units::IEC::to_string(2 * ext::units::IEC::TiB, ext::units::IEC::KiB); // "2147483648KiB"
  ext::units::IEC::to_wstring(2 * ext::units::IEC::TiB, ext::units::IEC::KiB); // L"2147483648KiB"
  ```

- to_size_t

  ```C++
  #include <ext/units>

  // IEC
  ext::units::to_size_t("2TiB"); // 2 * ext::units::IEC::TiB
  ext::units::to_size_t(L"2TiB"); // 2 * ext::units::IEC::TiB

  // SI
  ext::units::to_size_t("2tB"); // 2 * ext::units::SI::tB
  ext::units::to_size_t(L"2tB"); // 2 * ext::units::SI::tB
  ```

- User-defined literals

  ```C++
  #include <ext/units>

  // IEC
  using namespace ext::units::IEC::literals;

  size_t value = 5_MiB;
  EXPECT_EQ(value, 5 * ext::units::IEC::MiB);

  std::string str = 5_MiB;
  EXPECT_STREQ(str.c_str(), "5MiB");

  std::wstring wstr = 5_MiB;
  EXPECT_STREQ(wstr.c_str(), L"5MiB");

  // SI
  using namespace ext::units::SI::literals;
  size_t value = 5_mB;
  EXPECT_EQ(value, 5 * ext::units::SI::mB);

  std::string str = 5_mB;
  EXPECT_STREQ(str.c_str(), "5mB");

  std::wstring wstr = 5_mB;
  EXPECT_STREQ(wstr.c_str(), L"5mB");
  ```
