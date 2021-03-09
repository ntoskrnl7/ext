#include <ext/path>

#define GTEST_HAS_TR1_TUPLE 0
#include <gtest/gtest.h>

TEST(path_test, test) {
#ifdef _WIN32
  std::string r = ext::path::join("c:", "dir");
  EXPECT_STREQ(r.c_str(), "c:\\dir");
#else
  std::string r = ext::path::join("/home", "dir");
  EXPECT_STREQ(r.c_str(), "/home/dir");
#endif
#ifdef _WIN32
  r = ext::path::join("c:", "dir", "file");
  EXPECT_STREQ(r.c_str(), "c:\\dir\\file");
#else
  r = ext::path::join("/home", "dir", "file");
  EXPECT_STREQ(r.c_str(), "/home/dir/file");
#endif
#ifdef _WIN32
  std::string path = "d:";
  r = ext::path::join(path, "dir");
  EXPECT_STREQ(r.c_str(), "d:\\dir");
  r = ext::path::join(path, std::string("dir"), std::string("file"));
  EXPECT_STREQ(r.c_str(), "d:\\dir\\file");
#else
  std::string path = "/home";
  r = ext::path::join(path, "dir");
  EXPECT_STREQ(r.c_str(), "/home/dir");
  r = ext::path::join(path, std::string("dir"), std::string("file"));
  EXPECT_STREQ(r.c_str(), "/home/dir/file");
#endif
}
