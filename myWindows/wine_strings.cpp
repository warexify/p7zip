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

LPSTR WINAPI CharPrevA( LPCSTR start, LPCSTR ptr ) { // OK for MBS
  while (*start && (start < ptr)) {
    LPCSTR next = CharNextA( start );
    if (next >= ptr)
      break;
    start = next;
  }
  return (LPSTR)start;
}

/***********************************************************************************************************/
#include <limits.h>
#ifndef MB_LEN_MAX
#define MB_LEN_MAX 1024
#endif


LPSTR WINAPI CharNextA( LPCSTR ptr ) {
  if (!*ptr)
    return (LPSTR)ptr;
  wchar_t wc;
  size_t len  = mbrtowc(&wc,ptr,MB_LEN_MAX,0); 
  if (len >= 1) return (LPSTR)(ptr + len);
  printf("INTERNAL ERROR - CharNextA\n");
  exit(EXIT_FAILURE);
}

