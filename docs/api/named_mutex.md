# named_mutex

[Back to API reference](README.md)

## Header

`#include <ext/named_mutex>`

## Overview

Provides a small RAII wrapper for cross-process named mutual exclusion. Windows
uses a native named mutex. POSIX platforms use a named semaphore as a binary
mutex.

## Key APIs

- `ext::named_mutex(name)` creates or opens a named synchronization object.
- `lock()` waits until the mutex can be acquired.
- `try_lock()` attempts to acquire the mutex without blocking.
- `unlock()` releases a lock acquired by this instance.
- `valid()` reports whether the native handle is open.
- `abandoned()` reports whether Windows returned `WAIT_ABANDONED` for the most
  recent successful lock operation. POSIX always reports false.
- `unlink()` removes the POSIX named semaphore entry. On Windows, named mutex
  lifetime is handle-based, so this is a no-op that returns true.

## Behavior Notes

- Names are normalized on POSIX by adding a leading `/` when omitted.
- The class satisfies the basic lockable shape used by `std::lock_guard`.
- POSIX named semaphores are not robust mutexes. If a process exits while
  holding the semaphore, another process may block until application-level
  recovery runs.
- POSIX named semaphores do not enforce lock ownership. Callers must pair
  `lock()` or successful `try_lock()` calls with exactly one `unlock()`.
- Windows named mutexes can be recursively acquired by the owning thread. Avoid
  relying on recursion when writing portable code.
- Use one named mutex per shared resource or shared-memory payload that needs
  cross-process write synchronization.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2010+
- **std::atomic** required

## Examples

```C++
#include <ext/named_mutex>
#include <mutex>

ext::named_mutex mutex("shared-state-lock");

{
  std::lock_guard<ext::named_mutex> lock(mutex);
  // Access the protected shared state.
}

if (mutex.try_lock()) {
  // Access the protected shared state without blocking.
  mutex.unlock();
}
```
