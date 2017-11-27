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
#define GetModuleFileName  GetModuleFileNameA

typedef struct _STGMEDIUM *STGMEDIUM;
void ReleaseStgMedium(STGMEDIUM *);

/***************************/

#include "Common/Types.h"

#endif 
