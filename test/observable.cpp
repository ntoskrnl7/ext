#include <gtest/gtest.h>

#if CXX_USE_BOOST
#define CXX_USE_STD_MAKE_UNIQUE
#include <boost/move/unique_ptr.hpp>

#define CXX_USE_STD_CHRONO
#include <boost/chrono.hpp>

#define CXX_USE_STD_THREAD
#include <boost/thread.hpp>

#define CXX_USE_STD_CONDITION_VARIABLE
#include <boost/thread/condition_variable.hpp>

#define CXX_USE_STD_MUTEX
#include <boost/thread/mutex.hpp>
#endif

#define CXX_USE_STD_MOVE
#define CXX_USE_NULLPTR
#include <ext/observable>
#include <ext/shared_recursive_mutex>

#if !defined(_EXT_STD_CHRONO_) && !defined(CXX_STD_CHRONO_NOT_SUPPORTED)
#include <chrono>
#endif
#if !defined(_EXT_STD_THREAD_) && !defined(CXX_STD_THREAD_NOT_SUPPORTED)
#include <thread>
#endif
#if !defined(_EXT_STD_CONDITION_VARIABLE_) &&                                  \
    !defined(CXX_STD_CONDITION_VARIABLE_NOT_SUPPORTED)
#include <condition_variable>
#endif
#if !defined(_EXT_STD_MUTEX_) && !defined(CXX_STD_MUTEX_NOT_SUPPORTED)
#include <mutex>
#endif
#include <ext/stl_compat>

#include <iostream>

class object_with_name {
public:
  object_with_name(const std::string &name) : name_(name) {}
  const std::string &name() const { return name_; }

private:
  std::string name_;
};

#ifdef __cpp_variadic_templates
using observable_no_args =
    ext::observable<class object_with_observable_no_args>;

class object_with_observable_no_args : public object_with_name,
                                       public observable_no_args {
public:
  object_with_observable_no_args(const std::string &name)
      : observable_no_args(), object_with_name(name) {}

public:
  void test() { notify(); }
};

class observer_no_args : public object_with_name,
                         public object_with_observable_no_args::observer {
public:
  observer_no_args(const std::string &name)
      : observer(), object_with_name(name) {}

private:
  void update(object_with_observable_no_args &item) {
    std::cout << "[" << name() << "] " << item.name() << " "
              << "updated\n";
  }
};

TEST(observable_test, observer_no_args) {
  object_with_observable_no_args obj("obj");
  object_with_observable_no_args obj_1("obj_1");
  object_with_observable_no_args obj_2("obj_2");

  observer_no_args obsvr("obsvr_no_args");
  observer_no_args obsvr_1("obsvr_no_args_1");
  observer_no_args obsvr_2("obsvr_no_args_2");

  obsvr += obj;
  obsvr_1 += obj;
  obsvr_2 += obj;

  obsvr += obj_1;
  obsvr_1 += obj_1;
  obsvr_2 += obj_1;

  obsvr += obj_2;
  obsvr_1 += obj_2;
  obsvr_2 += obj_2;

  obj.test();
  obj_1.test();
  obj_2.test();
}
#endif

typedef ext::observable<class object_with_observable_one_arg, int>
    observable_one_arg;

class object_with_observable_one_arg : public object_with_name,
                                       public observable_one_arg {
public:
  object_with_observable_one_arg(const std::string &name)
      : observable_one_arg(), object_with_name(name) {}

public:
  void test(int arg) { notify(arg); }
};

class observer_with_one_arg : public object_with_name,
                              public object_with_observable_one_arg::observer {
public:
  observer_with_one_arg(const std::string name)
      : observer(), object_with_name(name) {}

private:
  void update(object_with_observable_one_arg &item, int arg) {
    if (arg < 0)
      return;
    std::cout << "[" << name() << "] " << item.name() << " "
              << "value(" << arg << ") "
              << "updated\n";
  }
};

