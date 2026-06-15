# observable

[Back to API reference](README.md)

## Header

`#include <ext/observable>`

## Overview

Provides an `observable<Self, Args...>` base and nested `observer` type. Derived classes call protected `notify(args...)`; observers implement `update(Self&, Args...)` and subscribe with operators or member functions.

## Key APIs

- `observable<Self, Args...>::observer` is the base class for subscribers.
- `observer::subscribe`, `unsubscribe`, `operator+=`, and `operator-=` manage subscriptions.
- `observable::notify(args...)` calls every subscribed observer.
- `observable::push(other)` forwards current observers to another observable.

## Behavior Notes

- The destructor paths remove cross-references to avoid stale observer links.
- When supported, a shared global mutex protects subscription and notification lists.
- Use it for object-to-observer relationships; use `callback` for a simpler multicast callable list.

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+ with **Boost 1.69.0+**
- Visual Studio 2017+
- **std::shared_mutex or std::shared_timed_mutex required**

## Examples

```C++
#include <ext/observable>

class document : public ext::observable<document, int> {
public:
  void set_revision(int revision) {
    revision_ = revision;
    notify(revision_);
  }

private:
  int revision_ = 0;
};

class revision_observer : public document::observer {
public:
  int last_revision = 0;

private:
  void update(document &, int revision) override {
    last_revision = revision;
  }
};

document doc;
revision_observer observer;

observer += doc;
doc.set_revision(3);
// observer.last_revision == 3
```
