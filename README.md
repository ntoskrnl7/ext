# ext

C++ **EX**tended **T**emplate Library

**ext** is a modern, cross-platform C++ template utility library designed to bridge the gap between the Standard Library and real-world production needs. It provides practical, reusable components that make C++ development easier, safer, and more productive without the complexity or overhead of larger frameworks.

[![CMake](https://github.com/ntoskrnl7/ext/actions/workflows/cmake.yml/badge.svg?branch=master&event=push)](https://github.com/ntoskrnl7/ext/actions/workflows/cmake.yml?query=branch%3Amaster)
[![MSYS2](https://github.com/ntoskrnl7/ext/actions/workflows/msys2.yml/badge.svg?branch=master&event=push)](https://github.com/ntoskrnl7/ext/actions/workflows/msys2.yml?query=branch%3Amaster)
[![License: BSD-3-Clause](https://img.shields.io/badge/license-BSD--3--Clause-green.svg)](LICENSE)
![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/ntoskrnl7/ext)
![CMake 3.14+](https://img.shields.io/badge/CMake-3.14+-yellow.svg?logo=cmake&logoColor=white)
![C++ 03+](https://img.shields.io/badge/C++-03+-white.svg?logo=cplusplus&logoColor=blue)

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+
- Boost 1.69.0+ (optional)
- Git 2.0+
- CMake 3.14+

See [Build and Test](docs/build-and-test.md) for tested platforms, MSYS2 setup, and local test commands.

## Quick Start

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(MyProject)

add_executable(tests tests.cpp)

include(cmake/CPM.cmake)
CPMAddPackage("gh:ntoskrnl7/ext@0.5.17")

target_link_libraries(tests ext)
```

## Documentation

- [API reference](docs/api/README.md)
- [Build and test](docs/build-and-test.md)

## Features

| Feature | Header | Description |
| --- | --- | --- |
| [any_function](docs/api/any_function.md) | `<ext/any_function>` | Invoke functions stored in `std::any` values. |
| [async_result](docs/api/async_result.md) | `<ext/async_result>` | Run asynchronous work and retrieve typed results. |
| [base64](docs/api/base64.md) | `<ext/base64>` | Encode and decode Base64 strings. |
| [callback](docs/api/callback.md) | `<ext/callback>` | Manage callback handlers and dispatch. |
| [cancelable_thread](docs/api/cancelable_thread.md) | `<ext/cancelable_thread>` | Wrap a thread with cancellation helpers. |
| [cdbg](docs/api/cdbg.md) | `<ext/cdbg>` | Small conditional debug-printing helper. |
| [chain](docs/api/chain.md) | `<ext/chain>` | Compose fluent callable chains. |
| [debug_utils](docs/api/debug_utils.md) | `<ext/debug_utils.h>` | Debug-time utility macros and helpers. |
| [collection](docs/api/collection.md) | `<ext/collection>` | Collection helpers for common container operations. |
| [ini](docs/api/ini.md) | `<ext/ini>` | Read and write INI-style configuration data. |
| [lang](docs/api/lang.md) | `<ext/lang>` | Language and Unicode helpers, including Korean Hangul utilities. |
| [observable](docs/api/observable.md) | `<ext/observable>` | Observable value and event notification helpers. |
| [path](docs/api/path.md) | `<ext/path>` | Path utility helpers. |
| [pipe](docs/api/pipe.md) | `<ext/pipe>` | Pipe utility helpers. |
| [process](docs/api/process.md) | `<ext/process>` | Process execution helpers. |
| [property](docs/api/property.md) | `<ext/property>` | Property wrapper helpers. |
| [pstream](docs/api/pstream.md) | `<ext/pstream>` | Process stream helpers. |
| [result](docs/api/result.md) | `<ext/result>` | Result type for value-or-error flows. |
| [safe_object](docs/api/safe_object.md) | `<ext/safe_object>` | Thread-safe object access wrapper. |
| [shared_recursive_mutex](docs/api/shared_recursive_mutex.md) | `<ext/shared_recursive_mutex>` | Shared recursive mutex implementation. |
| [shared_mem](docs/api/shared_mem.md) | `<ext/shared_mem>` | Shared memory helper. |
| [singleton](docs/api/singleton.md) | `<ext/singleton>` | Singleton helper template. |
| [string](docs/api/string.md) | `<ext/string>` | String conversion and formatting helpers. |
| [stl_compat](docs/api/stl_compat.md) | `<ext/stl_compat>` | Compatibility layer for standard library features. |
| [thread_pool](docs/api/thread_pool.md) | `<ext/thread_pool>` | Thread pool helper. |
| [type_traits](docs/api/type_traits.md) | `<ext/type_traits>` | Additional compile-time type traits. |
| [typeinfo](docs/api/typeinfo.md) | `<ext/typeinfo>` | Type information helpers. |
| [units](docs/api/units.md) | `<ext/units>` | Strongly typed unit helpers. |
| [uri](docs/api/uri.md) | `<ext/uri>` | URI parsing and formatting helpers. |
| [version](docs/api/version.md) | `<ext/version>` | Version parsing and comparison helpers. |
| [wordexp](docs/api/wordexp.md) | `<ext/wordexp>` | Shell-style word expansion helpers. |

## License

This project is distributed under the [BSD-3-Clause license](LICENSE).
