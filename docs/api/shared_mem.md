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

- Pocess B

  ```C++
  #include <ext/shared_mem>

  struct memory_struct0 {
    int i;
    int j;
  };

  ext::shared_mem<memory_struct0> st_mem("memory_struct0");
  if (st_mem.opened()) {
    st_mem2->i; // 10
    st_mem2->j; // 20
  }
  ```
