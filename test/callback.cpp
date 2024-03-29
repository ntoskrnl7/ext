#include <ext/callback>

#ifdef _EXT_CALLBACK_
#include <functional>
#include <gtest/gtest.h>

void sum_fn(int *sum, int val) { *sum += val; }

TEST(callback_test, callback_add) {
  ext::callback<int> int_callback;
  int sum = 0;
  int_callback += std::bind(&sum_fn, &sum, std::placeholders::_1);
  int_callback += std::bind(&sum_fn, &sum, std::placeholders::_1);
#ifdef __cpp_lambdas
  int_callback += [&sum](int val) { sum += val; };
  int_callback += [&sum](int val) { sum += val; };
#endif
  int_callback(1);
#ifdef __cpp_lambdas
  EXPECT_EQ(sum, 4);
#else
  EXPECT_EQ(sum, 2);
#endif
}

TEST(callback_test, callback_remove) {
  int sum = 0;
  ext::callback<int> int_callback;
#ifdef __cpp_lambdas
  int_callback += [&sum](int val) { sum += val; };
  auto cookie = int_callback += [&sum](int val) { sum += val; };
#else
  int_callback += std::bind(&sum_fn, &sum, std::placeholders::_1);
  ext::callback<int>::cookie cookie = int_callback +=
      std::bind(&sum_fn, &sum, std::placeholders::_1);
#endif
  int_callback(1);
  EXPECT_EQ(sum, 2);

  int_callback -= cookie;
  sum = 0;
  int_callback(1);
  EXPECT_EQ(sum, 1);
}

#ifdef __cpp_variadic_templates
TEST(callback_test, callback_args_test) {
  ext::callback<std::string, int> on_changed;
  int sum = 0;
  on_changed += [&sum](const std::string &a0, int a1) {
    EXPECT_EQ(a0.size(), 3);
    EXPECT_GE(a1, 10);
    sum += a1;
  };
  on_changed += [&sum](const std::string &a0, int a1) {
    EXPECT_EQ(a0.size(), 3);
    EXPECT_GE(a1, 10);
    sum += a1;
  };
  on_changed("aaa", 10);
  on_changed("bbb", 20);

  std::string test = "ccc";
  on_changed(test, 10);
  EXPECT_EQ(sum, 80);
}
#endif
#endif // _EXT_CALLBACK_