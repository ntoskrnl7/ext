#include <ext/async_iterator>
#include <gtest/gtest.h>

TEST(async_iterator_test, int_test) {
  using int_result = ext::async_result<int>;
  int_result res = {[](int_result::context &ctx) {
    ctx.begin(4);
    ctx.push(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ctx.emplace(2);
    ctx.push(3);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ctx.emplace(4);
    ctx.end();
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }};

  for (auto &i : res) {
    std::cout << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  for (auto &i : res) {
    EXPECT_TRUE(false);
    std::cout << i << std::endl;
  }
}

TEST(async_iterator_test, int_thread_test) {
  using int_result = ext::async_result<int>;
  const size_t count = 1000;
  int_result res = {[count](int_result::context &ctx) {
    ctx.begin(count);
    for (int i = 0; i < count; ++i)
      ctx.push(i);
  }};

  std::mutex mtx;
  std::thread t([&res, &mtx]() {
    for (auto &i : res) {
      std::unique_lock lk(mtx);
      std::cout << "t(" << res.current() << "/" << res.size() << "):\t" << i << std::endl;
      EXPECT_LT(i, res.size());
    }
  });
  std::thread t2([&res, &mtx]() {
    for (auto &i : res) {
      std::unique_lock lk(mtx);
      std::cout << "t2(" << res.current() << "/" << res.size() << "):\t" << i << std::endl;
      EXPECT_LT(i, res.size());
    }
  });
  if (t.joinable())
    t.join();
  if (t2.joinable())
    t2.join();
}

TEST(async_iterator_test, string_test) {
  using str_result = ext::async_result<std::string>;
  str_result res = {[](str_result::context &ctx) {
    ctx.emplace("str 1");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ctx.push("str 2");
    ctx.emplace("str 3");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ctx.push("str 4");
  }};

  for (auto &s : res) {
    std::cout << s << std::endl;
  }
}

TEST(async_iterator_test, pair_test) {
  using str_result = ext::async_result<std::pair<std::string, size_t>>;
  str_result res = {[](str_result::context &ctx) {
    ctx.emplace("str 1", 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ctx.push({"str 2", 2});
    ctx.emplace("str 3", 3);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ctx.push({"str 4", 4});
  }};

  for (auto &s : res) {
    std::cout << s.first << "," << s.second << std::endl;
    EXPECT_EQ(s.first, "str " + std::to_string(s.second) );
    EXPECT_EQ(s.second, s.second );
  }
}