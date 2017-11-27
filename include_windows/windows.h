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

/* translate GCC target defines to MS equivalents. Keep this synchronized
   with winnt.h. */
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
  DWORD WINAPI GetLastError(void);
  void WINAPI SetLastError( DWORD err );
  int WINAPI wsprintfA(LPSTR,LPCSTR,...);
  int WINAPI wsprintfW(LPWSTR,LPCWSTR,...);
  #ifdef UNICODE
  #define wsprintf wsprintfW
  #else
  #define wsprintf wsprintfA
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

/* BEGIN #include <ole2.h> */
  #ifdef __cplusplus
  // extern "C" {
  #endif
#include "basetyps.h"

#ifdef __cplusplus
inline BOOL IsEqualGUID(REFGUID rguid1, REFGUID rguid2)
	{ return !memcmp(&rguid1, &rguid2, sizeof(GUID)); }
inline BOOL operator==(const GUID& guidOne, const GUID& guidOther)
	{ return !memcmp(&guidOne,&guidOther,sizeof(GUID)); }
inline BOOL operator!=(const GUID& g1, const GUID& g2)
	{ return !(g1 == g2); }
#else
#define IsEqualGUID(rguid1, rguid2) (!memcmp(rguid1, rguid2, sizeof(GUID)))
#endif


typedef WCHAR OLECHAR;
typedef LPWSTR LPOLESTR;
typedef LPCWSTR LPCOLESTR;
#define OLESTR(s) L##s

typedef unsigned short VARTYPE;
typedef short VARIANT_BOOL;
typedef VARIANT_BOOL _VARIANT_BOOL;
#define VARIANT_TRUE ((VARIANT_BOOL)0xffff)
#define VARIANT_FALSE ((VARIANT_BOOL)0)
typedef OLECHAR *BSTR;

#ifdef NONAMELESSUNION
#define __VARIANT_NAME_1 n1
#define __VARIANT_NAME_2 n2
#define __VARIANT_NAME_3 n3
#define __VARIANT_NAME_4 n4
#else
#define __tagVARIANT
#define __VARIANT_NAME_1
#define __VARIANT_NAME_2
#define __VARIANT_NAME_3
#define __VARIANT_NAME_4
#endif


#if defined (__GNUC__) && !defined (NONAMELESSUNION)
__extension__   /* no named members  */
#endif
typedef struct tagVARIANT {
	/*
  _ANONYMOUS_UNION union {
	struct __tagVARIANT {
	*/
	VARTYPE vt;
	WORD wReserved1;
	WORD wReserved2;
	WORD wReserved3;
	_ANONYMOUS_UNION union {
		long lVal;
		unsigned char bVal;
		short iVal;
		float fltVal;
		double dblVal;
		VARIANT_BOOL  boolVal;
		BSTR bstrVal;
/*
		SCODE scode;
		CY cyVal;
		DATE date;
		IUnknown *punkVal;
		LPDISPATCH pdispVal;
		SAFEARRAY *parray;
*/
		unsigned char *pbVal;
		short *piVal;
		long *plVal;
		float *pfltVal;
		double *pdblVal;
		VARIANT_BOOL *pboolVal;
		_VARIANT_BOOL  *pbool;
/*
		SCODE *pscode;
		CY *pcyVal;
		DATE *pdate;
		BSTR *pbstrVal;
		IUnknown **ppunkVal;
		LPDISPATCH *ppdispVal;
		SAFEARRAY **pparray;
*/
		struct tagVARIANT *pvarVal;
		void *byref;
		CHAR cVal;
		USHORT uiVal;
		ULONG ulVal;
		INT intVal;
		UINT uintVal;
		/* DECIMAL *pdecVal; */
		CHAR  *pcVal;
		USHORT  *puiVal;
		ULONG  *pulVal;
		INT  *pintVal;
		UINT  *puintVal;
		/*
		_ANONYMOUS_STRUCT struct {
			PVOID pvRecord;
			struct IRecordInfo *pRecInfo;
		} __VARIANT_NAME_4;
		*/
	} __VARIANT_NAME_3;
	/*
    } __VARIANT_NAME_2;
    * DECIMAL decVal; *
  } __VARIANT_NAME_1;
*/
} VARIANT,*LPVARIANT;


typedef VARIANT VARIANTARG;
typedef VARIANT *LPVARIANTARG;


typedef struct tagPROPVARIANT {
	VARTYPE vt;
	WORD wReserved1;
	WORD wReserved2;
	WORD wReserved3;
	_ANONYMOUS_UNION union {
		UCHAR bVal;
		short iVal;
		USHORT uiVal;
		VARIANT_BOOL boolVal;
		long lVal;
		ULONG ulVal;
		float fltVal;
		SCODE scode;
		LARGE_INTEGER hVal;
		ULARGE_INTEGER uhVal;
		double dblVal;
		FILETIME filetime;
		BSTR bstrVal;
		/*
		CY cyVal;
		DATE date;
		CLSID *puuid;
		BLOB blob;
		CLIPDATA *pclipdata;
		LPSTREAM pStream;
		LPSTORAGE pStorage;
		BSTRBLOB bstrblobVal;
		LPSTR pszVal;
		LPWSTR pwszVal;

		CAUB caub;
		CAI cai;
		CAUI caui;
		CABOOL cabool;
		CAL cal;
		CAUL caul;
		CAFLT caflt;
		CASCODE cascode;
		CAH cah;
		CAUH cauh;
		CADBL cadbl;
		CACY cacy;
		CADATE cadate;
		CAFILETIME cafiletime;
		CACLSID cauuid;
		CACLIPDATA caclipdata;
		CABSTR cabstr;
		CABSTRBLOB cabstrblob;
		CALPSTR calpstr;
		CALPWSTR calpwstr;
		CAPROPVARIANT capropvar;
*/		
	} DUMMYUNIONNAME;
} PROPVARIANT;


typedef struct  tagSTATPROPSTG {
	LPOLESTR lpwstrName;
	PROPID propid;
	VARTYPE vt;
} STATPROPSTG;



#define WINOLEAPI STDAPI
#define WINOLEAPI_(type) STDAPI_(type)
WINOLEAPI CoInitialize(PVOID);
WINOLEAPI_(void) CoUninitialize(void);

#define WINOLEAUTAPI STDAPI
#define WINOLEAUTAPI_(type) STDAPI_(type)
WINOLEAUTAPI_(BSTR) SysAllocString(const OLECHAR*);
WINOLEAUTAPI_(void) SysFreeString(BSTR);
WINOLEAUTAPI_(BSTR) SysAllocStringByteLen(const char*,unsigned int);
WINOLEAUTAPI_(unsigned int) SysStringLen(BSTR);
WINOLEAUTAPI_(unsigned int) SysStringByteLen(BSTR);

WINOLEAUTAPI VariantClear(VARIANTARG*);
WINOLEAUTAPI VariantCopy(VARIANTARG*,VARIANTARG*);
WINOLEAUTAPI VariantChangeType(VARIANTARG*,VARIANTARG*,unsigned short,VARTYPE);

typedef enum tagSTREAM_SEEK {
	STREAM_SEEK_SET,
	STREAM_SEEK_CUR,
	STREAM_SEEK_END
} STREAM_SEEK;


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

#include <wchar.h>
#ifdef __cplusplus
extern "C" {
#endif
char*  _ui64toa(unsigned __int64, char *, int);
#ifdef __cplusplus
}
#endif

#endif

