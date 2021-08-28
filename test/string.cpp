#define CXX_USE_NULLPTR
#include <ext/string>
#include <gtest/gtest.h>

TEST(string_test, stoul) {
#if defined(_MSC_VER)
  EXPECT_EQ(std::stoul("-12345"), 4294954951);
  EXPECT_EQ(std::stoul("12345"), 12345);
  EXPECT_EQ(std::stoul("0xffffffff", nullptr, 16),
            std::numeric_limits<unsigned long>::max());

  EXPECT_EQ(std::stoul(L"-12345"), 4294954951);
  EXPECT_EQ(std::stoul(L"12345"), 12345);
  EXPECT_EQ(std::stoul(L"0xffffffff", nullptr, 16),
            std::numeric_limits<unsigned long>::max());

#else
  EXPECT_EQ((uint32_t)std::stoul("-12345"), 4294954951);
  EXPECT_EQ(std::stoul("12345"), 12345);
  EXPECT_EQ((uint32_t)std::stoul("0xffffffff", nullptr, 16),
            std::numeric_limits<uint32_t>::max());

  EXPECT_EQ((uint32_t)std::stoul(L"-12345"), 4294954951);
  EXPECT_EQ(std::stoul(L"12345"), 12345);
  EXPECT_EQ((uint32_t)std::stoul(L"0xffffffff", nullptr, 16),
            std::numeric_limits<uint32_t>::max());
#endif
  EXPECT_THROW(EXPECT_EQ(std::stoul("hello", nullptr, 16),
                         std::numeric_limits<unsigned long>::max()),
               std::invalid_argument);

  EXPECT_THROW(EXPECT_EQ(std::stoul("Lhello", nullptr, 16),
                         std::numeric_limits<unsigned long>::max()),
               std::invalid_argument);

  EXPECT_THROW(EXPECT_EQ(std::stoul("0xffffffffffffffffff", nullptr, 16),
                         std::numeric_limits<unsigned long>::max()),
               std::out_of_range);

  EXPECT_THROW(EXPECT_EQ(std::stoul(L"0xffffffffffffffffff", nullptr, 16),
                         std::numeric_limits<unsigned long>::max()),
               std::out_of_range);
}

TEST(string_test, stoull) {
  EXPECT_EQ(std::stoull("-12345"), 18446744073709539271ull);
  EXPECT_EQ(std::stoull("12345"), 12345);
  EXPECT_EQ(std::stoull("0xffffffffffffffff", nullptr, 16),
            std::numeric_limits<unsigned long long>::max());

  EXPECT_EQ(std::stoull("-12345"), 18446744073709539271ull);
  EXPECT_EQ(std::stoull("12345"), 12345);
  EXPECT_EQ(std::stoull("0xffffffffffffffff", nullptr, 16),
            std::numeric_limits<unsigned long long>::max());

  EXPECT_EQ(std::stoull(L"-12345"), 18446744073709539271ull);
  EXPECT_EQ(std::stoull(L"12345"), 12345);

  EXPECT_THROW(EXPECT_EQ(std::stoull("hello", nullptr, 16),
                         std::numeric_limits<unsigned long long>::max()),
               std::invalid_argument);

  EXPECT_THROW(EXPECT_EQ(std::stoull("Lhello", nullptr, 16),
                         std::numeric_limits<unsigned long long>::max()),
               std::invalid_argument);

  EXPECT_THROW(EXPECT_EQ(std::stoull("0xffffffffffffffffff", nullptr, 16),
                         std::numeric_limits<unsigned long long>::max()),
               std::out_of_range);

  EXPECT_THROW(EXPECT_EQ(std::stoull(L"0xffffffffffffffffff", nullptr, 16),
                         std::numeric_limits<unsigned long long>::max()),
               std::out_of_range);
}

