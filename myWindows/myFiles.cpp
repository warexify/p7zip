#include "StdAfx.h"

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string>

#include "myPrivate.h"

#include <sys/types.h>
#include <utime.h>

extern BOOLEAN WINAPI RtlTimeToSecondsSince1970( const LARGE_INTEGER *Time, LPDWORD Seconds );

// #define TRACEN(u) u;
#define TRACEN(u)  /* */

#define IDENT_FILE 0x1234ABEF

class CFileHandlerInternal
{
  public:
   int ident_file;
   int fd;
   std::string unix_filename;
};

bool myGetFileLength(t_file_handle hFile,UINT64 &length) {
  TRACEN((printf("myGetFileLength(%d...)\n",hFile)))

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

  TRACEN((printf("myGetFileLength(%d.length=%ld)\n",hFile,(long)length)))

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
  nameWindowToUnixA(filename,name);

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

  if (dwDesiredAccess & GENERIC_WRITE) flags |= O_WRONLY;
  if (dwDesiredAccess & GENERIC_READ)  flags |= O_RDONLY;

  switch (dwCreationDisposition)
  {
    case CREATE_NEW : 
      break;
    case CREATE_ALWAYS : flags |= O_CREAT;
      break;
    case OPEN_EXISTING: 
      break;
    case OPEN_ALWAYS  : flags |= O_CREAT;  
      break;
    case TRUNCATE_EXISTING : flags |= O_TRUNC;
      break;
  }

  file->fd = open(name,flags, 0666);

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

  if (file->fd == -1) {
    printf("myCreateFileA : errno = %d (%s)\n",errno,strerror(errno));
    delete file;
    file = 0;
  } else {
    file->ident_file = IDENT_FILE;
    file->unix_filename = name;
  }

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
  TRACEN((printf("THR 0x%lx : myCloseFile(%d)=%d\n",(unsigned long)pthread_self(),hFile,(unsigned)ret)))
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

  ret = stat(hFile->unix_filename.c_str(),&oldbuf);
  if (ret == 0) {
    buf.actime  = oldbuf.st_atime;
    buf.modtime = oldbuf.st_mtime;
  } else {
    buf.actime  = buf.modtime = time(0);
  }
  
  if (lpLastAccessTime)
       RtlTimeToSecondsSince1970( (PLARGE_INTEGER) lpLastAccessTime, (DWORD *)&buf.actime );
  if (lpLastWriteTime)
       RtlTimeToSecondsSince1970( (PLARGE_INTEGER) lpLastWriteTime, (DWORD *)&buf.modtime );

  ret = utime(hFile->unix_filename.c_str(), &buf);
  return (ret == 0);
}

BOOL WINAPI WriteFile( t_file_handle hFile, LPCVOID buffer, DWORD bytesToWrite,
                       LPDWORD bytesWritten, LPOVERLAPPED overlapped ) {
  TRACEN((printf("THR 0x%lx : WriteFile(%d...)\n",(unsigned long)pthread_self(),hFile)))

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
    TRACEN((printf("WriteFile(%d...)=TRUE\n",hFile)))
    return TRUE;
  }
  *bytesWritten =0;
  TRACEN((printf("WriteFile(%d...)=FALSE\n",hFile)))
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
  TRACEN((printf("SetEndOfFile(%d...)=%d\n",hFile,(unsigned)ret)))

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
    TRACEN((printf("ReadFile(%d,,0)=TRUE\n",hFile)))
    return TRUE;
  }
  ssize_t  ret = read  (hFile->fd,buffer,bytesToRead);

  if (ret != -1) {
    *bytesRead = ret;
    TRACEN((printf("ReadFile(%d,,)=TRUE\n",hFile)))
    return TRUE;
  }
  *bytesRead =0;
  TRACEN((printf("ReadFile(%d,,)=FALSE\n",hFile)))
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
  TRACEN((printf("myFileSeek(%d,,)=%d\n",hFile,(unsigned)ret)))

  return ret;
}

