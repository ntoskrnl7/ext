# thread_pool

[Back to API reference](README.md)

## Header

`#include <ext/thread_pool>`

## Overview

Creates worker threads that consume queued packaged tasks. The API is intentionally small: start workers, queue work, stop workers, and observe the pool status.

## Key APIs

- `ext::thread_pool` owns worker threads and a task queue.
- `start(pool_size)` creates worker threads when the pool is stopped.
- `queue(fn, args...)` submits work and returns a `std::future` for the packaged task result.
- `stop(wait)` requests worker shutdown and optionally joins the worker threads.
- `status()` reports `running`, `stop_pending`, or `stopped`.

## Behavior Notes

- The pool requires standard thread, mutex, and condition variable support or configured Boost equivalents.
- Task results and exceptions are surfaced through the returned `std::future`.
- `queue()` throws when the pool is not running.
- `stop()` changes the pool status and wakes workers; it does not promise to
  execute every task still waiting in the queue.
- The destructor calls `stop()`.

## Queue Contract

- Keep the returned `std::future` for every submitted task whose result or
  exception matters.
- Wait on the futures you require before calling `stop()` if all queued work
  must complete.
- Do not enqueue work after `stop()` has started; `queue()` rejects calls unless
  the pool status is `running`.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2017+
- C++14 or later

## Examples

```C++
#include <ext/thread_pool>

ext::thread_pool pool(2);
std::future<int> result = pool.queue([]() { return 42; });

int value = result.get(); // 42
pool.stop();
```
