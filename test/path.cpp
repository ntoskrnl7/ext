#include <ext/path>

#define GTEST_HAS_TR1_TUPLE 0
#include <gtest/gtest.h>

TEST(path_test, test) {
#if defined(_WIN32)
  std::string r = ext::path::join("c:", "dir");
  EXPECT_STREQ(r.c_str(), "c:\\dir");

  r = ext::path::dirname("c:\\dir\\test\\test");
  EXPECT_STREQ(r.c_str(), "c:\\dir\\test");
  
  r = ext::path::basename("c:\\dir\\test\\test\\abc");
  EXPECT_STREQ(r.c_str(), "abc");

  r = ext::path::join("c:", "dir", ".test\\test", "..\\abc");
  EXPECT_STREQ(r.c_str(), "c:\\dir\\.test\\abc");

  r = ext::path::join("c:", "dir", "test\\te.st", ".\\abc");
  EXPECT_STREQ(r.c_str(), "c:\\dir\\test\\te.st\\abc");

  r = ext::path::join("c:", "dir", "test1\\test2", "..\\..\\..\\abc");
  EXPECT_STREQ(r.c_str(), "c:\\abc");

  r = ext::path::join("c:", "dir", "test1\\test2", "..\\.\\..\\abc");
  EXPECT_STREQ(r.c_str(), "c:\\dir\\abc");

  r = ext::path::join("c:", "dir", "test\\test", "..\\..\\..\\..\\abc");
  EXPECT_STREQ(r.c_str(), "");

  std::wstring ws = ext::path::join(L"c:", L"dir");
  ws = ext::path::join(L"c:", L"dir", L"test\\te.st", L".\\abc");
  EXPECT_STREQ(ws.c_str(), L"c:\\dir\\test\\te.st\\abc");

  ws = ext::path::join(L"c:", L"dir", L"test1\\test2", L"..\\..\\..\\abc");
  EXPECT_STREQ(ws.c_str(), L"c:\\abc");
#else
  std::string r = ext::path::join("/home", "dir");
  EXPECT_STREQ(r.c_str(), "/home/dir");
#endif
#if defined(_WIN32)
  r = ext::path::join("c:", "dir", "file");
  EXPECT_STREQ(r.c_str(), "c:\\dir\\file");
#else
  r = ext::path::join("/home", "dir", "file");
  EXPECT_STREQ(r.c_str(), "/home/dir/file");
#endif
#if defined(_WIN32)
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
