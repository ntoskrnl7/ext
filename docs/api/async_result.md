# async_result

[Back to API reference](README.md)

## Header

`#include <ext/async_result>`

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+

## Examples

```C++
#include <ext/async_result>

typedef ext::async_result<int> int_result;
int_result res([](int_result::context &ctx) {
    ctx.push(1);
    ctx.push(2);
    ...
});

....

for (auto &i : res) {
    ...
}
```
