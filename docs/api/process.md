# process

[Back to API reference](README.md)

## Header

`#include <ext/process>`

## Overview

Starts a child command with optional arguments and working directory, exposes pipe streams for standard input/output/error, and tracks exit state. Tests cover invalid commands, working-directory execution, standard stream piping, and move semantics.

## Key APIs

- `ext::process(command, arguments, working_directory)` starts a child process.
- `joinable()` checks whether the child is still running and refreshes exit state when it has ended.
- `join()` waits for completion and closes pipe streams.
- `in()`, `out()`, and `err()` expose process stdin, stdout, and stderr streams.
- `get_id()`, `native_handle()`, `exit_code()`, and `last_error()` expose process metadata.
- `get_cmdline()`, `get_cwd()`, and `ext::this_process` helpers expose command-line and working-directory details.

## Behavior Notes

- The destructor calls `std::terminate()` if the process is still joinable, mirroring `std::thread`-style ownership rules.
- The class is move-only on modern compilers and supports `operator|` to connect stdout to the next process stdin.
- The implementation uses Windows process APIs on Windows and `fork`/`exec`/`waitpid`-style behavior on POSIX systems.

## Lifetime Contract

- Always call `join()` or move the process object before it is destroyed.
- Close `in()` when the child process expects EOF on stdin.
- Read `out()` and `err()` according to the child process behavior; a child that
  writes enough data to a pipe can block if the parent never drains it.
- `exit_code()` is meaningful after the process has finished and join state has
  been refreshed.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- stdout

  ```C++
  #include <ext/process>

  ext::process process("ls", {"-al", "."});
  std::cout << process.get_cmdline() << std::endl;
  std::cout << process.out().rdbuf() << std::endl;
  if (process.joinable())
    process.join();
  ```

- stdin

  ```C++
  #include <ext/process>

  ext::process process("more");
  process.in() << "test 1\n";
  process.in() << "test 2\ntest 3\n";
  process.in().close();
  std::cout << process.out().rdbuf() << std::endl;
  if (process.joinable())
    process.join();
  ```

- pipe (stdin, stdout)

  ```C++
  #include <ext/process>

  auto result = ext::process("ps", {"-ef"}) | ext::process("grep", {"root"}) |
                ext::process("grep", {"/usr"}) | ext::process("wc", {"-l"});

  result.get_cmdline(); // "ps -ef | grep root | grep /usr | wc -l"

  std::cout << "cmdline : " << result.get_cmdline() << std::endl;
  std::cout << "result :" << result.out().rdbuf() << std::endl;
  if (result.joinable())
    result.join();
  ```
