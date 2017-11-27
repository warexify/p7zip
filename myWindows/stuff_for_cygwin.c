
#ifdef __CYGWIN__
#include <stdio.h>
#include <wchar.h>

#define	UNSIGNED	1
#define	USE_WIDE_CHAR	1
// code for : unsigned long wcstoul (const wchar_t*, wchar_t**, int);
#include <generic/strtol.c>

#else
// NOTHING
int cygwin = 0;
#endif

