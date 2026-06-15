# any_function

[Back to API reference](README.md)

## Header

`#include <ext/any_function>`

## Overview

Provides a `std::function`-compatible wrapper that can be called with a `std::vector<std::any>`. It is useful for command queues, reflection-like dispatch, and APIs that need to store callable objects while binding arguments later.

## Key APIs

- `ext::any_function<R(Args...)>` stores a callable and exposes both typed calls and `std::any`-based calls.
- `push_back`, `set_args`, and `clear` manage the stored argument vector used by the nullary `operator()()`.
- `call(args...)` invokes the stored callable with typed arguments and returns `R` directly.
- `invalid_argument_type` and `argument_count_mismatch` describe failed dynamic argument conversion.

## Behavior Notes

- Dynamic calls validate the number of arguments before invocation.
- Each `std::any` argument is cast to the function signature type; mismatches throw with the failing argument index.
- Reference wrappers are supported for pass-by-reference command patterns.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2017+
- **std::any** required
- **if constexpr** required

## Examples

```C++
#include <ext/any_function>

ext::any_function fn(strlen);

if (fn.call("test") == 4) {
}

if (std::any_cast<decltype(fn)::result_type>(fn({"test"})) == 4) {
}

size_t len;
std::any result;
result = fn({"test"});
if (result.has_value())
    len = std::any_cast<size_t>(result);

std::vector<std::any> args;
args.push_back("test");
result = fn(args);
if (result.has_value())
    len = std::any_cast<size_t>(result);

```
