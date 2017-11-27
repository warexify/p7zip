// Windows/FileIO.cpp

#include "StdAfx.h"

#include "FileIO.h"
#include "Defs.h"
#ifndef _UNICODE
#include "../Common/StringConvert.h"
#endif

#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NEED_NAME_WINDOWS_TO_UNIX
#include "myPrivate.h"

#include <sys/types.h>
#include <utime.h>

extern BOOLEAN WINAPI RtlTimeToSecondsSince1970( const LARGE_INTEGER *Time, DWORD *Seconds );

namespace NWindows {
namespace NFile {
namespace NIO {

CFileBase::~CFileBase()
{
  Close();
}

bool CFileBase::Create(LPCTSTR filename, DWORD dwDesiredAccess,
    DWORD dwShareMode, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes)
{
  Close();
  
  const char * name = nameWindowToUnix(filename);

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
    case CREATE_NEW    : flags |= O_CREAT | O_EXCL; break;
    case CREATE_ALWAYS : flags |= O_CREAT;          break;
    case OPEN_EXISTING :                            break;
    case OPEN_ALWAYS   : flags |= O_CREAT;          break;
    // case TRUNCATE_EXISTING : flags |= O_TRUNC;      break;
  }

  size_t len = strlen(name);
  if (len >= 4) {
    if (    (tolower((unsigned char)name[len-1]) == 'e')
         && (tolower((unsigned char)name[len-2]) == 'x')
         && (tolower((unsigned char)name[len-3]) == 'e')
         && (name[len-4] == '.') ) {
       mode = 0777;
    }
  }
  
  _fd = open(name,flags, mode);

  if (_fd == -1) {
    /* an invalid symbolic link => errno == ENOENT */
    return false;
  } else {
    _unix_filename = name;
  }

