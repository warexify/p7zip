// Windows/FileIO.cpp

#include "StdAfx.h"

#include "FileIO.h"
#include "Defs.h"
#ifndef _UNICODE
#include "../Common/StringConvert.h"
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


namespace NWindows {
namespace NFile {
namespace NIO {

CFileBase::~CFileBase()
{
  Close();
}

bool CFileBase::Create(LPCTSTR fileName, DWORD desiredAccess,
    DWORD shareMode, DWORD creationDisposition, DWORD flagsAndAttributes)
{
  Close();
  _handle = ::myCreateFile(fileName, desiredAccess, shareMode, 
      (LPSECURITY_ATTRIBUTES)NULL, creationDisposition, 
      flagsAndAttributes);
  _fileIsOpen = _handle != FILE_HANDLE_INVALID;
  return _fileIsOpen;
}

#ifndef _UNICODE
bool CFileBase::Create(LPCWSTR fileName, DWORD desiredAccess,
    DWORD shareMode, DWORD creationDisposition, DWORD flagsAndAttributes)
{
  Close();
    return Create(UnicodeStringToMultiByte(fileName, ::AreFileApisANSI() ? CP_ACP : CP_OEMCP), 
      desiredAccess, shareMode, creationDisposition, flagsAndAttributes);
}
#endif

bool CFileBase::Close()
{
  if(!_fileIsOpen)
    return true;
  bool result = BOOLToBool(::myCloseFile(_handle));
  _fileIsOpen = !result;
  return result;
}

bool CFileBase::GetLength(UINT64 &length) const
{
	return myGetFileLength(_handle,length);
/*	
  DWORD sizeHigh;
  DWORD sizeLow = ::GetFileSize(_handle, &sizeHigh);
  if(sizeLow == 0xFFFFFFFF)
    if(::GetLastError() != NO_ERROR )
      return false;
  length = (((UINT64)sizeHigh) << 32) + sizeLow;
  return true;
*/
}

bool CFileBase::Seek(INT64 distanceToMove, DWORD moveMethod, UINT64 &newPosition) const
{
  return myFileSeek(_handle,distanceToMove,moveMethod,newPosition);
	/*
  LARGE_INTEGER *pointer = (LARGE_INTEGER *)&distanceToMove;
  pointer->LowPart = ::SetFilePointer(_handle, pointer->LowPart, 
      &pointer->HighPart, moveMethod);
  if (pointer->LowPart == 0xFFFFFFFF)
    if(::GetLastError() != NO_ERROR) 
      return false;
  newPosition = *((UINT64 *)pointer);
  return true;
  */
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

bool CInFile::Read(void *data, UINT32 size, UINT32 &processedSize)
{
  return BOOLToBool(::ReadFile(_handle, data, size, 
      (DWORD *)&processedSize, NULL));
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

bool COutFile::SetTime(const FILETIME *creationTime,
  const FILETIME *lastAccessTime, const FILETIME *lastWriteTime)
{
  return BOOLToBool(::SetFileTime(_handle, creationTime,
      lastAccessTime, lastWriteTime));
}

bool COutFile::SetLastWriteTime(const FILETIME *lastWriteTime)
{
  return SetTime(NULL, NULL, lastWriteTime);
}

bool COutFile::Write(const void *data, UINT32 size, UINT32 &processedSize)
{
  return BOOLToBool(::WriteFile(_handle, data, size, 
      (DWORD *)&processedSize, NULL));
}

bool COutFile::SetEndOfFile()
{
  return BOOLToBool(::SetEndOfFile(_handle));
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
