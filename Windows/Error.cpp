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
  TCHAR msgBuf[1024];
#ifdef _UNICODE
  wsprintf(msgBuf,L"GetLastError=0x%lx",(unsigned)messageID);
#else
  sprintf(msgBuf,"GetLastError=0x%lx",(unsigned)messageID);
#endif
  message = msgBuf;
#endif
  
  return true;
}

#ifndef _UNICODE
bool MyFormatMessage(DWORD messageID, UString &message)
{
    CSysString messageSys;
    bool result = MyFormatMessage(messageID, messageSys);
    message = GetUnicodeString(messageSys);
    return result;
}
#endif

}}
