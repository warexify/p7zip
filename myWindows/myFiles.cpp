#include "StdAfx.h"

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <Common/String.h>

#include "myPrivate.h"

#include <sys/types.h>
#include <utime.h>

extern BOOLEAN WINAPI RtlTimeToSecondsSince1970( const LARGE_INTEGER *Time, LPDWORD Seconds );

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

static void local_nameWindowToUnixA(LPCSTR lpFileName,char name[MAX_PATHNAME_LEN]) {
  if (strncmp("c:",lpFileName,2) == 0) {
    strcpy(name,lpFileName+2);
  } else {
    strcpy(name,lpFileName);
  }
  TRACEN((printf("local_nameWindowToUnixA: '%s' => '%s'\n",lpFileName,name)))
}



#define IDENT_FILE 0x1234ABEF

class CFileHandlerInternal
{
  public:
   int ident_file;
   int fd;
   AString unix_filename;
};

bool myGetFileLength(t_file_handle hFile,UINT64 &length) {
  TRACEN((printf("myGetFileLength(%p...)\n",hFile)))

  if (    (hFile == FILE_HANDLE_INVALID)
       || (hFile->fd == -1)
       || (hFile->ident_file != IDENT_FILE))
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  off_t pos_cur = lseek(hFile->fd, 0, SEEK_CUR);
  if (pos_cur == (off_t)-1)
    return false;

  off_t pos_end = lseek(hFile->fd, 0, SEEK_END);
  if (pos_end == (off_t)-1)
    return false;

  off_t pos_cur2 = lseek(hFile->fd, pos_cur, SEEK_SET);
  if (pos_cur2 == (off_t)-1)
    return false;

  length = (UINT64)pos_end;

  TRACEN((printf("myGetFileLength(%p.length=%ld)\n",hFile,(long)length)))

  return true;
}

t_file_handle WINAPI myCreateFileA(
  LPCSTR filename,
  DWORD dwDesiredAccess,
  DWORD dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD dwCreationDisposition,
  DWORD dwFlagsAndAttributes) {
  char name[1024];
  local_nameWindowToUnixA(filename,name);

  CFileHandlerInternal * file = new CFileHandlerInternal;

  if (file == 0) {
     SetLastError(ERROR_GEN_FAILURE);
     return FILE_HANDLE_INVALID;
  }
#ifdef O_BINARY
  int   flags = O_BINARY;
#else
  int   flags = 0;
#endif

#ifdef O_LARGEFILE
  flags |= O_LARGEFILE;
#endif

 int mode = 0666;

  if (dwDesiredAccess & GENERIC_WRITE) flags |= O_WRONLY;
  if (dwDesiredAccess & GENERIC_READ)  flags |= O_RDONLY;

  switch (dwCreationDisposition)
  {
    case CREATE_NEW    : flags |= O_CREAT | O_EXCL;
      break;
    case CREATE_ALWAYS : flags |= O_CREAT;
      break;
    case OPEN_EXISTING : 
      break;
    case OPEN_ALWAYS   : flags |= O_CREAT;  
      break;
    case TRUNCATE_EXISTING : flags |= O_TRUNC;
      break;
  }

  TRACEN((printf("myCreateFileA flags=%x\n",flags)))

  size_t len = strlen(name);
  if (len >= 4) {
    if (    (tolower((unsigned char)name[len-1]) == 'e')
         && (tolower((unsigned char)name[len-2]) == 'x')
         && (tolower((unsigned char)name[len-3]) == 'e')
         && (name[len-4] == '.') ) {
       mode = 0777;
    }
  }
  
  file->fd = open(name,flags, mode);

  if (file->fd == -1) {
    int save_errno = errno; // save errno before lstat

    delete file;
    file = 0;

    struct stat stat_info;
    int ret = lstat(name,&stat_info);
    if ((ret == 0) && (S_ISLNK(stat_info.st_mode)))
    {
       // FIXME : an invalid symbolic link becomes a sharing violation for 7-zip
       SetLastError(ERROR_SHARING_VIOLATION);
    } else {
       errno = save_errno;
       FILE_SetDosError();
    }
  } else {
    file->ident_file = IDENT_FILE;
    file->unix_filename = name;
  }

  TRACEN((printf("\nTHR 0x%lx : myCreateFileA(%s) %s %s %s %s %s => %d\n",
                 (unsigned long)pthread_self(),name,
                 ((dwDesiredAccess & GENERIC_READ)==GENERIC_READ)?"GENERIC_READ ":"",
                 ((dwDesiredAccess & GENERIC_WRITE)==GENERIC_WRITE)?"GENERIC_WRITE ":"",
                 (!dwDesiredAccess)?"QUERY_ACCESS ":"",
                 ((dwShareMode & FILE_SHARE_READ)==FILE_SHARE_READ)?"FILE_SHARE_READ ":"",
                 /* ((dwShareMode & FILE_SHARE_WRITE)==FILE_SHARE_WRITE)?"FILE_SHARE_WRITE ":"",
                  ((dwShareMode & FILE_SHARE_DELETE)==FILE_SHARE_DELETE)?"FILE_SHARE_DELETE ":"", */
                 (dwCreationDisposition ==CREATE_NEW)?"CREATE_NEW":
                 (dwCreationDisposition ==CREATE_ALWAYS)?"CREATE_ALWAYS ":
                 (dwCreationDisposition ==OPEN_EXISTING)?"OPEN_EXISTING ":
                 (dwCreationDisposition ==OPEN_ALWAYS)?"OPEN_ALWAYS ":
                 (dwCreationDisposition ==TRUNCATE_EXISTING)?"TRUNCATE_EXISTING ":"",
                 file->fd)))
  return file;
}

