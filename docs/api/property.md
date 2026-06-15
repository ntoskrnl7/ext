# property

[Back to API reference](README.md)

## Header

`#include <ext/property>`

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
