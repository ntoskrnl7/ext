# API Reference

Detailed feature documentation lives here so the root README can stay focused on project orientation and quick-start usage.

For cross-cutting guarantees, especially around old compiler support and
threading behavior, see [Portability and API contracts](../portability-and-contracts.md).

## Feature Groups

- Compatibility: [stl_compat](stl_compat.md), [type_traits](type_traits.md), [typeinfo](typeinfo.md)
- Text, parsing, and data: [base64](base64.md), [ini](ini.md), [lang](lang.md), [path](path.md), [string](string.md), [uri](uri.md), [version](version.md), [wordexp](wordexp.md)
- Function and object patterns: [any_function](any_function.md), [callback](callback.md), [chain](chain.md), [collection](collection.md), [observable](observable.md), [property](property.md), [result](result.md), [singleton](singleton.md)
- Concurrency and IPC: [async_result](async_result.md), [cancelable_thread](cancelable_thread.md), [pipe](pipe.md), [process](process.md), [pstream](pstream.md), [safe_object](safe_object.md), [shared_mem](shared_mem.md), [shared_recursive_mutex](shared_recursive_mutex.md), [thread_pool](thread_pool.md)

## Feature Table

| Feature | Header | Description |
| --- | --- | --- |
| [any_function](any_function.md) | `<ext/any_function>` | Type-erased function wrapper that accepts arguments as `std::any` values and reports argument count/type errors explicitly. |
| [async_result](async_result.md) | `<ext/async_result>` | Asynchronous producer/result container with iterator-style consumption and cooperative cancellation flag support. |
| [base64](base64.md) | `<ext/base64>` | Base64 encoder/decoder for strings, wide strings, byte vectors, and trivially copyable objects. |
| [callback](callback.md) | `<ext/callback>` | Multicast callback list with add/remove operators and argument forwarding. |
| [cancelable_thread](cancelable_thread.md) | `<ext/cancelable_thread>` | Thread wrapper with deferred and immediate cancellation paths over pthread or Windows primitives. |
| [cdbg](cdbg.md) | `<ext/cdbg>` | Debug stream objects that write through platform debug sinks or console fallback streams. |
| [chain](chain.md) | `<ext/chain>` | Composable chain-of-responsibility helper with typed results, continuation links, and exception-aware result state. |
| [debug_utils](debug_utils.md) | `<ext/debug_utils.h>` | Debugger detection and wait helpers for POSIX-style debug workflows. |
| [collection](collection.md) | `<ext/collection>` | Self-registering object collection with shared or exclusive locking around global per-type item lists. |
| [ini](ini.md) | `<ext/ini>` | INI parser and writer backed by nested string maps. |
| [lang](lang.md) | `<ext/lang>` | Korean language helpers for Hangul syllables, postpositions, and native/Sino-Korean number words. |
| [observable](observable.md) | `<ext/observable>` | Observer pattern base template with automatic unsubscribe on observer or observable destruction. |
| [path](path.md) | `<ext/path>` | Path helpers for existence checks, relative path detection, and path joining. |
| [pipe](pipe.md) | `<ext/pipe>` | Cross-platform anonymous pipe wrapper for narrow and wide byte streams. |
| [process](process.md) | `<ext/process>` | Cross-platform child process launcher with stdin/stdout/stderr pipe streams and process lifetime management. |
| [property](property.md) | `<ext/property>` | Observable value wrapper with assignment validation and property-to-property propagation. |
| [pstream](pstream.md) | `<ext/pstream>` | Native-handle-backed stream wrappers used to read from and write to process pipes. |
| [result](result.md) | `<ext/result>` | Small `ok`/`err` result type for explicit value-or-error returns. |
| [safe_object](safe_object.md) | `<ext/safe_object>` | RAII lock proxy for globally named objects and mutexes selected at compile time. |
| [shared_recursive_mutex](shared_recursive_mutex.md) | `<ext/shared_recursive_mutex>` | Shared mutex variant that permits recursive locking by the owning thread. |
| [shared_mem](shared_mem.md) | `<ext/shared_mem>` | Named shared memory creation, opening, mapping, unmapping, and destruction helpers. |
| [singleton](singleton.md) | `<ext/singleton>` | CRTP singleton base that exposes one static instance per derived type. |
| [string](string.md) | `<ext/string>` | String utility namespace for trimming, printable filtering, searching, splitting, replacement, numeric conversion, and UTF-8 helpers. |
| [stl_compat](stl_compat.md) | `<ext/stl_compat>` | Compatibility macros, aliases, and fallback implementations for older C++ standards and compilers. |
| [thread_pool](thread_pool.md) | `<ext/thread_pool>` | Fixed-size worker pool with future-returning task submission and explicit start/stop state. |
| [type_traits](type_traits.md) | `<ext/type_traits>` | Type-trait helpers for removing class qualifiers from member functions and deducing member-function signatures. |
| [typeinfo](typeinfo.md) | `<ext/typeinfo>` | Portable type-name helper around C++ RTTI type information. |
| [units](units.md) | `<ext/units>` | Strongly typed SI and IEC byte-size units with arithmetic and conversion helpers. |
| [uri](uri.md) | `<ext/uri>` | RFC 3986-oriented URI parser and percent-encoding helpers for narrow, wide, and UTF-8 input. |
| [version](version.md) | `<ext/version>` | Semantic version parser, formatter, hashing, comparison, and mutation helper. |
| [wordexp](wordexp.md) | `<ext/wordexp>` | Environment or shell-style string expansion wrapper with platform-specific behavior. |
