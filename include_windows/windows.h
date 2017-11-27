/*
	windows.h - main header file for the Win32 API

	Written by Anders Norlander <anorland@hem2.passagen.se>

	This file is part of a free library for the Win32 API.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/
#ifndef _WINDOWS_H
#define _WINDOWS_H

#include <stdarg.h>
#include <windef.h>
/* BEGIN #include <wincon.h> */
  #ifdef __cplusplus
  extern "C" {
  #endif
  typedef BOOL(*PHANDLER_ROUTINE)(DWORD);
  BOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE,BOOL);
  #ifdef __cplusplus
  }
  #endif
/* END #include <wincon.h> */


#include <winbase.h>

/* BEGIN #include <winuser.h> */
  #ifdef __cplusplus
  extern "C" {
  #endif
  LPSTR WINAPI CharNextA(LPCSTR);
  LPSTR WINAPI CharPrevA(LPCSTR,LPCSTR);
  LPSTR WINAPI CharLowerA(LPSTR);
  LPSTR WINAPI CharUpperA(LPSTR);
  LPWSTR WINAPI CharUpperW(LPWSTR);
  LPWSTR WINAPI CharLowerW(LPWSTR);
  /* FIXED DWORD WINAPI GetLastError(void); */
  void WINAPI SetLastError( DWORD err );
  int WINAPI wsprintfA(LPSTR,LPCSTR,...);
  int WINAPI wsprintfW(LPWSTR,LPCWSTR,...);
  #ifdef UNICODE
  #define wsprintf wsprintfW
  #else
  /* #define wsprintf wsprintfA */
  #define wsprintf sprintf
  #define wsprintfA sprintf
  #endif
  #ifdef __cplusplus
  }
  #endif
/* END #include <winuser.h> */



/* BEGIN #include <winnls.h> */
#define NORM_IGNORECASE	1

#define CSTR_LESS_THAN 1
#define CSTR_EQUAL 2
#define CSTR_GREATER_THAN 3

#define CP_ACP 0
#define CP_OEMCP 1
#define CP_INSTALLED 1
#define CP_UTF8 65001

#define MB_USEGLYPHCHARS 4

#define LOCALE_USER_DEFAULT	0x400
#define SORT_STRINGSORT	4096

#ifdef __cplusplus
extern "C" {
#endif
int WINAPI CompareStringA(LCID,DWORD,LPCSTR,int,LPCSTR,int);
int WINAPI CompareStringW(LCID,DWORD,LPCWSTR,int,LPCWSTR,int);
int WINAPI WideCharToMultiByte(UINT,DWORD,LPCWSTR,int,LPSTR,int,LPCSTR,LPBOOL);
int WINAPI MultiByteToWideChar(UINT,DWORD,LPCSTR,int,LPWSTR,int);
#ifdef __cplusplus
}
#endif

/* END #include <winnls.h> */

#include <unknwn.h>

typedef WCHAR OLECHAR;
typedef LPWSTR LPOLESTR;
typedef LPCWSTR LPCOLESTR;
#define OLESTR(s) L##s

typedef unsigned short VARTYPE;
typedef short VARIANT_BOOL;
typedef VARIANT_BOOL _VARIANT_BOOL;
/*
#define VARIANT_TRUE ((VARIANT_BOOL)0xffff)
#define VARIANT_FALSE ((VARIANT_BOOL)0)
*/
typedef OLECHAR *BSTR;

void CoInitialize(void *);
void CoUninitialize(void);

typedef struct  tagSTATPROPSTG {
	LPOLESTR lpwstrName;
	PROPID propid;
	VARTYPE vt;
} STATPROPSTG;

EXTERN_C const IID IID_ISequentialStream;
#undef INTERFACE
#define INTERFACE ISequentialStream
DECLARE_INTERFACE_(ISequentialStream,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(Read)(THIS_ void*,ULONG,ULONG*) PURE;
	STDMETHOD(Write)(THIS_ void const*,ULONG,ULONG*) PURE;
};


  #ifdef __cplusplus
  // }
  #endif
/* END #include <ole2.h> */

#include <stddef.h>

#endif

