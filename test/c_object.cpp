#include <gtest/gtest.h>

extern "C" int object_test_c();
extern "C" size_t object_count_c();

TEST(object_test, basic) { EXPECT_EQ(object_test_c(), EXIT_SUCCESS); }

TEST(object_test, leak) { EXPECT_EQ(object_count_c(), 0); }