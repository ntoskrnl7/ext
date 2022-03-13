#include <gtest/gtest.h>

#include <functional>
#include <vector>

#define CXX_USE_STD_THREAD
#include <ext/pipe>

void pipe_test(ext::pipe::opstream *stream) { *stream << "test" << std::endl; }
TEST(pipe_test, basic_test) {
  ext::pipe pipe;
  std::thread t(std::bind(pipe_test, &pipe.out()));
  std::string val;
  pipe.in() >> val;
  EXPECT_STREQ(val.c_str(), "test");
  if (t.joinable())
    t.join();
}

void wpipe_test(ext::wpipe::opstream *stream) {
  *stream << L"test" << std::endl;
}
TEST(pipe_test, wpipe_test) {
  ext::wpipe pipe;
  std::thread t(std::bind(wpipe_test, &pipe.out()));
  std::wstring val;
  pipe.in() >> val;
  EXPECT_STREQ(val.c_str(), L"test");
  if (t.joinable())
    t.join();
}