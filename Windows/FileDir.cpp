// Windows/FileDir.cpp

#include "StdAfx.h"

#include "FileDir.h"
#include "FileName.h"
#include "FileFind.h"
#include "Defs.h"
#ifndef _UNICODE
#include "../Common/StringConvert.h"
#endif

namespace NWindows {
namespace NFile {
namespace NDirectory {

#ifndef _UNICODE
static inline UINT GetCurrentCodePage() 
  { return ::AreFileApisANSI() ? CP_ACP : CP_OEMCP; } 
#endif

bool MyGetWindowsDirectory(CSysString &path)
{
  DWORD needLength = ::GetWindowsDirectory(path.GetBuffer(MAX_PATH + 1), MAX_PATH + 1);
  path.ReleaseBuffer();
  return (needLength > 0 && needLength <= MAX_PATH);
}

#ifndef _UNICODE
bool MyGetWindowsDirectory(UString &path)
{
  CSysString sysPath;
  if (!MyGetWindowsDirectory(sysPath))
    return false;
  path = MultiByteToUnicodeString(sysPath, GetCurrentCodePage());
  return true;
}
#endif

#ifndef _UNICODE
bool MySetFileAttributes(LPCWSTR fileName, DWORD fileAttributes)
{  
  return MySetFileAttributes(UnicodeStringToMultiByte(fileName, 
      GetCurrentCodePage()), fileAttributes);
}

bool MyRemoveDirectory(LPCWSTR pathName)
{  
  return MyRemoveDirectory(UnicodeStringToMultiByte(pathName, 
      GetCurrentCodePage()));
}

bool MyMoveFile(LPCWSTR existFileName, LPCWSTR newFileName)
{  
  UINT codePage = GetCurrentCodePage();
  return MyMoveFile(UnicodeStringToMultiByte(existFileName, codePage),
      UnicodeStringToMultiByte(newFileName, codePage));
}
#endif

bool MyCreateDirectory(LPCTSTR pathName)
{  
  return BOOLToBool(::CreateDirectory(pathName, NULL)); 
}

#ifndef _UNICODE
bool MyCreateDirectory(LPCWSTR pathName)
{  
  return MyCreateDirectory(UnicodeStringToMultiByte(pathName, 
      GetCurrentCodePage()));
}
#endif

bool CreateComplexDirectory(LPCTSTR _aPathName)
{
  CSysString pathName = _aPathName;
  int pos = pathName.ReverseFind(TEXT('\\'));
  if (pos > 0 && pos == pathName.Length() - 1)
  {
    if (pathName.Length() == 3 && pathName[1] == ':')
      return true; // Disk folder;
    pathName.Delete(pos);
  }
  CSysString pathName2 = pathName;
  pos = pathName.Length();
  while(true)
  {
    if(MyCreateDirectory(pathName))
      break;
    if(::GetLastError() == ERROR_ALREADY_EXISTS)
    {
      NFind::CFileInfo fileInfo;
      if (!NFind::FindFile(pathName, fileInfo)) // For network folders
        return true;
      if (!fileInfo.IsDirectory())
        return false;
      break;
    }
    pos = pathName.ReverseFind(TEXT('\\'));
    if (pos < 0 || pos == 0)
      return false;
    if (pathName[pos - 1] == ':')
      return false;
    pathName = pathName.Left(pos);
  }
  pathName = pathName2;
  while(pos < pathName.Length())
  {
    pos = pathName.Find(TEXT('\\'), pos + 1);
    if (pos < 0)
      pos = pathName.Length();
    if(!MyCreateDirectory(pathName.Left(pos)))
      return false;
  }
  return true;
}

#ifndef _UNICODE

bool CreateComplexDirectory(LPCWSTR _aPathName)
{
  UString pathName = _aPathName;
  int pos = pathName.ReverseFind(L'\\');
  if (pos > 0 && pos == pathName.Length() - 1)
  {
    if (pathName.Length() == 3 && pathName[1] == L':')
      return true; // Disk folder;
    pathName.Delete(pos);
  }
  UString pathName2 = pathName;
  pos = pathName.Length();
  while(true)
  {
    if(MyCreateDirectory(pathName))
      break;
    if(::GetLastError() == ERROR_ALREADY_EXISTS)
    {
      NFind::CFileInfoW fileInfo;
      if (!NFind::FindFile(pathName, fileInfo)) // For network folders
        return true;
      if (!fileInfo.IsDirectory())
        return false;
      break;
    }
    pos = pathName.ReverseFind(L'\\');
    if (pos < 0 || pos == 0)
      return false;
    if (pathName[pos - 1] == L':')
      return false;
    pathName = pathName.Left(pos);
  }
  pathName = pathName2;
  while(pos < pathName.Length())
  {
    pos = pathName.Find(L'\\', pos + 1);
    if (pos < 0)
      pos = pathName.Length();
    if(!MyCreateDirectory(pathName.Left(pos)))
      return false;
  }
  return true;
}

#endif

bool DeleteFileAlways(LPCTSTR name)
{
  if(!::SetFileAttributes(name, 0))
    return false;
  return BOOLToBool(::DeleteFile(name));
}

#ifndef _UNICODE
bool DeleteFileAlways(LPCWSTR name)
{  
  if(!MySetFileAttributes(name, 0))
    return false;
  return DeleteFileAlways(UnicodeStringToMultiByte(name, 
      GetCurrentCodePage()));
}
#endif

static bool RemoveDirectorySubItems2(const CSysString pathPrefix,
    const NFind::CFileInfo &fileInfo)
{
  if(fileInfo.IsDirectory())
    return RemoveDirectoryWithSubItems(pathPrefix + fileInfo.Name);
  else
    return DeleteFileAlways(pathPrefix + fileInfo.Name);
}

bool RemoveDirectoryWithSubItems(const CSysString &path)
{
  NFind::CFileInfo fileInfo;
  CSysString pathPrefix = path + NName::kDirDelimiter;
  {
    NFind::CEnumerator enumerator(pathPrefix + TCHAR(NName::kAnyStringWildcard));
    while(enumerator.Next(fileInfo))
      if(!RemoveDirectorySubItems2(pathPrefix, fileInfo))
        return false;
  }
  if(!BOOLToBool(::SetFileAttributes(path, 0)))
    return false;
  return BOOLToBool(::RemoveDirectory(path));
}

#ifndef _UNICODE
static bool RemoveDirectorySubItems2(const UString pathPrefix,
    const NFind::CFileInfoW &fileInfo)
{
  if(fileInfo.IsDirectory())
    return RemoveDirectoryWithSubItems(pathPrefix + fileInfo.Name);
  else
    return DeleteFileAlways(pathPrefix + fileInfo.Name);
}
bool RemoveDirectoryWithSubItems(const UString &path)
{
  NFind::CFileInfoW fileInfo;
  UString pathPrefix = path + UString(NName::kDirDelimiter);
  {
    NFind::CEnumeratorW enumerator(pathPrefix + UString(NName::kAnyStringWildcard));
    while(enumerator.Next(fileInfo))
      if(!RemoveDirectorySubItems2(pathPrefix, fileInfo))
        return false;
  }
  if(!MySetFileAttributes(path, 0))
    return false;
  return MyRemoveDirectory(path);
}
#endif

#ifndef _WIN32_WCE

bool MyGetFullPathName(LPCTSTR fileName, CSysString &resultPath, 
    int &fileNamePartStartIndex)
{
  LPTSTR fileNamePointer = 0;
  LPTSTR buffer = resultPath.GetBuffer(MAX_PATH);
  DWORD needLength = ::GetFullPathName(fileName, MAX_PATH + 1, 
      buffer, &fileNamePointer);
  resultPath.ReleaseBuffer();
  if (needLength == 0 || needLength >= MAX_PATH)
    return false;
  if (fileNamePointer == 0)
    fileNamePartStartIndex = lstrlen(fileName);
  else
    fileNamePartStartIndex = fileNamePointer - buffer;
  return true;
}

#ifndef _UNICODE
bool MyGetFullPathName(LPCWSTR fileName, UString &resultPath, 
    int &fileNamePartStartIndex)
{
    const UINT currentPage = GetCurrentCodePage();
    CSysString sysPath;
    if (!MyGetFullPathName(UnicodeStringToMultiByte(fileName, 
        currentPage), sysPath, fileNamePartStartIndex))
      return false;
    UString resultPath1 = MultiByteToUnicodeString(
        sysPath.Left(fileNamePartStartIndex), currentPage);
    UString resultPath2 = MultiByteToUnicodeString(
        sysPath.Mid(fileNamePartStartIndex), currentPage);
    fileNamePartStartIndex = resultPath1.Length();
    resultPath = resultPath1 + resultPath2;
    return true;
}
#endif


bool MyGetFullPathName(LPCTSTR fileName, CSysString &path)
{
  int index;
  return MyGetFullPathName(fileName, path, index);
}

#ifndef _UNICODE
bool MyGetFullPathName(LPCWSTR fileName, UString &path)
{
  int index;
  return MyGetFullPathName(fileName, path, index);
}
#endif

bool GetOnlyName(LPCTSTR fileName, CSysString &resultName)
{
  int index;
  if (!MyGetFullPathName(fileName, resultName, index))
    return false;
  resultName = resultName.Mid(index);
  return true;
}

#ifndef _UNICODE
bool GetOnlyName(LPCWSTR fileName, UString &resultName)
{
  int index;
  if (!MyGetFullPathName(fileName, resultName, index))
    return false;
  resultName = resultName.Mid(index);
  return true;
}
#endif

bool GetOnlyDirPrefix(LPCTSTR fileName, CSysString &resultName)
{
  int index;
  if (!MyGetFullPathName(fileName, resultName, index))
    return false;
  resultName = resultName.Left(index);
  return true;
}

#ifndef _UNICODE
bool GetOnlyDirPrefix(LPCWSTR fileName, UString &resultName)
{
  int index;
  if (!MyGetFullPathName(fileName, resultName, index))
    return false;
  resultName = resultName.Left(index);
  return true;
}
#endif

bool MyGetCurrentDirectory(CSysString &path)
{
  DWORD needLength = ::GetCurrentDirectory(MAX_PATH + 1, 
      path.GetBuffer(MAX_PATH + 1));
  path.ReleaseBuffer();
  return (needLength > 0 && needLength <= MAX_PATH);
}

#ifndef _UNICODE
bool MyGetCurrentDirectory(UString &path)
{
  CSysString sysPath;
  if (!MyGetCurrentDirectory(sysPath))
    return false;
  path = MultiByteToUnicodeString(sysPath, GetCurrentCodePage());
  return true;
}
#endif
#endif

/*
bool MySearchPath(LPCTSTR path, LPCTSTR fileName, LPCTSTR extension, 
  CSysString &resultPath, UINT32 &filePart)
{
  LPTSTR filePartPointer;
  DWORD value = ::SearchPath(path, fileName, extension, 
    MAX_PATH, resultPath.GetBuffer(MAX_PATH), &filePartPointer);
  filePart = filePartPointer - (LPCTSTR)resultPath;
  resultPath.ReleaseBuffer();
  if (value == 0 || value > MAX_PATH)
    return false;
  return true;
}

#ifndef _UNICODE
bool MySearchPath(LPCWSTR path, LPCWSTR fileName, LPCWSTR extension, 
  UString &resultPath, UINT32 &filePart)
{
  const UINT currentPage = GetCurrentCodePage();
  CSysString sysPath;
  if (!MySearchPath(
      path != 0 ? (LPCTSTR)UnicodeStringToMultiByte(path, currentPage): 0,
      fileName != 0 ? (LPCTSTR)UnicodeStringToMultiByte(fileName, currentPage): 0,
      extension != 0 ? (LPCTSTR)UnicodeStringToMultiByte(extension, currentPage): 0,
      sysPath, filePart))
    return false;
  UString resultPath1 = MultiByteToUnicodeString(
    sysPath.Left(filePart), currentPage);
  UString resultPath2 = MultiByteToUnicodeString(
    sysPath.Mid(filePart), currentPage);
  filePart = resultPath1.Length();
  resultPath = resultPath1 + resultPath2;
  return true;
}
#endif
*/

bool MyGetTempPath(CSysString &path)
{
  DWORD needLength = ::GetTempPath(MAX_PATH + 1, 
      path.GetBuffer(MAX_PATH));
  path.ReleaseBuffer();
  return (needLength > 0 && needLength <= MAX_PATH);
}

#ifndef _UNICODE
bool MyGetTempPath(UString &path)
{
    CSysString sysPath;
    if (!MyGetTempPath(sysPath))
      return false;
    path = MultiByteToUnicodeString(sysPath, GetCurrentCodePage());
    return true;
}
#endif

UINT MyGetTempFileName(LPCTSTR dirPath, LPCTSTR prefix, CSysString &path)
{
  UINT number = ::GetTempFileName(dirPath, prefix, 0,
      path.GetBuffer(MAX_PATH));
  path.ReleaseBuffer();
  return number;
}

#ifndef _UNICODE
UINT MyGetTempFileName(LPCWSTR dirPath, LPCWSTR prefix, UString &path)
{
      const UINT currentPage = GetCurrentCodePage();
      CSysString sysPath;
      UINT number = MyGetTempFileName(
          dirPath ? (LPCTSTR)UnicodeStringToMultiByte(dirPath, currentPage): 0, 
          prefix ?  (LPCTSTR)UnicodeStringToMultiByte(prefix, currentPage): 0, 
          sysPath);
      path = MultiByteToUnicodeString(sysPath, currentPage);
  return number;
}
#endif

UINT CTempFile::Create(LPCTSTR dirPath, LPCTSTR prefix, CSysString &resultPath)
{
  Remove();
  UINT number = MyGetTempFileName(dirPath, prefix, resultPath);
  if(number != 0)
  {
    _fileName = resultPath;
    _mustBeDeleted = true;
  }
  return number;
}

bool CTempFile::Create(LPCTSTR prefix, CSysString &resultPath)
{
  CSysString tempPath;
  if(!MyGetTempPath(tempPath))
    return false;
  if (Create(tempPath, prefix, resultPath) != 0)
    return true;
  if(!MyGetWindowsDirectory(tempPath))
    return false;
  return (Create(tempPath, prefix, resultPath) != 0);
}

bool CTempFile::Remove()
{
  if (!_mustBeDeleted)
    return true;
  _mustBeDeleted = !DeleteFileAlways(_fileName);
  return !_mustBeDeleted;
}

#ifndef _UNICODE

UINT CTempFileW::Create(LPCWSTR dirPath, LPCWSTR prefix, UString &resultPath)
{
  Remove();
  UINT number = MyGetTempFileName(dirPath, prefix, resultPath);
  if(number != 0)
  {
    _fileName = resultPath;
    _mustBeDeleted = true;
  }
  return number;
}

bool CTempFileW::Create(LPCWSTR prefix, UString &resultPath)
{
  UString tempPath;
  if(!MyGetTempPath(tempPath))
    return false;
  if (Create(tempPath, prefix, resultPath) != 0)
    return true;
  if(!MyGetWindowsDirectory(tempPath))
    return false;
  return (Create(tempPath, prefix, resultPath) != 0);
}

bool CTempFileW::Remove()
{
  if (!_mustBeDeleted)
    return true;
  _mustBeDeleted = !DeleteFileAlways(_fileName);
  return !_mustBeDeleted;
}

#endif

}}}
