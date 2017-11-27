// Windows/DLL.cpp

#include "StdAfx.h"

#ifdef __APPLE_CC__
#include <mach-o/dyld.h>
#else
#include <dlfcn.h>  // dlopen ...
#endif

#include "DLL.h"
#include "Defs.h"
#ifndef _UNICODE
#include "../Common/StringConvert.h"
#endif

#include "myPrivate.h"

//#define TRACEN(u) u;
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

#ifdef __APPLE_CC__
  int ret = NSUnLinkModule (_module, 0);
#else
  int ret = dlclose(_module);
#endif
TRACEN((printf("CLibrary::Free dlclose(%p)=%d\n",(void *)_module,ret)))
  if (ret != 0) return false;
  _module = 0;
  return true;
}

static FARPROC local_GetProcAddress(HMODULE module,LPCSTR lpProcName)
{
  void *ptr = 0;
  TRACEN((printf("local_GetProcAddress(%p,%s)\n",(void *)module,lpProcName)))
  if (module) {
#ifdef __APPLE_CC__
    char name[1024];
    sprintf(name,"_%s",lpProcName);
    TRACEN((printf("NSLookupSymbolInModule(%p,%s)\n",(void *)module,name)))
    NSSymbol sym;
    sym = NSLookupSymbolInModule(module, name);
    if (sym) {
      ptr = NSAddressOfSymbol(sym);
    } else {
      ptr = 0;
    }
#else
    ptr = dlsym (module, lpProcName);
#endif
	TRACEN((printf("CLibrary::GetProcAddress : dlsym(%p,%s)=%p\n",(void *)module,lpProcName,ptr)))
  }
  return (FARPROC)ptr;
}

FARPROC CLibrary::GetProcAddress(LPCSTR lpProcName) const
{
  TRACEN((printf("CLibrary::GetProcAddress(%p,%s)\n",(void *)_module,lpProcName)))
  return local_GetProcAddress(_module,lpProcName);
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

typedef BOOL (*t_DllMain)(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

bool CLibrary::Load(LPCTSTR lpLibFileName)
{
  // HMODULE handler = ::LoadLibrary(fileName);
  void *handler = 0;
  char name[1024];
  nameWindowToUnixA(lpLibFileName,name);

#ifdef __APPLE_CC__
  NSObjectFileImage image;
  NSObjectFileImageReturnCode nsret;

  nsret = NSCreateObjectFileImageFromFile (name, &image);
  if (nsret == NSObjectFileImageSuccess) {
     TRACEN((printf("NSCreateObjectFileImageFromFile(%s) : OK\n",name)))
     handler = (HMODULE)NSLinkModule(image,lpLibFileName,NSLINKMODULE_OPTION_RETURN_ON_ERROR
           | NSLINKMODULE_OPTION_PRIVATE | NSLINKMODULE_OPTION_BINDNOW);
  } else {
     TRACEN((printf("NSCreateObjectFileImageFromFile(%s) : ERROR\n",name)))
  }
#else
#ifdef RTLD_GROUP
  handler = dlopen(name,RTLD_GLOBAL | RTLD_GROUP | RTLD_NOW);
#else
  handler = dlopen(name,RTLD_GLOBAL |              RTLD_NOW);
#endif
#endif // __APPLE_CC__
  TRACEN((printf("LoadLibraryA(%s)=%p\n",name,handler)))
  if (handler) {
    void (*ptr)(const char *) = (void (*)(const char *))local_GetProcAddress (handler, "mySetModuleFileNameA");
	if (ptr)
	{
		ptr(lpLibFileName);
	}
    t_DllMain p_DllMain = (t_DllMain)local_GetProcAddress (handler, "DllMain");
	if (p_DllMain)
	{
		p_DllMain(0,DLL_PROCESS_ATTACH,0);
	}
  } else {
#ifdef __APPLE_CC__
    NSLinkEditErrors c;
    int num_err;
    const char *file,*err;
    NSLinkEditError(&c,&num_err,&file,&err);
    printf("Can't load '%s' (%s)\n", lpLibFileName,err);
#else
    printf("Can't load '%s' (%s)\n", lpLibFileName,dlerror());
#endif
  } 

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
