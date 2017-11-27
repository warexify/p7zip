#include "StdAfx.h"

#include "Common/String.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

extern void my_windows_split_path(const AString &p_path, AString &dir , AString &base);


#include "myPrivate.h"

// #define TRACEN(u) u;
#define TRACEN(u)  /* */

static void FILE_SetDosError(void) {
  int save_errno = errno;
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
}

typedef struct {
#define IDENT_DIR_HANDLER 0x12345678
  int IDENT;
  DIR *dirp;
  AString pattern;
  AString directory;
}
t_st_dir;

static int fillin_WIN32_FIND_DATA(WIN32_FIND_DATA *lpFindData,const char *rep,const char *nom) {
  struct stat stat_info;
  char filename[MAX_PATHNAME_LEN];
  int ret;
  snprintf(filename,MAX_PATHNAME_LEN,"%s/%s",rep,nom);
  filename[MAX_PATHNAME_LEN-1] = 0;
  ret = stat(filename,&stat_info);  // FIXED lstat
  if (ret != 0) {
    FILE_SetDosError();
    TRACEN((printf("fillin_WIN32_FIND_DATA : %s\n",filename)))
    return ret;
  }
  memset(lpFindData,0,sizeof(*lpFindData));

  /* FIXME : FILE_ATTRIBUTE_HIDDEN */
  if (S_ISDIR(stat_info.st_mode))
    lpFindData->dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
  else
    lpFindData->dwFileAttributes = FILE_ATTRIBUTE_ARCHIVE;
  if (!(stat_info.st_mode & S_IWUSR))
    lpFindData->dwFileAttributes |= FILE_ATTRIBUTE_READONLY;

  RtlSecondsSince1970ToFileTime( stat_info.st_mtime, &lpFindData->ftCreationTime );
  RtlSecondsSince1970ToFileTime( stat_info.st_mtime, &lpFindData->ftLastWriteTime );
  RtlSecondsSince1970ToFileTime( stat_info.st_atime, &lpFindData->ftLastAccessTime );

  lpFindData->nFileSizeHigh = 0;
  lpFindData->nFileSizeLow  = 0;
  if (!S_ISDIR(stat_info.st_mode)) {
    lpFindData->nFileSizeHigh = stat_info.st_size >> 32;
    lpFindData->nFileSizeLow  = stat_info.st_size & 0xffffffff;
  }
  if (S_ISLNK(stat_info.st_mode)) {
    struct stat stat_info2;
    if (stat(filename,&stat_info2) == 0) {
       lpFindData->nFileSizeHigh = stat_info2.st_size >> 32;
       lpFindData->nFileSizeLow  = stat_info2.st_size & 0xffffffff;
    }
  }
  strncpy(lpFindData->cFileName,nom,MAX_PATH);
  lpFindData->cAlternateFileName[0] = 0;
  return 0;
}

static int filtre_pattern(const char *string , const char *pattern , int flags_nocase) {
  if ((string == 0) || (*string==0)) {
    if (pattern == 0)
      return 1;
    while (*pattern=='*')
      ++pattern;
    return (!*pattern);
  }

  switch (*pattern) {
  case '*':
    if (!filtre_pattern(string+1,pattern,flags_nocase))
      return filtre_pattern(string,pattern+1,flags_nocase);
    return 1;
  case 0:
    if (*string==0)
      return 1;
    break;
  case '?':
    return filtre_pattern(string+1,pattern+1,flags_nocase);
  default:
    if (   ((flags_nocase) && (tolower(*pattern)==tolower(*string)))
           || (*pattern == *string)
       ) {
      return filtre_pattern(string+1,pattern+1,flags_nocase);
    }
    break;
  }
  return 0;
}

