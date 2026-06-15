# pipe

[Back to API reference](README.md)

## Header

`#include <ext/pipe>`

## Overview

Creates a connected read/write pipe pair and exposes stream objects for moving data through it. Tests cover both narrow and wide pipe variants.

## Key APIs

- `ext::basic_pipe<CharT>` owns the platform pipe handles.
- `ext::pipe` is the narrow-character pipe alias.
- `ext::wpipe` is the wide-character pipe alias.
- Read and write stream endpoints expose standard stream-style operations.

## Behavior Notes

- The wrapper is used internally by `process` for stdin, stdout, and stderr plumbing.
- Pipe endpoints close their native handles when the owning stream/buffer closes.
- Close the write endpoint when readers should observe EOF.
- Pipe buffering follows the operating system; writers can block when readers do
  not drain the pipe.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

```C++
#include <ext/pipe>
#include <string>
#include <thread>

ext::pipe pipe;
std::thread t([&pipe]() {
  pipe.out() << "test" << std::endl;
});

std::string val;
pipe.in() >> val;
// val == "test"

if (t.joinable())
  t.join();
```
