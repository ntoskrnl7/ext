# process

[Back to API reference](README.md)

## Header

`#include <ext/process>`

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
