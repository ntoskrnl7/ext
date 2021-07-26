#include <ext/path>
#include <ext/process>

#define GTEST_HAS_TR1_TUPLE 0
#include <gtest/gtest.h>

TEST(process_test, run_invalid_cmd) {
  ext::process process("_invalid_");
#if defined(_WIN32)
  EXPECT_EQ(process.last_error(), ERROR_FILE_NOT_FOUND);
  EXPECT_FALSE(process.joinable());
#else
  if (process.joinable())
    process.join();
#endif
}

TEST(process_test, run_list_working_directory_cmd) {
#if defined(_WIN32)
#ifdef __cpp_initializer_lists
  ext::process process("cmd", {"/c", "dir", "."});
#else
  std::list<std::string> args;
  args.push_back("/c");
  args.push_back("dir");
  args.push_back(".");
  ext::process process("cmd", args);
#endif // __cpp_initializer_lists
#else
  ext::process process("ls", {"-al", "."});
#endif
  EXPECT_TRUE(process.joinable());
  process.join();
  EXPECT_EQ(process.exit_code(), EXIT_SUCCESS);
}

TEST(process_test,
     run_list_working_directory_cmd_with_working_directory_set_to_root) {
#if defined(_WIN32)
  std::string systemDrive;
  size_t requiredCount = sizeof("C:");
  systemDrive.resize(requiredCount);
  errno_t err =
      getenv_s(&requiredCount, &systemDrive[0], requiredCount, "SystemDrive");
  if (err == ERANGE) {
    puts(std::to_string((long long)requiredCount).c_str());
    systemDrive.resize(requiredCount);
    err =
        getenv_s(&requiredCount, &systemDrive[0], requiredCount, "SystemDrive");
  }
  EXPECT_EQ(err, 0);
#ifdef __cpp_initializer_lists
  ext::process process("cmd", {"/c", "dir", "."}, systemDrive.c_str());
#else
  std::list<std::string> args;
  args.push_back("/c");
  args.push_back("dir");
  args.push_back(".");
  ext::process process("cmd", args, systemDrive.c_str());
#endif // __cpp_initializer_lists
#else
  ext::process process("ls", {"-al", "."}, "/");
#endif
  EXPECT_TRUE(process.joinable());
  process.join();
  EXPECT_EQ(process.exit_code(), EXIT_SUCCESS);
}

TEST(process_test, this_process_test) {
  ext::process::id pid = ext::this_process::get_id();
#if defined(_WIN32)
  EXPECT_EQ(pid, ext::process::id(GetCurrentProcessId()));
#else
  EXPECT_EQ(pid, ext::process::id(getpid()));
#endif
  std::string cmdline = ext::this_process::get_cmdline();
  EXPECT_FALSE(cmdline.empty());
  std::string name = ext::path::basename(cmdline);
#if defined(_WIN32)
  EXPECT_STREQ(name.c_str(), "unittest.exe");
#else
  EXPECT_STREQ(name.c_str(), "unittest");
#endif
}