# any_function

[Back to API reference](README.md)

## Header

`#include <ext/any_function>`

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2017+
- **std::any** required
- **if constexpr** required

## Examples

```C++
#include <ext/any_function>

ext::any_function fn(strlen);

if (fn.call("test") == 4) {
}

if (std::any_cast<decltype(fn)::result_type>(fn({"test"})) == 4) {
}

size_t len;
std::any result;
result = fn({"test"});
if (result.has_value())
    len = std::any_cast<size_t>(result);

std::vector<std::any> args;
args.push_back("test");
result = fn(args);
if (result.has_value())
    len = std::any_cast<size_t>(result);

```
