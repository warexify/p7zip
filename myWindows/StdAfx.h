// stdafx.h

#ifndef __STDAFX_H
#define __STDAFX_H

#include <pthread.h>

#include <windows.h>

#include "myWindows.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <wchar.h>
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

// FIXME
wchar_t *_itow (int, wchar_t *, int);


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

#if 0
FARPROC GetProcAddress( HMODULE hModule, LPCSTR lpProcName);

/* winbase.h */
BOOL FreeLibrary( HMODULE hModule);

HMODULE LoadLibraryA(LPCSTR lpLibFileName);
HMODULE LoadLibraryW(LPCWSTR lpLibFileName);
HMODULE LoadLibraryExA( LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
HMODULE LoadLibraryExW( LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);

DWORD GetModuleFileNameA( HMODULE hModule, LPSTR lpFilename, DWORD nSize);
DWORD GetModuleFileNameW( HMODULE hModule, LPWSTR lpFilename, DWORD nSize);
#ifdef UNICODE
#define LoadLibrary  LoadLibraryW
#define LoadLibraryEx  LoadLibraryExW
#define GetModuleFileName  GetModuleFileNameW
#else
#define LoadLibrary  LoadLibraryA
#define LoadLibraryEx  LoadLibraryExA
#define GetModuleFileName  GetModuleFileNameA
#endif // !UNICODE

#endif // #if 0

/***************************/

#endif 
