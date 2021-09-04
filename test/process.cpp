#include <ext/process>

#ifdef _EXT_PROCESS_
#define GTEST_HAS_TR1_TUPLE 0
#include <ext/path>
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

TEST(process_test, process_stdout_basic_test) {
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
  std::cout << process.get_cmdline() << std::endl;
  std::cout << process.out().rdbuf() << std::endl;
  if (process.joinable())
    process.join();
}

TEST(process_test, process_stdin_basic_test) {
#if defined(_WIN32)
#ifdef __cpp_initializer_lists
  ext::process process("cmd", {"/c", "more"});
#else
  std::list<std::string> args;
  args.push_back("/c");
  args.push_back("more");
  ext::process process("cmd", args);
#endif // __cpp_initializer_lists
#else
  ext::process process("more");
#endif
  process.in() << "test 1\n";
  process.in() << "test 2\ntest 3\n";
  process.in().close();
  std::cout << process.out().rdbuf() << std::endl;
  if (process.joinable())
    process.join();
}

TEST(process_test, process_pipe_operator_test) {
#if defined(_WIN32)
#ifdef __cpp_initializer_lists
  auto result = ext::process("cmd", {"/c", "echo", "test-1-2-3"}) |
                ext::process("cmd", {"/c", "more"});
#else
  std::list<std::string> args;
  args.push_back("/c");
  args.push_back("echo");
  args.push_back("test-1-2-3");

  std::list<std::string> args2;
  args2.push_back("/c");
  args2.push_back("more");
  ext::process result = ext::process("cmd", args) | ext::process("cmd", args2);
#endif // __cpp_initializer_lists
#else
  auto result = ext::process("echo", {"test-1-2-3"}) | ext::process("more");
#endif
  std::cout << result.out().rdbuf() << std::endl;
  if (result.joinable())
    result.join();
}

#if !defined(_WIN32)
#include <condition_variable>
#include <mutex>

TEST(process_test, process_stdout_test) {
  ext::process process("find", {"/", "-name", "*.service"});
  std::condition_variable cv;
  std::mutex mtx;

  std::thread stdout_thread([&process] {
    ext::process wc("wc", {"-l"});
    wc.in() << process.out().rdbuf();
    wc.in().close();
    std::cout << wc.out().rdbuf();
    if (wc.joinable())
      wc.join();
  });

  std::thread delayed_kill_thread([&mtx, &cv, &process] {
    std::unique_lock lk(mtx);
    cv.wait_for(lk, std::chrono::seconds(1));
    if (process.joinable())
      process.kill();
  });

  EXPECT_TRUE(process.joinable());
  process.join();
  cv.notify_all();
  EXPECT_EQ(process.exit_code(), EXIT_SUCCESS);

  if (stdout_thread.joinable())
    stdout_thread.join();
  if (delayed_kill_thread.joinable())
    delayed_kill_thread.join();
}

TEST(process_test, process_stdin_test) {
  ext::process whoami("whoami");
  std::string name((std::istreambuf_iterator<char>(whoami.out().rdbuf())),
                   std::istreambuf_iterator<char>());
  if (whoami.joinable())
    whoami.join();
  std::cout << "whoami : " << name << std::endl;
  ext::process ps("ps", {"-ef"});
  ext::process grep("grep", {name});
  std::condition_variable cv;
  std::mutex mtx;

  std::thread stdout_thread([&ps, &grep] {
    std::stringstream ss;
    ss << "----------------------------------------------------------------\n"
       << grep.out().rdbuf()
       << "---------------------------------------------------------------"
          "-\n";
    auto s = ss.str();
    std::cout << ((s.size() > 200) ? s.substr(0, 200) : s) << '\n';
  });

  std::thread delayed_kill_thread([&mtx, &cv, &ps, &grep] {
    std::unique_lock lk(mtx);
    cv.wait_for(lk, std::chrono::seconds(10));
    if (grep.joinable())
      grep.kill();
    if (ps.joinable())
      ps.kill();
  });

  grep.in() << ps.out().rdbuf();
  if (ps.joinable())
    ps.join();
  grep.in().close();

  EXPECT_TRUE(grep.joinable());
  grep.join();
  EXPECT_EQ(grep.exit_code(), EXIT_SUCCESS);

  cv.notify_all();

  if (stdout_thread.joinable())
    stdout_thread.join();
  if (delayed_kill_thread.joinable())
    delayed_kill_thread.join();
}

TEST(process_test, process_pipe_operator_test2) {
  auto result = ext::process("ps", {"-ef"}) | ext::process("grep", {"root"}) |
                ext::process("grep", {"/usr"}) | ext::process("wc", {"-l"});
  EXPECT_STREQ("ps -ef | grep root | grep /usr | wc -l",
               result.get_cmdline().c_str());
  std::cout << "cmdline : " << result.get_cmdline() << std::endl;
  std::cout << "result :" << result.out().rdbuf() << std::endl;
  if (result.joinable())
    result.join();
}
#endif
#endif
