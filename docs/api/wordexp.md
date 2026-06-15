# wordexp

[Back to API reference](README.md)

## Header

`#include <ext/wordexp>`

Expands environment-variable strings and replaces them with the values defined for the current user.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

```C++
#if defined(_WIN32)
  std::string system_drive = ext::wordexp("%SYSTEMDRIVE%");
  std::string windir = ext::wordexp("%WINDIR%");
  std::string user_profile = ext::wordexp("%USERPROFILE%");
  std::string user_name = ext::wordexp("%USERNAME%");
#else
  std::string home_path = ext::wordexp("$HOME");
  std::string user = ext::wordexp("$USER");
#endif
```

---
