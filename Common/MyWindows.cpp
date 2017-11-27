// MyWindows.cpp

#include "StdAfx.h"

#ifndef WIN32

#include "MyWindows.h"
#include "Types.h"
#include <stdlib.h> /* FIXED <malloc.h> */

static inline void *AllocateForBSTR(size_t cb) { return ::malloc(cb); }
static inline void FreeForBSTR(void *pv) { ::free(pv);}

static int MyStringLen(const wchar_t *s)
{ 
  int i;
  for (i = 0; s[i] != '\0'; i++);
  return i;
}

BSTR SysAllocStringByteLen(LPCSTR psz, unsigned int len)
{
  // FIXED int realLen = len + sizeof(UInt32) + 3;
  int realLen = len + sizeof(UInt32) + sizeof(wchar_t);
  void *p = AllocateForBSTR(realLen);
  if (p == 0)
    return 0;
  *(UInt32 *)p = len;
  BSTR bstr = (BSTR)((UInt32 *)p + 1);
  memmove(bstr, psz, len);
/* FIXED
  Byte *pb = ((Byte *)bstr) + len;
  pb[0] = pb[1] = pb[2] = 0;
*/
  wchar_t *pb = (wchar_t *)(((Byte *)bstr) + len);
  *pb =  L'\0';
  return bstr;
}

BSTR SysAllocString(const OLECHAR *sz)
{
  if (sz == 0)
    return 0;
  UInt32 strLen = MyStringLen(sz);
  UInt32 len = (strLen + 1) * sizeof(OLECHAR);
  void *p = AllocateForBSTR(len + sizeof(UInt32));
  if (p == 0)
    return 0;
  *(UInt32 *)p = strLen * sizeof(OLECHAR); // FIXED
  BSTR bstr = (BSTR)((UInt32 *)p + 1);
  memmove(bstr, sz, len);
  return bstr;
}

void SysFreeString(BSTR bstr)
{
  if (bstr != 0)
    FreeForBSTR((UInt32 *)bstr - 1);
}

UINT SysStringByteLen(BSTR bstr)
{
  if (bstr == 0)
    return 0;
  return *((UInt32 *)bstr - 1);

}

UINT SysStringLen(BSTR bstr)
{
  // FIXED return SysStringByteLen(bstr) >> 1;
  return SysStringByteLen(bstr) / sizeof(wchar_t);
}

HRESULT VariantClear(VARIANTARG *prop)
{
  if (prop->vt == VT_BSTR)
    SysFreeString(prop->bstrVal);
  prop->vt = VT_EMPTY;
  return S_OK;
}

HRESULT VariantCopy(VARIANTARG *dest, VARIANTARG *src)
{
  HRESULT res = ::VariantClear(dest);
  if (res != S_OK)
    return res;
  if (src->vt == VT_BSTR)
  {
    dest->bstrVal = SysAllocStringByteLen((LPCSTR)src->bstrVal, 
        SysStringByteLen(src->bstrVal));
    if (dest->bstrVal == 0)
      return E_OUTOFMEMORY;
    dest->vt = VT_BSTR;
  }
  else
    *dest = *src;
  return S_OK;
}

LONG CompareFileTime(const FILETIME* ft1, const FILETIME* ft2)
{
  if(ft1->dwHighDateTime < ft2->dwHighDateTime)
    return -1;
  if(ft1->dwHighDateTime > ft2->dwHighDateTime)
    return 1;
  if(ft1->dwLowDateTime < ft2->dwLowDateTime)
    return -1;
  if(ft1->dwLowDateTime > ft2->dwLowDateTime)
    return 1;
  return 0;
}

/* FIXED
DWORD GetLastError()
{
  return 0;
}
*/

#endif
