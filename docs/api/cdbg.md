# cdbg

[Back to API reference](README.md)

## Header

`#include <ext/cdbg>`

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- Sends a string to the debugger for display.
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
