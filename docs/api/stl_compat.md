# stl_compat

[Back to API reference](README.md)

## Header

`#include <ext/stl_compat>`

## Overview

Centralizes feature detection and compatibility shims used throughout the library. Headers opt into required standard library features by defining `CXX_USE_*` macros before including this file.

## Key APIs

- Feature macros indicate whether standard facilities are available or emulated.
- Fallback definitions cover selected C++11/C++14/C++17 utilities when older toolchains lack them.
- Loop, noexcept, constexpr, move, type-trait, and threading compatibility helpers are provided for internal headers.

## Behavior Notes

- Most users include feature headers directly and do not need to include `stl_compat` themselves.
- The file is intentionally broad because this library supports old Visual Studio and Boost-assisted builds.
