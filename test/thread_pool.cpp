#include <ext/thread_pool>
#include <gtest/gtest.h>

#if defined(_EXT_THREAD_POOL_)
#include <atomic>
#include <future>

TEST(thread_pool_test, worker_callbacks_are_called) {
  std::atomic<int> initialized(0);
  std::atomic<int> finalized(0);

  ext::thread_pool pool(
      3, [&initialized]() {
        ++initialized;
        return true;
      },
      [&finalized]() {
        ++finalized;
        return true;
      });

  std::future<int> result0 = pool.queue([]() { return 10; });
  std::future<int> result1 = pool.queue([]() { return 20; });

  EXPECT_EQ(10, result0.get());
  EXPECT_EQ(20, result1.get());

  pool.stop();

  EXPECT_EQ(3, initialized.load());
  EXPECT_EQ(3, finalized.load());
  EXPECT_EQ(ext::thread_pool::stopped, pool.status());
}

TEST(thread_pool_test, stop_without_wait_is_joined_by_destructor) {
  {
    ext::thread_pool pool(1);
    pool.stop(false);
    EXPECT_EQ(ext::thread_pool::stop_pending, pool.status());
  }
  SUCCEED();
}
#endif
