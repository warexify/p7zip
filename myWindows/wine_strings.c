/*
 * Project Wine
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
#include <ctype.h>
#include <wctype.h>


LPSTR WINAPI CharNextA( LPCSTR ptr ) {
  if (!*ptr)
    return (LPSTR)ptr; // FIXME : if you use MBS (MultiByte String)
  return (LPSTR)(ptr + 1);
}

LPSTR WINAPI CharPrevA( LPCSTR start, LPCSTR ptr ) {
  while (*start && (start < ptr)) {
    LPCSTR next = CharNextA( start );
    if (next >= ptr)
      break;
    start = next;
  }
  return (LPSTR)start;
}


INT WINAPI lstrlenA( LPCSTR str ) {
  return strlen(str); // FIXME : if you use MBS
}

LPSTR WINAPI lstrcatA( LPSTR dst, LPCSTR src ) {
  strcat( dst, src );  // FIXME : if you use MBS
  return dst;
}

int WINAPI CompareStringA(LCID lcid,DWORD style,LPCSTR str1,int len1,LPCSTR str2,int len2) {
 // FIXME : if you use MBS
  INT ret, len;

  if (!str1 || !str2) {
    SetLastError(ERROR_INVALID_PARAMETER);
    return 0;
  }

  if (len1 < 0)
    len1 = lstrlenA(str1);
  if (len2 < 0)
    len2 = lstrlenA(str2);

  len = (len1 < len2) ? len1 : len2;
  ret = (style & NORM_IGNORECASE) ? strncasecmp(str1, str2, len) :
        strncmp(str1, str2, len);

  if (ret) /* need to translate result */
    return (ret < 0) ? CSTR_LESS_THAN : CSTR_GREATER_THAN;

  if (len1 == len2)
    return CSTR_EQUAL;
  /* the longer one is lexically greater */
  return (len1 < len2) ? CSTR_LESS_THAN : CSTR_GREATER_THAN;
}

LPSTR WINAPI CharLowerA(LPSTR str) { // FIXME : if you use MBS
  if (!HIWORD(str)) {
    unsigned char ch = LOWORD(str);
    ch = tolower(ch);
    return (LPSTR)(UINT_PTR)(BYTE)ch;
  }

  unsigned char *ret = (unsigned char*)str;
  while ((*str = tolower(*str)))
    str++;
  return ret;
}

LPSTR WINAPI CharUpperA(LPSTR str) { // FIXME : if you use MBS
  if (!HIWORD(str)) {
    unsigned char ch = LOWORD(str);
    ch = toupper(ch);
    return (LPSTR)(UINT_PTR)(BYTE)ch;
  }

  unsigned char *ret = (unsigned char*)str;
  while ((*str = toupper(*str)))
    str++;
  return ret;
}


int strncmpiW( const WCHAR *str1, const WCHAR *str2, int n ) {
  int ret = 0;
  for ( ; n > 0; n--, str1++, str2++)
    if ((ret = towupper(*str1) - towupper(*str2)) || !*str1)
      break;
  return ret;
}

static inline int strncmpW( const WCHAR *str1, const WCHAR *str2, int n ) {
  if (n <= 0)
    return 0;
  while ((--n > 0) && *str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return *str1 - *str2;
}

INT WINAPI CompareStringW(LCID lcid, DWORD style,
                          LPCWSTR str1, INT len1, LPCWSTR str2, INT len2) {
  INT ret, len;

  if (!str1 || !str2) {
    SetLastError(ERROR_INVALID_PARAMETER);
    return 0;
  }

  if (len1 < 0)
    len1 = lstrlenW(str1);
  if (len2 < 0)
    len2 = lstrlenW(str2);

  len = (len1 < len2) ? len1 : len2;
  ret = (style & NORM_IGNORECASE) ? strncmpiW(str1, str2, len) :
        strncmpW(str1, str2, len);

  if (ret) /* need to translate result */
    return (ret < 0) ? CSTR_LESS_THAN : CSTR_GREATER_THAN;

  if (len1 == len2)
    return CSTR_EQUAL;
  /* the longer one is lexically greater */
  return (len1 < len2) ? CSTR_LESS_THAN : CSTR_GREATER_THAN;
}

INT WINAPI lstrlenW( LPCWSTR str ) {
  const WCHAR *s = str;
  while (*s)
    s++;
  return s - str;
}


static inline WCHAR *struprW( WCHAR *str ) {
  WCHAR *ret = str;
  while ((*str = towupper(*str)))
    str++;
  return ret;
}

LPWSTR WINAPI CharUpperW(LPWSTR x) {
  if (HIWORD(x))
    return struprW(x);
  else
    return (LPWSTR)((UINT)towupper(LOWORD(x)));
}

static inline WCHAR *strlwrW( WCHAR *str ) {
  WCHAR *ret = str;
  while ((*str = towlower(*str)))
    str++;
  return ret;
}

LPWSTR WINAPI CharLowerW(LPWSTR x) {
  if (HIWORD(x))
    return strlwrW(x);
  else
    return (LPWSTR)((UINT)towlower(LOWORD(x)));
}
