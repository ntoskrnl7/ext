#ifdef CXX_USE_BOOST
#define CXX_USE_STD_CHRONO
#include <boost/chrono.hpp>
#define CXX_USE_STD_THREAD
#include <boost/thread.hpp>
#endif
#include <ext/async_iterator>
#include <gtest/gtest.h>

#ifdef __cpp_lambdas
TEST(async_iterator_test, int_test) {
  typedef ext::async_result<int> int_result;
  int_result res([](int_result::context &ctx) {
    ctx.begin(4);
    ctx.push(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ctx.push(2);
    ctx.push(3);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ctx.push(4);
    ctx.end();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  });

  int j = 1;
  CXX_FOR(auto &i, res) {
    EXPECT_EQ(j++, i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  j = 1;
  CXX_FOR(auto &i, res) {
    EXPECT_EQ(j++, i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  CXX_FOR(auto &i, res) { EXPECT_TRUE(false); }

  res = int_result([](int_result::context &ctx) {
    ctx.begin(4);
    ctx.push(5);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ctx.push(7);
    ctx.push(9);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ctx.push(11);
    ctx.push(13);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  });
  EXPECT_EQ(res.size(), 5);

  j = 3;
  CXX_FOR(auto &i, res) {
    EXPECT_EQ(j += 2, i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

TEST(async_iterator_test, int_thread_test) {
  typedef ext::async_result<int> int_result;
  const int count = 1000;
  int_result res([count](int_result::context &ctx) {
    ctx.begin(count);
    for (int i = 0; i < count; ++i)
      ctx.push(i);
  });

  std::thread t([&res]() {
    CXX_FOR(auto &i, res) { EXPECT_LT(i, (int)res.size()); }
  });
  std::thread t2([&res]() {
    CXX_FOR(auto &i, res) { EXPECT_LT(i, (int)res.size()); }
  });
  if (t.joinable())
    t.join();
  if (t2.joinable())
    t2.join();
}

TEST(async_iterator_test, int_thread_cancelable_test) {
  typedef ext::async_result<int> int_result;
  const int count = 1000000;
  int processed = 0;
  int_result res([count, &processed](int_result::context &ctx) {
    ctx.begin(count);
    for (int i = 0; i < count; ++i) {
      if (ctx.cancel_requested())
        break;
      processed = i;
      ctx.push(i);
    }
  });

  std::thread t0([&res, &processed]() {
    std::this_thread::sleep_for(std::chrono::microseconds(500));
    res.cancel();
  });
  std::thread t1([&res, &processed]() {
    CXX_FOR(auto &i, res) {
      EXPECT_LE(i, processed);
      EXPECT_LT(i, (int)res.size());
    }
  });
  std::thread t2([&res, &processed]() {
    CXX_FOR(auto &i, res) {
      EXPECT_LE(i, processed);
      EXPECT_LT(i, (int)res.size());
    }
  });

  if (t0.joinable())
    t0.join();
  if (t1.joinable())
    t1.join();
  if (t2.joinable())
    t2.join();
}

TEST(async_iterator_test, string_test) {
  typedef ext::async_result<std::string> str_result;
  str_result res([](str_result::context &ctx) {
    ctx.push("str 1");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ctx.push("str 2");
    ctx.push("str 3");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ctx.push("str 4");
  });

  int j = 1;
  CXX_FOR(auto &s, res) {
    EXPECT_EQ(s, "str " + std::to_string((long long)j++));
  }
}

TEST(async_iterator_test, pair_test) {
  typedef ext::async_result<std::pair<std::string, size_t>> pair_result;
  pair_result res([](pair_result::context &ctx) {
    typedef ext::async_result<std::pair<std::string, size_t>> pair_result;
#ifdef __cpp_variadic_templates
    ctx.emplace("str 1", 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
#endif
#ifdef __cpp_aggregate_nsdmi
    ctx.push({"str 2", 2});
#else
    ctx.push(pair_result::type("str 2", 2));
#endif
#ifdef __cpp_variadic_templates
    ctx.emplace("str 3", 3);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
#endif
#ifdef __cpp_aggregate_nsdmi
    ctx.push({"str 4", 4});
#else
    ctx.push(pair_result::type("str 4", 4));
#endif
  });

  int j = 0;
  CXX_FOR(auto &s, res) {
    EXPECT_EQ(s.first, "str " + std::to_string((long long)s.second));
    EXPECT_EQ(s.second, s.second);
  }
}
#else
typedef ext::async_result<int> int_result;
void int_test_phase0(int_result::context &ctx) {
  ctx.begin(4);
  ctx.push(1);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ctx.push(2);
  ctx.push(3);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ctx.push(4);
  ctx.end();
  std::this_thread::sleep_for(std::chrono::seconds(3));
}
void int_test_phase1(int_result::context &ctx) {
  ctx.begin(4);
  ctx.push(5);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  ctx.push(6);
  ctx.push(7);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  ctx.push(8);
  ctx.push(9);
  std::this_thread::sleep_for(std::chrono::seconds(3));
}

TEST(async_iterator_test, int_test) {
  typedef ext::async_result<int> int_result;
  int_result res = int_test_phase0;

  int j = 1;
  CXX_FOR(int i, res) {
    EXPECT_EQ(j++, i);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  j = 1;
  CXX_FOR(int i, res) {
    EXPECT_EQ(j++, i);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  CXX_FOR(int &i, res) { EXPECT_TRUE(false); }

  res = int_result(int_test_phase1);
  EXPECT_EQ((int)res.size(), 5);

  j = 5;
  CXX_FOR(int &i, res) {
    EXPECT_EQ(j++, i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
#endif