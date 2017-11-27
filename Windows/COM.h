// Windows/COM.h

// #pragma once

#ifndef __WINDOWS_COM_H
#define __WINDOWS_COM_H

#include "Common/String.h"

namespace NWindows {
namespace NCOM {

#ifdef WIN32
class CComInitializer
{
public:
  CComInitializer() { CoInitialize(NULL);};
  ~CComInitializer() { CoUninitialize(); };
};
#endif


//////////////////////////////////
// GUID <--> String Conversions
UString GUIDToStringW(REFGUID guid);
AString GUIDToStringA(REFGUID guid);
#ifdef UNICODE
  #define GUIDToString GUIDToStringW
#else
  #define GUIDToString GUIDToStringA
#endif // !UNICODE

HRESULT StringToGUIDW(const wchar_t *string, GUID &classID);
HRESULT StringToGUIDA(const char *string, GUID &classID);
#ifdef UNICODE
  #define StringToGUID StringToGUIDW
#else
  #define StringToGUID StringToGUIDA
#endif // !UNICODE

  
}}

#endif
