# ext

C++ **EX**tended **T**emplate Library

**ext** is a small, header-oriented C++ utility library for projects that need
portable building blocks across old and modern toolchains. It focuses on
independent helpers around compatibility, strings, parsing, process I/O,
threading, and small application patterns rather than trying to be a framework.

The library intentionally carries compatibility code for older compilers such
as Visual Studio 2008 SP1 while also exposing cleaner APIs on newer C++
standards. Some features therefore have different availability and guarantees
depending on compiler, standard library, and platform support.

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
- [Portability and API contracts](docs/portability-and-contracts.md)

## Project Scope

ext is best used as a collection of opt-in headers:

- Use one feature at a time; most headers are independent utility components.
- Prefer the standard library first when it already provides the exact behavior
  you need on every supported toolchain.
- Treat concurrency, cancellation, process, and shared-memory APIs as thin
  wrappers over platform behavior. Their exact guarantees are documented per API
  and summarized in [Portability and API contracts](docs/portability-and-contracts.md).
- Compatibility shims live behind feature checks and `CXX_USE_*` macros. New
  code should avoid depending on those internal macros unless it is extending
  ext itself.

## Features

| Feature | Header | Description |
| --- | --- | --- |
| [any_function](docs/api/any_function.md) | `<ext/any_function>` | Type-erased function wrapper that accepts arguments as `std::any` values and reports argument count/type errors explicitly. |
| [async_result](docs/api/async_result.md) | `<ext/async_result>` | Asynchronous producer/result container with iterator-style consumption and cooperative cancellation flag support. |
| [base64](docs/api/base64.md) | `<ext/base64>` | Base64 encoder/decoder for strings, wide strings, byte vectors, and trivially copyable objects. |
| [callback](docs/api/callback.md) | `<ext/callback>` | Multicast callback list with add/remove operators and argument forwarding. |
| [cancelable_thread](docs/api/cancelable_thread.md) | `<ext/cancelable_thread>` | Thread wrapper with deferred and immediate cancellation paths over pthread or Windows primitives. |
| [cdbg](docs/api/cdbg.md) | `<ext/cdbg>` | Debug stream objects that write through platform debug sinks or console fallback streams. |
| [chain](docs/api/chain.md) | `<ext/chain>` | Composable chain-of-responsibility helper with typed results, continuation links, and exception-aware result state. |
| [debug_utils](docs/api/debug_utils.md) | `<ext/debug_utils.h>` | Debugger detection and wait helpers for POSIX-style debug workflows. |
| [collection](docs/api/collection.md) | `<ext/collection>` | Self-registering object collection with shared or exclusive locking around global per-type item lists. |
| [ini](docs/api/ini.md) | `<ext/ini>` | INI parser and writer backed by nested string maps. |
| [lang](docs/api/lang.md) | `<ext/lang>` | Korean language helpers for Hangul syllables, postpositions, and native/Sino-Korean number words. |
| [named_mutex](docs/api/named_mutex.md) | `<ext/named_mutex>` | Cross-process named mutex wrapper for coordinating shared resources and shared-memory payloads. |
| [observable](docs/api/observable.md) | `<ext/observable>` | Observer pattern base template with automatic unsubscribe on observer or observable destruction. |
| [path](docs/api/path.md) | `<ext/path>` | Path helpers for existence checks, relative path detection, and path joining. |
| [pipe](docs/api/pipe.md) | `<ext/pipe>` | Cross-platform anonymous pipe wrapper for narrow and wide byte streams. |
| [process](docs/api/process.md) | `<ext/process>` | Cross-platform child process launcher with stdin/stdout/stderr pipe streams and process lifetime management. |
| [property](docs/api/property.md) | `<ext/property>` | Observable value wrapper with assignment validation and property-to-property propagation. |
| [pstream](docs/api/pstream.md) | `<ext/pstream>` | Native-handle-backed stream wrappers used to read from and write to process pipes. |
| [result](docs/api/result.md) | `<ext/result>` | Small `ok`/`err` result type for explicit value-or-error returns. |
| [safe_object](docs/api/safe_object.md) | `<ext/safe_object>` | RAII lock proxy for globally named objects and mutexes selected at compile time. |
| [shared_recursive_mutex](docs/api/shared_recursive_mutex.md) | `<ext/shared_recursive_mutex>` | Shared mutex variant that permits recursive locking by the owning thread. |
| [shared_mem](docs/api/shared_mem.md) | `<ext/shared_mem>` | Named shared memory creation, opening, mapping, unmapping, and destruction helpers. |
| [singleton](docs/api/singleton.md) | `<ext/singleton>` | CRTP singleton base that exposes one static instance per derived type. |
| [string](docs/api/string.md) | `<ext/string>` | String utility namespace for trimming, printable filtering, searching, splitting, replacement, numeric conversion, and UTF-8 helpers. |
| [stl_compat](docs/api/stl_compat.md) | `<ext/stl_compat>` | Compatibility macros, aliases, and fallback implementations for older C++ standards and compilers. |
| [thread_pool](docs/api/thread_pool.md) | `<ext/thread_pool>` | Fixed-size worker pool with future-returning task submission and explicit start/stop state. |
| [type_traits](docs/api/type_traits.md) | `<ext/type_traits>` | Type-trait helpers for removing class qualifiers from member functions and deducing member-function signatures. |
| [typeinfo](docs/api/typeinfo.md) | `<ext/typeinfo>` | Portable type-name helper around C++ RTTI type information. |
| [units](docs/api/units.md) | `<ext/units>` | Strongly typed SI and IEC byte-size units with arithmetic and conversion helpers. |
| [uri](docs/api/uri.md) | `<ext/uri>` | RFC 3986-oriented URI parser and percent-encoding helpers for narrow, wide, and UTF-8 input. |
| [version](docs/api/version.md) | `<ext/version>` | Semantic version parser, formatter, hashing, comparison, and mutation helper. |
| [wordexp](docs/api/wordexp.md) | `<ext/wordexp>` | Environment or shell-style string expansion wrapper with platform-specific behavior. |

## License

This project is distributed under the [BSD-3-Clause license](LICENSE).
