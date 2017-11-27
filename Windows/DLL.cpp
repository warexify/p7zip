// Windows/DLL.cpp

#include "StdAfx.h"

#include <dlfcn.h>  // dlopen ...

#include "DLL.h"
#include "Defs.h"
#ifndef _UNICODE
#include "../Common/StringConvert.h"
#endif

#include "myPrivate.h"

// #define TRACEN(u) u;
#define TRACEN(u)  /* */

namespace NWindows {
namespace NDLL {

CLibrary::~CLibrary()
{
  Free();
}

bool CLibrary::Free()
{
TRACEN((printf("CLibrary::Free(%p)\n",(void *)_module)))
  if (_module == 0)
    return true;

  int ret = dlclose(_module);
TRACEN((printf("CLibrary::Free dlclose(%p)=%d\n",(void *)_module,ret)))
  if (ret != 0) return false;
  _module = 0;
  return true;
}

FARPROC CLibrary::GetProcAddress(LPCSTR lpProcName) const
{
  void *ptr = 0;
  TRACEN((printf("CLibrary::GetProcAddress(%p,%s)\n",(void *)_module,lpProcName)))
  if (_module) {
    ptr = dlsym (_module, lpProcName);
	TRACEN((printf("CLibrary::GetProcAddress : dlsym(%p,%s)=%p\n",(void *)_module,lpProcName,ptr)))
  }
  return (FARPROC)ptr;
}

bool CLibrary::LoadOperations(HMODULE newModule)
{
  if (newModule == NULL)
    return false;
  if(!Free())
    return false;
  _module = newModule;
  return true;
}


bool CLibrary::LoadEx(LPCTSTR fileName, DWORD flags)
{
  /* return LoadOperations(::LoadLibraryEx(fileName, NULL, flags)); */
  return this->Load(fileName);
}


bool CLibrary::Load(LPCTSTR lpLibFileName)
{
  // HMODULE handler = ::LoadLibrary(fileName);
  void *handler = 0;
  char name[1024];
  nameWindowToUnixA(lpLibFileName,name);

  handler = dlopen(name,RTLD_GLOBAL |  RTLD_NOW); // FIXME
  TRACEN((printf("LoadLibraryA(%s)=%p\n",name,handler)))
  if (handler) {
    void (*ptr)(const char *) = (void (*)(const char *))dlsym (handler, "mySetModuleFileNameA");
	if (ptr)
	{
		ptr(lpLibFileName);
	}
  } /* else {
    printf("Can't load '%s' (%s)", lpLibFileName,dlerror());
  } */

  return LoadOperations(handler);
}

#ifndef _UNICODE
static inline UINT GetCurrentCodePage() 
  { return ::AreFileApisANSI() ? CP_ACP : CP_OEMCP; } 
 
 
bool CLibrary::LoadEx(LPCWSTR fileName, DWORD flags)
{
#ifdef WIN32
  HMODULE module = ::LoadLibraryExW(fileName, NULL, flags);
  if (module != 0)
    return LoadOperations(module);
  if (::GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
    return false;
#endif
  return LoadEx(UnicodeStringToMultiByte(fileName, GetCurrentCodePage()), flags);
}


bool CLibrary::Load(LPCWSTR fileName)
{
#ifdef WIN32
  HMODULE module = ::LoadLibraryW(fileName);
  if (module != 0)
    return LoadOperations(module);
  if (::GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
    return false;
#endif
  return Load(UnicodeStringToMultiByte(fileName, GetCurrentCodePage()));
}
#endif



bool MyGetModuleFileName(HMODULE hModule, CSysString &result)
{
  result.Empty();
  TCHAR fullPath[MAX_PATH + 2];
  DWORD size = ::GetModuleFileName(hModule, fullPath, MAX_PATH + 1);
  if (size <= MAX_PATH && size != 0)
  {
    result = fullPath;
    return true;
  }
  return false;
}

#ifndef _UNICODE
bool MyGetModuleFileName(HMODULE hModule, UString &result)
{
#ifdef WIN32
  result.Empty();
  wchar_t fullPath[MAX_PATH + 2];
  DWORD size = ::GetModuleFileNameW(hModule, fullPath, MAX_PATH + 1);
  if (size <= MAX_PATH && size != 0)
  {
    result = fullPath;
    return true;
  }
  if (::GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
    return false;
#endif
  CSysString resultSys;
  if (!MyGetModuleFileName(hModule, resultSys))
    return false;
  result = MultiByteToUnicodeString(resultSys, GetCurrentCodePage());
  return true;
}
#endif

}}
