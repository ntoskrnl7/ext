#include <ext/shared_mem>
#include <gtest/gtest.h>

struct memory_struct0 {
  int i;
  int j;
};

TEST(shared_mem_test, create_open_compare) {
  ext::shared_mem<memory_struct0> st_mem("memory_struct0",
                                         shared_mem_all_access);
  if (st_mem.opened()) {
    st_mem.destroy();
    st_mem.create();
  }
  EXPECT_TRUE(st_mem.created());
  st_mem->i = 10;
  st_mem->j = 20;

  ext::shared_mem<memory_struct0> st_mem2("memory_struct0");
  EXPECT_EQ(st_mem->i, st_mem2->i);
  EXPECT_EQ(st_mem->j, st_mem2->j);

  st_mem->i = 1;
  st_mem->j = 2;
  EXPECT_EQ(st_mem->i, st_mem2->i);
  EXPECT_EQ(st_mem->j, st_mem2->j);

  ext::shared_mem_base mem("memory_struct0");
  EXPECT_TRUE(mem.open());
  memory_struct0 *buffer = (memory_struct0 *)mem.map(0, sizeof(memory_struct0));
  EXPECT_NE(buffer, (memory_struct0 *)nullptr);

  st_mem->i = 100;
  st_mem->j = 200;
  EXPECT_EQ(st_mem->i, st_mem2->i);
  EXPECT_EQ(st_mem->j, st_mem2->j);
  EXPECT_EQ(st_mem->i, buffer->i);
  EXPECT_EQ(st_mem->j, buffer->j);

  EXPECT_TRUE(mem.unmap(buffer, sizeof(memory_struct0)));

#if defined(_WIN32)
  // 관리자 권한이 있는 Windows 환경이라면 영구 전역 객체를 삭제합니다.
  if (IsUserAdmin())
    EXPECT_TRUE(st_mem.destroy());
#else
  // Linux나 macOS환경에서는 항상 영구 전역 객체로 생성되므로 삭제합니다.
  st_mem.destroy();
#endif
}

TEST(shared_mem_test, after_destory) {
  ext::shared_mem_base mem("memory_struct0");
  EXPECT_FALSE(mem.exists());
}