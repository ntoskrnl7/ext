# pipe

[Back to API reference](README.md)

## Header

`#include <ext/pipe>`

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

```C++
#include <ext/pipe>
#include <thread>

ext::pipe pipe;
std::thread t([stream = std::move(pipe.out())]() mutable {
  stream << "test" << std::endl;
});

std::string val;
pipe.in() >> val;
EXPECT_STREQ(val.c_str(), "test");

if (t.joinable())
  t.join();
```
