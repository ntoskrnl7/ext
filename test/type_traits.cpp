
#include <ext/typeinfo>
#include <ext/type_traits>
#include <gtest/gtest.h>

class test_callable {
public:
  std::string operator()(int, char, std::vector<std::string>) { return ""; }
};

class test_callable_2 {
public:
  void operator()(){};
  std::string operator()(int, char, std::vector<std::string>) { return ""; }
};

TEST(deduce_mem_fn_test, test) {
  auto ld = []() {};
  auto ts = ext::get_type_name<ext::deduce_mem_fn<decltype(ld)>::type>();

  auto ld2 = [](int, char, std::vector<std::string>) -> std::string {
    return "";
  };

  ts = ext::get_type_name<ext::deduce_mem_fn<decltype(ld2)>::type>();

  test_callable obj;
  ts = ext::get_type_name<test_callable>();

  ts = ext::get_type_name<ext::deduce_mem_fn<decltype(obj)>::type>();

  void (test_callable_2::*ptr)(void) = &test_callable_2::operator();
  ts = ext::get_type_name<ext::remove_class<decltype(ptr)>::type>();

  std::string (test_callable_2::*ptr2)(int, char, std::vector<std::string>) =
      &test_callable_2::operator();
  ts = ext::get_type_name<ext::remove_class<decltype(ptr2)>::type>();

  ts = ext::get_type_name<decltype(ptr2)>();

  test_callable_2 obj2;
  std::bind(ptr, obj2)();
}
