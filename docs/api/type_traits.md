# type_traits

[Back to API reference](README.md)

## Header

`#include <ext/type_traits>`

## Overview

Adds compile-time utilities that the rest of the library uses for callable and chain support. Tests cover removing the owning class from member-function pointers and deducing member-function types.

## Key APIs

- `ext::remove_class<T>` strips the class from member-function pointer types.
- `ext::deduce_mem_fn<T>` derives a callable function signature from a member-function pointer.
- Const and non-const member-function pointer forms are supported.

## Behavior Notes

- These traits are intended for template metaprogramming and usually appear in helper code rather than application code.
- They rely on compiler support for the relevant type-trait and template features.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

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
