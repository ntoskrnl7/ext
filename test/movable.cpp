#include <gtest/gtest.h>

#define CXX_USE_STD_MOVE
#define CXX_USE_NULLPTR
#define CXX_USE_STD_SHARED_PTR
#define CXX_USE_STD_MAKE_SHARED
#include <ext/stl_compat>
#include <ext/string>

TEST(movable_test, std_string) {
  std::string a = "hello";
  std::string b = std::move(a);
  EXPECT_EQ(a, "");
  EXPECT_EQ(b, "hello");
}

TEST(movable_test, movable_string) {
  ext::string::movable::string a = "hello";
  ext::string::movable::string b = std::move(a);
  EXPECT_EQ(a, "");
  EXPECT_EQ(b, "hello");
}

TEST(movable_test, large_std_string) {
  std::string a(512, 'a');
  std::string b = std::move(a);
  EXPECT_EQ(a, "");
  EXPECT_EQ(b, std::string(512, 'a'));
}

TEST(movable_test, large_movable_string2) {
  ext::string::movable::string a(512, 'a');
  ext::string::movable::string b = std::move(a);
  EXPECT_EQ(a, "");
  EXPECT_EQ(b, std::string(512, 'a'));
}

TEST(movable_test, vector) {
  std::vector<int> a;
  a.push_back(1);
  a.push_back(2);

  std::vector<int> b = std::move(a);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 2);
}

#ifdef _EXT_STD_MOVE_
TEST(movable_test, primitive) {
  int i = 1;
  int j = std::move(i);
  EXPECT_EQ(i, 1);
  EXPECT_EQ(j, 1);
}

TEST(movable_test, disallow_copy) {
  class test {
  private:
    test(test &other) : value(nullptr) { swap(other); }
    test &operator=(test &rhs) {
      swap(rhs);
      return *this;
    }

  public:
    test() : value(nullptr) {}
    ~test() { delete value; }
    test(ext::movable<test> &other) : value(nullptr) { swap(other); }
    test &operator=(ext::movable<test> &rhs) {
      swap(rhs);
      return *this;
    }

    test &swap(test &other) {
      int *tmp_value = value;
      value = other.value;
      other.value = tmp_value;
      return *this;
    }

    int *value;
  };

  test x;
  x.value = new int(1);
  test y = std::move(x);
  // test y = x; // Assign operator not allowed.
  EXPECT_EQ(x.value, nullptr);
  EXPECT_NE(y.value, nullptr);
  EXPECT_EQ(*y.value, 1);

  test z(std::move(y));
  // test z(y); // Copy constructor not allowed.
  EXPECT_EQ(y.value, nullptr);
  EXPECT_NE(z.value, nullptr);
  EXPECT_EQ(*z.value, 1);
}

TEST(movable_test, always_use_move) {
  class test {
  public:
    test(test &other) : value(nullptr) { swap(other); }
    test &operator=(test &rhs) {
      swap(rhs);
      return *this;
    }

  public:
    test() : value(nullptr) {}
    ~test() { delete value; }
    test(ext::movable<test> &other) : value(nullptr) { swap(other); }
    test &operator=(ext::movable<test> &rhs) {
      swap(rhs);
      return *this;
    }

    test &swap(test &other) {
      int *tmp_value = value;
      value = other.value;
      other.value = tmp_value;
      return *this;
    }

    int *value;
  };

  test x;
  x.value = new int(1);
  test y = x;
  EXPECT_EQ(x.value, nullptr);
  EXPECT_NE(y.value, nullptr);
  EXPECT_EQ(*y.value, 1);

  test z(y);
  EXPECT_EQ(y.value, nullptr);
  EXPECT_NE(z.value, nullptr);
  EXPECT_EQ(*z.value, 1);

  y = std::move(z);
  EXPECT_EQ(*y.value, 1);
  EXPECT_EQ(z.value, nullptr);
  EXPECT_NE(y.value, nullptr);
}
#endif