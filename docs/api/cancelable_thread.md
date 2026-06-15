# cancelable_thread

[Back to API reference](README.md)

## Header

`#include <ext/cancelable_thread>`

## Overview

Wraps `std::thread` and exposes cancellation-oriented state such as ready, completed, canceled, joinable, and wait-for-completion. It supports a deferred cancellation mode and an immediate mode with a caller-supplied cleanup callback.

## Key APIs

- `ext::cancelable_thread(fn)` starts a worker in deferred-cancel mode.
- `ext::cancelable_thread(fn, cleanup)` enables immediate-cancel mode and calls `cleanup` when the thread is interrupted.
- `cancel_request()` requests cancellation without joining.
- `cancel()` requests cancellation and joins, while `join()` and `wait_for()` manage completion explicitly.

## Behavior Notes

- Deferred mode is modeled after `PTHREAD_CANCEL_DEFERRED`; immediate mode is modeled after `PTHREAD_CANCEL_ASYNCHRONOUS`.
- The macOS pthread implementation does not guarantee C++ stack unwinding for deferred cancellation, so RAII cleanup is not documented as supported there.
- Immediate cancellation is inherently dangerous because ordinary C++ destructors may not run; use the cleanup callback to release resources that must be unlocked.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+

## Examples

- Cancel
  - **MSYS is not supported.**
  - **macOS does not guarantee C++ stack unwinding for pthread cancellation, so
    scoped destructors and lock release are not supported for this mode.**
  - Like PTHREAD_CANCEL_DEFERRED

    ```C++
    #include <ext/cancelable_thread>

    std::mutex mtx;
    ext::cancelable_thread t([&mtx]() {
        std::unique_lock<std::mutex> lk(mtx);
        ...
    });

    ...

    t.cancel_request();
    t.wait_for(std::chrono::milliseconds(500));
    t.join();

    // or t.cancel();

    if (t.canceled()) ...
    ```

- Cancel immediately.
  - **Use this method with extreme caution**
  - **macOS and MinGW Clang32/Clang64 is not supported.**
  - Like PTHREAD_CANCEL_ASYNCHRONOUS

    ```C++
    #include <ext/cancelable_thread>

    std::mutex mtx;
    ext::cancelable_thread t([&mtx]() {
        std::unique_lock<std::mutex> lk(mtx);
        ...
    }, [&mtx]() { mtx.unlock(); });

    ...

    t.cancel_request();
    t.wait_for(std::chrono::milliseconds(500));
    t.join();

    // or t.cancel();

    if (t.canceled()) ...
    ```
