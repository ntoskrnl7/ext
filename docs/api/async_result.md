# async_result

[Back to API reference](README.md)

## Header

`#include <ext/async_result>`

## Overview

Runs a callback that writes values through an `async_result<T>::context`, then lets the caller iterate over values as they become available. It supports both immediate producer callbacks and threaded producers.

## Key APIs

- `ext::async_result<T>` owns the shared queue, progress counters, and worker thread when threaded mode is used.
- `async_result<T>::context` gives producers `begin(size)`, `push`, `emplace`, `end`, `size`, and `cancel_requested`.
- `begin()` and `end()` return an iterator that blocks until data or completion is available.
- `cancel()` sets the shared cancellation flag observed by producer code.

## Behavior Notes

- Cancellation is cooperative; producer callbacks should check `ctx.cancel_requested()` and stop pushing when requested.
- `size()` and `current()` expose total and consumed item counts for progress-style workflows.
- The iterator becomes stopped when the producer has finished and the queue is drained.
- The `async_result` destructor joins the producer thread when one is running.

## Lifetime Contract

- Producer callbacks should call `ctx.end()` when they finish. The context
  destructor also marks the result as finished, but explicit `end()` makes the
  producer intent clear.
- `cancel()` only sets a flag; it does not interrupt the producer thread.
- A long-running producer that ignores `ctx.cancel_requested()` can keep
  iterators and destruction waiting.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+

## Examples

```C++
#include <ext/async_result>

typedef ext::async_result<int> int_result;
int_result res([](int_result::context &ctx) {
    ctx.begin(3);
    ctx.push(1);
    ctx.push(2);
    ctx.emplace(3);
    ctx.end();
});

int sum = 0;
for (auto &i : res) {
    sum += i;
}
// sum == 6
```
