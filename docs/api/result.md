# result

[Back to API reference](README.md)

## Header

`#include <ext/result>`

## Overview

Models a return value that is either successful `ok<T>` data or failed `err<E>` data. The API offers boolean state checks and accessor methods that throw if the wrong side is read.

## Key APIs

- `ext::ok<T>` wraps successful values; `ok<void>` represents success without a value.
- `ext::err<E>` wraps error values and an optional error message.
- `ext::result<T, E>` stores either success data or error data.
- `ext::void_result<E>` stores success/failure when there is no success value.
- `get()` returns the successful value wrapper and `error()` returns the error wrapper.

## Behavior Notes

- `operator bool()` is true on success and false on error.
- `get()` throws `error_occurred` when called on an error result.
- `error()` throws `no_error_occurred` when called on a successful `result<T, E>`.
- `void_result<E>::error()` returns the stored error wrapper and does not throw on success.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- ext::void_result<error_t>

  ```C++
  #include <ext/result>

  #include <errno.h>

  ext::void_result<error_t> ok_fn() { return ext::ok<void>(); }
  ext::void_result<error_t> err_fn() { return ext::err<error_t>(EBUSY); }

  ext::void_result<error_t> result = ok_fn();
  if (result) { // true
  }

  result = err_fn();
  if (!result) { // false
    result.error(); // EBUSY
  }
  ```

- ext::result<int, error_t>

  - Basic

    ```C++
    #include <ext/result>

    #include <errno.h>

    ext::result<int, error_t> ok_fn() { return ext::ok<int>(10); }
    ext::result<int, error_t> err_fn() { return ext::err<error_t>(EBUSY); }

    ext::result<int, error_t> result = ok_fn();
    if (result) { // true
      result.get(); // 10
    }

    result = err_fn();
    if (!result) { // false
      result.error(); // EBUSY
    }
    ```

  - Error with message

    ```C++
    #include <ext/result>

    #include <errno.h>

    ext::result<int, error_t> ok_fn() { return ext::ok<int>(10); }
    ext::result<int, error_t> err_fn() {
      return ext::err<error_t>(EBUSY, "I'm busy");
    }

    ext::result<int, error_t> result = ok_fn();
    if (result) { // true
      result.get(); // 10
    }
    try {
      result.error();
    } catch (const ext::result_error &e) {
      e.what(); // "No error occurred."
    }

    result = err_fn();
    if (!result) { // false
      result.error(); // EBUSY
    }
    try {
      result.get();
    } catch (const ext::result_error &e) {
      e.what(); // "I'm busy"
    }
    try {
      result.get();
    } catch (const ext::error_occurred &e) {
      e.what(); // "I'm busy"
    }
    ```
