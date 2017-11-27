#include "StdAfx.h"

#include <errno.h>

#include "myPrivate.h"

//#define TRACEN(u) u;
#define TRACEN(u)  /* */

void nameWindowToUnixA(LPCSTR lpFileName,char name[MAX_PATHNAME_LEN]) {
  char temp[MAX_PATHNAME_LEN];
  strcpy(temp,lpFileName);

  if (strncmp("c:\\",temp,3) == 0) {
    strcpy(name,temp+2);
  } else {
    strcpy(name,temp);
  }

  /* transform separators */
  char *ptr = name;
  while (*ptr) {
    if (*ptr == '\\')
      *ptr = '/';
    ptr++;
  }
  TRACEN((printf("nameWindowToUnixA: '%s' => '%s'\n",temp,name)))
}

BOOL WINAPI AreFileApisANSI(void) {
  return TRUE;
}

void WINAPI SetLastError( DWORD err ) {
  errno = err;
}
DWORD WINAPI GetLastError(void) {
  TRACEN((printf("GetLastError()=%d\n",last_err)))
  return errno;
}

BOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE fct ,BOOL flag) {
  /* FIXME : CTRL-C ? */
  return TRUE;
}
