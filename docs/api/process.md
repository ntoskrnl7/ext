# process

[Back to API reference](README.md)

## Header

`#include <ext/process>`

## Overview

Starts a child command with optional arguments and working directory, exposes pipe streams for standard input/output/error, and tracks exit state. Tests cover invalid commands, working-directory execution, standard stream piping, and move semantics.

## Key APIs

- `ext::process()` creates a non-running process object.
- `ext::process(command, arguments, working_directory)` starts a child process.
- On old Windows builds without the variadic expansion path, an overload accepts
  a custom `CreateProcessA`-compatible function for tests or custom launch
  behavior.
- `joinable()` checks whether the child is still running and refreshes exit
  state when it has ended.
- `join()` waits for completion and closes pipe streams.
- `detach()` releases process ownership. On POSIX it starts a detached waiter to
  reap the child.
- `kill()` terminates the child with `TerminateProcess` on Windows or
  `SIGKILL` on POSIX.
- `in()`, `out()`, and `err()` expose process stdin, stdout, and stderr streams.
- `get_id()`, `native_handle()`, `exit_code()`, and `last_error()` expose process metadata.
- `get_cmdline()` returns the command plus arguments assembled by this wrapper.
- `get_cwd()` returns the working directory requested for this child.
- `operator|` connects stdout from one process into stdin of the next process
  and returns the right-hand process as the pipeline result.
- `ext::this_process::get_id()`, `get_cmdline()`, and `get_cwd()` expose
  information about the current process.

## Behavior Notes

- The destructor calls `std::terminate()` if the process is still joinable, mirroring `std::thread`-style ownership rules.
- The class is move-only on modern compilers and supports `operator|` to connect stdout to the next process stdin.
- The implementation uses Windows process APIs on Windows and `fork`/`exec`/`waitpid`-style behavior on POSIX systems.
- Constructor launch failures are reflected through `last_error()`. Calling
  `in()`, `out()`, or `err()` after a launch failure throws `std::runtime_error`.
- `joinable()` is not only a query: it may observe child completion, close pipe
  streams, update `exit_code()`, and mark the object non-joinable.
- `exit_code()` defaults to success before a child is launched or observed.
  Read it after `join()` or after `joinable()` has refreshed a completed child.
- `kill()` only requests termination. Call `join()` afterward if this object
  still owns the child.
- Pipeline support is eager: `rhs.in() << lhs.out().rdbuf()` copies stdout in
  the parent process, closes the right-hand stdin, detaches the left-hand
  process, and returns the right-hand process.

## Lifetime Contract

- Always call `join()` or move the process object before it is destroyed.
- Close `in()` when the child process expects EOF on stdin.
- Read `out()` and `err()` according to the child process behavior; a child that
  writes enough data to a pipe can block if the parent never drains it.
- `exit_code()` is meaningful after the process has finished and join state has
  been refreshed.
- Do not ignore a live `ext::process` object. Join, detach, kill-and-join, or
  move it before destruction.

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

- current process

  ```C++
  #include <ext/process>

  ext::process::id pid = ext::this_process::get_id();
  std::string executable = ext::this_process::get_cmdline();
  std::string cwd = ext::this_process::get_cwd();
  ```

- kill and join

  ```C++
  #include <ext/process>

  ext::process process("sleep", {"30"});
  process.kill();
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
