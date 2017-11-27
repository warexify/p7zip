// Windows/Error.h

#include "StdAfx.h"

#include "Windows/Error.h"
#ifndef _UNICODE
#include "Common/StringConvert.h"
#endif

namespace NWindows {
namespace NError {

bool MyFormatMessage(DWORD messageID, CSysString &message)
{
#ifdef WIN32
  LPVOID msgBuf;
  if(::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
      FORMAT_MESSAGE_FROM_SYSTEM | 
      FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      messageID,
      0, // Default language
      (LPTSTR) &msgBuf,
      0,
      NULL) == 0)
    return false;

  message = (LPCTSTR)msgBuf;
  ::LocalFree(msgBuf);
#else
  char msgBuf[1024];
  switch(messageID)
  {
    case NO_ERROR                   : strcpy(msgBuf,"no error"); break;
    case ERROR_FILE_NOT_FOUND       : strcpy(msgBuf,"file not found"); break;
    case ERROR_PATH_NOT_FOUND       : strcpy(msgBuf,"path not found"); break;
    case ERROR_ACCESS_DENIED        : strcpy(msgBuf,"access denied"); break;
    case ERROR_INVALID_HANDLE       : strcpy(msgBuf,"invalid handle"); break;
    case ERROR_BAD_FORMAT           : strcpy(msgBuf,"bad format"); break;
    case ERROR_NO_MORE_FILES        : strcpy(msgBuf,"no more files"); break;
    case ERROR_SEEK                 : strcpy(msgBuf,"seek error"); break;
    case ERROR_GEN_FAILURE          : strcpy(msgBuf,"generic failure"); break;
    case ERROR_SHARING_VIOLATION    : strcpy(msgBuf,"sharing violation or invalid symbolic link"); break;
    case ERROR_LOCK_VIOLATION       : strcpy(msgBuf,"lock violation"); break;
    case ERROR_HANDLE_DISK_FULL     : strcpy(msgBuf,"handle disk full"); break;
    case ERROR_FILE_EXISTS          : strcpy(msgBuf,"file exists"); break;
    case ERROR_CANNOT_MAKE          : strcpy(msgBuf,"cannot make"); break;
    case ERROR_INVALID_PARAMETER    : strcpy(msgBuf,"invalid parameter"); break;
    case ERROR_BROKEN_PIPE          : strcpy(msgBuf,"broken pipe"); break;
    case ERROR_DISK_FULL            : strcpy(msgBuf,"disk full"); break;
    case ERROR_CALL_NOT_IMPLEMENTED : strcpy(msgBuf,"call not implemented"); break;
    case ERROR_DIR_NOT_EMPTY        : strcpy(msgBuf,"dir not empty"); break;
    case ERROR_ALREADY_EXISTS       : strcpy(msgBuf,"already exists"); break;
    case ERROR_FILENAME_EXCED_RANGE : strcpy(msgBuf,"filename exced range"); break;
    default:
      sprintf(msgBuf,"unknown error 0x%x",(unsigned)messageID);
  }
  strcat(msgBuf,"                ");
  message = msgBuf;
#endif
  return true;

}

#ifndef _UNICODE
bool MyFormatMessage(DWORD messageID, UString &message)
{
#ifdef WIN32
  LPVOID msgBuf;
  if(::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
      FORMAT_MESSAGE_FROM_SYSTEM | 
      FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      messageID,
      0, // Default language
      (LPWSTR) &msgBuf,
      0,
      NULL) == 0)
  {
    if (::GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
      return false;
    CSysString messageSys;
    bool result = MyFormatMessage(messageID, messageSys);
    message = GetUnicodeString(messageSys);
    return result;
  }
  message = (LPCWSTR)msgBuf;
  ::LocalFree(msgBuf);
  return true;
#else
    CSysString messageSys;
    bool result = MyFormatMessage(messageID, messageSys);
    message = GetUnicodeString(messageSys);
    return result;
#endif
}
#endif

}}

