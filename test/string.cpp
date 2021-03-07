#include <ext/string>
#include <gtest/gtest.h>

TEST(string_test, trim_test) {
  std::string str = " test ";
  EXPECT_STREQ(ext::trim(str).c_str(), "test");

  std::wstring str_w = L" test ";
  EXPECT_STREQ(ext::trim(str_w).c_str(), L"test");

  str = " test ";
  EXPECT_STREQ(ext::ltrim(str).c_str(), "test ");

  str_w = L" test ";
  EXPECT_STREQ(ext::ltrim(str_w).c_str(), L"test ");

  str = " test ";
  EXPECT_STREQ(ext::rtrim(str).c_str(), " test");

  str_w = L" test ";
  EXPECT_STREQ(ext::rtrim(str_w).c_str(), L" test");

  EXPECT_STREQ(ext::trim(std::string(" test ")).c_str(), "test");
  EXPECT_STREQ(ext::trim(std::wstring(L" test ")).c_str(), L"test");
  EXPECT_STREQ(ext::ltrim(std::string(" test ")).c_str(), "test ");
  EXPECT_STREQ(ext::ltrim(std::wstring(L" test ")).c_str(), L"test ");
  EXPECT_STREQ(ext::rtrim(std::string(" test ")).c_str(), " test");
  EXPECT_STREQ(ext::rtrim(std::wstring(L" test ")).c_str(), L" test");

  EXPECT_STREQ(ext::trim(" test ").c_str(), "test");
  EXPECT_STREQ(ext::trim(L" test ").c_str(), L"test");
  EXPECT_STREQ(ext::ltrim(" test ").c_str(), "test ");
  EXPECT_STREQ(ext::ltrim(L" test ").c_str(), L"test ");
  EXPECT_STREQ(ext::rtrim(" test ").c_str(), " test");
  EXPECT_STREQ(ext::rtrim(L" test ").c_str(), L" test");

  const std::string const_str = "  test  ";
  EXPECT_STREQ(ext::trim(const_str).c_str(), "test");

  const std::wstring const_wstr = L"  test  ";
  EXPECT_STREQ(ext::trim(const_wstr).c_str(), L"test");
}

TEST(string_test, search_test) {
  EXPECT_TRUE(ext::search("hello, world :-)", "world"));
  EXPECT_TRUE(ext::search("hello, world :-)", "World"));

  EXPECT_TRUE(ext::search("hello, world :-)", "world", true));
  EXPECT_FALSE(ext::search("hello, world :-)", "World", true));
}

TEST(string_test, equal_test) {
  EXPECT_TRUE(ext::equal("hello, world :-)", "hello, world :-)"));
  EXPECT_TRUE(ext::equal("hello, world :-)", "hello, World :-)"));

  EXPECT_TRUE(ext::equal("hello, world :-)", "hello, world :-)", true));
  EXPECT_FALSE(ext::equal("hello, world :-)", "hello, World :-)", true));
}

TEST(string_test, replace_all_test) {
  std::string str = "hello, world :-)";
  EXPECT_STREQ(ext::replace_all(str, ":-", ";-").c_str(), "hello, world ;-)");

  std::wstring str_w = L"hello, world :-)";
  EXPECT_STREQ(ext::replace_all(str_w, L":-", L";-").c_str(),
               L"hello, world ;-)");
}

TEST(string_test, split_test) {
  std::vector<std::string> list = ext::split("a,b,c,d", ",");
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list[0], "a");
  EXPECT_EQ(list[1], "b");
  EXPECT_EQ(list[2], "c");
  EXPECT_EQ(list[3], "d");
}

#ifdef __cpp_lambdas
TEST(string_test, split_int_test) {
  std::vector<int> list =
      ext::split<int>("10,20,30,40", ",",
                      [](const std::string &val) { return std::stoul(val); });
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list[0], 10);
  EXPECT_EQ(list[1], 20);
  EXPECT_EQ(list[2], 30);
  EXPECT_EQ(list[3], 40);
}

#ifndef CXX_STD_ANY_NOT_SUPPORTED
#include <any>
TEST(string_test, split_any_test) {
  auto list = ext::split<std::any>("10,b,30,c", ",",
                                   [](const std::string &val) -> std::any {
                                     try {
                                       return std::stoul(val);
                                     } catch (const std::exception &) {
                                     }
                                     return val;
                                   });
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(std::any_cast<unsigned long>(list[0]), 10);
  EXPECT_EQ(std::any_cast<std::string>(list[1]), "b");
  EXPECT_EQ(std::any_cast<unsigned long>(list[2]), 30);
  EXPECT_EQ(std::any_cast<std::string>(list[3]), "c");
}
#endif
#endif