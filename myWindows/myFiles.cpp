#include "StdAfx.h"

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "myPrivate.h"


// #define TRACEN(u) u;
#define TRACEN(u)  /* */

bool myGetFileLength(t_file_handle hFile,UINT64 &length) {
  TRACEN((printf("myGetFileLength(%d...)\n",hFile)))

  off_t pos_cur = lseek(hFile, 0, SEEK_CUR);
  if (pos_cur == (off_t)-1)
    return false;

  off_t pos_end = lseek(hFile, 0, SEEK_END);
  if (pos_end == (off_t)-1)
    return false;

  off_t pos_cur2 = lseek(hFile, pos_cur, SEEK_SET);
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

  t_file_handle file;
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

  file = open(name,flags, 0666);

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
                 file)))

  if (file == -1)
    printf("myCreateFileA : errno = %d (%s)\n",errno,strerror(errno));

  return file;
}

BOOL WINAPI myCloseFile(t_file_handle hFile) {
  BOOL ret = (close(hFile) == 0);
  TRACEN((printf("THR 0x%lx : myCloseFile(%d)=%d\n",(unsigned long)pthread_self(),hFile,(unsigned)ret)))
  if (!ret)
    printf("myCloseFile : errno = %d (%s)\n",errno,strerror(errno));
  return ret;
}

BOOL WINAPI SetFileTime( t_file_handle hFile, // FIXME
                         const FILETIME *lpCreationTime,
                         const FILETIME *lpLastAccessTime,
                         const FILETIME *lpLastWriteTime ) {
  // printf("SetFileTime(%d) : FIXME\n",hFile);
  /*
      #include <sys/types.h>
       #include <utime.h>

       int utime(const char *filename, struct utimbuf *buf);
  struct utimbuf {
                      time_t actime;  // access time
                      time_t modtime; // modification time
              };
        if (lpLastAccessTime)
            RtlTimeToSecondsSince1970( (PLARGE_INTEGER) lpLastAccessTime, (DWORD *)&req->access_time );
        else
            req->access_time = 0; // FIXME
        if (lpLastWriteTime)
            RtlTimeToSecondsSince1970( (PLARGE_INTEGER) lpLastWriteTime, (DWORD *)&req->write_time );
        else
            req->write_time = 0; // FIXME 
  */
  return TRUE;
}

BOOL WINAPI WriteFile( t_file_handle hFile, LPCVOID buffer, DWORD bytesToWrite,
                       LPDWORD bytesWritten, LPOVERLAPPED overlapped ) {
  TRACEN((printf("THR 0x%lx : WriteFile(%d...)\n",(unsigned long)pthread_self(),hFile)))
  ssize_t  ret = write  (hFile,buffer, bytesToWrite);

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

  off_t pos_cur = lseek(hFile, 0, SEEK_CUR);
  if (pos_cur != (off_t)-1) {
    ret =  (ftruncate(hFile, pos_cur) == 0);
  }
  TRACEN((printf("SetEndOfFile(%d...)=%d\n",hFile,(unsigned)ret)))

  return ret;
}

BOOL WINAPI ReadFile( t_file_handle hFile, LPVOID buffer, DWORD bytesToRead,
                      LPDWORD bytesRead, LPOVERLAPPED overlapped ) {

  if (bytesToRead == 0) {
    *bytesRead =0;
    TRACEN((printf("ReadFile(%d,,0)=TRUE\n",hFile)))
    return TRUE;
  }
  size_t  ret = read  (hFile,buffer,bytesToRead);

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

    off_t newpos = lseek(hFile,pos,direction);

    if (newpos == ((off_t)-1)) {
      ret = false;
    } else {
      newPosition = (UINT64)newpos;
    }
  }
  TRACEN((printf("myFileSeek(%d,,)=%d\n",hFile,(unsigned)ret)))

  return ret;
}

