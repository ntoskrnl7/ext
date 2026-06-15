# ini

[Back to API reference](README.md)

## Header

`#include <ext/ini>`

## Overview

Reads section/key/value pairs from streams and lets callers inspect, mutate, erase, and serialize INI data. Tests cover string streams, files, output streams, and erase behavior.

## Key APIs

- `ext::ini` stores data as sections containing name/value string pairs.
- `contains(section)` and `contains(section, name)` test for existing entries.
- `operator[](section)` exposes the section map for reading or assignment.
- `erase(section)` and `erase(section, name)` remove data, and stream insertion serializes it.

## Behavior Notes

- The parser recognizes bracketed sections and simple `name=value` entries.
- All stored values are strings; callers convert typed values themselves.
- Ordering follows the underlying `std::map` ordering.

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
