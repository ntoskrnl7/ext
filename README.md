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

## Contents

- [C++ Extended Template Library](#c-extended-template-library)
  - [Requirements](#requirements)
  - [Contents](#contents)
  - [Test Environments](#test-environments)
  - [Features](#features)
    - [any_function](#any_function)
      - [Requirements](#requirements-1)
      - [Examples](#examples)
    - [async_result](#async_result)
      - [Requirements](#requirements-2)
      - [Examples](#examples-1)
    - [base64](#base64)
      - [Requirements](#requirements-3)
      - [Examples](#examples-2)
    - [callback](#callback)
      - [Requirements](#requirements-4)
      - [Examples](#examples-3)
    - [cancelable_thread](#cancelable_thread)
      - [Requirements](#requirements-5)
      - [Examples](#examples-4)
    - [cdbg](#cdbg)
      - [Requirements](#requirements-6)
      - [Examples](#examples-5)
    - [chain](#chain)
      - [Requirements](#requirements-7)
      - [Examples](#examples-6)
    - [debug_utils](#debug_utils)
      - [Requirements](#requirements-8)
      - [Examples](#examples-7)
    - [collection](#collection)
      - [Requirements](#requirements-9)
      - [Examples](#examples-8)
    - [ini](#ini)
      - [Requirements](#requirements-10)
      - [Examples](#examples-9)
    - [lang](#lang)
      - [Requirements](#requirements-11)
      - [Examples](#examples-10)
    - [observable](#observable)
      - [Requirements](#requirements-12)
      - [Examples](#examples-11)
    - [path](#path)
      - [Requirements](#requirements-13)
      - [Examples](#examples-12)
    - [pipe](#pipe)
      - [Requirements](#requirements-14)
      - [Examples](#examples-13)
    - [process](#process)
      - [Requirements](#requirements-15)
      - [Examples](#examples-14)
    - [property](#property)
      - [Requirements](#requirements-16)
      - [Examples](#examples-15)
    - [pstream](#pstream)
      - [Requirements](#requirements-17)
      - [Examples](#examples-16)
    - [result](#result)
      - [Requirements](#requirements-18)
      - [Examples](#examples-17)
    - [safe_object](#safe_object)
      - [Requirements](#requirements-19)
      - [Examples](#examples-18)
    - [shared_recursive_mutex](#shared_recursive_mutex)
      - [Requirements](#requirements-20)
      - [Examples](#examples-19)
    - [shared_mem](#shared_mem)
      - [Requirements](#requirements-21)
      - [Examples](#examples-20)
    - [singleton](#singleton)
      - [Requirements](#requirements-22)
      - [Examples](#examples-21)
    - [string](#string)
      - [Requirements](#requirements-23)
      - [Examples](#examples-22)
    - [stl_compat](#stl_compat)
    - [thread_pool](#thread_pool)
      - [Requirements](#requirements-24)
      - [Examples](#examples-23)
    - [type_traits](#type_traits)
      - [Requirements](#requirements-25)
      - [Examples](#examples-24)
    - [typeinfo](#typeinfo)
      - [Requirements](#requirements-26)
      - [Examples](#examples-25)
    - [units](#units)
      - [Requirements](#requirements-27)
      - [Examples](#examples-26)
    - [uri](#uri)
      - [Requirements](#requirements-28)
      - [Examples](#examples-27)
    - [version](#version)
      - [Requirements](#requirements-29)
      - [Examples](#examples-28)
    - [wordexp](#wordexp)
      - [Requirements](#requirements-30)
      - [Examples](#examples-29)
  - [Test](#test)
    - [Windows](#windows)
      - [Visual Studio](#visual-studio)
      - [MSYS or MinGW(32/64/CLANG32/CLANG64/CLANGARM64/UCRT64)](#msys-or-mingw3264clang32clang64clangarm64ucrt64)
    - [Linux or macOS](#linux-or-macos)
  - [Usage](#usage)
    - [CMakeLists.txt](#cmakeliststxt)

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

### any_function

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2017+
- **std::any** required
- **if constexpr** required

#### Examples

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

### async_result

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+

#### Examples

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

### base64

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

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

### callback

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+

#### Examples

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

### cancelable_thread

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+

#### Examples

- Cancel
  - **MSYS is not supported.**
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
  - **macOS and MinGW Clang32/Clang64 is not supported.**
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

### cdbg

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

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

### chain

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

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

### debug_utils

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

- Wait for debugger **(C/C++)**

    ```C
    #include <ext/debug_utils>

    wait_for_debugger(100);

    if (is_debugger_present()) {
        ...
    }

    msleep(500);
    ```

### collection

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+
- **std::shared_mutex** or **std::shared_timed_mutex** required

#### Examples

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

### ini

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2010+
- **std::regex** required

#### Examples

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

### lang

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

- ko_kr::syllable

  ```C++
  #include <ext/lang>

  ext::lang::ko_kr::syllable::letter lt = L'a';
  EXPECT_FALSE(lt.valid());

  lt = L'ㄱ';
  EXPECT_FALSE(lt.valid());
  EXPECT_EQ(lt.onset, L'ㄱ');

  lt = L'ㅏ';
  EXPECT_FALSE(lt.valid());
  EXPECT_EQ(lt.nucleus, L'ㅏ');

  lt = L'가';
  EXPECT_TRUE(lt.valid());
  EXPECT_EQ(lt.onset, L'ㄱ');
  EXPECT_EQ(lt.nucleus, L'ㅏ');

  lt = L'간';
  EXPECT_TRUE(lt.valid());
  EXPECT_EQ(lt.onset, L'ㄱ');
  EXPECT_EQ(lt.nucleus, L'ㅏ');
  EXPECT_EQ(lt.coda, L'ㄴ');
  ```

- ko_kr::postposition

  ```C++
  #include <ext/lang>

  using namespace ext::lang::ko_kr;
  EXPECT_STREQ(postposition::topic(L"산").c_str(), L"은");
  EXPECT_STREQ(postposition::topic(L"바다").c_str(), L"는");

  EXPECT_STREQ(postposition::identifier(L"산").c_str(), L"이");
  EXPECT_STREQ(postposition::identifier(L"바다").c_str(), L"가");

  EXPECT_STREQ(postposition::objective(L"산").c_str(), L"을");
  EXPECT_STREQ(postposition::objective(L"바다").c_str(), L"를");

  EXPECT_STREQ(postposition::destination(L"산").c_str(), L"으로");
  EXPECT_STREQ(postposition::destination(L"바다").c_str(), L"로");

  EXPECT_STREQ(postposition::destination(L"산").c_str(), L"으로");
  EXPECT_STREQ(postposition::destination(L"바다").c_str(), L"로");

  EXPECT_STREQ(postposition::conjunction(L"산").c_str(), L"과");
  EXPECT_STREQ(postposition::conjunction(L"바다").c_str(), L"와");

  EXPECT_STREQ(postposition::vocative(L"산").c_str(), L"아");
  EXPECT_STREQ(postposition::vocative(L"바다").c_str(), L"야");

  EXPECT_STREQ(postposition::exclamation(L"산").c_str(), L"이여");
  EXPECT_STREQ(postposition::exclamation(L"바다").c_str(), L"여");
  ```

### observable

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+
- **std::shared_mutex or std::shared_timed_mutex required**

#### Examples

```C++
```

### path

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

```C++
#include <ext/path>

ext::path::join("aaa", "bbb", "ccc"); // aaa/bbb/ccc
ext::path::is_relative("./test"); // true
ext::path::is_relative("/test"); // false
ext::path::exists("/test");
```

### pipe

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

```C++
#include <ext/pipe>
#include <thread>

ext::pipe pipe;
std::thread t([stream = std::move(pipe.out())]() mutable {
  stream << "test" << std::endl;
});

std::string val;
pipe.in() >> val;
EXPECT_STREQ(val.c_str(), "test");

if (t.joinable())
  t.join();
```

### process

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

- stdout

  ```C++
  #include <ext/process>
  
  ext::process process("ls", {"-al", "."});
  std::cout << process.get_cmdline() << std::endl;
  std::cout << process.out().rdbuf() << std::endl;
  if (process.joinable())
    process.join();
  ```

- stdin

  ```C++
  #include <ext/process>
  
  ext::process process("more");
  process.in() << "test 1\n";
  process.in() << "test 2\ntest 3\n";
  process.in().close();
  std::cout << process.out().rdbuf() << std::endl;
  if (process.joinable())
    process.join();
  ```

- pipe (stdin, stdout)

  ```C++
  #include <ext/process>
  
  auto result = ext::process("ps", {"-ef"}) | ext::process("grep", {"root"}) |
                ext::process("grep", {"/usr"}) | ext::process("wc", {"-l"});

  result.get_cmdline(); // "ps -ef | grep root | grep /usr | wc -l"
  
  std::cout << "cmdline : " << result.get_cmdline() << std::endl;
  std::cout << "result :" << result.out().rdbuf() << std::endl;
  if (result.joinable())
    result.join();
  ```

### property

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2017+
- C++17 or later

#### Examples

```C++
#include <ext/property>

ext::property<size_t> val1;
ext::property<size_t> val2;
ext::property<size_t> total;

val1 = 10;
val2 = 0;
total = val1 + val2;
total.value(); // 10;

val1 = 20;
val2 = 40;
total.value(); // 60
```

### pstream

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

```C++
```

### result

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

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

### safe_object

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2017+
- **std::shared_mutex** or **std::shared_timed_mutex** required
- C++14 or later

#### Examples

```C++
```

### shared_recursive_mutex

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+
- **std::shared_mutex** or **std::shared_timed_mutex** required

#### Examples

```C++
```

### shared_mem

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

- Process A

  ```C++
  #include <ext/shared_mem>

  struct memory_struct0 {
    int i;
    int j;
  };

  shared_mem<memory_struct0> st_mem("memory_struct0", shared_mem_all_access);
  if (st_mem.opened()) {
    st_mem.destroy();
    st_mem.create();
  }

  if (st_mem.created()) {
    st_mem->i = 10;
    st_mem->j = 20;
  }
  ```

- Pocess B

  ```C++
  #include <ext/shared_mem>

  struct memory_struct0 {
    int i;
    int j;
  };

  shared_mem<memory_struct0> st_mem("memory_struct0");
  if (st_mem.opened()) {
    st_mem2->i; // 10
    st_mem2->j; // 20
  }
  ```

### singleton

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

```C++
```

### string

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

- split

  ```C++
  std::vector<std::string> list = ext::split("a,b,c,d", ",");
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list[0], "a");
  EXPECT_EQ(list[1], "b");
  EXPECT_EQ(list[2], "c");
  EXPECT_EQ(list[3], "d");
  ```

- u8string

  ```C++
  #define CXX_USE_STD_U8STRING
  #include <ext/string>

  #if defined(CXX_STD_U8STRING_NOT_SUPPORTED)
  #if defined(__cpp_user_defined_literals) &&                                    \
      (CXX_VER >= __cpp_user_defined_literals)
    std::u8string str = ext::from_u8(u8"한글+english");
    EXPECT_STREQ((const char *)str.c_str(), u8"한글+english");
  #else
    std::u8string str = ext::from_u8(ext::to_u8string(L"한글+english"));
    EXPECT_STREQ((const char *)str.c_str(), "\xED\x95\x9C\xEA\xB8\x80+english");
  #endif
  #else
    std::u8string str = u8"한글+english";
    EXPECT_STREQ(str.c_str(), u8"한글+english");
  #endif
  ```

### stl_compat

### thread_pool

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2017+
- C++14 or later

#### Examples

```C++
```

### type_traits

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

- ext::remove_class

  ```C++
  #include <ext/type_traits>
  #include <ext/typeinfo>

  class test_callable {
  public:
    std::string operator()(int, char, std::vector<std::string>) { return "1"; }
  };

  class test_callable_2 {
  public:
    void operator()(){};
    std::string operator()(int, char, std::vector<std::string>) { return "2"; }
  };

  std::string (test_callable_2::*ptr)(int, char, std::vector<std::string>) =
      &test_callable_2::operator();
  EXPECT_STREQ(
      ext::get_type_name<ext::remove_class<decltype(ptr)>::type>().c_str(),
      ext::get_type_name<std::string(int, char, std::vector<std::string>)>()
          .c_str());
  ```

- ext::deduce_mem_fn

  ```C++
  #include <ext/type_traits>
  #include <ext/typeinfo>

  auto ld = []() {};
  EXPECT_STREQ(
      ext::get_type_name<void()>().c_str(),
      ext::get_type_name<ext::deduce_mem_fn<decltype(ld)>::type>().c_str());
  ```

### typeinfo

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

```C++
#include <ext/typeinfo>

ext::get_type_name<void()>();

ext::get_type_name(typeid(std::string));
```

### units

- SI
- IEC

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

- to_string

  ```C++
  #include <ext/units>
  
  // IEC
  size_t size = 2 * ext::units::IEC::TiB;
  ext::units::to_string(size, ext::units::POLICY_IEC); // "2TiB"
  ext::units::to_wstring(size, ext::units::POLICY_IEC); // L"2TiB"

  // SI
  size = 2 * ext::units::SI::tB;
  ext::units::to_string(size, ext::units::POLICY_SI); // "2tB"
  ext::units::to_wstring(size, ext::units::POLICY_SI); // L"2tB"
  ```

- to_size_t

  ```C++
  #include <ext/units>
  
  // IEC
  ext::units::to_size_t("2TiB"); // 2 * ext::units::IEC::TiB
  ext::units::to_size_t(L"2TiB"); // 2 * ext::units::IEC::TiB

  // SI
  ext::units::to_size_t("2tB"); // 2 * ext::units::SI::tB
  ext::units::to_size_t(L"2tB"); // 2 * ext::units::SI::tB
  ```

- User-defined literals

  ```C++
  #include <ext/units>
  
  // IEC
  using namespace ext::units::IEC::literals;

  size_t value = 5_MiB;
  EXPECT_EQ(value, 5 * ext::units::IEC::MiB);

  std::string str = 5_MiB;
  EXPECT_STREQ(str.c_str(), "5MiB");

  std::wstring wstr = 5_MiB;
  EXPECT_STREQ(wstr.c_str(), L"5MiB");

  // SI
  using namespace ext::units::SI::literals;
  size_t value = 5_mB;
  EXPECT_EQ(value, 5 * ext::units::SI::mB);

  std::string str = 5_mB;
  EXPECT_STREQ(str.c_str(), "5mB");

  std::wstring wstr = 5_mB;
  EXPECT_STREQ(wstr.c_str(), L"5mB");
  ```

### uri

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

- uri

  ```C++
  ext::uri u("https://localhost:8443/test");
  EXPECT_STREQ(u.scheme.c_str(), "https");
  EXPECT_STREQ(u.host.c_str(), "localhost");
  EXPECT_EQ(u.port, 8443);
  EXPECT_STREQ(u.path.c_str(), "/test");
  EXPECT_STREQ(u.scheme_host_port().c_str(), "https://localhost:8443");

  u = ext::uri("foo://info.example.com?fred");
  EXPECT_STREQ(u.scheme.c_str(), "foo");
  EXPECT_STREQ(u.host.c_str(), "info.example.com");
  EXPECT_TRUE(u.path.empty());
  EXPECT_STREQ(u.query.c_str(), "?fred");
  ```

- wuri

  ```C++
  ext::wuri u(L"https://localhost:8443/test");
  EXPECT_STREQ(u.scheme.c_str(), L"https");
  EXPECT_STREQ(u.host.c_str(), L"localhost");
  EXPECT_EQ(u.port, 8443);
  EXPECT_STREQ(u.path.c_str(), L"/test");
  EXPECT_STREQ(u.scheme_host_port().c_str(), L"https://localhost:8443");

  u = ext::wuri(L"foo://info.example.com?fred");
  EXPECT_STREQ(u.scheme.c_str(), L"foo");
  EXPECT_STREQ(u.host.c_str(), L"info.example.com");
  EXPECT_TRUE(u.path.empty());
  EXPECT_STREQ(u.query.c_str(), L"?fred");
  ```

- User-defined literals

  ```C++
  #include <ext/uri>
  
  using namespace ext::literals;

  ext::uri u = "http://test.com:1234/test?key=value&key1=value1"_uri;
  ext::wuri u = L"http://test.com:1234/test?key=value&key1=value1"_uri;
  ```

- encode

  ```C++
  #define CXX_USE_STD_U8STRING
  #include <ext/uri>

  #if defined(CXX_STD_U8STRING_NOT_SUPPORTED)
  #if defined(__cpp_user_defined_literals) &&                                    \
    (CXX_VER >= __cpp_user_defined_literals)
    const std::u8string uri_u8str = ext::from_u8(u8"https://www.google.com/search?q=한글+english");
  #else
    const std::u8string uri_u8str =ext::to_u8string(L"https://www.google.com/search?q=한글+english");
  #endif
  #else
    const std::u8string uri_u8str = u8"https://www.google.com/search?q=한글+english";
  #endif
    ext::uri u(uri_u8str);
    ext::wuri u(uri_u8str);
  ```

### version

[Semantic Versioning](https://semver.org/)

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2010+
- **std::regex** required

#### Examples

- Basic

  ```C++
  ext::version v("a.b.c"); // std::invalid_argument

  ext::version v("0.0.4");
  v.major(); // 0
  v.minor(); // 0
  v.patch(); // 4
  v.released(); // true
  v.prerelease(); // ""
  v.build_metadata(); // ""

  ext::version v("1.1.2-prerelease+meta");
  v.major(); // 1
  v.minor(); // 1
  v.patch(); // 2
  v.released(); // false
  v.prerelease(); // "prerelease"
  v.build_metadata(); // "meta"
  ```

- std::hash

  ```C++
  std::unordered_map<ext::version, std::string> map = {
    {ext::version("1.2.3"), "abc"},
    {ext::version("5.0.0"), "def"},
    {ext::version("1.2.3-prerelease"), "ghi"},
  };

  auto it = map.find(ext::version("1.2.3"));
  EXPECT_EQ(it->second, "abc");

  it = map.find(ext::version("5.0.0"));
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->second, "def");

  it = map.find(ext::version("1.2.0"));
  EXPECT_EQ(it, map.end());

  it = map.find(ext::version("1.2.3-prerelease"));
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->second, "ghi");

  it = map.find(ext::version("1.2.3-prerelease+meta"));
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->second, "ghi");

  it = map.find(ext::version("1.2.3-test+meta"));
  EXPECT_EQ(it, map.end());
  ```

### wordexp

Expands environment-variable strings and replaces them with the values defined for the current user.

#### Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

#### Examples

```C++
#if defined(_WIN32)
  std::string system_drive = ext::wordexp("%SYSTEMDRIVE%");
  std::string windir = ext::wordexp("%WINDIR%");
  std::string user_profile = ext::wordexp("%USERPROFILE%");
  std::string user_name = ext::wordexp("%USERNAME%");
#else
  std::string home_path = ext::wordexp("$HOME");
  std::string user = ext::wordexp("$USER");
#endif
```

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
  - cmake -DEXT_NO_WIN32_EX=On ..

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
CPMAddPackage("gh:ntoskrnl7/ext@0.5.12")

# link dependencies
target_link_libraries(tests ext)
```
