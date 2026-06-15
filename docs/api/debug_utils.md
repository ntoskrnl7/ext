# debug_utils

[Back to API reference](README.md)

## Header

`#include <ext/debug_utils.h>`

## Overview

Adds small utilities for debugger-aware tests and diagnostics. The implementation probes debugger presence with `SIGTRAP` handling and offers a timeout-based wait loop.

## Key APIs

- `ext::is_debugger_present()` returns whether a debugger appears to be attached.
- `ext::wait_for_debugger(timeout)` waits up to the supplied timeout for debugger attachment.
- `ext::msleep(msec)` provides a small millisecond sleep helper used by the wait loop.

## Behavior Notes

- The helpers are lightweight diagnostics and should not be treated as a security boundary.
- Timeout values are expressed in milliseconds.

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
