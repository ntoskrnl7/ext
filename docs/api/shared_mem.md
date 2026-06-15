# shared_mem

[Back to API reference](README.md)

## Header

`#include <ext/shared_mem>`

## Overview

Wraps Windows file mappings and POSIX shared memory objects behind a common access-mask API. It supports creating or opening named memory, mapping views, and destroying the backing object.

## Key APIs

- `shared_mem_access_mask` describes read, write, execute, delete, and combined access.
- `create_shared_mem` and `open_shared_mem` return native shared memory handles.
- `map_shared_mem` and `unmap_shared_mem` map/unmap views.
- `delete_shared_mem` removes the named shared memory object.
- `ext::shared_mem<T>` wraps create/open/map/destroy operations for typed shared-memory payloads.

## Behavior Notes

- The API is intentionally close to the native OS model; callers manage handles and mapped pointers carefully.
- Windows global mappings may require privileges for `Global\` names.
- `ext::shared_mem<T>::operator->` and `operator*` map the memory and expose it as `T`.
- The wrapper constructs `T` in-place only when this instance created the
  backing object.
- `destroy()` removes the named backing object; coordinate that call with every
  process that may still open or map the object.

## Layout Contract

- Every process must use the same `T` layout, packing, alignment, and binary
  compatibility assumptions.
- Prefer trivially copyable payloads. Pointers, references, process-local
  handles, virtual functions, and allocator-owned members are not portable
  across process boundaries.
- Synchronization is not provided by `shared_mem<T>`; use an external
  interprocess synchronization primitive when multiple processes can write.
- `ext::named_mutex` is the companion primitive for portable cross-process
  write synchronization.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- Process A

  ```C++
  #include <ext/shared_mem>

  struct memory_struct0 {
    int i;
    int j;
  };

  ext::shared_mem<memory_struct0> st_mem("memory_struct0", shared_mem_all_access);
  if (st_mem.opened()) {
    st_mem.destroy();
    st_mem.create();
  }

  if (st_mem.created()) {
    st_mem->i = 10;
    st_mem->j = 20;
  }
  ```

- Synchronized access

  ```C++
  #include <ext/named_mutex>
  #include <ext/shared_mem>
  #include <mutex>

  struct memory_struct0 {
    int i;
    int j;
  };

  ext::shared_mem<memory_struct0> st_mem("memory_struct0",
                                         shared_mem_all_access);
  ext::named_mutex lock("memory_struct0.lock");

  {
    std::lock_guard<ext::named_mutex> guard(lock);
    st_mem->i += 1;
    st_mem->j += 1;
  }
  ```

- Process B

  ```C++
  #include <ext/shared_mem>

  struct memory_struct0 {
    int i;
    int j;
  };

  ext::shared_mem<memory_struct0> st_mem("memory_struct0");
  if (st_mem.opened()) {
    int i = st_mem->i; // 10
    int j = st_mem->j; // 20
  }
  ```
