// stdafx.h

#ifndef __STDAFX_H
#define __STDAFX_H

#include <pthread.h>

#include <windows.h>

#include "myWindows.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <wchar.h>
#include <ctype.h>
#include <unistd.h>

#ifdef __CYGWIN__  // FIXME
#ifdef __cplusplus 
extern "C" {
#endif
unsigned long wcstoul (const wchar_t*, wchar_t**, int);
#ifdef __cplusplus
}	/* end of extern "C" */
#endif
#endif

#include <vector>
#include <memory>

#endif 
