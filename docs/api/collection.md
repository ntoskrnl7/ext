# collection

[Back to API reference](README.md)

## Header

`#include <ext/collection>`

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
        int val = dat->value;
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
    //data_list_r::size() == 21;
    //data_list_rw::size() == 21;

    data *ptr = new data;
    // data_list_r::size() == 22;
    // data_list_rw::size() == 22;

    delete ptr;
    // data_list_r::size() == 21;
    // data_list_rw::size() == 21;

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
        int val = dat->value;
        data->value = 10;
        cnt++;
    }
    // cnt == 1
    // data0.value == 10

    mgr.remove(data0);
    // data_list_r::size() == 0
    // data_list_rw::size() == 0
    ```
