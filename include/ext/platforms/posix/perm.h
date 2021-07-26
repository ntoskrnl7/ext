#pragma once

#if defined(__linux__) | defined(__APPLE__)
#include <sys/stat.h>

typedef mode_t perm;
typedef mode_t access_mask;

#define read_access 4
#define write_access 2
#define execute_access 1
#define all_access (write_access | read_access | execute_access)
#define perm_unspecified ((mode_t)0)
#define mode_t_from_perm(_perm) ((mode_t)(_perm))

//
//   예) "rwxr-xr-x"
//  (추후 "u::rw-,u:lisa:rw-,g::r--,g:toolies:rw-,m::r--,o::r--"와 같은
//   SHORT TEXT FORM을 지원하도록 처리할 예정임)
//	https://www.man7.org/linux/man-pages/man5/acl.5.html
//

inline perm alloc_perm_from_string(const char *form) {
  return (((form[0] == 'r') * 4 | (form[1] == 'w') * 2 | (form[2] == 'x'))
          << 6) |
         (((form[3] == 'r') * 4 | (form[4] == 'w') * 2 | (form[5] == 'x'))
          << 3) |
         (((form[6] == 'r') * 4 | (form[7] == 'w') * 2 | (form[8] == 'x')));
}

inline perm alloc_everyone_perm() { return (S_IRWXU | S_IRWXG | S_IRWXO); }

inline perm alloc_perm(access_mask owner, access_mask group,
                       access_mask other) {
  return ((owner << 6) | (group << 3) | (other & 0x7));
}

inline void free_perm(perm permission) { (void)permission; }
#endif