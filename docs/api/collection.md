# collection

[Back to API reference](README.md)

## Header

`#include <ext/collection>`

## Overview

Lets instances of `collection_base<T>::item` automatically register themselves in a per-type collection on construction and unregister on destruction. Collection views hold locks while iterating.

## Key APIs

- `ext::collection_base<T, Lock>::item` is the base class for objects that should be tracked.
- `ext::collection<T>` / `collection_with_unique_lock<T>` provide mutable exclusive access.
- `ext::const_collection<T>` / `collection_with_shared_lock<T>` provide shared const access.
- `collection_base<T, Lock>::size()` returns the current number of registered items.

## Behavior Notes

- The registry is per item type `T` and backed by static singleton storage.
- Construct an item with the temporary flag to avoid automatic registration.
- The implementation uses `std::shared_mutex`, Boost shared mutex, or `ext::shared_recursive_mutex` depending on platform support.
- Collection view objects hold the registry lock while the view object is alive.
- Registered pointers are not ownership handles; destroying an object without
  unregistering it leaves a stale pointer in the registry.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+
- **std::shared_mutex** or **std::shared_timed_mutex** required

## Examples

- Managed (Automatically add/remove items to the collection.)

    ```C++
    #include <ext/collection>

    class managed_data : public ext::collection<managed_data>::item {
    public:
        managed_data() : id(0), value(0) {}
        int id;
        int value;
    };

    typedef ext::collection<managed_data> managed_data_list_rw;
    typedef ext::const_collection<managed_data> managed_data_list_r;

    managed_data managed_data_list[20];

    // managed_data_list_r::size() == 20;
    // managed_data_list_rw::size() == 20;

    managed_data data0;
    //managed_data_list_r::size() == 21;
    //managed_data_list_rw::size() == 21;

    managed_data *ptr = new managed_data;
    //managed_data_list_r::size() == 22;
    //managed_data_list_rw::size() == 22;

    delete ptr;
    //managed_data_list_r::size() == 21;
    //managed_data_list_rw::size() == 21;

    size_t cnt = 0;
    for (auto data : managed_data_list_r()) {
        int val = data->value;
        // data->value = 10; compile error
        cnt++;
    }
    // cnt == 21
    cnt = 0;
    for (auto data : managed_data_list_rw()) {
        int val = data->value;
        data->value = 10;
        cnt++;
    }
    // cnt == 21
    ```

- Unmanaged (Manually add/remove items to the collection.)

    ```C++
    #include <ext/collection>

    class data {
    public:
        data() : id(0), value(0) {}
        int id;
        int value;
    };

    typedef ext::collection<data> data_list_rw;
    typedef ext::const_collection<data> data_list_r;

    data data_list[20];

    // data_list_r::size() == 0;
    // data_list_rw::size() == 0;

    data data0;
    // data_list_r::size() == 0;
    // data_list_rw::size() == 0;

    data *ptr = new data;
    // data_list_r::size() == 0;
    // data_list_rw::size() == 0;

    delete ptr;
    // data_list_r::size() == 0;
    // data_list_rw::size() == 0;

    // data_list_r::size() == 0
    // data_list_rw::size() == 0

    data data1;
    // data_list_r::size() == 0
    // data_list_rw::size() == 0

    ext::collection_mgr<data> mgr;
    mgr.add(data0);
    // data_list_r::size() == 1
    // data_list_rw::size() == 1

    size_t cnt = 0;
    for (auto data : data_list_r()) {
        int val = data->value;
        // data->value = 10; compile error
        cnt++;
    }
    // cnt == 1
    cnt = 0;
    for (auto data : data_list_rw()) {
        int val = data->value;
        data->value = 10;
        cnt++;
    }
    // cnt == 1
    // data0.value == 10

    mgr.remove(data0);
    // data_list_r::size() == 0
    // data_list_rw::size() == 0
    ```
