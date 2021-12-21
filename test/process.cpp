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
  EXPECT_TRUE(process.joinable());
  EXPECT_STREQ(process.get_cmdline().c_str(), "cmd /c dir .");
#if defined(_MSC_VER) || _MSC_VER <= 1600
  std::stringstream ss;
  ss << process.out().rdbuf();
#endif
#else
  ext::process process("ls", {"-al", "."});
  EXPECT_TRUE(process.joinable());
  EXPECT_STREQ(process.get_cmdline().c_str(), "ls -al .");
#endif

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
  EXPECT_TRUE(process.joinable());
  EXPECT_STREQ(process.get_cwd().c_str(), systemDrive.c_str());
#if defined(_MSC_VER) || _MSC_VER <= 1600
  std::stringstream ss;
  ss << process.out().rdbuf();
#endif
#else
  ext::process process("ls", {"-al", "."}, "/");
  EXPECT_TRUE(process.joinable());
  EXPECT_STREQ(process.get_cwd().c_str(), "/");
#endif
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
  std::string cwd = ext::this_process::get_cwd();
  EXPECT_FALSE(cwd.empty());
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

// #include <fstream>
// TEST(process_test, process_pipe_operator_test4) {
//   ext::process curl("curl",
//   {"https://az764295.vo.msecnd.net/stable/e7d7e9a9348e6a8cc8c03f877d39cb72e5dfb1ff/VSCodeUserSetup-x64-1.60.0.exe"});
//   std::ofstream file("test.exe", std::ofstream::binary);
//   file << curl.out().rdbuf();
//   if (curl.joinable())
//     curl.join();
// }

// TEST(process_test, process_pipe_operator_test3) {
//   auto result = ext::process("curl", {"https://github.com"}) |
//   ext::process("grep div"); std::cout << result.out().rdbuf() << std::endl;
//   if (result.joinable())
//     result.join();
// }

#if defined(_WIN32)
#include <Win32Ex/System/Process.h>
#if !defined(__cpp_lambdas)
BOOL CreateProcessWrapper(_In_opt_ LPCSTR lpApplicationName,
                          _Inout_opt_ LPSTR lpCommandLine,
                          _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
                          _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
                          _In_ BOOL bInheritHandles, _In_ DWORD dwCreationFlags,
                          _In_opt_ LPVOID lpEnvironment,
                          _In_opt_ LPCSTR lpCurrentDirectory,
                          _In_ LPSTARTUPINFOA lpStartupInfo,
                          _Out_ LPPROCESS_INFORMATION lpProcessInformation) {
  return CreateSystemAccountProcess(
      WTSGetActiveConsoleSessionId(), lpApplicationName, lpCommandLine,
      lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags,
      lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}
#endif

TEST(process_test, system_process_test) {
  if (IsUserAdmin()) {
#if defined(__cpp_lambdas)
#ifdef __cpp_initializer_lists
    ext::process process(
        [](_In_opt_ LPCSTR lpApplicationName, _Inout_opt_ LPSTR lpCommandLine,
           _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
           _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
           _In_ BOOL bInheritHandles, _In_ DWORD dwCreationFlags,
           _In_opt_ LPVOID lpEnvironment, _In_opt_ LPCSTR lpCurrentDirectory,
           _In_ LPSTARTUPINFOA lpStartupInfo,
           _Out_ LPPROCESS_INFORMATION lpProcessInformation) -> BOOL {
          return CreateSystemAccountProcess(
              WTSGetActiveConsoleSessionId(), lpApplicationName, lpCommandLine,
              lpProcessAttributes, lpThreadAttributes, bInheritHandles,
              dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo,
              lpProcessInformation);
        },
        "cmd.exe", {"/c", "echo", "test-1-2-3"});
#else
    std::list<std::string> args;
    args.push_back("/c");
    args.push_back("echo");
    args.push_back("test-1-2-3");
    ext::process process(
        [](_In_opt_ LPCSTR lpApplicationName, _Inout_opt_ LPSTR lpCommandLine,
           _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
           _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
           _In_ BOOL bInheritHandles, _In_ DWORD dwCreationFlags,
           _In_opt_ LPVOID lpEnvironment, _In_opt_ LPCSTR lpCurrentDirectory,
           _In_ LPSTARTUPINFOA lpStartupInfo,
           _Out_ LPPROCESS_INFORMATION lpProcessInformation) -> BOOL {
          return CreateSystemAccountProcess(
              WTSGetActiveConsoleSessionId(), lpApplicationName, lpCommandLine,
              lpProcessAttributes, lpThreadAttributes, bInheritHandles,
              dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo,
              lpProcessInformation);
        },
        "cmd.exe", args);
#endif
#else
    std::list<std::string> args;
    args.push_back("/c");
    args.push_back("echo");
    args.push_back("test-1-2-3");
    ext::process process(CreateProcessWrapper, "cmd.exe", args);
#endif
    EXPECT_TRUE(process.joinable());
    process.join();
  }
}
#else
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <sstream>
#include <thread>

#include <ext/string>

TEST(process_test, process_stdout_test) {
  ext::process process("find", {"/", "-name", "*.service"});
  std::condition_variable cv;
  std::mutex mtx;

  std::thread stdout_thread([&process] {
    ext::process wc("wc", {"-l"});

    std::stringstream ss;
    ss << process.out().rdbuf();
    std::cout
        << "----------------------------------------------------------------\n"
        << ss.str() << '\n'
        << "exit code (" << process.exit_code() << ")\n"
        << "---------------------------------------------------------------"
           "-"
        << std::endl;

    try {
      wc.in() << ss.str();
      wc.in().close();
      std::cout << wc.out().rdbuf();
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
    if (wc.joinable())
      wc.join();
  });
  std::atomic_bool killed = false;
  std::thread delayed_kill_thread([&killed, &mtx, &cv, &process] {
    std::unique_lock lk(mtx);
    cv.wait_for(lk, std::chrono::seconds(1));
    if (process.joinable()) {
      killed = true;
      process.kill();
    }
  });

  EXPECT_TRUE(process.joinable());
  process.join();
  cv.notify_all();

  if (!killed) {
#if !defined(_MSC_VER)
    // :-( EXIT_FAILURE returned on Windows OS (MSYS).
    auto str = getenv("MSYSTEM");
    if ((str == NULL) || std::string(str) != "MSYS")
#endif
      EXPECT_EQ(process.exit_code(), EXIT_SUCCESS);
  }

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