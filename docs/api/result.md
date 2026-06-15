# result

[Back to API reference](README.md)

## Header

`#include <ext/result>`

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
  ext::void_result<error_t> err_fn() { return ext::err(EBUSY); }

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

    ext::result<int, error_t> ok_fn() { return ext::ok(10); }
    ext::result<int, error_t> err_fn() { return ext::err(EBUSY); }

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

    ext::result<int, error_t> ok_fn() { return ext::ok(10); }
    ext::result<int, error_t> err_fn() { return ext::err(EBUSY, "I'm busy"); }

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
