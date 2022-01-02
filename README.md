# C++ Extended Template Library

[![CMake](https://github.com/ntoskrnl7/ext/actions/workflows/cmake.yml/badge.svg)](https://github.com/ntoskrnl7/ext/actions/workflows/cmake.yml) [![MSYS2](https://github.com/ntoskrnl7/ext/actions/workflows/msys2.yml/badge.svg)](https://github.com/ntoskrnl7/ext/actions/workflows/msys2.yml) ![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/ntoskrnl7/ext)

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+
- Boost 1.69.0+ (optional)
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
     - **std::any required**
     - **if constexpr required**
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
     - Visual Studio 2008 SP1+ with Boost 1.69.0
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

        ```C++
        #include <ext/base64>

        std::string encoded = ext::base64::encode("1234");
        std::string decoded = ext::base64::decode_str(encoded);
        std::vector<std::byte> = ext::base64::decode(encoded);
        ```

4. callback
   - Compiler
     - GCC 8.3.0+
     - Clang 10.0+
     - Visual Studio 2008 SP1+ with Boost 1.69.0
     - Visual Studio 2017+
   - Example

        ```C++
        #include <ext/callback>

        ext::callback<int> int_callback;
        int_callback += [&sum](int val) { sum += val; };
        int_callback += [&sum](int val) { sum += val; };
        int_callback(1);
        ```

5. cdbg
   - GCC 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
6. chain
   - GCC 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
7. debug_utils
   - GCC 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
8. collection
   - GCC 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+ with Boost 1.69.0
   - Visual Studio 2017+
   - std::shared_mutex or std::shared_timed_mutex required
9. ini
   - GCC 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1 with Boost 1.69.0
   - Visual Studio 2010+
   - std::regex required
10. observable
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+ with Boost 1.69.0
    - Visual Studio 2017+
    - std::shared_mutex or std::shared_timed_mutex required
11. path
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
12. pipe
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
13. process
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
14. property
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2017+
    - C++17 or later
15. pstream
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
16. safe_object
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2017+
    - std::shared_mutex or std::shared_timed_mutex required
    - C++14 or later
17. shared_recursive_mutex
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+ with Boost 1.69.0
    - Visual Studio 2017+
    - std::shared_mutex or std::shared_timed_mutex required
18. shared_mem
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
19. singleton
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
20. string
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
21. stl_compat
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
22. thread_pool
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2017+
    - C++14 or later
23. type_traits
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
24. typeinfo
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
25. units
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

26. url
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
27. version
    - GCC 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1 with Boost 1.69.0
    - Visual Studio 2010+
    - std::regex required
28. wordexp
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
CPMAddPackage("gh:ntoskrnl7/ext@0.5.3")

# link dependencies
target_link_libraries(tests ext)
```
