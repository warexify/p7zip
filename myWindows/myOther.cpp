#include "StdAfx.h"


#include <unistd.h> // rmdir
#include <errno.h>

#include <sys/stat.h> // mkdir
#include <sys/types.h>

#include <limits.h>
#ifndef MB_LEN_MAX
#define MB_LEN_MAX 1024
#endif

#include "../Common/StringConvert.h"

#include "myPrivate.h"

//#define TRACEN(u) u;
#define TRACEN(u)  /* */

void nameWindowToUnixA(LPCSTR lpFileName,char name[MAX_PATHNAME_LEN]) {
  char temp[MAX_PATHNAME_LEN];
  strcpy(temp,lpFileName);

  if (strncmp("c:\\",temp,3) == 0) {
    strcpy(name,temp+2);
  } else {
    strcpy(name,temp);
  }

  /* transform separators */
  char *ptr = name;
  while (*ptr) {
    if (*ptr == '\\')
      *ptr = '/';
    ptr++;
  }
  TRACEN((printf("nameWindowToUnixA: '%s' => '%s'\n",temp,name)))
}

static void FILE_SetDosError(void) {
  int save_errno = errno; /* errno gets overwritten by printf */

  switch (save_errno) {
  case EAGAIN:
    SetLastError( ERROR_SHARING_VIOLATION );
    break;
  case EBADF:
    SetLastError( ERROR_INVALID_HANDLE );
    break;
  case ENOSPC:
    SetLastError( ERROR_HANDLE_DISK_FULL );
    break;
  case EACCES:
  case EPERM:
  case EROFS:
    SetLastError( ERROR_ACCESS_DENIED );
    break;
  case EBUSY:
    SetLastError( ERROR_LOCK_VIOLATION );
    break;
  case ENOENT:
    SetLastError( ERROR_FILE_NOT_FOUND );
    break;
  case EISDIR:
    SetLastError( ERROR_CANNOT_MAKE );
    break;
  case ENFILE:
  case EMFILE:
    SetLastError( ERROR_NO_MORE_FILES );
    break;
  case EEXIST:
    SetLastError( ERROR_FILE_EXISTS );
    break;
  case EINVAL:
  case ESPIPE:
    SetLastError( ERROR_SEEK );
    break;
  case ENOTEMPTY:
    SetLastError( ERROR_DIR_NOT_EMPTY );
    break;
  case ENOEXEC:
    SetLastError( ERROR_BAD_FORMAT );
    break;
  default:
    SetLastError( ERROR_GEN_FAILURE );
    break;
  }
  errno = save_errno;
}

BOOL WINAPI AreFileApisANSI(void) {
  return TRUE;
}


void WINAPI SetLastError( DWORD err ) {
  errno = err;
}
DWORD WINAPI GetLastError(void) {
  TRACEN((printf("GetLastError()=%d\n",last_err)))
  return errno;
}

BOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE fct ,BOOL flag) {
  /* FIXME : CTRL-C ? */
  return TRUE;
}

#ifdef _UNICODE
BOOL WINAPI CreateDirectoryW( LPCWSTR path,
                              LPSECURITY_ATTRIBUTES lpsecattribs ) {
  return CreateDirectoryA(UnicodeStringToMultiByte(path) , lpsecattribs);
}
#endif

BOOL WINAPI CreateDirectoryA( LPCSTR path,
                              LPSECURITY_ATTRIBUTES lpsecattribs ) {
  if (!path || !*path) {
    SetLastError(ERROR_PATH_NOT_FOUND);
    return FALSE;
  }

  char name[MAX_PATHNAME_LEN];
  nameWindowToUnixA(path,name);
  TRACEN((printf("mkdir(%s)\n",name)))

  if (mkdir( name, 0777 ) == -1) {
    switch (errno) {
    case EEXIST:
      SetLastError(ERROR_ALREADY_EXISTS);
      break;
    case ENOSPC:
      SetLastError(ERROR_DISK_FULL);
      break;
    default:
      FILE_SetDosError();
      break;
    }
    return FALSE;
  }
  return TRUE;
}

#ifdef _UNICODE
BOOL WINAPI MoveFileW( LPCWSTR fn1, LPCWSTR fn2) {
  return MoveFileA(UnicodeStringToMultiByte(fn1),UnicodeStringToMultiByte(fn2));
}
#endif

BOOL WINAPI MoveFileA( LPCSTR fn1, LPCSTR fn2 ) {
  char n1[MAX_PATHNAME_LEN];
  char n2[MAX_PATHNAME_LEN];
  nameWindowToUnixA(fn1,n1);
  nameWindowToUnixA(fn2,n2);

  TRACEN((printf("MoveFileW(%s,%s)\n",n1,n2)))

  return (rename(n1,n2) == 0);
}

#ifdef _UNICODE
BOOL WINAPI RemoveDirectoryW( LPCWSTR path ) {
  return RemoveDirectoryA(UnicodeStringToMultiByte(path));
}
#endif

BOOL WINAPI RemoveDirectoryA(LPCSTR path) {
  if (!path || !*path) {
    SetLastError(ERROR_PATH_NOT_FOUND);
    return FALSE;
  }

  char name[MAX_PATHNAME_LEN];
  nameWindowToUnixA(path,name);
  TRACEN((printf("RemoveDirectoryA(%s)\n",name)))

  if (rmdir( name ) != 0) {
    FILE_SetDosError();
    return FALSE;
  }
  return TRUE;
}

BOOL WINAPI DeleteFileA(LPCSTR lpFileName) {
  char name[MAX_PATHNAME_LEN];
  BOOL ret;
  nameWindowToUnixA(lpFileName,name);

  if (remove
      (name) == 0) ret = TRUE;
  else
    ret = FALSE;

  /* printf("DeleteFileA(%s)=%d\n",name,(int)ret); */
  return ret;
}

