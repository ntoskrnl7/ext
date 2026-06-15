# units

[Back to API reference](README.md)

## Header

`#include <ext/units>`

- SI
- IEC

## Overview

Defines unit constants, typed size wrappers, string formatters, parsers, and
user-defined literals for decimal SI and binary IEC byte quantities.

## Key APIs

- `ext::units::POLICY` selects unknown, IEC, or SI formatting through
  `POLICY_UNKNOWN`, `POLICY_IEC`, and `POLICY_SI`.
- `ext::units::IEC::UNIT` contains `B`, `KiB`, `MiB`, `GiB`, `TiB`, `PiB`,
  `EiB`, and `UNSPECIFIED`.
- `ext::units::SI::UNIT` contains `B`, `kB`, `mB`, `gB`, `tB`, `pB`, `eB`, and
  `UNSPECIFIED`.
- `ext::units::IEC::size<Unit>` and `ext::units::SI::size<Unit>` store a unit
  count and convert to byte count, `std::string`, or `std::wstring`.
- `ext::units::IEC::parse_size<CharT>(bytes, unit)` and
  `ext::units::SI::parse_size<CharT>(bytes, unit)` return a numeric value plus
  a unit suffix.
- `ext::units::IEC::to_string/to_wstring` and
  `ext::units::SI::to_string/to_wstring` format byte counts with a selected or
  inferred unit.
- `ext::units::to_string/to_wstring(bytes, policy)` dispatch to IEC, SI, or raw
  bytes.
- `ext::units::to_size_t("2MiB")` and `to_size_t(L"2MiB")` parse IEC, SI, or
  byte strings into byte counts.
- `ext::units::IEC::literals` provides `_KiB`, `_MiB`, `_GiB`, `_TiB`, `_PiB`,
  and `_EiB`.
- `ext::units::SI::literals` provides `_kB`, `_mB`, `_gB`, `_tB`, `_pB`, and
  `_eB`.

## Behavior Notes

- Use SI units for powers of 1000 and IEC units for powers of 1024.
- `B` has the value `0` in both unit enums. It is a sentinel for formatting
  rather than a multiplier type to instantiate as `size<B>`.
- `parse_size` and `to_string` choose a larger unit only when the byte count is
  strictly greater than the threshold, not equal to it.
- Formatting uses integer division; fractional values are not emitted.
- `to_size_t` recognizes uppercase IEC prefixes such as `KiB` and lowercase SI
  prefixes such as `kB`. Unknown suffixes return `0`; malformed numeric text may
  throw from `std::stoull`.
- On platforms where global `SIZE_MAX` does not fit the library assumptions,
  the header aliases `ext::units::size_t` to `unsigned long long`.

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
  ext::units::SI::to_string(size, ext::units::SI::kB); // "2000000000kB"
  ext::units::SI::to_wstring(size, ext::units::SI::kB); // L"2000000000kB"
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

- explicit typed unit

  ```C++
  #include <ext/units>

  ext::units::IEC::size<ext::units::IEC::MiB> cache_size(64);

  size_t bytes = cache_size;
  // bytes == 64 * ext::units::IEC::MiB

  std::string label = cache_size;
  // label == "64MiB"
  ```
