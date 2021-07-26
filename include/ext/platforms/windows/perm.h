#pragma once

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include "platforms/windows/win32-ex/include/Security/Descriptor.h"
#include <Windows.h>
#include <sddl.h>

typedef PSECURITY_DESCRIPTOR perm;
typedef ACCESS_MASK access_mask;

#define read_access GENERIC_READ
#define write_access GENERIC_WRITE
#define execute_access GENERIC_EXECUTE
#define all_access GENERIC_ALL

#define perm_unspecified ((perm)NULL)
#define SECURITY_DESCRIPTOR_FROM_PERM(_perm) ((PSECURITY_DESCRIPTOR)(_perm))
#define PERM_FROM_SECURITY_DESCRIPTOR(_sd) ((perm)(_sd))

//
//   예) "D:P(A;OICI;GA;;;SY)(A;OICI;GA;;;BA)(A;OICI;GR;;;IU)"
//		https://docs.microsoft.com/ko-kr/windows/win32/secauthz/ace-strings
//

inline perm alloc_acl_from_string(const char *String) {
  ULONG securityDescriptorSize = 0;
  PSECURITY_DESCRIPTOR securityDescriptor = NULL;
  PSECURITY_DESCRIPTOR securityDescriptorNew = NULL;

  ConvertStringSecurityDescriptorToSecurityDescriptorA(
      String, SDDL_REVISION_1, &securityDescriptor, &securityDescriptorSize);

  securityDescriptorNew = (PSECURITY_DESCRIPTOR)HeapAlloc(
      GetProcessHeap(), 0, securityDescriptorSize);
  if (!securityDescriptorNew)
    return perm_unspecified;
  CopyMemory(securityDescriptorNew, securityDescriptor, securityDescriptorSize);
  LocalFree(securityDescriptor);
  return PERM_FROM_SECURITY_DESCRIPTOR(securityDescriptorNew);
}

inline perm alloc_everyone_perm() {
  PSECURITY_DESCRIPTOR securityDescriptor;
  securityDescriptor = (PSECURITY_DESCRIPTOR)HeapAlloc(
      GetProcessHeap(), 0, SECURITY_DESCRIPTOR_MIN_LENGTH);

  if (securityDescriptor == NULL)
    return perm_unspecified;

  if (!InitializeSecurityDescriptor(securityDescriptor,
                                    SECURITY_DESCRIPTOR_REVISION)) {
    FreeSecurityDescriptor(securityDescriptor);
    return perm_unspecified;
  }
#pragma warning(disable : 6248)
  if (!SetSecurityDescriptorDacl(securityDescriptor, TRUE, NULL, FALSE)) {
    FreeSecurityDescriptor(securityDescriptor);
    return perm_unspecified;
  }
#pragma warning(default : 6248)
  return PERM_FROM_SECURITY_DESCRIPTOR(securityDescriptor);
}

inline perm alloc_perm(access_mask owner, access_mask group,
                       access_mask other) {
  return PERM_FROM_SECURITY_DESCRIPTOR(AllocateAndInitializeSecurityDescriptor(
      MAXDWORD, MAXDWORD, owner, group, owner, group, other));
}

inline void free_perm(perm perm) { FreeSecurityDescriptor(perm); }
#endif