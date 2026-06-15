# cdbg

[Back to API reference](README.md)

## Header

`#include <ext/cdbg>`

## Overview

Provides stream objects for debug-oriented output. On Windows the stream buffer writes through `OutputDebugString`, with Qt it writes through `qDebug`, and otherwise it falls back to standard console streams.

## Key APIs

- `ext::cdbg` is the narrow debug stream.
- `ext::wcdbg` is the wide-character debug stream.
- `ext::debug_streambuf<CharT>` is the stream buffer adapter behind those streams.
- Stream insertion operators are used in the same style as `std::cout` and `std::wcout`.

## Behavior Notes

- This is intended for diagnostic logging with platform-specific debug sinks.
- For debugger detection and waiting, see `debug_utils`.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- Sends a string to the platform debug output stream.
  - Like OutputDebugStringA

    ```C++
    #include <ext/cdbg>

    ext::cdbg << "test\n";
    ```

  - Like OutputDebugStringW

    ```C++
    #include <ext/cdbg>

    ext::wcdbg << L"test\n";
    ```
