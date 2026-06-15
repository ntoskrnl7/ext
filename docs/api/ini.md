# ini

[Back to API reference](README.md)

## Header

`#include <ext/ini>`

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2010+
- **std::regex** required

## Examples

- Create an ini file from a string.

    ```C++
    #include <ext/ini>

    std::istringstream ss("[TEST]\nX=10\nY=20\n[TEST1]\nZ=30");
    ext::ini ini(ss);
    // ini["TEST"]["X"] ==  "10"
    // ini["TEST"]["Y"] == "20"
    // ini["TEST1"]["Z"] == "30"
    std::ofstream ofs("sample.ini");
    ofs << ini;
    ```

- ini file (sample.ini)

    ```INI
    [TEST]
    X=10
    Y=20
    [TEST1]
    Z=30
    ```

- Load ini from file.

    ```C++
    #include <ext/ini>

    ext::ini ini(std::ifstream("sample.ini"));
    // ini["TEST"]["X"] ==  "10"
    // ini["TEST"]["Y"] == "20"
    // ini["TEST1"]["Z"] == "30"
    ```

- Edit the ini file.

    ```C++
    #include <ext/ini>

    ext::ini ini(std::ifstream("sample.ini"));
    // ini["TEST"]["X"] ==  "10"
    // ini["TEST"]["Y"] == "20"
    // ini["TEST1"]["Z"] == "30"

    ini["TEST"].erase("X");
    // ini["TEST"].find("X") == ini["TEST"].end()

    ini.erase("TEST1");
    // ini.contains("TEST1") == false

    std::ofstream ofs("output.ini");
    ofs << ini;
    ```

- ini file (output.ini)

    ```INI
    [TEST]
    Y=20
    ```
