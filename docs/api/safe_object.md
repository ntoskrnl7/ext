# safe_object

[Back to API reference](README.md)

## Header

`#include <ext/safe_object>`

## Overview

Builds a temporary object that locks a supplied mutex and returns a reference to the protected object through `operator()`. Macros hide the verbose template parameters required to bind object and mutex references.

## Key APIs

- `ext::safe_object<...>` is the lock-holding proxy type.
- `safe_object_type(obj, mutex, shared)` obtains the proxy type for a specific object/mutex pair.
- `get_object_safety(obj, mutex, shared)` creates a proxy and returns the protected object through `operator()`.
- Shared access returns a const reference; exclusive access returns a mutable reference.

## Behavior Notes

- The object and mutex are non-type template parameters, so they must have suitable storage duration.
- Shared access uses `std::shared_lock`; exclusive access uses `std::unique_lock`.
- The implementation depends on `decltype`, alias templates, atomics, threads, and a shared mutex implementation.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2017+
- **std::shared_mutex** or **std::shared_timed_mutex** required
- C++14 or later

## Examples

```C++
```