  return true;
}

#ifndef _UNICODE
bool CFileBase::Create(LPCWSTR fileName, DWORD desiredAccess,
    DWORD shareMode, DWORD creationDisposition, DWORD flagsAndAttributes)
{
  Close();
    return Create(UnicodeStringToMultiByte(fileName, CP_ACP), 
      desiredAccess, shareMode, creationDisposition, flagsAndAttributes);
}
#endif

bool CFileBase::Close()
{
  if(_fd == -1)
    return true;
  int ret = ::close(_fd);
  if (ret == 0) {
    _fd = -1;
    return true;
  }
  return false;
}

bool CFileBase::GetLength(UINT64 &length) const
{
  if (_fd == -1)
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  off_t pos_cur = ::lseek(_fd, 0, SEEK_CUR);
  if (pos_cur == (off_t)-1)
    return false;

  off_t pos_end = ::lseek(_fd, 0, SEEK_END);
  if (pos_end == (off_t)-1)
    return false;

  off_t pos_cur2 = ::lseek(_fd, pos_cur, SEEK_SET);
  if (pos_cur2 == (off_t)-1)
    return false;

  length = (UINT64)pos_end;

  return true;
}

bool CFileBase::Seek(INT64 distanceToMove, DWORD moveMethod, UINT64 &newPosition) const
{
  if (_fd == -1)
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  bool ret = true;

  off_t pos = (off_t)distanceToMove;

  off_t newpos = ::lseek(_fd,pos,moveMethod);

  if (newpos == ((off_t)-1)) {
    ret = false;
  } else {
    newPosition = (UINT64)newpos;
  }

  return ret;
}

bool CFileBase::Seek(UINT64 position, UINT64 &newPosition)
{
  return Seek(position, FILE_BEGIN, newPosition);
}

/////////////////////////
// CInFile

bool CInFile::Open(LPCTSTR fileName, DWORD shareMode, 
    DWORD creationDisposition,  DWORD flagsAndAttributes)
{
  return Create(fileName, GENERIC_READ, shareMode, 
      creationDisposition, flagsAndAttributes);
}

bool CInFile::Open(LPCTSTR fileName)
{
  return Open(fileName, FILE_SHARE_READ, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);
}

#ifndef _UNICODE
bool CInFile::Open(LPCWSTR fileName, DWORD shareMode, 
    DWORD creationDisposition,  DWORD flagsAndAttributes)
{
  return Create(fileName, GENERIC_READ, shareMode, 
      creationDisposition, flagsAndAttributes);
}

bool CInFile::Open(LPCWSTR fileName)
{
  return Open(fileName, FILE_SHARE_READ, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);
}
#endif

bool CInFile::Read(void *buffer, UINT32 bytesToRead, UINT32 &bytesRead)
{
  if (_fd == -1)
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  if (bytesToRead == 0) {
    bytesRead =0;
    return TRUE;
  }
  ssize_t  ret;
  do {
    ret = read(_fd,buffer,bytesToRead);
  } while (ret < 0 && (errno == EINTR));

  if (ret != -1) {
    bytesRead = ret;
    return TRUE;
  }
  bytesRead =0;
  return FALSE;
}

/////////////////////////
// COutFile

bool COutFile::Open(LPCTSTR fileName, DWORD shareMode, 
    DWORD creationDisposition, DWORD flagsAndAttributes)
{
  return CFileBase::Create(fileName, GENERIC_WRITE, shareMode, 
      creationDisposition, flagsAndAttributes);
}

static inline DWORD GetCreationDisposition(bool createAlways)
  {  return createAlways? CREATE_ALWAYS: CREATE_NEW; }

bool COutFile::Open(LPCTSTR fileName, DWORD creationDisposition)
{
  return Open(fileName, FILE_SHARE_READ, 
      creationDisposition, FILE_ATTRIBUTE_NORMAL);
}

bool COutFile::Create(LPCTSTR fileName, bool createAlways)
{
  return Open(fileName, GetCreationDisposition(createAlways));
}

#ifndef _UNICODE

bool COutFile::Open(LPCWSTR fileName, DWORD shareMode, 
    DWORD creationDisposition, DWORD flagsAndAttributes)
{
  return CFileBase::Create(fileName, GENERIC_WRITE, shareMode, 
      creationDisposition, flagsAndAttributes);
}

bool COutFile::Open(LPCWSTR fileName, DWORD creationDisposition)
{
  return Open(fileName, FILE_SHARE_READ, 
      creationDisposition, FILE_ATTRIBUTE_NORMAL);
}

bool COutFile::Create(LPCWSTR fileName, bool createAlways)
{
  return Open(fileName, GetCreationDisposition(createAlways));
}

#endif

bool COutFile::SetTime(const FILETIME *lpCreationTime,
  const FILETIME *lpLastAccessTime, const FILETIME *lpLastWriteTime)
{
  LARGE_INTEGER  ltime;
  struct stat    oldbuf;
  struct utimbuf buf;
  DWORD dw;
  bool ret;
  if (_fd == -1) {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  ret = stat((const char*)(_unix_filename),&oldbuf);
  if (ret == 0) {
    buf.actime  = oldbuf.st_atime;
    buf.modtime = oldbuf.st_mtime;
  } else {
    buf.actime  = buf.modtime = time(0);
  }
  
  if (lpLastAccessTime) {
     ltime.QuadPart = lpLastAccessTime->dwHighDateTime;
     ltime.QuadPart = (ltime.QuadPart << 32) | lpLastAccessTime->dwLowDateTime;
     RtlTimeToSecondsSince1970( &ltime, &dw );
     buf.actime = dw;
  }
  if (lpLastWriteTime) {
     ltime.QuadPart = lpLastWriteTime->dwHighDateTime;
     ltime.QuadPart = (ltime.QuadPart << 32) | lpLastWriteTime->dwLowDateTime;
     RtlTimeToSecondsSince1970( &ltime, &dw );
     buf.modtime = dw;
  }

  ret = utime((const char *)(_unix_filename), &buf);
  if (ret == 0) return true;
  return false;
}

bool COutFile::SetLastWriteTime(const FILETIME *lastWriteTime)
{
  return SetTime(NULL, NULL, lastWriteTime);
}

bool COutFile::Write(const void *buffer, UINT32 bytesToWrite, UINT32 &bytesWritten)
{
  if (_fd == -1)
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  ssize_t  ret;
  do {
    ret = write(_fd,buffer, bytesToWrite);
  } while (ret < 0 && (errno == EINTR));

  if (ret != -1) {
    bytesWritten = ret;
    return TRUE;
  }
  bytesWritten =0;
  return FALSE;
}

bool COutFile::SetEndOfFile()
{
  if (_fd == -1)
  {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  bool bret = false;

  off_t pos_cur = lseek(_fd, 0, SEEK_CUR);
  if (pos_cur != (off_t)-1) {
    int iret = ftruncate(_fd, pos_cur);
    if (iret == 0) bret = true;
  }

  return bret;
}

bool COutFile::SetLength(UINT64 length)
{
  UINT64 newPosition;
  if(!Seek(length, newPosition))
    return false;
  if(newPosition != length)
    return false;
  return SetEndOfFile();
}

}}}
