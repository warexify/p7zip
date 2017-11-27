#ifndef _WINNT_H
#define _WINNT_H


#ifdef __cplusplus
extern "C" {
#endif

#include <winerror.h>

#include <string.h>
#include <stddef.h>
/* #include <wchar.h> */

#ifdef __cplusplus
}
#endif

#ifndef VOID
#define VOID void
#endif
typedef void *PVOID,*LPVOID;
typedef WCHAR *PWCHAR,*LPWCH,*PWCH,*NWPSTR,*LPWSTR,*PWSTR;
typedef CHAR *PCHAR,*LPCH,*PCH,*NPSTR,*LPSTR,*PSTR;
typedef TCHAR *LPTCH,*PTSTR,*LPTSTR,*LP,*PTCHAR;

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
typedef ULONGLONG DWORDLONG;

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

typedef BYTE FCHAR;
typedef WORD FSHORT;
typedef DWORD FLONG;

/* BEGIN #include <basetsd.h> */
#ifndef __int64
#define __int64 long long
#endif
typedef unsigned __int64 UINT64,  *PUINT64;
typedef __int64 INT64,  *PINT64;
typedef  unsigned int UINT_PTR, *PUINT_PTR;
/* END #include <basetsd.h> */


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

typedef LARGE_INTEGER *PLARGE_INTEGER;
#endif

