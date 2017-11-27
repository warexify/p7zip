// stdafx.h

#ifndef __STDAFX_H
#define __STDAFX_H

#include <pthread.h>

#include "Common/MyWindows.h"

#include <windows.h>

#include "myPublicWindows.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>

#ifdef __CYGWIN__  // FIXME
#ifdef __cplusplus 
extern "C" {
#endif
unsigned long wcstoul (const wchar_t*, wchar_t**, int);
#ifdef __cplusplus
}	/* end of extern "C" */
#endif
#endif

#include <vector>
#include <memory>


/***************************/
typedef void * HINSTANCE; // FIXME
typedef void * HMODULE; // FIXME

// FIXME
#define lstrcpy strcpy
#define lstrcat strcat

typedef int (WINAPI *FARPROC)();
#define CLASS_E_CLASSNOTAVAILABLE        ((HRESULT)0x80040111L)
#define DLL_PROCESS_ATTACH   1

DWORD GetModuleFileNameA( HMODULE hModule, LPSTR lpFilename, DWORD nSize);
DWORD GetModuleFileNameW( HMODULE hModule, LPWSTR lpFilename, DWORD nSize);
#ifdef UNICODE
#define GetModuleFileName  GetModuleFileNameW
#else
#define GetModuleFileName  GetModuleFileNameA
#endif // !UNICODE

typedef struct _STGMEDIUM *STGMEDIUM;
void ReleaseStgMedium(STGMEDIUM *);

/***************************/

#include "Common/Types.h"
typedef UInt16 UINT16;

#endif 