#ifdef _UNICODE
BOOL WINAPI DeleteFileW(LPCWSTR lpFileName) {
	return DeleteFileA(UnicodeStringToMultiByte(lpFileName));
}
#endif


DWORD WINAPI GetFullPathNameA( LPCSTR name, DWORD len, LPSTR buffer,
                               LPSTR *lastpart ) {
  if ((name[0] == '\\') || (name[0] == '/')) {
    DWORD ret = strlen(name)+2;
    if (ret >= len) {
      TRACEN((printf("GetFullPathNameA(%s,%d,)=0000 (case 0)\n",name, (int)len)))
      return 0;
    }
    strcpy(buffer,"c:");
    strcat(buffer,name);

    *lastpart=buffer;
    char *ptr=buffer;
    while (*ptr) {
      if ((*ptr == '/') || (*ptr == '\\'))
        *lastpart=ptr+1;
      ptr++;
    }
    TRACEN((printf("GetFullPathNameA(%s,%d,%s,%s)=%d\n",name, (int)len,buffer, *lastpart,(int)ret)))
    return ret;
  }
  if (isascii(name[0]) && (name[1] == ':')) {
    DWORD ret = strlen(name);
    if (ret >= len) {
      TRACEN((printf("GetFullPathNameA(%s,%d,)=0000 (case 1)\n",name, (int)len)))
      return 0;
    }
    strcpy(buffer,name);

    *lastpart=buffer;
    char *ptr=buffer;
    while (*ptr) {
      if ((*ptr == '/') || (*ptr == '\\'))
        *lastpart=ptr+1;
      ptr++;
    }
    TRACEN((printf("GetFullPathNameA(%s,%d,%s,%s)=%d\n",name, (int)len,buffer, *lastpart,(int)ret)))
    return ret;
  }

  // name is a relative pathname.
  //
  if (len < 2) {
    TRACEN((printf("GetFullPathNameA(%s,%d,)=0000 (case 1)\n",name, (int)len)))
    return 0;
  }

  DWORD ret = 0;
  char begin[MAX_PATHNAME_LEN];
  DWORD begin_len = GetCurrentDirectoryA(MAX_PATHNAME_LEN,begin);
  if (begin_len >= 1) {
    snprintf(buffer,len,"%s\\%s",begin,name);
    buffer[len-1]=0;
    ret = strlen(buffer);
    *lastpart=buffer + begin_len + 1;
    TRACEN((printf("GetFullPathNameA(%s,%d,%s,%s)=%d\n",name, (int)len,buffer, *lastpart,(int)ret)))
  } else {
    ret = 0;
    TRACEN((printf("GetFullPathNameA(%s,%d,)=0000 (case 2)\n",name, (int)len)))
  }
  return ret;
}

UINT WINAPI GetTempFileNameA( LPCSTR path, LPCSTR prefix, UINT unique, LPSTR buffer ) {
  static UINT num;

  if (unique)
    num = unique;
  else
    num = (UINT)getpid();

  sprintf(buffer,"%s%s%d.tmp",path,prefix,num);

  TRACEN((printf("GetTempFileNameA(%s,%s,%d,%s)=%d\n",path,prefix,unique,buffer,num)))
  return num;
}

UINT WINAPI GetWindowsDirectoryA(LPSTR path,UINT len) {
  static const char *windowsDir = "c:\\tmp";

  size_t ret_len = strlen(windowsDir);

  strncpy(path,windowsDir,len);

  return ret_len;
}

DWORD WINAPI GetTempPathA(DWORD len ,LPSTR path) {
  static const char *tmpDir = "c:\\tmp\\"; // final '\\' is needed

  size_t ret_len = strlen(tmpDir);

  strncpy(path,tmpDir,len);

  return ret_len;

}

DWORD WINAPI GetCurrentDirectoryA(DWORD len,LPSTR path) {
  if (len >= 2) {
    path[0]='c';
    path[1]=':';
    char * cret = getcwd(path+2, len - 3);
    if (cret) {
      /* transform separators */
      char *ptr = path;
      while (*ptr) {
        if (*ptr == '/')
          *ptr = '\\';
        ptr++;
      }
      return strlen(path);
    }
    return 0;
  }
  return 0;
}

BOOL WINAPI SetFileAttributesA(LPCSTR lpFileName, DWORD attributes)  // FIXME
{
  char name[MAX_PATHNAME_LEN];
  nameWindowToUnixA(lpFileName,name);

  FILE *file = fopen(name,"rb");
  if (file) {
    TRACEN((printf("SetFileAttributesW(%s,%d) : TRUE\n",name,attributes)))
    fclose(file);
    return TRUE;
  }
  TRACEN((printf("SetFileAttributesW(%s,%d) : FALSE\n",name,attributes)))
  return FALSE;
}


int WINAPI CompareStringA(LCID lcid,DWORD style,LPCSTR str1,int len1,LPCSTR str2,int len2) {
  INT ret, len;

  if (!str1 || !str2) {
    SetLastError(ERROR_INVALID_PARAMETER);
    return 0;
  }

  return CompareStringW(lcid, style, MultiByteToUnicodeString(str1), len1, MultiByteToUnicodeString(str2), len2);
}

LPSTR WINAPI CharNextA( LPCSTR ptr ) {
  if (!*ptr)
    return (LPSTR)ptr;
  wchar_t wc;
  size_t len  = mbrtowc(&wc,ptr,MB_LEN_MAX,0); 
  if (len >= 1) return (LPSTR)(ptr + len);
  printf("INTERNAL ERROR - CharNextA\n");
  exit(EXIT_FAILURE);
}

