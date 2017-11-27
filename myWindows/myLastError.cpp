#include "StdAfx.h"

#include <errno.h>

#include "myPrivate.h"

// #define TRACEN(u) u;
#define TRACEN(u)  /* */

void nameWindowToUnixA(LPCSTR lpFileName,char name[MAX_PATHNAME_LEN]) {
  if (strncmp("c:",lpFileName,2) == 0) {
    strcpy(name,lpFileName+2);
  } else {
    strcpy(name,lpFileName);
  }

  TRACEN((printf("nameWindowToUnixA: '%s' => '%s'\n",lpFileName,name)))
}

BOOL WINAPI AreFileApisANSI(void) {
  return TRUE;
}

void WINAPI SetLastError( DWORD err ) {
  errno = err;
}
DWORD WINAPI GetLastError(void) {
  TRACEN((printf("GetLastError()=%d\n",errno)))
  return errno;
}

BOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE fct ,BOOL flag) {
  /* FIXME : CTRL-C ? */
  return TRUE;
}
