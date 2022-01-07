#ifdef CXX_USE_BOOST
#define CXX_USE_STD_CHRONO
#include <boost/chrono.hpp>

#define CXX_USE_STD_THREAD
#include <boost/thread.hpp>

#define CXX_USE_STD_MUTEX
#include <boost/thread/mutex.hpp>
#endif

#include <ext/cancelable_thread>
#include <gtest/gtest.h>

#if defined(_EXT_CANCELABLE_THREAD_)
class test_class {
public:
  test_class(int i, bool &flag) : i_(i), flag_(flag) {
    std::cout << i << " Constructor\n";
    flag_ = false;
  }
  ~test_class() {
    std::cout << i_ << " Destructor\n";
    flag_ = true;
  }
  int i_;
  bool &flag_;
};

#ifdef __cpp_lambdas
TEST(cancelable_thread_test, cancel_immediately) {
  std::mutex mtx;
  bool reached = false;
#if defined(_WIN32)
  bool destructor_invoked[] = {false, false};
#endif
  ext::cancelable_thread t(
#if defined(_WIN32)
      [&mtx, &destructor_invoked, &reached]() {
        std::cout
            << "cancelable_thread_test::cancel_immediately thread started\n";
        test_class t1(1, destructor_invoked[0]);
        test_class t2(2, destructor_invoked[1]);
#else
      [&mtx, &reached]() {
        std::cout
            << "cancelable_thread_test::cancel_immediately thread started\n";
#endif
        std::unique_lock<std::mutex> lk(mtx);
        while (true) {
          // std::this_thread::yield();
        }

        reached = true;
        std::cout
            << "cancelable_thread_test::cancel_immediately thread stopped\n";
      },
      [&mtx]() { mtx.unlock(); });

  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(t.joinable());
  t.cancel();
  t.join();
  EXPECT_FALSE(t.completed());
  EXPECT_TRUE(t.canceled());

#if defined(_WIN32)
  EXPECT_FALSE(destructor_invoked[0]);
  EXPECT_FALSE(destructor_invoked[1]);
#endif
  EXPECT_FALSE(reached);
  if (mtx.try_lock()) {
    mtx.unlock();
  } else {
    EXPECT_TRUE(false);
  }
}

TEST(cancelable_thread_test, cancel) {
  std::mutex mtx;
  bool reached = false;
  bool destructor_invoked[] = {false, false};
  ext::cancelable_thread t([&mtx, &destructor_invoked, &reached]() {
    std::cout << "cancelable_thread_test::cancelthread started\n";
    test_class t1(1, destructor_invoked[0]);
    test_class t2(2, destructor_invoked[1]);
    std::unique_lock<std::mutex> lk(mtx);
#if EXT_CANCELABLE_THREAD_USE_PTHREAD
    std::this_thread::sleep_for(std::chrono::seconds(50));
    char *msystem = getenv("MSYSTEM");
    if (msystem && strcmp(msystem, "MSYS") == 0)
      throw ext::canceled_exception();
#else
    if (SleepEx(50000, TRUE) == WAIT_IO_COMPLETION)
      throw ext::canceled_exception();
#endif
    reached = false;
    std::cout << "cancelable_thread_test::cancelthread stopped\n";
  });
  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(t.joinable());
  t.cancel();
  t.join();
  EXPECT_FALSE(t.completed());
  EXPECT_TRUE(t.canceled());

  EXPECT_TRUE(destructor_invoked[0]);
  EXPECT_TRUE(destructor_invoked[1]);
  EXPECT_FALSE(reached);
  if (mtx.try_lock()) {
    mtx.unlock();
  } else {
    EXPECT_TRUE(false);
  }
}
#else  // !defined(__cpp_lambdas)
std::mutex mtx;
bool reached = false;
bool destructor_invoked[] = {false, false};

void cancel_immediately_test_fn() {
  test_class t1(1, destructor_invoked[0]);
  test_class t2(2, destructor_invoked[1]);
  std::unique_lock<std::mutex> lk(mtx);
  std::cout << "cancelable_thread_test::cancel_immediately thread started\n";
  while (true) {
    // std::this_thread::yield();
  }
  reached = true;
  std::cout << "cancelable_thread_test::cancel_immediately thread stopped\n";
}

TEST(cancelable_thread_test, cancel_immediately) {
  reached = false;

  ext::cancelable_thread t(cancel_immediately_test_fn,
                           std::bind(&std::mutex::unlock, &mtx));

  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(t.joinable());
  t.cancel();
  t.join();
  EXPECT_FALSE(t.completed());
  EXPECT_TRUE(t.canceled());

  EXPECT_FALSE(destructor_invoked[1]);
  EXPECT_FALSE(destructor_invoked[0]);
  EXPECT_FALSE(reached);

  if (mtx.try_lock()) {
    mtx.unlock();
  } else {
    EXPECT_TRUE(false);
  }
}

void cancel_test_fn() {
  std::cout << "cancelable_thread_test::cancelthread started\n";
  test_class t1(1, destructor_invoked[0]);
  test_class t2(2, destructor_invoked[1]);
  std::unique_lock<std::mutex> lk(mtx);

  if (SleepEx(50000, TRUE) == WAIT_IO_COMPLETION)
    throw ext::canceled_exception();

  reached = true;
  std::cout << "cancelable_thread_test::cancelthread stopped\n";
}

TEST(cancelable_thread_test, cancel) {
  reached = false;
  ext::cancelable_thread t(cancel_test_fn);
  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(t.joinable());
  t.cancel();
  t.join();
  EXPECT_FALSE(t.completed());
  EXPECT_TRUE(t.canceled());
  EXPECT_FALSE(reached);

  EXPECT_TRUE(destructor_invoked[0]);
  EXPECT_TRUE(destructor_invoked[1]);

  if (mtx.try_lock()) {
    mtx.unlock();
  } else {
    EXPECT_TRUE(false);
  }
}
#endif // !defined(__cpp_lambdas)
#endif