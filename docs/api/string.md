# string

[Back to API reference](README.md)

## Header

`#include <ext/string>`

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- split

  ```C++
  std::vector<std::string> list = ext::split("a,b,c,d", ",");
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list[0], "a");
  EXPECT_EQ(list[1], "b");
  EXPECT_EQ(list[2], "c");
  EXPECT_EQ(list[3], "d");
  ```

- u8string

  ```C++
  #define CXX_USE_STD_U8STRING
  #include <ext/string>

  #if defined(CXX_STD_U8STRING_NOT_SUPPORTED)
  #if defined(__cpp_user_defined_literals) &&                                    \
      (CXX_VER >= __cpp_user_defined_literals)
    std::u8string str = ext::from_u8(u8"한글+english");
    EXPECT_STREQ((const char *)str.c_str(), u8"한글+english");
  #else
    std::u8string str = ext::from_u8(ext::to_u8string(L"한글+english"));
    EXPECT_STREQ((const char *)str.c_str(), "\xED\x95\x9C\xEA\xB8\x80+english");
  #endif
  #else
    std::u8string str = u8"한글+english";
    EXPECT_STREQ(str.c_str(), u8"한글+english");
  #endif
  ```
