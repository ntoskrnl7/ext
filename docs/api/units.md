# units

[Back to API reference](README.md)

## Header

`#include <ext/units>`

- SI
- IEC

## Overview

Defines unit wrapper types for decimal SI and binary IEC quantities. Tests cover construction, conversion, arithmetic, and suffix-style usage.

## Key APIs

- `ext::units::si` provides decimal kilo/mega/giga-style units.
- `ext::units::iec` provides binary kibi/mebi/gibi-style units.
- Unit values support arithmetic and conversion back to their base numeric representation.
- Convenience aliases and suffix-like helpers make expressions readable.

## Behavior Notes

- Use SI units for powers of 1000 and IEC units for powers of 1024.
- The wrappers are compile-time typed so mixed-unit expressions are clearer than raw integers.

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

  size_t iec_value = 5_MiB;
  // iec_value == 5 * ext::units::IEC::MiB

  std::string iec_str = 5_MiB;
  // iec_str == "5MiB"

  std::wstring iec_wstr = 5_MiB;
  // iec_wstr == L"5MiB"

  // SI
  using namespace ext::units::SI::literals;
  size_t metric_value = 5_mB;
  // metric_value == 5 * ext::units::SI::mB

  std::string metric_str = 5_mB;
  // metric_str == "5mB"

  std::wstring metric_wstr = 5_mB;
  // metric_wstr == L"5mB"
  ```
