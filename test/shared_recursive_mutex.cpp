#include <ext/shared_recursive_mutex>
#include <gtest/gtest.h>

#if defined(_EXT_SHARED_RECURSIVE_MUTEX_)
TEST(shared_recursive_mutex, lock_test) {
  ext::shared_recursive_mutex mtx;
  EXPECT_FALSE(mtx.locked());
  mtx.lock();
  EXPECT_TRUE(mtx.locked());
  mtx.lock();
  EXPECT_TRUE(mtx.locked());
  mtx.unlock();
  mtx.unlock();
}

TEST(shared_recursive_mutex, lock_shared_test) {
  ext::shared_recursive_mutex mtx;
  EXPECT_FALSE(mtx.locked());
  mtx.lock_shared();
  EXPECT_TRUE(mtx.locked());
  mtx.lock_shared();
  EXPECT_TRUE(mtx.locked());
  mtx.unlock_shared();
  mtx.unlock_shared();
}

// TEST(shared_recursive_mutex, complex_test) {
//   ext::shared_recursive_mutex mtx;
//   mtx.lock_shared();
//   mtx.lock();
//   mtx.lock_shared();
//   mtx.unlock_shared();
//   mtx.unlock_shared();
//   mtx.lock();
// }
#endif