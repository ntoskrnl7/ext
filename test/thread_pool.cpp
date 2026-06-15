#include <ext/thread_pool>
#include <gtest/gtest.h>

#if defined(_EXT_THREAD_POOL_)
#include <atomic>
#include <future>
#include <stdexcept>

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

TEST(thread_pool_test, cancellable_task_can_be_canceled_before_execution) {
  ext::thread_pool pool(1);
  std::promise<void> release;
  std::shared_future<void> release_future = release.get_future().share();

  std::future<void> blocker = pool.queue([release_future]() {
    release_future.wait();
  });

  ext::thread_pool::queue_item<int> item =
      pool.queue_cancellable([]() { return 42; });
  std::future<int> result = item.get_future();

  EXPECT_TRUE(item.cancel());
  EXPECT_TRUE(item.canceled());

  release.set_value();
  blocker.get();
  pool.stop();

  EXPECT_THROW(result.get(), ext::thread_pool::task_canceled);
}

TEST(thread_pool_test, worker_initializer_failure_stops_pool) {
  std::atomic<int> initialized(0);
  std::atomic<int> finalized(0);

  ext::thread_pool pool(
      [&initialized]() {
        ++initialized;
        return false;
      },
      [&finalized]() {
        ++finalized;
        return true;
      });

  EXPECT_FALSE(pool.start(2));
  EXPECT_EQ(ext::thread_pool::stopped, pool.status());
  EXPECT_GE(initialized.load(), 1);
  EXPECT_EQ(0, finalized.load());
  EXPECT_THROW(pool.queue([]() {}), std::runtime_error);
}
#endif
