# callback

[Back to API reference](README.md)

## Header

`#include <ext/callback>`

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
