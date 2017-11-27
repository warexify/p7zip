#ifndef _WINDEF_H
#define _WINDEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Common/MyWindows.h" // FIXED

#ifndef CONST
#define CONST const
#endif

#undef MAX_PATH
#define MAX_PATH 260

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define WINAPI 

#define LOWORD(l)	((WORD)((DWORD)(l)))
#define HIWORD(l)	((WORD)(((DWORD)(l)>>16)&0xFFFF))

#ifndef NOMINMAX
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#endif

typedef int WINBOOL,*PWINBOOL,*LPWINBOOL;
typedef WINBOOL BOOL;
typedef BOOL *PBOOL,*LPBOOL;
typedef DWORD *PDWORD,*LPDWORD;
typedef WORD *PWORD,*LPWORD;
typedef unsigned int *PUINT,*LPUINT;
typedef CONST void *PCVOID,*LPCVOID;

#include <winnt.h>

#ifdef __cplusplus
}
#endif
#endif
