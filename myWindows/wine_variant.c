/*
 * VARIANT
 *
 * Project Wine : ./dlls/oleaut32/variant.c
 * 
 * Copyright 1998 Jean-Claude Cote
 * Copyright 2003 Jon Griffiths
 * The alorithm for conversion from Julian days to day/month/year is based on
 * that devised by Henry Fliegel, as implemented in PostgreSQL, which is
 * Copyright 1994-7 Regents of the University of California
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include <wchar.h>
#include <windows.h>

// #define TRACE_BSTR(u) u;
#define TRACE_BSTR(u)  /* */

HRESULT WINAPI VariantClear(VARIANTARG* pvarg) {
  switch(pvarg->vt) {
  case VT_EMPTY:
  case VT_UI1:
  case VT_I1:
  case VT_I2:
  case VT_UI2:
  case VT_BOOL:
  case VT_I4:
  case VT_UI4:
  case VT_R4:
  case VT_INT:
  case VT_UINT:
  case VT_ERROR:
  case VT_FILETIME:
  case VT_UI8:
  case VT_R8:
  case VT_CY:
  case VT_DATE:
    memset(pvarg,0,sizeof(*pvarg));
    pvarg->vt = VT_EMPTY;
    return S_OK;
  case VT_BSTR:
    if (pvarg->bstrVal) {
      SysFreeString(pvarg->bstrVal);
    }
    memset(pvarg,0,sizeof(*pvarg));
    pvarg->vt = VT_EMPTY;
    return S_OK;

  }
  printf("VariantClear : type %d - not implemented\n",pvarg->vt);
  exit(EXIT_FAILURE);
  return S_OK;
}

HRESULT WINAPI VariantCopy(VARIANTARG* pvargDest, VARIANTARG* pvargSrc) {
  if (pvargSrc->vt != VT_BSTR) {
    printf("VariantCopy : %d - not implemented\n",pvargSrc->vt);
    exit(EXIT_FAILURE);
  }
  VariantClear(pvargDest);

  pvargDest->bstrVal = SysAllocStringByteLen((char*)(pvargSrc->bstrVal), SysStringByteLen(pvargSrc->bstrVal));
  pvargDest->vt = VT_BSTR;

  TRACE_BSTR((printf("\nVariantCopy '%p|%ls' -> '%p|%ls'\n",pvargSrc->bstrVal,pvargSrc->bstrVal,
                     pvargDest->bstrVal,pvargDest->bstrVal)))

  return S_OK;
}

