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
  EXPECT_NO_THROW(result.error());
  EXPECT_EQ((int)result.error(), 10);
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
  EXPECT_EQ((int)result.get(), 10);
  EXPECT_THROW(result.error(), ext::no_error_occurred);

  result = int_result_err_fn();
  EXPECT_FALSE(result);
  EXPECT_NO_THROW(result.error());
  EXPECT_EQ((int)result.error(), 10);
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
  EXPECT_EQ((short)result.get(), 10);

  result = short_int_result_err_fn();
  EXPECT_FALSE(result);
  EXPECT_NO_THROW(result.error());
  EXPECT_EQ((int)result.error(), 10);
}

#include <errno.h>

#if defined(_WIN32) || (!defined(__GLIBCXX__))
typedef errno_t error_t;
#endif

#if defined(__cpp_deduction_guides)
ext::result<int, error_t> int_error_t_result_ok_fn() { return ext::ok(10); }
ext::result<int, error_t> int_error_t_result_err_fn() {
  return ext::err(EBUSY, "I'm busy");
}
#else
ext::result<int, error_t> int_error_t_result_ok_fn() {
  return ext::ok<int>(10);
}
ext::result<int, error_t> int_error_t_result_err_fn() {
  return ext::err<error_t>(EBUSY, "I'm busy");
}
#endif

TEST(result_test, int_error_t_result_test) {
  ext::result<int, error_t> result = int_error_t_result_ok_fn();
  EXPECT_TRUE(result);
  EXPECT_THROW(result.error(), ext::no_error_occurred);
  try {
    result.error();
  } catch (const std::exception &e) {
    EXPECT_STREQ(e.what(), "No error occurred.");
  }
  try {
    result.error();
  } catch (const ext::result_error &e) {
    EXPECT_STREQ(e.what(), "No error occurred.");
  }
  try {
    result.error();
  } catch (const ext::no_error_occurred &e) {
    EXPECT_STREQ(e.what(), "No error occurred.");
  }
  EXPECT_EQ(result.get(), 10);

  result = int_error_t_result_err_fn();
  EXPECT_FALSE(result);
  EXPECT_NO_THROW(result.error());
  EXPECT_EQ((error_t)result.error(), EBUSY);
  EXPECT_STREQ(result.error().what(), "I'm busy");
  try {
    result.get();
  } catch (const std::exception &e) {
    EXPECT_STREQ(e.what(), "I'm busy");
  }
  try {
    result.get();
  } catch (const ext::result_error &e) {
    EXPECT_STREQ(e.what(), "I'm busy");
  }
  try {
    result.get();
  } catch (const ext::error_occurred &e) {
    EXPECT_STREQ(e.what(), "I'm busy");
  }
}