# debug_utils

[Back to API reference](README.md)

## Header

`#include <ext/debug_utils.h>`

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- Wait for debugger **(C/C++)**

    ```C
    #include <ext/debug_utils>

    wait_for_debugger(100);

    if (is_debugger_present()) {
        ...
    }

    msleep(500);
    ```
