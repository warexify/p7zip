#include "StdAfx.h"

#ifdef _UNICODE
#include "../Common/StringConvert.h"
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#ifdef __CYGWIN__
/* basename from glibc 2.3.1 */
char * basename (const char *filename)
{
  char *p = strrchr (filename, '/');
  return p ? p + 1 : (char *) filename;
}
/* dirname from dietlibc 0.25 */
static char *dot=".";
#define SLASH '/'
#define EOL (char)0
char *dirname(char *path)
{
  char *c;
  if ( path  == NULL ) return dot;
  for(;;) {
    if ( !(c=strrchr(path,SLASH)) ) return dot; /* no slashes */
    if ( c[1]==EOL && c!=path ) {   /* remove trailing slashes */
      while ( *c==SLASH && c!=path ) *c--=EOL;
      continue;
    }
    if ( c!=path )
      while ( *c==SLASH ) *c--=EOL; /* slashes in the middle */
    else
      path[1]=EOL;                  /* slash is first symbol */
    return path;
  }
}
#else
#include <libgen.h> // dirname
#endif


#include "myPrivate.h"

// #define TRACEN(u) u;
#define TRACEN(u)  /* */

typedef struct {
#define IDENT_DIR_HANDLER 0x12345678
  int IDENT;
  DIR *dirp;
  char *pattern;
  char *directory;
}
t_st_dir;

static void remplirWIN32_FIND_DATA(WIN32_FIND_DATA *lpFindData,const char *rep,const char *nom) {
  struct stat stat_info;
  char filename[MAX_PATHNAME_LEN];
  int ret;
  snprintf(filename,MAX_PATHNAME_LEN,"%s/%s",rep,nom);
  filename[MAX_PATHNAME_LEN-1] = 0;
  ret = stat(filename,&stat_info);
  if (ret != 0) {
    printf("remplirWIN32_FIND_DATA(%s) : ERROR !?\n",filename);
    exit(EXIT_FAILURE);
  }
  memset(lpFindData,0,sizeof(*lpFindData));

  /* FIXME : FILE_ATTRIBUTE_HIDDEN */
  if (S_ISDIR(stat_info.st_mode))
    lpFindData->dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
  else
    lpFindData->dwFileAttributes = FILE_ATTRIBUTE_ARCHIVE;
  if (!(stat_info.st_mode & S_IWUSR))
    lpFindData->dwFileAttributes |= FILE_ATTRIBUTE_READONLY;

  RtlSecondsSince1970ToTime( stat_info.st_mtime, (LARGE_INTEGER *)&lpFindData->ftCreationTime );
  RtlSecondsSince1970ToTime( stat_info.st_mtime, (LARGE_INTEGER *)&lpFindData->ftLastWriteTime );
  RtlSecondsSince1970ToTime( stat_info.st_atime, (LARGE_INTEGER *)&lpFindData->ftLastAccessTime );

  lpFindData->nFileSizeHigh = 0;
  lpFindData->nFileSizeLow  = 0;
  if (!S_ISDIR(stat_info.st_mode)) {
    lpFindData->nFileSizeHigh = stat_info.st_size >> 32;
    lpFindData->nFileSizeLow  = stat_info.st_size & 0xffffffff;
  }
#ifdef _UNICODE
  UString ustr = MultiByteToUnicodeString(AString(nom));
  wcsncpy(lpFindData->cFileName,&ustr[0],MAX_PATH);
  lpFindData->cAlternateFileName[0] = 0;
#else
  strncpy(lpFindData->cFileName,nom,MAX_PATH);
  lpFindData->cAlternateFileName[0] = 0;
#endif
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

HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, WIN32_FIND_DATA *lpFindData ) {
  char cb[MAX_PATHNAME_LEN];
  char cd[MAX_PATHNAME_LEN];
  char *b,*d;
  t_st_dir *retour;
  nameWindowToUnixA(lpFileName,cb);
  strcpy(cd,cb);
  b = basename(cb);
  d = dirname(cd);

  TRACEN((printf("FindFirstFileA : %s (dirname=%s,pattern=%s)\n",lpFileName,d,b)))

  if (!lpFileName) {
    SetLastError(ERROR_PATH_NOT_FOUND);
    return INVALID_HANDLE_VALUE;
  }


  retour = (t_st_dir *)calloc(1,sizeof(t_st_dir));
  if (retour == 0) {
    SetLastError( ERROR_NO_MORE_FILES );
    return INVALID_HANDLE_VALUE;
  }

  retour->IDENT = IDENT_DIR_HANDLER;
  retour->dirp = opendir(d);
  TRACEN((printf("FindFirstFileA : dirp=%p\n",retour->dirp)))
  retour->directory = strdup(d);
  retour->pattern = strdup(b);

  if (retour->dirp) {
    struct dirent *dp;
    while ((dp = readdir(retour->dirp)) != NULL) {
      if (filtre_pattern(dp->d_name,retour->pattern,0) == 1) {
        remplirWIN32_FIND_DATA(lpFindData,retour->directory,dp->d_name);
        TRACEN((printf("FindFirstFileA : ret_handle=%ld\n",(unsigned long)retour)))
        return (HANDLE)retour;
      }
    }
  }
  free(retour->directory);
  free(retour->pattern);
  TRACEN((printf("FindFirstFileA : closedir(dirp=%p)\n",retour->dirp)))
  closedir(retour->dirp);
  free(retour);
  SetLastError( ERROR_NO_MORE_FILES );
  return INVALID_HANDLE_VALUE;
}

BOOL WINAPI FindNextFileA( HANDLE handle, WIN32_FIND_DATA  *lpFindData) {
  t_st_dir *retour = (t_st_dir *)handle;

  if ((handle == 0) || (handle == INVALID_HANDLE_VALUE) || (retour->IDENT != IDENT_DIR_HANDLER)) {
    SetLastError( ERROR_INVALID_HANDLE );
    return FALSE;
  }

  if (retour->dirp) {
    struct dirent *dp;
    while ((dp = readdir(retour->dirp)) != NULL) {
      if (filtre_pattern(dp->d_name,retour->pattern,0) == 1) {
        remplirWIN32_FIND_DATA(lpFindData,retour->directory,dp->d_name);
        return TRUE;
      }
    }
  }

  SetLastError( ERROR_NO_MORE_FILES );
  return FALSE;
}

BOOL WINAPI FindClose( HANDLE handle ) {
  TRACEN((printf("FindClose(%ld)\n",(unsigned long)handle)))
  if (handle != INVALID_HANDLE_VALUE) {
    t_st_dir *retour = (t_st_dir *)handle;
    if ((retour) && (retour->IDENT == IDENT_DIR_HANDLER)) {
      free(retour->directory);
      free(retour->pattern);
      TRACEN((printf("FindClose : closedir(dirp=%p)\n",retour->dirp)))
      closedir(retour->dirp);
      free(retour);
      return TRUE;
    }
  }
  SetLastError( ERROR_INVALID_HANDLE );
  return FALSE;
}


