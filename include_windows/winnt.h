#ifndef _WINNT_H
#define _WINNT_H

/* translate GCC target defines to MS equivalents. Keep this synchronized
   with windows.h. */
#if defined(__i686__) && !defined(_M_IX86)
#define _M_IX86 600
#elif defined(__i586__) && !defined(_M_IX86)
#define _M_IX86 500
#elif defined(__i486__) && !defined(_M_IX86)
#define _M_IX86 400
#elif defined(__i386__) && !defined(_M_IX86)
#define _M_IX86 300
#endif

#if defined(_M_IX86) && !defined(_X86_)
#define _X86_
#elif defined(_M_ALPHA) && !defined(_ALPHA_)
#define _ALPHA_
#elif defined(_M_PPC) && !defined(_PPC_)
#define _PPC_
#elif defined(_M_MRX000) && !defined(_MIPS_)
#define _MIPS_
#elif defined(_M_M68K) && !defined(_68K_)
#define _68K_
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <winerror.h>

#include <string.h>
#include <stddef.h>
#include <wchar.h>

#ifdef __cplusplus
}
#endif

#ifndef VOID
#define VOID void
#endif
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef char CCHAR, *PCCHAR;
typedef unsigned char UCHAR,*PUCHAR;
typedef unsigned short USHORT,*PUSHORT;
typedef unsigned long ULONG,*PULONG;
typedef char *PSZ;

typedef void *PVOID,*LPVOID;

typedef wchar_t WCHAR;
typedef WCHAR *PWCHAR,*LPWCH,*PWCH,*NWPSTR,*LPWSTR,*PWSTR;
typedef CONST WCHAR *LPCWCH,*PCWCH,*LPCWSTR,*PCWSTR;
typedef CHAR *PCHAR,*LPCH,*PCH,*NPSTR,*LPSTR,*PSTR;
typedef CONST CHAR *LPCCH,*PCSTR,*LPCSTR;
#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
#ifdef UNICODE
/*
 * NOTE: This tests UNICODE, which is different from the _UNICODE define
 *       used to differentiate standard C runtime calls.
 */
typedef WCHAR TCHAR;
typedef WCHAR _TCHAR;
#else
typedef CHAR TCHAR;
typedef CHAR _TCHAR;
#endif
#endif
typedef TCHAR TBYTE,*PTCH,*PTBYTE;
typedef TCHAR *LPTCH,*PTSTR,*LPTSTR,*LP,*PTCHAR;
typedef const TCHAR *LPCTSTR;
#ifdef UNICODE
/*
 * __TEXT is a private macro whose specific use is to force the expansion of a
 * macro passed as an argument to the macro TEXT.  DO NOT use this
 * macro within your programs.  It's name and function could change without
 * notice.
 */
#define __TEXT(q) L##q
#else
#define __TEXT(q) q
#endif
/*
 * UNICODE a constant string when UNICODE is defined, else returns the string
 * unmodified.
 * The corresponding macros  _TEXT() and _T() for mapping _UNICODE strings
 * passed to C runtime functions are defined in mingw/tchar.h
 */
#define TEXT(q) __TEXT(q)    
typedef SHORT *PSHORT;
typedef LONG *PLONG;
typedef void *HANDLE;
typedef HANDLE *PHANDLE,*LPHANDLE;

typedef DWORD LCID;

#define _HAVE_INT64
#define _INTEGRAL_MAX_BITS 64
#undef __int64
#define __int64 long long

typedef __int64 LONGLONG;
typedef unsigned __int64 DWORDLONG;

typedef LONGLONG *PLONGLONG;
typedef DWORDLONG *PDWORDLONG;
typedef DWORDLONG ULONGLONG,*PULONGLONG;
typedef LONGLONG USN;

#ifdef _HAVE_INT64
#define Int32x32To64(a,b) ((LONGLONG)(a)*(LONGLONG)(b))
#define UInt32x32To64(a,b) ((DWORDLONG)(a)*(DWORDLONG)(b))
#define Int64ShllMod32(a,b) ((DWORDLONG)(a)<<(b))
#define Int64ShraMod32(a,b) ((LONGLONG)(a)>>(b))
#define Int64ShrlMod32(a,b) ((DWORDLONG)(a)>>(b))
#endif

#define ANSI_NULL '\0'
#define UNICODE_NULL L'\0'
typedef BYTE BOOLEAN,*PBOOLEAN;
#endif
typedef BYTE FCHAR;
typedef WORD FSHORT;
typedef DWORD FLONG;

#include <basetsd.h>

#define FILE_ATTRIBUTE_READONLY   1
#define FILE_ATTRIBUTE_HIDDEN	2
#define FILE_ATTRIBUTE_SYSTEM	4
#define FILE_ATTRIBUTE_DIRECTORY	16
#define FILE_ATTRIBUTE_ARCHIVE	32
#define FILE_ATTRIBUTE_DEVICE	64
#define FILE_ATTRIBUTE_NORMAL	128
#define FILE_ATTRIBUTE_TEMPORARY	256
#define FILE_ATTRIBUTE_SPARSE_FILE	512
#define FILE_ATTRIBUTE_REPARSE_POINT	1024
#define FILE_ATTRIBUTE_COMPRESSED	2048
#define FILE_ATTRIBUTE_OFFLINE	0x1000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED	0x2000
#define FILE_ATTRIBUTE_ENCRYPTED	0x4000
#define INVALID_FILE_ATTRIBUTES	((DWORD)-1)

#ifndef RC_INVOKED

#if ! (defined _GUID_DEFINED || defined GUID_DEFINED) /* also defined in basetyps.h */
#define GUID_DEFINED
typedef struct _GUID {
	unsigned long  Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char  Data4[8];
} GUID, *REFGUID, *LPGUID;
#define SYSTEM_LUID { QuadPart:999 }
#endif /* GUID_DEFINED */

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
#if ! defined(NONAMELESSUNION) || defined(__cplusplus)
  /*
  _ANONYMOUS_STRUCT struct {
    DWORD LowPart;
    LONG  HighPart;
  }; */
#endif /* NONAMELESSUNION */
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
  struct {
    DWORD LowPart;
    DWORD HighPart;
  } u;
#if ! defined(NONAMELESSUNION) || defined(__cplusplus)
  /*
  _ANONYMOUS_STRUCT struct {
    DWORD LowPart;
    DWORD HighPart;
  };
  */
#endif /* NONAMELESSUNION */
  ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;


#endif

