#include <ext/type_traits>
#include <ext/typeinfo>
#include <gtest/gtest.h>

class test_callable {
public:
  std::string operator()(int, char, std::vector<std::string>) { return "1"; }
};

class test_callable_2 {
public:
  void operator()(){};
  std::string operator()(int, char, std::vector<std::string>) { return "2"; }
};

#ifdef _EXT_REMOVE_CLASS_
TEST(type_traits_test, remove_class_test) {
  std::string (test_callable_2::*ptr)(int, char, std::vector<std::string>) =
      &test_callable_2::operator();

  EXPECT_STREQ(ext::get_type_name<decltype(ptr)>().c_str(),
               ext::get_type_name<std::string (test_callable_2::*)(
                   int, char, std::vector<std::string>)>()
                   .c_str());

  EXPECT_STREQ(
      ext::get_type_name<ext::remove_class<decltype(ptr)>::type>().c_str(),
      ext::get_type_name<std::string(int, char, std::vector<std::string>)>()
          .c_str());
}
#endif //_EXT_REMOVE_CLASS_

#ifdef _EXT_DEDUCE_MEM_FN_
TEST(type_traits_test, deduce_mem_fn_test) {
  auto ld = []() {};
  EXPECT_STREQ(
      ext::get_type_name<void()>().c_str(),
      ext::get_type_name<ext::deduce_mem_fn<decltype(ld)>::type>().c_str());

  auto ld2 = [](int, char, std::vector<std::string>) -> std::string {
    return "3";
  };
  EXPECT_STREQ(
      ext::get_type_name<std::string(int, char, std::vector<std::string>)>()
          .c_str(),
      ext::get_type_name<ext::deduce_mem_fn<decltype(ld2)>::type>().c_str());

  test_callable obj;
  EXPECT_STREQ(
      ext::get_type_name<std::string(int, char, std::vector<std::string>)>()
          .c_str(),
      ext::get_type_name<ext::deduce_mem_fn<decltype(obj)>::type>().c_str());

  void (test_callable_2::*ptr)(void) = &test_callable_2::operator();
  auto ts = ext::get_type_name<ext::remove_class<decltype(ptr)>::type>();
}
#endif // _EXT_DEDUCE_MEM_FN_