/**
 * @file debug_utils.h
 * @author Jung-kang Lee (ntoskrnl7@gmail.com)
 * @brief This module implements debug helper features.
 *
 * @copyright Copyright (c) 2020 C++ Extended template library Authors
 *
 */

#ifndef __EXT_DEBUG_UTIL_H__
#define __EXT_DEBUG_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define is_debugger_present() (IsDebuggerPresent() == TRUE)
#define breakpoint() DebugBreak()
#define msleep(msec) Sleep(msec)
#else
#include <csignal>
#include <errno.h>
#include <time.h>
#include <unistd.h>

static int _debugger_present = 0;
inline void _sigtrap_handler(int signum) {
  _debugger_present = 0;
  signal(SIGTRAP, SIG_DFL);
}

inline bool is_debugger_present() {
  if (_debugger_present == 0) {
    _debugger_present = 1;
    signal(SIGTRAP, _sigtrap_handler);
    raise(SIGTRAP);
  }
  return _debugger_present == 1;
}

#define breakpoint() std::raise(SIGINT)

inline int msleep(long msec) {
  struct timespec ts;
  int res;

  if (msec < 0) {
    errno = EINVAL;
    return -1;
  }

  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;

  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR);

  return res;
}
#endif

inline bool wait_for_debugger(unsigned long timeout) {
  const long duration = 100;
  timeout /= duration;
  for (unsigned long i = 0; i < timeout; ++i) {
    if (is_debugger_present())
      return true;
    msleep(duration);
  }
  return false;
}
#ifdef __cplusplus
}
#endif
#endif // __EXT_DEBUG_UTIL_H__