# typeinfo

[Back to API reference](README.md)

## Header

`#include <ext/typeinfo>`

## Overview

Provides readable type-name extraction used by error messages in facilities such as `any_function` and diagnostics in safe-object helpers.

## Key APIs

- `ext::get_type_name(typeid(T))` returns a string form of a type.
- Template overloads can return the name for a type or value depending on compiler support.
- Demangling is used where platform support is available.

## Behavior Notes

- Returned names are intended for diagnostics, not stable serialization.
- Exact spelling can vary by compiler and standard library.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

```C++
#include <ext/typeinfo>

ext::get_type_name<void()>();

ext::get_type_name(typeid(std::string));
```
