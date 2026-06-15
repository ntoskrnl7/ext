# thread_pool

[Back to API reference](README.md)

## Header

`#include <ext/thread_pool>`

## Overview

Creates worker threads that consume queued packaged tasks. The API is intentionally small: start workers, queue work, stop workers, and observe the pool status.

## Key APIs

- `ext::thread_pool` owns worker threads and a task queue.
- Constructors may accept per-worker initializer and finalizer callbacks.
- `start(pool_size)` creates worker threads when the pool is stopped.
- `queue(fn, args...)` submits work and returns a `std::future` for the packaged task result.
- `queue_cancellable(fn, args...)` submits work and returns a `queue_item<T>`
  that can cancel the task before a worker starts executing it.
- `stop(wait)` requests worker shutdown and optionally joins the worker threads.
- `status()` reports `running`, `stop_pending`, or `stopped`.

## Behavior Notes

- The pool requires standard thread, mutex, and condition variable support or configured Boost equivalents.
- Task results and exceptions are surfaced through the returned `std::future`.
- `queue()` throws when the pool is not running.
- Canceling a pending `queue_item<T>` completes its future with
  `ext::thread_pool::task_canceled`.
- `queue_item<T>::cancel()` returns false once the task is already running,
  completed, or previously canceled.
- `stop()` changes the pool status and wakes workers; it does not promise to
  execute every task still waiting in the queue.
- `stop(false)` requests shutdown without joining immediately; destruction or a
  later `stop(true)` still joins worker threads.
- The destructor calls `stop()`.
- Worker initializer callbacks run once when each worker starts. Worker
  finalizer callbacks run once when each worker exits.
- If any worker initializer returns false or throws, `start()` returns false and
  the pool returns to the stopped state.

## Queue Contract

- Keep the returned `std::future` for every submitted task whose result or
  exception matters.
- Wait on the futures you require before calling `stop()` if all queued work
  must complete.
- Do not enqueue work after `stop()` has started; `queue()` rejects calls unless
  the pool status is `running`.
- Use `queue_cancellable()` only for pre-execution cancellation. It does not
  interrupt a task after a worker has started running it.

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

- Cancel a pending task

  ```C++
  #include <ext/thread_pool>

  ext::thread_pool pool(1);

  ext::thread_pool::queue_item<int> item =
      pool.queue_cancellable([]() { return 42; });
  std::future<int> result = item.get_future();

  if (item.cancel()) {
    // result.get() throws ext::thread_pool::task_canceled.
  }

  pool.stop();
  ```

- Worker callbacks

  ```C++
  #include <ext/thread_pool>

  ext::thread_pool pool(
      2,
      []() {
        // Initialize per-worker resources.
        return true;
      },
      []() {
        // Release per-worker resources.
        return true;
      });

  pool.stop();
  ```
