# C++ Extended Template Library

[![CMake](https://github.com/ntoskrnl7/ext/actions/workflows/cmake.yml/badge.svg)](https://github.com/ntoskrnl7/ext/actions/workflows/cmake.yml) [![MSYS2](https://github.com/ntoskrnl7/ext/actions/workflows/msys2.yml/badge.svg)](https://github.com/ntoskrnl7/ext/actions/workflows/msys2.yml) ![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/ntoskrnl7/ext)

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+
- Boost 1.69.0++ (optional)
- Git 2.0+
- CMake 3.10+

---

## Test Environments

- Windows 10
  - Visual Studio 2008 SP1, 2010, 2017, 2019
  - MSYS2
    - MSYS (GCC 10.2.0)
    - MinGW32 (GCC 10.3.0)
    - MinGW64 (GCC 10.3.0)
    - CLANG32 (Clang 12.0.1)
    - CLANG64 (Clang 12.0.1)
    - UCRT64 (GCC 10.3.0)

- macOS 10.14, macOS 10.15
  - Clang 10.0.0, 11.0.0

- Linux (Ubuntu 18.04.3 LTS / Debian 10 / Gooroom 2.0, 2.3)
  - GCC 7.5.0, 8.3.0

---

## Features

1. any_function
   - Compiler
     - GCC 8.3.0+
     - Clang 10.0+
     - Visual Studio 2017+
     - **std::any** required
     - **if constexpr** required
   - Example

        ```C++
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

2. async_result
   - Compiler
     - GCC 8.3.0+
     - Clang 10.0+
     - Visual Studio 2008 SP1+ with **Boost 1.69.0+**
     - Visual Studio 2017+
   - Example

        ```C++
        #include <ext/async_result>

        typedef ext::async_result<int> int_result;
        int_result res([](int_result::context &ctx) {
            ctx.push(1);
            ctx.push(2);
            ...
        });

        ....

        for (auto &i : res) {
            ...
        }
        ```

3. base64
   - Compiler
     - GCC 8.3.0+
     - Clang 10.0+
     - Visual Studio 2008 SP1+
   - Example
     - string

        ```C++
        #include <ext/base64>

        // std::string <--> base64(std::string).
        std::string encoded = ext::base64::encode("1234");
        std::string decoded = ext::base64::decode_str(encoded); // "1234"
        std::vector<std::byte> decoded_vec = ext::base64::decode(encoded); // '1', '2', '3', '4

        // std::string <--> base64(std::wstring).
        std::wstring encoded_w = ext::base64::encode<wchar_t>("1234");
        decoded = ext::base64::decode_str(encoded_w);
        decoded_vec = ext::base64::decode(encoded_w);
        ```

     - wstring

        ```C++
        #include <ext/base64>

        // std::wstring <--> base64(std::string).
        std::string encoded = ext::base64::encode(L"1234");
        std::wstring decoded = ext::base64::decode_str<wchar_t>(encoded); // L"1234"
        std::vector<std::byte> decoded_vec = ext::base64::decode(encoded); // L'1', L'2', L'3', L'4

        // std::wstring <--> base64(std::wstring).
        std::wstring encoded_w = ext::base64::encode<wchar_t>(L"1234");
        decoded = ext::base64::decode_str<wchar_t>(encoded_w); // L"1234"
        decoded_vec = ext::base64::decode(encoded_w); // L'1', L'2', L'3', L'4
        ```

     - std::vector\<std::byte\>

        ```C++
        #include <ext/base64>

        // std::vector<std::byte> <--> base64(std::string).
        std::vector<std::byte> vec = {(std::byte)'1', (std::byte)'2',
                                    (std::byte)'3', (std::byte)'4'};
        std::string encoded = ext::base64::encode(vec);
        std::vector<std::byte> decoded = ext::base64::decode(encoded); // '1', '2', '3', '4
        std::string decoded_str = ext::base64::decode_str(encoded); // "1234"

        // std::vector<std::byte> <--> base64(std::wstring).
        std::wstring encoded_w = ext::base64::encode<wchar_t>(vec);
        decoded = ext::base64::decode(encoded_w); // '1', '2', '3', '4
        decoded_str = ext::base64::decode_str(encoded_w); // "1234"
        ```

     - structure

        ```C++
        #include <ext/base64>

        struct test {
            char a;
            char b;
            char c;
            char d;
        };

        test data = {'1', '2', '3', '4'};
        std::string encoded = ext::base64::encode(data);
        test decoded;
        ext::base64::decode(encoded, decoded); // a='1', b='2', c='3', d='4'
        std::shared_ptr<test> decoded_ptr =
            ext::base64::decode_shared_ptr<test>(encoded);  // a='1', b='2', c='3', d='4'
        std::string decoded_str = ext::base64::decode_str(encoded); // "1234"

        std::wstring encoded_w = ext::base64::encode<wchar_t>(data);
        decoded = {
            0,
        };
        ext::base64::decode(encoded_w, decoded); // a='1', b='2', c='3', d='4'
        decoded_ptr = ext::base64::decode_shared_ptr<test>(encoded_w); // a='1', b='2', c='3', d='4'
        decoded_str = ext::base64::decode_str(encoded_w); // "1234"
        ```

4. callback
   - Compiler
     - GCC 8.3.0+
     - Clang 10.0+
     - Visual Studio 2008 SP1+ with **Boost 1.69.0+**
     - Visual Studio 2017+
   - Example
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

5. cancelable_thread
   - Compiler
     - GCC 8.3.0+
     - Clang 10.0+
     - Visual Studio 2008 SP1+ with **Boost 1.69.0+**
     - Visual Studio 2017+
   - Example
        - Cancel
          - Like PTHREAD_CANCEL_DEFERRED

            ```C++
            #include <ext/cancelable_thread>

            std::mutex mtx;
            ext::cancelable_thread t([&mtx]() {
                std::unique_lock<std::mutex> lk(mtx);
                ...
            });

            ...

            t.cancel_request();
            t.wait_for(std::chrono::milliseconds(500));
            t.join();

            // or t.cancel();

            if (t.canceled()) ...
            ```

        - Cancel immediately.
          - **Use this method with extreme caution**
          - Like PTHREAD_CANCEL_ASYNCHRONOUS

            ```C++
            #include <ext/cancelable_thread>

            std::mutex mtx;
            ext::cancelable_thread t([&mtx]() {
                std::unique_lock<std::mutex> lk(mtx);
                ...
            }, [&mtx]() { mtx.unlock(); });

            ...

            t.cancel_request();
            t.wait_for(std::chrono::milliseconds(500));
            t.join();

            // or t.cancel();

            if (t.canceled()) ...
            ```

6. cdbg
   - GCC 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
   - Example
   - Sends a string to the debugger for display.
      - Like OutputDebugStringA

        ```C++
        #include <ext/cdbg>

        ext::cdbg << "test\n";
        ```

      - Like OutputDebugStringW

        ```C++
        #include <ext/cdbg>

        ext::wcdbg << L"test\n";
        ```

7. chain
   - GCC 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
   - Example
     - Implements an http request chain.

        ```C++
        #include <map>
        #include <string>
        #include <string>
        #include <tuple>

        #include <ext/chain>

        namespace http {
            struct request {
                enum method { http_get, http_post, http_delete, http_put, http_invalid };
                request() : method(method::http_invalid) {}
                request(const std::string &path, method method,
                        const std::map<std::string, std::string> headers = {})
                    : path(path), method(method), headers(headers) {}
                method method;
                std::string path;
                std::map<std::string, std::string> headers;
                std::string get_method() const {
                    switch (method) {
                    case method::http_get:
                        return "GET";
                    case method::http_post:
                        return "POST";
                    case method::http_delete:
                        return "DELETE";
                    case method::http_put:
                        return "PUT";
                    default:
                        throw std::runtime_error("Invalid method");
                    }
                }
                void validate() const {
                    if (path[0] != '/')
                        throw std::runtime_error("Invalid path : " + path);
                }
            };
            struct response {
                enum status {
                    ok = 200,
                    unauthorized = 401,
                    forbidden = 403,
                    not_found = 404,
                    internal_server_error = 500
                };
                response() : status(internal_server_error) {}
                response(status s, const std::string &body = {}) : status(s), body(body) {}
                status status;
                std::string body;
            };

            template <class T> struct validation_chain : T {
                typename T::result execute(const request &req) {
                    try {
                        req.validate();
                        return T::execute(req);
                    } catch (const std::exception &e) {
                        return T::done(response(response::internal_server_error, e.what()));
                    }
                }
            };
            struct basic_chain : ext::chain<basic_chain, response, const request &> {};
        } // namespace http

        struct auth_check_chain_type : public http::basic_chain {
            result execute(const http::request &req) {
            auto it = req.headers.find("auth");
            if (it != req.headers.cend() && it->second == "authorized")
                return chain::next(req);
            return chain::done(http::response(http::response::unauthorized));
            }
        };
        http::validation_chain<auth_check_chain_type> auth_check_chain;

        struct get_info_chain_type : public http::basic_chain {
            result execute(const http::request &req) {
            if ((req.path == "/info") && (req.method == http::request::http_get))
                return chain::done(http::response(
                    http::response::ok, "[" + req.get_method() + "] " + req.path));
            return chain::next(req);
            }
        };
        http::validation_chain<get_info_chain_type> get_info_chain;

        struct not_found_chain_type : public http::basic_chain {
            result execute(const http::request &req) {
            return chain::done(http::response(
                http::response::not_found, "[" + req.get_method() + "] " + req.path));
            }
        };
        http::validation_chain<not_found_chain_type> not_found_chain;

        // Build a chain.
        auth_check_chain >> get_info_chain >> not_found_chain;

        // Execute the first chain (auth_check_chain).
        auto res = auth_check_chain(http::request("/info", http::request::http_get)).get();
        // res.status == http::response::unauthorized

        res = auth_check_chain(http::request("/info", http::request::http_post, {{"auth", "authorized"}})).get();
        // res.status == http::response::not_found

        res = auth_check_chain(http::request("/test", http::request::http_get, {{"auth", "authorized"}})).get();
        // res.status == http::response::not_found

        res = auth_check_chain(http::request("1234", http::request::http_post, {{"auth", "authorized"}})).get();
        // res.status == http::response::internal_server_error
        // res.body == "Invalid path : 1234"

        res = auth_check_chain(http::request("/info", http::request::http_get, {{"auth", "authorized"}})).get();
        // res.status == http::response::ok
        // res.body == "[GET] /info"

        // Execute the second chain (get_info_chain).
        res = get_info_chain(http::request("/info", http::request::http_get)).get();
        // res.status == http::response::ok
        // res.body == "[GET] /info"
        ```

8. debug_utils
   - GCC 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
   - Example
     - Wait for debugger **(C/C++)**

        ```C
        #include <ext/debug_utils>

        wait_for_debugger(100);

        if (is_debugger_present()) {
            ...
        }

        msleep(500);
        ```

9. collection
   - GCC 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+ with **Boost 1.69.0+**
   - Visual Studio 2017+
   - **std::shared_mutex** or **std::shared_timed_mutex** required
   - Example
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

10. ini
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+ with **Boost 1.69.0+**
    - Visual Studio 2010+
    - **std::regex** required
    - Example
      - Create an ini file from a string.

        ```C++
        #include <ext/ini>

        std::istringstream ss("[TEST]\nX=10\nY=20\n[TEST1]\nZ=30");
        ext::ini ini(ss);
        // ini["TEST"]["X"] ==  "10"
        // ini["TEST"]["Y"] == "20"
        // ini["TEST1"]["Z"] == "30"
        std::ofstream ofs("sample.ini");
        ofs << ini;
        ```

      - ini file (sample.ini)

        ```INI
        [TEST]
        X=10
        Y=20
        [TEST1]
        Z=30
        ```

      - Load ini from file.

        ```C++
        #include <ext/ini>

        ext::ini ini(std::ifstream("sample.ini"));
        // ini["TEST"]["X"] ==  "10"
        // ini["TEST"]["Y"] == "20"
        // ini["TEST1"]["Z"] == "30"
        ```

      - Edit the ini file.

        ```C++
        #include <ext/ini>

        ext::ini ini(std::ifstream("sample.ini"));
        // ini["TEST"]["X"] ==  "10"
        // ini["TEST"]["Y"] == "20"
        // ini["TEST1"]["Z"] == "30"

        ini["TEST"].erase("X");
        // ini["TEST"].find("X") == ini["TEST"].end()

        ini.erase("TEST1");
        // ini.contains("TEST1") == false

        std::ofstream ofs("output.ini");
        ofs << ini;
        ```

      - ini file (output.ini)

        ```INI
        [TEST]
        Y=20
        ```

11. observable
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+ with **Boost 1.69.0+**
    - Visual Studio 2017+
    - **std::shared_mutex or std::shared_timed_mutex required**
12. path
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
13. pipe
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
14. process
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
15. property
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2017+
    - C++17 or later
16. pstream
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
17. safe_object
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2017+
    - std::shared_mutex or std::shared_timed_mutex required
    - C++14 or later
18. shared_recursive_mutex
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+ with **Boost 1.69.0+**
    - Visual Studio 2017+
    - std::shared_mutex or std::shared_timed_mutex required
19. shared_mem
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
20. singleton
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
21. string
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
22. stl_compat
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
23. thread_pool
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2017+
    - C++14 or later
24. type_traits
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
25. typeinfo
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
26. units
    - Compiler
      - GCC 8.3.0+
      - Clang 10.0+
      - Visual Studio 2008 SP1+
    - Example

        ```C++
        #include <fstream>
        std::ifstream ifs("~~~~");
        ifs.seekg(0, std::ios::end);
        ext::units::to_string(ifs.tellg(), ext::units::POLICY_IEC);
        ext::units::to_string(ifs.tellg(), ext::units::POLICY_SI);
        ```

27. url
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
28. version
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+ with **Boost 1.69.0+**
    - Visual Studio 2010+
    - std::regex required
29. wordexp
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+

---

## Test

### Windows

#### Visual Studio

- Default
  - CMAKE_CXX_STANDARD=17
  - CMAKE_BUILD_TYPE=Debug
- Examples
  - cmake -DCMAKE_CXX_STANDARD=11  ..
  - cmake -DCMAKE_CXX_STANDARD=14  ..
  - cmake -DCMAKE_CXX_STANDARD=17  ..
  - cmake -G "Visual Studio 10 2010" -DCXX_USE_BOOST=On ..

```batch
cd test
mkdir build && cd build
cmake ..
cmake --build .
ctest . -C Debug --verbose
```

#### MSYS or MinGW(32/64/CLANG32/CLANG64/CLANGARM64/UCRT64)

```bash
pacman -Syu
pacman -Su
pacman -S --needed base-devel git
case "${MSYSTEM}" in
    "MINGW32") pacman -S --needed mingw-w64-i686-toolchain mingw-w64-i686-cmake;;
    "MINGW64") pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake;;
    "CLANG32") pacman -S --needed mingw-w64-clang-i686-toolchain mingw-w64-clang-i686-cmake;;
    "CLANG64") pacman -S --needed mingw-w64-clang-x86_64-toolchain mingw-w64-clang-x86_64-cmake;;
    "CLANGARM64") pacman -S --needed mingw-w64-clang-aarch64-toolchain mingw-w64-clang-aarch64-cmake;;
    "UCRT64") pacman -S --needed mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-cmake;;
    "MSYS") pacman -S --needed gcc cmake;;
    *) pacman -S --needed gcc cmake;;
esac
```

```bash
cd test
mkdir build && cd build
if [ "$MSYSTEM" = "MSYS" ]; then
    cmake ..
else
    cmake -G "MinGW Makefiles" ..
fi
cmake --build .
export LC_ALL=C; unset LANGUAGE
ctest . --verbose
```

### Linux or macOS

```bash
cd test
mkdir build && cd build
cmake ..
cmake --build .
ctest . --verbose
```

## Usage

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# create project
project(MyProject)

# add executable
add_executable(tests tests.cpp)

# add dependencies
include(cmake/CPM.cmake)
CPMAddPackage("gh:ntoskrnl7/ext@0.5.4")

# link dependencies
target_link_libraries(tests ext)
```