TEST(observable_test, observer_with_one_arg) {
  observer_with_one_arg obsvr("obsvr_one_arg");
  observer_with_one_arg obsvr_1("obsvr_one_arg_1");
  observer_with_one_arg obsvr_2("obsvr_one_arg_2");

  object_with_observable_one_arg obj("obj_one_arg");
  object_with_observable_one_arg obj_1("obj_one_arg_1");
  object_with_observable_one_arg obj_2("obj_one_arg_2");
#if defined(__cpp_lambdas) && defined(OBSERVABLE_WITH_LOCK)
  std::mutex mtx;
  std::condition_variable cv;

  bool running = true;
  bool ready = false;

  std::thread t([&]() {
    ready = true;
    cv.notify_all();

    while (running) {
      object_with_observable_one_arg obj_t("obj_one_arg_thread");
      obsvr += obj_t;
      obsvr_1 += obj_t;
      obsvr_2 += obj_t;

      obj_t.test(100);
      obj.test(-100);
      obj_1.test(-200);
      obj_2.test(-300);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });
  {
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, [&]() { return ready; });
  }
#endif
  obsvr += obj;
  obsvr_1 += obj;
  obsvr_2 += obj;

  obsvr += obj_1;
  obsvr_1 += obj_1;
  obsvr_2 += obj_1;

  obsvr += obj_2;
  obsvr_1 += obj_2;
  obsvr_2 += obj_2;

  obj.test(1);
  obj_1.test(2);
  obj_2.test(3);

  obsvr -= obj;
  obsvr -= obj_1;
  obsvr -= obj_2;

  obj.test(4);
  obj_1.test(5);
  obj_2.test(6);

  obsvr_1.unsubscribe();

  obj.test(7);
  obj_1.test(8);
  obj_2.test(9);

  std::cout << "begin obj_one_arg_ptr\n";
  std::unique_ptr<object_with_observable_one_arg> obj_ptr =
      std::make_unique<object_with_observable_one_arg>(
          std::string("obj_one_arg_ptr"));
  obsvr += *obj_ptr;
  obsvr_1 += *obj_ptr;
  obsvr_2 += *obj_ptr;
  obj_ptr->test(10);
  obj_ptr = nullptr;
  std::cout << "end obj_one_arg_ptr test\n";

  std::cout << "begin obsvr_one_arg_ptr test\n";
  std::unique_ptr<observer_with_one_arg> obsvr_ptr =
      std::make_unique<observer_with_one_arg>(std::string("obsvr_one_arg_ptr"));
  *obsvr_ptr += obj;
  *obsvr_ptr += obj_1;
  *obsvr_ptr += obj_2;

  obj.test(11);
  obj_1.test(12);
  obj_2.test(13);

  obsvr_ptr = nullptr;
  std::cout << "end obsvr_one_arg_ptr test\n";

  obj.test(14);
  obj_1.test(15);
  obj_2.test(16);

#if defined(__cpp_lambdas) && defined(OBSERVABLE_WITH_LOCK)
  running = false;
  if (t.joinable())
    t.join();
#endif
}

#ifdef __cpp_variadic_templates
using observable_two_args =
    ext::observable<class object_with_observable_two_args, int,
                    const std::string &>;

class object_with_observable_two_args : public object_with_name,
                                        public observable_two_args {
public:
  object_with_observable_two_args(const std::string &name)
      : observable_two_args(), object_with_name(name) {}

public:
  void test(int arg) { notify(arg, std::to_string(arg + 100)); }
};

class observer_with_two_args
    : public object_with_name,
      public object_with_observable_two_args::observer {
public:
  observer_with_two_args(const std::string name)
      : observer(), object_with_name(name) {}

private:
  void update(object_with_observable_two_args &item, int arg0,
              const std::string &arg1) {
    if (arg0 < 0)
      return;
    std::cout << "[" << name() << "] " << item.name() << " "
              << "value(arg0 - " << arg0 << ": arg1 - \"" << arg1 << "\") "
              << "updated\n";
  }
};

TEST(observable_test, observer_with_two_args) {
  observer_with_two_args obsvr("obsvr_two_args");
  observer_with_two_args obsvr_1("obsvr_two_args_1");

  object_with_observable_two_args obj("obj_one_arg");
  object_with_observable_two_args obj_1("obj_one_arg_1");
  object_with_observable_two_args obj_2("obj_one_arg_2");

  obsvr += obj;
  obsvr_1 += obj;

  obj.test(100);
}

class object_with_observable_no_args_base
    : public object_with_name,
      public ext::observable<object_with_observable_no_args_base> {
  using object_with_name::object_with_name;
};

class object_with_observable_no_args_x
    : public object_with_name,
      public ext::observable<object_with_observable_no_args_base> {
  using object_with_name::object_with_name;

public:
  void call() { notify(); }
};

class object_with_observable_no_args_y
    : public object_with_name,
      public ext::observable<object_with_observable_no_args_base> {
  using object_with_name::object_with_name;

public:
  void notify() { notify(); }
};

class object_with_observable_no_args_
    : public object_with_name,
      public ext::observable<object_with_observable_no_args> {
  using object_with_name::object_with_name;

public:
  void signal() { notify(); }
};

class object_with_observable_no_args_2
    : public object_with_name,
      public ext::observable<object_with_observable_no_args_2> {
  using object_with_name::object_with_name;

public:
  void test() { notify(); }
};

class observer_no_args_ : public object_with_name,
                          public object_with_observable_no_args::observer {
  using object_with_name::object_with_name;

  void update(object_with_observable_no_args &item) {
    std::cout << "[" << name() << "] " << item.name() << " "
              << "updated\n";
  }
};

TEST(observable_test, observer_no_args_complex) {

  observer_no_args obsvr("obsvr_no_args");
  observer_no_args obsvr2("obsvr_no_args-2");
  observer_no_args_ obsvr_2("obsvr_no_args_");

  object_with_observable_no_args_ obj_("obj_");
  object_with_observable_no_args obj("obj");
  object_with_observable_no_args obj2("obj-2");
  object_with_observable_no_args_2 obj_2("obj_2");
  object_with_observable_no_args_x obj_x("obj_x");

  obsvr += obj_;

  obsvr2 += obj_;
  obsvr_2 += obj_;
  obj_.signal();

  // obsvr += obj_2;

  obsvr_2 += obj2;

  obsvr += obj;
  obsvr2 += obj;
  obj.test();

  obsvr += obj2;

  obj.test();
  obj2.test();

  obsvr -= obj;
  obj.test();

  obsvr += obj_;
  obsvr += obj;
  obsvr += obj2;
  // obsvr += obj_2;
  obj_.signal();
  obj.test();
  obj2.test();
}
#endif