TEST(string_test, movable_string_test) {
  using namespace ext::string;
  movable::string a(512, 'a');
  movable::string b(a.begin(), a.end());
  EXPECT_EQ(a, b);

  movable::wstring aw(512, L'a');
  movable::wstring bw(aw.begin(), aw.end());
  EXPECT_EQ(aw, bw);
}

TEST(string_test, printable_test) {
  std::string str = "\x0e\x10test\x0f\x11test\x0a\x12";
  EXPECT_STREQ(ext::printable(str).c_str(), "testtest");

  std::wstring str_w = L"\x0e\x10test\x0f\x11test\x0a\x12";
  EXPECT_STREQ(ext::printable(str_w).c_str(), L"testtest");

  str = "\x0e\x10test\x0f\x11test\x0a\x12";
  EXPECT_STREQ(ext::lprintable(str).c_str(), "test\x0f\x11test\x0a\x12");

  str_w = L"\x0e\x10test\x0f\x11test\x0a\x12";
  EXPECT_STREQ(ext::lprintable(str_w).c_str(), L"test\x0f\x11test\x0a\x12");

  str = "\x0e\x10test\x0f\x11test\x0a\x12";
  EXPECT_STREQ(ext::rprintable(str).c_str(), "\x0e\x10test\x0f\x11test");

  str_w = L"\x0e\x10test\x0f\x11test\x0a\x12";
  EXPECT_STREQ(ext::rprintable(str_w).c_str(), L"\x0e\x10test\x0f\x11test");

  EXPECT_STREQ(ext::printable(std::string("\x0e\x10test\x0e\x10")).c_str(),
               "test");
  EXPECT_STREQ(ext::printable(std::wstring(L"\x0e\x10test\x0e\x10")).c_str(),
               L"test");
  EXPECT_STREQ(ext::lprintable(std::string("\x0e\x10test\x0e\x10")).c_str(),
               "test\x0e\x10");
  EXPECT_STREQ(ext::lprintable(std::wstring(L"\x0e\x10test\x0e\x10")).c_str(),
               L"test\x0e\x10");
  EXPECT_STREQ(ext::rprintable(std::string("\x0e\x10test\x0e\x10")).c_str(),
               "\x0e\x10test");
  EXPECT_STREQ(ext::rprintable(std::wstring(L"\x0e\x10test\x0e\x10")).c_str(),
               L"\x0e\x10test");

  EXPECT_STREQ(ext::printable("\x0e\x10test\x0e\x10").c_str(), "test");
  EXPECT_STREQ(ext::printable(L"\x0e\x10test\x0e\x10").c_str(), L"test");
  EXPECT_STREQ(ext::lprintable("\x0e\x10test\x0e\x10").c_str(), "test\x0e\x10");
  EXPECT_STREQ(ext::lprintable(L"\x0e\x10test\x0e\x10").c_str(),
               L"test\x0e\x10");
  EXPECT_STREQ(ext::rprintable("\x0e\x10test\x0e\x10").c_str(), "\x0e\x10test");
  EXPECT_STREQ(ext::rprintable(L"\x0e\x10test\x0e\x10").c_str(),
               L"\x0e\x10test");

#if (!defined(_MSC_VER)) || (defined(_MSC_VER) && _MSC_VER > 1600)
  const std::string const_str = "\x0e\x10\x0e\x10test\x0e\x10\x0e\x10";
  EXPECT_STREQ(ext::printable(const_str).c_str(), "test");

  const std::wstring const_wstr = L"\x0e\x10\x0e\x10test\x0e\x10\x0e\x10";
  EXPECT_STREQ(ext::printable(const_wstr).c_str(), L"test");
#endif
}

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

#if (!defined(_MSC_VER)) || (defined(_MSC_VER) && _MSC_VER > 1600)
  const std::string const_str = "  test  ";
  EXPECT_STREQ(ext::trim(const_str).c_str(), "test");

  const std::wstring const_wstr = L"  test  ";
  EXPECT_STREQ(ext::trim(const_wstr).c_str(), L"test");
#endif
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