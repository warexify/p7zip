/*
 *	OLEAUT32
 *
 *  project Wine : ./dlls/oleaut32/oleaut.c
 *
 * Copyright 1999, 2000 Marcus Meissner
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
 *
 *
 * MODIFICATIONS From Christophe JOUIN for 7zip
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

void WINAPI SysFreeString(BSTR str)
{
    DWORD* bufferPointer;

    if(!str) return;
 
    TRACE_BSTR((printf("\nSysFreeString(%p|%ls)\n",str,str)))

    bufferPointer = (DWORD*)str;
    bufferPointer--;
    /* Free the memory from its "real" origin.  */
    free(bufferPointer);
}

BSTR WINAPI SysAllocStringByteLen(LPCSTR str, UINT len)
{
    DWORD* newBuffer;
    WCHAR* stringBuffer;

    /*
     * Allocate a new buffer to hold the string.
     * don't forget to keep an empty spot at the beginning of the
     * buffer for the character count and an extra character at the
     * end for the NULL.
     */
    newBuffer = (DWORD*)malloc(len + sizeof(WCHAR) + sizeof(DWORD));

    /*
     * If the memory allocation failed, return a null pointer.
     */
    if (newBuffer==0){
      printf("\nSysAllocStringByteLen(%p|%ls,%d)=NULL'\n",str,(WCHAR *)str,len);   
      exit(EXIT_FAILURE);
    }

    /*
     * Copy the length of the string in the placeholder.
     */
    *newBuffer = len;

    /*
     * Skip the byte count.
     */
    newBuffer++;

    /*
     * Copy the information in the buffer.
     * Since it is valid to pass a NULL pointer here, we'll initialize the
     * buffer to nul if it is the case.
     */
    if (str != 0)
      memcpy(newBuffer, str, len);

    /* Make sure that there is a nul character at the end of the string.  */
    stringBuffer = (WCHAR *)(((char *)newBuffer)+len);
    *stringBuffer = L'\0';  // FIXED : CHANGE FROM WINE CODE because of sizeof(wchar_t) != 2

    TRACE_BSTR((printf("\nSysAllocStringByteLen(%p|%ls,%d)='%p|%ls'\n",str,str,len,newBuffer,newBuffer)))

    return (LPWSTR)newBuffer;  // FIXED :  CHANGE FROM WINE CODE because of sizeof(wchar_t) != 2
}

UINT WINAPI SysStringByteLen(BSTR str)
{
    DWORD* bufferPointer;

     if (!str) return 0;
    /*
     * The length of the string (in bytes) is contained in a DWORD placed
     * just before the BSTR pointer
     */
    bufferPointer = (DWORD*)str;

    bufferPointer--;

    return (int)(*bufferPointer);
}

BSTR WINAPI SysAllocStringLen(const OLECHAR *in, unsigned int len)
{
    DWORD  bufferSize;
    DWORD* newBuffer;
    WCHAR* stringBuffer;

    bufferSize = len * sizeof (WCHAR);

    newBuffer = (DWORD*)malloc(bufferSize + sizeof(WCHAR) + sizeof(DWORD));

    if (newBuffer==0)
      return 0;

    *newBuffer = bufferSize;

    newBuffer++;

    if (in != 0) memcpy(newBuffer, in, bufferSize);
    else memset(newBuffer, 0, bufferSize);

    stringBuffer = (WCHAR*)newBuffer;
    stringBuffer[len] = L'\0';

    TRACE_BSTR((printf("\nSysAllocStringLen(%p|%ls,%d)='%p|%ls'\n",in,in,len,newBuffer,newBuffer)))

    return (LPWSTR)stringBuffer;
}

BSTR WINAPI SysAllocString(LPCOLESTR in)
{
    if (!in) return 0;

    /* Delegate this to the SysAllocStringLen32 method. */
    /* return SysAllocStringLen(in, lstrlenW(in)); */
    return SysAllocStringLen(in, wcslen(in));
}

UINT WINAPI SysStringLen(BSTR str)
{
    DWORD* bufferPointer;

     if (!str) return 0;
    /*
     * The length of the string (in bytes) is contained in a DWORD placed
     * just before the BSTR pointer
     */
    bufferPointer = (DWORD*)str;

    bufferPointer--;

    return (int)(*bufferPointer/sizeof(WCHAR));
}