extern "C" HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, WIN32_FIND_DATA *lpFindData ) {
  char cb[MAX_PATHNAME_LEN];
  t_st_dir *retour;

  if ((!lpFileName) || (lpFileName[0]==0)) {
    SetLastError(ERROR_PATH_NOT_FOUND);
    return INVALID_HANDLE_VALUE;
  }
 
  nameWindowToUnixA(lpFileName,cb);

  AString base,dir;
  my_windows_split_path(cb,dir,base);

  TRACEN((printf("FindFirstFileA : %s (dirname=%s,pattern=%s)\n",lpFileName,(const char *)dir,(const char *)base)))

  retour = new t_st_dir;
  if (retour == 0) {
    SetLastError( ERROR_NO_MORE_FILES );
    return INVALID_HANDLE_VALUE;
  }

  retour->IDENT = IDENT_DIR_HANDLER;
  retour->dirp = opendir((const char *)dir);
  TRACEN((printf("FindFirstFileA : dirp=%p\n",retour->dirp)))
  retour->directory = dir;
  retour->pattern   = base;

  if (retour->dirp) {
    struct dirent *dp;
    while ((dp = readdir(retour->dirp)) != NULL) {
      if (filtre_pattern(dp->d_name,(const char *)retour->pattern,0) == 1) {
        int retf = fillin_WIN32_FIND_DATA(lpFindData,(const char *)retour->directory,dp->d_name);
        if (retf)
        {
           TRACEN((printf("FindFirstFileA : closedir-1(dirp=%p)\n",retour->dirp)))
           closedir(retour->dirp);
           delete retour;
           SetLastError( ERROR_NO_MORE_FILES );
           return INVALID_HANDLE_VALUE;

        }
        TRACEN((printf("FindFirstFileA -%s- ret_handle=%ld\n",dp->d_name,(unsigned long)retour)))
        return (HANDLE)retour;
      }
    }
  }
  TRACEN((printf("FindFirstFileA : closedir-2(dirp=%p)\n",retour->dirp)))
  closedir(retour->dirp);
  delete retour;
  SetLastError( ERROR_NO_MORE_FILES );
  return INVALID_HANDLE_VALUE;
}

extern "C" BOOL WINAPI FindNextFileA( HANDLE handle, WIN32_FIND_DATA  *lpFindData) {
  t_st_dir *retour = (t_st_dir *)handle;

  if ((handle == 0) || (handle == INVALID_HANDLE_VALUE) || (retour->IDENT != IDENT_DIR_HANDLER)) {
    SetLastError( ERROR_INVALID_HANDLE );
    return FALSE;
  }

  if (retour->dirp) {
    struct dirent *dp;
    while ((dp = readdir(retour->dirp)) != NULL) {
      if (filtre_pattern(dp->d_name,(const char *)retour->pattern,0) == 1) {
        int retf = fillin_WIN32_FIND_DATA(lpFindData,(const char *)retour->directory,dp->d_name);
        if (retf)
        {
           TRACEN((printf("FindNextFileA -%s- ret_handle=FALSE (errno=%d)\n",dp->d_name,errno)))
           return FALSE;

        }
        TRACEN((printf("FindNextFileA -%s- ret_handle=%ld\n",dp->d_name,(unsigned long)retour)))
        return TRUE;
      }
    }
  }

  TRACEN((printf("FindNextFileA ret_handle=FALSE (ERROR_NO_MORE_FILES)\n")))
  SetLastError( ERROR_NO_MORE_FILES );
  return FALSE;
}

extern "C" BOOL WINAPI FindClose( HANDLE handle ) {
  TRACEN((printf("FindClose(%ld)\n",(unsigned long)handle)))
  if (handle != INVALID_HANDLE_VALUE) {
    t_st_dir *retour = (t_st_dir *)handle;
    if ((retour) && (retour->IDENT == IDENT_DIR_HANDLER)) {
      TRACEN((printf("FindClose : closedir(dirp=%p)\n",retour->dirp)))
      closedir(retour->dirp);
      delete retour;
      return TRUE;
    }
  }
  SetLastError( ERROR_INVALID_HANDLE );
  return FALSE;
}

