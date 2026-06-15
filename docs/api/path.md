# path

[Back to API reference](README.md)

## Header

`#include <ext/path>`

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

```C++
#include <ext/path>

ext::path::join("aaa", "bbb", "ccc"); // aaa/bbb/ccc
ext::path::is_relative("./test"); // true
ext::path::is_relative("/test"); // false
ext::path::exists("/test");
```
