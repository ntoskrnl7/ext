# shared_mem

[Back to API reference](README.md)

## Header

`#include <ext/shared_mem>`

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
