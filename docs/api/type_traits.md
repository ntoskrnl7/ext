# type_traits

[Back to API reference](README.md)

## Header

`#include <ext/type_traits>`

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
