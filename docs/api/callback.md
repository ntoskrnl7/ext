# callback

[Back to API reference](README.md)

## Header

`#include <ext/callback>`

## Overview

Stores multiple callback functions and invokes all registered handlers with the supplied arguments. The tests cover add, remove, and argument-carrying callbacks.

## Key APIs

- `ext::callback<Args...>` stores a list of handlers with the matching function signature.
- `operator+=` registers a handler and returns a cookie.
- `operator-=` removes a handler by the cookie returned from registration.
- `operator()(args...)` invokes the currently registered handlers in list order.

## Behavior Notes

- Handlers are ordinary callable objects compatible with `std::function` for the callback signature.
- Removing a handler prevents later invocations from calling it.
- Use it when the publisher does not need the observer lifetime tracking provided by `ext::observable`.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+

## Examples

- Register a callbacks.

    ```C++
    #include <ext/callback>

    int sum = 1;
    ext::callback<int> int_callback;
    int_callback += [&sum](int val) { sum += val; };
    int_callback += [&sum](int val) { sum *= val; };
    int_callback(5);
    // sum == 10
    ```

- Register a callbacks.

    ```C++
    #include <ext/callback>

    int sum = 1;
    ext::callback<int> int_callback;
    int_callback += [&sum](int val) { sum *= val; };
    int_callback += [&sum](int val) { sum += val; };
    int_callback(5);
    // sum == 30
    ```

- Unregister a callback.

    ```C++
    #include <ext/callback>

    int sum = 0;
    ext::callback<int> int_callback;

    int_callback += [&sum](int val) { sum += val; };
    auto cookie = int_callback += [&sum](int val) { sum += val; };
    int_callback(1);
    // sum == 2

    sum = 0;
    int_callback -= cookie;
    int_callback(1);
    //sum == 1
    ```
