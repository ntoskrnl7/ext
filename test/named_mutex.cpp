#include <ext/named_mutex>
#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <mutex>
#include <string>
#include <thread>

#ifdef _EXT_NAMED_MUTEX_
namespace {
std::string unique_mutex_name() {
  static std::atomic_uint counter(0);
  unsigned long long stamp = static_cast<unsigned long long>(
      std::chrono::steady_clock::now().time_since_epoch().count() %
      100000000ULL);
  return "enm" + std::to_string(stamp) + "_" +
         std::to_string(counter.fetch_add(1));
}
} // namespace

TEST(named_mutex_test, locks_across_instances) {
  std::string name = unique_mutex_name();
  ext::named_mutex owner(name.c_str());
  ext::named_mutex contender(name.c_str());

  EXPECT_TRUE(owner.valid());
  EXPECT_TRUE(contender.valid());

  owner.lock();

  std::atomic_bool acquired(false);
  std::thread contender_thread([&contender, &acquired]() {
    acquired.store(contender.try_lock());
    if (acquired.load())
      contender.unlock();
  });
  contender_thread.join();

  EXPECT_FALSE(acquired.load());

  owner.unlock();
  EXPECT_TRUE(contender.try_lock());
  contender.unlock();

  EXPECT_TRUE(owner.unlink());
}

TEST(named_mutex_test, lock_guard_compatible) {
  std::string name = unique_mutex_name();
  ext::named_mutex mutex(name.c_str());

  {
    std::lock_guard<ext::named_mutex> lock(mutex);
    EXPECT_FALSE(mutex.abandoned());
  }

  EXPECT_TRUE(mutex.try_lock());
  mutex.unlock();

  EXPECT_TRUE(mutex.unlink());
}
#endif
