# base64

[Back to API reference](README.md)

## Header

`#include <ext/base64>`

## Overview

Implements RFC 2045-style Base64 conversion helpers. The API accepts narrow or wide encoded text and can decode into strings, byte vectors, caller-provided objects, or `std::shared_ptr<T>` results.

## Key APIs

- `ext::base64::encode(value)` encodes strings, wide strings, byte vectors, or object bytes.
- `ext::base64::decode(encoded)` returns decoded bytes as `std::vector<std::byte>`.
- `ext::base64::decode_str<T>(encoded)` converts decoded bytes into a `std::basic_string<T>`.
- `ext::base64::decode(encoded, object)` and `decode_shared_ptr<T>` decode bytes into typed storage.

## Behavior Notes

- The text character type can be selected with template arguments such as `encode<wchar_t>(...)`.
- Object decoding treats the object as raw bytes; it is intended for simple binary-compatible data layouts.
- The tests include RFC 2045 sample text and long narrow/wide payloads.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- string

    ```C++
    #include <ext/base64>

    // std::string <--> base64(std::string).
    std::string encoded = ext::base64::encode("1234");
    std::string decoded = ext::base64::decode_str(encoded); // "1234"
    std::vector<std::byte> decoded_vec = ext::base64::decode(encoded); // '1', '2', '3', '4

    // std::string <--> base64(std::wstring).
    std::wstring encoded_w = ext::base64::encode<wchar_t>("1234");
    decoded = ext::base64::decode_str(encoded_w);
    decoded_vec = ext::base64::decode(encoded_w);
    ```

- wstring

    ```C++
    #include <ext/base64>

    // std::wstring <--> base64(std::string).
    std::string encoded = ext::base64::encode(L"1234");
    std::wstring decoded = ext::base64::decode_str<wchar_t>(encoded); // L"1234"
    std::vector<std::byte> decoded_vec = ext::base64::decode(encoded); // L'1', L'2', L'3', L'4

    // std::wstring <--> base64(std::wstring).
    std::wstring encoded_w = ext::base64::encode<wchar_t>(L"1234");
    decoded = ext::base64::decode_str<wchar_t>(encoded_w); // L"1234"
    decoded_vec = ext::base64::decode(encoded_w); // L'1', L'2', L'3', L'4
    ```

- std::vector\<std::byte\>

    ```C++
    #include <ext/base64>

    // std::vector<std::byte> <--> base64(std::string).
    std::vector<std::byte> vec = {(std::byte)'1', (std::byte)'2',
                                (std::byte)'3', (std::byte)'4'};
    std::string encoded = ext::base64::encode(vec);
    std::vector<std::byte> decoded = ext::base64::decode(encoded); // '1', '2', '3', '4
    std::string decoded_str = ext::base64::decode_str(encoded); // "1234"

    // std::vector<std::byte> <--> base64(std::wstring).
    std::wstring encoded_w = ext::base64::encode<wchar_t>(vec);
    decoded = ext::base64::decode(encoded_w); // '1', '2', '3', '4
    decoded_str = ext::base64::decode_str(encoded_w); // "1234"
    ```

- structure

    ```C++
    #include <ext/base64>

    struct test {
        char a;
        char b;
        char c;
        char d;
    };

    test data = {'1', '2', '3', '4'};
    std::string encoded = ext::base64::encode(data);
    test decoded;
    ext::base64::decode(encoded, decoded); // a='1', b='2', c='3', d='4'
    std::shared_ptr<test> decoded_ptr =
        ext::base64::decode_shared_ptr<test>(encoded);  // a='1', b='2', c='3', d='4'
    std::string decoded_str = ext::base64::decode_str(encoded); // "1234"

    std::wstring encoded_w = ext::base64::encode<wchar_t>(data);
    decoded = {
        0,
    };
    ext::base64::decode(encoded_w, decoded); // a='1', b='2', c='3', d='4'
    decoded_ptr = ext::base64::decode_shared_ptr<test>(encoded_w); // a='1', b='2', c='3', d='4'
    decoded_str = ext::base64::decode_str(encoded_w); // "1234"
    ```
