#include <gtest/gtest.h>

#include <ext/result>

ext::void_result<int> void_result_ok_fn() { return ext::ok<void>(); }
#if defined(__cpp_deduction_guides)
ext::void_result<int> void_result_err_fn() { return ext::err(10); }
#else
ext::void_result<int> void_result_err_fn() { return ext::err<int>(10); }
#endif

TEST(result_test, void_result_test) {
  ext::void_result<int> result = void_result_ok_fn();
  EXPECT_TRUE(result);

  result = void_result_err_fn();
  EXPECT_FALSE(result);
  EXPECT_EQ((int)result.err(), 10);
}

#if defined(__cpp_deduction_guides)
ext::result<int, int> int_result_ok_fn() { return ext::ok(10); }
ext::result<int, int> int_result_err_fn() { return ext::err(10); }
#else
ext::result<int, int> int_result_ok_fn() { return ext::ok<int>(10); }
ext::result<int, int> int_result_err_fn() { return ext::err<int>(10); }
#endif

TEST(result_test, int_result_test) {
  ext::result<int, int> result = int_result_ok_fn();
  EXPECT_TRUE(result);
  EXPECT_EQ((int)result.ok(), 10);

  result = int_result_err_fn();
  EXPECT_FALSE(result);
  EXPECT_EQ((int)result.err(), 10);
}

ext::result<short, int> short_int_result_ok_fn() { return ext::ok<short>(10); }
#if defined(__cpp_deduction_guides)
ext::result<short, int> short_int_result_err_fn() { return ext::err(10); }
#else
ext::result<short, int> short_int_result_err_fn() { return ext::err<int>(10); }
#endif

TEST(result_test, short_int_result_test) {
  ext::result<short, int> result = short_int_result_ok_fn();
  EXPECT_TRUE(result);
  EXPECT_EQ((short)result.ok(), 10);

  result = short_int_result_err_fn();
  EXPECT_FALSE(result);
  EXPECT_EQ((int)result.err(), 10);
}

#include <errno.h>

#if defined(_WIN32) || (!defined(__GLIBCXX__))
typedef errno_t error_t;
#endif

#if defined(__cpp_deduction_guides)
ext::result<int, error_t> int_error_t_result_ok_fn() { return ext::ok(10); }
ext::result<int, error_t> int_error_t_result_err_fn() {
  return ext::err(EBUSY);
}
#else
ext::result<int, error_t> int_error_t_result_ok_fn() {
  return ext::ok<int>(10);
}
ext::result<int, error_t> int_error_t_result_err_fn() {
  return ext::err<error_t>(EBUSY);
}
#endif

TEST(result_test, int_error_t_result_test) {
  ext::result<int, error_t> result = int_error_t_result_ok_fn();
  EXPECT_TRUE(result);
  EXPECT_EQ(result.ok(), 10);

  result = int_error_t_result_err_fn();
  EXPECT_FALSE(result);
  EXPECT_EQ((error_t)result.err(), EBUSY);
}