BOOL WINAPI myCloseFile(t_file_handle hFile) {
  if (    (hFile == FILE_HANDLE_INVALID)
       || (hFile->fd == -1)
       || (hFile->ident_file != IDENT_FILE))
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }
  BOOL ret = (close(hFile->fd) == 0);
  delete hFile;
  TRACEN((printf("THR 0x%lx : myCloseFile(%p)=%d\n",(unsigned long)pthread_self(),hFile,(unsigned)ret)))
  if (!ret)
    printf("myCloseFile : errno = %d (%s)\n",errno,strerror(errno));
  return ret;
}

BOOL WINAPI SetFileTime( t_file_handle hFile,
                         const FILETIME *lpCreationTime,
                         const FILETIME *lpLastAccessTime,
                         const FILETIME *lpLastWriteTime )
{
  struct stat  oldbuf;
  struct utimbuf buf;
  int ret;
  if (    (hFile == FILE_HANDLE_INVALID)
       || (hFile->fd == -1)
       || (hFile->ident_file != IDENT_FILE))
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  ret = stat((const char*)(hFile->unix_filename),&oldbuf);
  if (ret == 0) {
    buf.actime  = oldbuf.st_atime;
    buf.modtime = oldbuf.st_mtime;
  } else {
    buf.actime  = buf.modtime = time(0);
  }
  
  if (lpLastAccessTime)
       RtlTimeToSecondsSince1970( (LARGE_INTEGER *) lpLastAccessTime, (DWORD *)&buf.actime );
  if (lpLastWriteTime)
       RtlTimeToSecondsSince1970( (LARGE_INTEGER *) lpLastWriteTime, (DWORD *)&buf.modtime );

  ret = utime((const char *)(hFile->unix_filename), &buf);
  return (ret == 0);
}

BOOL WINAPI WriteFile( t_file_handle hFile, LPCVOID buffer, DWORD bytesToWrite,
                       LPDWORD bytesWritten, LPOVERLAPPED overlapped ) {
  TRACEN((printf("THR 0x%lx : WriteFile(%p...)\n",(unsigned long)pthread_self(),hFile)))

  if (    (hFile == FILE_HANDLE_INVALID)
       || (hFile->fd == -1)
       || (hFile->ident_file != IDENT_FILE))
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  ssize_t  ret = write  (hFile->fd,buffer, bytesToWrite);

  if (ret != -1) {
    *bytesWritten = ret;
    TRACEN((printf("WriteFile(%p...)=TRUE\n",hFile)))
    return TRUE;
  }
  *bytesWritten =0;
  TRACEN((printf("WriteFile(%p...)=FALSE\n",hFile)))
  return FALSE;
}

BOOL WINAPI SetEndOfFile(t_file_handle hFile) {
  BOOL ret = FALSE;

  if (    (hFile == FILE_HANDLE_INVALID)
       || (hFile->fd == -1)
       || (hFile->ident_file != IDENT_FILE))
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  off_t pos_cur = lseek(hFile->fd, 0, SEEK_CUR);
  if (pos_cur != (off_t)-1) {
    ret =  (ftruncate(hFile->fd, pos_cur) == 0);
  }
  TRACEN((printf("SetEndOfFile(%p...)=%d\n",hFile,(unsigned)ret)))

  return ret;
}

BOOL WINAPI ReadFile( t_file_handle hFile, LPVOID buffer, DWORD bytesToRead,
                      LPDWORD bytesRead, LPOVERLAPPED overlapped ) {

  if (    (hFile == FILE_HANDLE_INVALID)
       || (hFile->fd == -1)
       || (hFile->ident_file != IDENT_FILE))
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  if (bytesToRead == 0) {
    *bytesRead =0;
    TRACEN((printf("ReadFile(%p,,0)=TRUE\n",hFile)))
    return TRUE;
  }
  ssize_t  ret = read  (hFile->fd,buffer,bytesToRead);

  if (ret != -1) {
    *bytesRead = ret;
    TRACEN((printf("ReadFile(%p,,)=TRUE\n",hFile)))
    return TRUE;
  }
  *bytesRead =0;
  TRACEN((printf("ReadFile(%p,,)=FALSE\n",hFile)))
  return FALSE;
}

bool myFileSeek( t_file_handle hFile, INT64 distanceToMove, DWORD moveMethod, UINT64 &newPosition) {
  int direction;
  bool ret = true;

  if (    (hFile == FILE_HANDLE_INVALID)
       || (hFile->fd == -1)
       || (hFile->ident_file != IDENT_FILE))
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  if      (moveMethod == FILE_BEGIN)
    direction = SEEK_SET;
  else if (moveMethod == FILE_CURRENT)
    direction = SEEK_CUR;
  else if (moveMethod == FILE_END)
    direction = SEEK_END;
  else
    ret = false;

  if (ret) {
    off_t pos = (off_t)distanceToMove;

    off_t newpos = lseek(hFile->fd,pos,direction);

    if (newpos == ((off_t)-1)) {
      ret = false;
    } else {
      newPosition = (UINT64)newpos;
    }
  }
  TRACEN((printf("myFileSeek(%p,,)=%d\n",hFile,(unsigned)ret)))

  return ret;
}

