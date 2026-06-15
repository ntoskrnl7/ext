# Portability and API Contracts

[Back to documentation index](README.md)

ext supports a broad compiler and platform range. This page describes the
library-level expectations that apply before reading an individual API page.

## Scope

ext is an opt-in utility library, not an application framework.

- Include the feature header you need instead of treating ext as one large
  dependency surface.
- Prefer standard library facilities when they are available and provide the
  same behavior on every compiler you support.
- Use ext where it provides portability glue, a small missing abstraction, or a
  tested wrapper around platform-specific behavior.

## Compatibility Model

Different headers require different language and library features. API pages
list their own requirements, and `stl_compat` centralizes feature detection for
the implementation.

- `CXX_USE_BOOST` can opt some APIs into Boost-backed compatibility paths.
- `CXX_USE_*` macros are implementation controls. Applications normally include
  public feature headers directly and do not need to define these macros.
- A header may be excluded at compile time when the compiler or standard library
  does not provide the required feature set.
- The root `C++ 03+` badge describes the project compatibility goal, not a
  promise that every feature is available under C++03.

## Threading and Lifetime Contracts

Threading-related APIs intentionally stay close to the underlying platform
primitives. Code that depends on cancellation, locks, process I/O, or shared
memory should read the API-specific behavior notes.

- `cancelable_thread` exposes platform cancellation. Deferred cancellation may
  unwind C++ frames on some pthread implementations, but macOS is documented as
  not guaranteeing RAII cleanup for this library. Immediate cancellation should
  be treated as an emergency escape path; ordinary C++ destructors may not run.
- `async_result` cancellation is cooperative. Producers must check the context
  cancellation flag and return voluntarily.
- `thread_pool::stop()` requests worker shutdown. It is not a queue-drain API;
  callers that require all queued work to complete should wait on returned
  futures before stopping the pool. `stop(false)` requests shutdown without an
  immediate join; destruction or a later waiting stop still joins workers.
  `queue_cancellable()` cancels only work that has not started running.
- `observable` protects subscription bookkeeping when a shared mutex is
  available, but callbacks run synchronously from `notify()`. Avoid mutating
  subscriptions from inside an observer callback unless the specific locking
  behavior has been reviewed.
- `safe_object` protects access only for the lifetime of the temporary proxy.
  Do not store references returned through the proxy beyond the expression or
  scope that owns the lock.
- `shared_recursive_mutex` exists for cases that truly need recursive
  shared/exclusive behavior. Prefer ordinary standard mutex types when
  recursion is not required.
- `shared_mem` maps named platform resources. The creating and opening
  processes must agree on the object type layout, name, and lifetime.

## Error and Exception Boundaries

- `result` and `void_result` model explicit value-or-error returns, but they are
  small ext-specific types rather than `std::expected`.
- `thread_pool` task exceptions are delivered through returned futures.
- Parsing helpers such as `version` and `uri` throw or store parsed state
  according to their API pages.
- Platform wrapper failures generally follow the behavior of the underlying
  system call or standard library primitive.
