# singleton

[Back to API reference](README.md)

## Header

`#include <ext/singleton>`

## Overview

Provides a small `singleton<T>` base class for types that want a process-local static instance. It is used internally by collection storage and safe-object tracing helpers.

## Key APIs

- `ext::singleton<T>::instance()` returns the single static `T` instance.
- Constructors/destructors are protected so derived classes control direct construction policy.
- Copying is disabled where compiler support allows it.

## Behavior Notes

- The derived type generally declares `singleton<T>` as a friend when it wants private construction.
- Initialization follows the platform/compiler static local initialization rules.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

```C++
```
