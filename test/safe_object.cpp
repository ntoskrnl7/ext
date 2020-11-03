#include <thread>

#include <ext/cdbg>
#include <ext/safe_object>
#include <ext/shared_recursive_mutex>
#include <gtest/gtest.h>

#ifdef _EXT_SAFE_OBJECT_
class test_object {
public:
  int value;
};

test_object obj;
ext::shared_recursive_mutex mtx;

#define obj_rw get_object_safety(obj, mtx, false)
#define obj_r get_object_safety(obj, mtx, true)

TEST(safe_object_test, safe_object) {
  EXPECT_TRUE((std::is_same<test_object &, decltype(obj_rw)>::value));
  obj_rw.value = 10;
  int value = obj_rw.value;

  EXPECT_TRUE((std::is_same<const test_object &, decltype(obj_r)>::value));
  // obj_r.value = 10;
  value = obj_r.value;

  EXPECT_EQ(value, obj_rw.value);

  obj_rw.value = 20;
  EXPECT_EQ(obj_rw.value, obj_r.value);
}

#define obj_t mutex_trace_data_type(obj, mtx)::instance()
#define obj_t_rw (get_object_safety_with_trace(obj, mtx, false, ext::cdbg))
#define obj_t_r (get_object_safety_with_trace(obj, mtx, true, ext::cdbg))

TEST(safe_object_test, safe_object_with_trace) {
  obj_t.enabled = true;
  EXPECT_TRUE((std::is_same<test_object &, decltype(obj_t_rw)>::value));
  obj_t_rw.value = 10;
  int value = obj_t_rw.value;

  EXPECT_TRUE((std::is_same<const test_object &, decltype(obj_t_r)>::value));
  // obj_r.value = 10;
  value = obj_t_r.value;

  EXPECT_EQ(value, obj_t_rw.value);

  obj_t_rw.value = 20;
  EXPECT_EQ(obj_t_rw.value, obj_t_r.value);
}

TEST(safe_object_test, safe_object_both) {
  obj_t.enabled = true;
  EXPECT_TRUE((std::is_same<test_object &, decltype(obj_rw)>::value));
  EXPECT_TRUE((std::is_same<test_object &, decltype(obj_t_rw)>::value));
  obj_t_rw.value = 10;
  int value = obj_t_rw.value;

  EXPECT_EQ(value, obj_t_rw.value);
  EXPECT_EQ(value, obj_rw.value);

  EXPECT_TRUE((std::is_same<const test_object &, decltype(obj_r)>::value));
  EXPECT_TRUE((std::is_same<const test_object &, decltype(obj_t_r)>::value));
  // obj_r.value = 10;
  value = obj_t_r.value;

  EXPECT_EQ(value, obj_t_r.value);
  EXPECT_EQ(value, obj_r.value);

  EXPECT_EQ(value, obj_t_rw.value);

  obj_t_rw.value = 20;
  EXPECT_EQ(obj_t_rw.value, obj_t_r.value);
  EXPECT_EQ(obj_t_rw.value, obj_t_rw.value);
  EXPECT_EQ(obj_t_rw.value, obj_rw.value);
}
#endif // _EXT_SAFE_OBJECT_