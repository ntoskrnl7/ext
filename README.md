# C++ Extended Template Library

## Requirements

- gcc 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+
- CMake 3.10+
- Boost 1.69.0+ (optional)

---

## Test Environments

### Operating system

- Windows 10
- macOS 10.14, macOS 10.15
- Linux (Ubuntu 18.04.3 LTS / Gooroom 2.0 / Debian 10)

### Compiler

- gcc 7.5.0, 8.3.0
- g++ 7.5.0, 8.3.0
- Clang 10.0.0, 11.0.0
- Visual Studio 2008 SP1, 2010, 2017

---

## Features

1. any_function
   - gcc 8.3.0+
   - Clang 10.0+
   - Visual Studio 2017+
2. base64
   - gcc 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
3. callback
   - gcc 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
4. cdbg
   - gcc 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
5. chain
   - gcc 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
6. collection
   - gcc 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+ (with Boost 1.69.0)
   - std::shared_mutex or std::shared_timed_mutex required
7. ini
   - gcc 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
8. observable
   - gcc 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
9. path
   - gcc 8.3.0+
   - Clang 10.0+
   - Visual Studio 2008 SP1+
10. process
    - gcc 8.3.0+
    - Clang 10.0+
    - Visual Studio 2017+
    - C++11 or later
11. property
    - gcc 8.3.0+
    - Clang 10.0+
    - Visual Studio 2017+
    - C++17 or later
12. safe_object
    - gcc 8.3.0+
    - Clang 10.0+
    - Visual Studio 2017+
    - std::shared_mutex or std::shared_timed_mutex required
    - C++14 or later
13. shared_recursive_mutex
    - gcc 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+ (with Boost 1.69.0)
    - std::shared_mutex or std::shared_timed_mutex required
14. singleton
    - gcc 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
15. string
    - gcc 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
16. stl_compat
    - gcc 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
17. thread_pool
    - gcc 8.3.0+
    - Clang 10.0+
    - Visual Studio 2017+
    - C++14 or later
18. type_traits
    - gcc 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+
19. typeinfo
    - gcc 8.3.0+
    - Clang 10.0+
    - Visual Studio 2008 SP1+

---

## Test

1. cd test
2. mkdir build && cd build
3. cmake ..
   - default
     - CMAKE_CXX_STANDARD=17
     - CMAKE_BUILD_TYPE=Debug
   - ex
     - cmake -DCMAKE_CXX_STANDARD=11  ..
     - cmake -DCMAKE_CXX_STANDARD=14  ..
     - cmake -DCMAKE_CXX_STANDARD=17  ..
4. cmake --build .
5. execute a unittest
   - macOS or Linux : ./unittest
   - Windows : Debug\unittext.exe
