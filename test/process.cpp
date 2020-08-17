
#include <gtest/gtest.h>
#include <ext/process>

TEST(process_test, run_list_cwd_cmd)
{
#ifdef _WIN32
    ext::process process("cmd", { "/c", "dir", "/s", "."});
#else
    ext::process process("ls", { "-al", "."});
#endif
    process.join();
}