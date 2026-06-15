# pstream

[Back to API reference](README.md)

## Header

`#include <ext/pstream>`

## Overview

Wraps platform pipe/file handles in C++ stream buffers and stream types. It provides input and output stream aliases that `process` uses for child standard streams.

## Key APIs

- `ext::basic_pipebuf<CharT>` adapts a native pipe handle to a stream buffer.
- `ext::pstream<Mode, Stream>` owns a pipe buffer and stream facade.
- `ext::ipstream` is a binary input stream alias.
- `ext::opstream` is a binary output stream alias.

## Behavior Notes

- `native_handle()` exposes the underlying platform handle when direct integration is required.
- `detach()` transfers handle ownership on implementations that allocate the buffer dynamically.
- Call `close()` when the stream endpoint should be closed before object destruction.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

```C++
```
