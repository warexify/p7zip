#include "StdAfx.h"
#include <locale.h>

#include "Common/String.h"
#include "Common/StringConvert.h"

//#define TRACEN(u) u;
#define TRACEN(u)  /* */

static UString wcmd;

void myInit(int numArguments,const char *arguments[]) {
  setlocale(LC_ALL,0);

  wcmd = L"";
  UString tmp;
  for(int ind=0;ind<numArguments;ind++) {
    tmp = MultiByteToUnicodeString(arguments[ind]);
    wcmd += L" ";
    wcmd += tmp;
  }
  TRACEN((printf("myInit(%d) => '%ls'\n",numArguments,wcmd.GetBuffer(1))))
}

LPWSTR WINAPI GetCommandLineW(VOID) {
  TRACEN((printf("GetCommandLineW()='%ls'\n",wcmd.GetBuffer(1))))
  return wcmd.GetBuffer(1);
}

