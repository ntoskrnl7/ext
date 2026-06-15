# shared_recursive_mutex

[Back to API reference](README.md)

## Header

`#include <ext/shared_recursive_mutex>`

## Overview

Provides a mutex with exclusive and shared locking operations while tracking ownership so recursive acquisition by the same thread can succeed. Tests cover exclusive and shared lock construction.

## Key APIs

- `ext::shared_recursive_mutex` exposes mutex-style `lock`, `unlock`, `try_lock`, `lock_shared`, and `unlock_shared` operations.
- It is compatible with standard lock wrappers such as `std::unique_lock` and `std::shared_lock`.
- The type can back `collection`, `observable`, and `safe_object` when standard shared mutex support is unavailable or insufficient.

## Behavior Notes

- Recursive exclusive ownership is tracked per thread.
- Recursive shared ownership is tracked per thread through an internal map.
- `unlock()` by a thread that does not own the exclusive lock throws
  `std::system_error`.
- Upgrading from shared ownership to exclusive ownership is specialized
  behavior; prefer a simpler lock design when recursive upgrade-like behavior is
  not required.
- Use it only where recursive shared/exclusive behavior is required; standard mutexes are simpler for ordinary locking.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+
- **std::shared_mutex** or **std::shared_timed_mutex** required

## Examples

```C++
#include <ext/shared_recursive_mutex>

ext::shared_recursive_mutex mtx;

mtx.lock();
mtx.lock();
mtx.unlock();
mtx.unlock();

mtx.lock_shared();
mtx.lock_shared();
mtx.unlock_shared();
mtx.unlock_shared();
```
