#include <ext/callback>
#include <gtest/gtest.h>

void sum_fn(int *sum, int val) { *sum += val; }

TEST(callback_test, callback_test) {
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
