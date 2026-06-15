# property

[Back to API reference](README.md)

## Header

`#include <ext/property>`

## Overview

Stores a value, optionally validates assignments, and inherits from `observable` so dependent properties can react to changes. Tests cover assignment, comparison-like chain helpers, and notification behavior.

## Key APIs

- `ext::property<T>` stores a value of type `T`.
- Constructors accept an initial value and optional `std::function<bool(const T&)>` validator.
- `operator=` updates the value and notifies observers when validation succeeds.
- `operator T()` reads the current value.

## Behavior Notes

- Invalid assignments are rejected by the validator and leave the previous value in place.
- Property chaining can mirror one property into another through the observable update path.
- Use this when value mutation should be observable rather than manually notifying callbacks.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2017+
- C++17 or later

## Examples

```C++
#include <ext/property>

ext::property<size_t> val1;
ext::property<size_t> val2;
ext::property<size_t> total;

val1 = 10;
val2 = 0;
total = val1 + val2;
total.value(); // 10;

val1 = 20;
val2 = 40;
total.value(); // 60
```
