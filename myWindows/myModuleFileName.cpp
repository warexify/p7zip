#include "StdAfx.h"


#include <unistd.h> // rmdir
#include <string.h>
#include <errno.h>

#include <sys/stat.h> // mkdir
#include <sys/types.h>

#include <limits.h>
#ifndef MB_LEN_MAX
#define MB_LEN_MAX 1024
#endif

#include "../Common/StringConvert.h"

#include "myPrivate.h"

#include <string>

// #define TRACEN(u) u;
#define TRACEN(u)  /* */

static const char * myModuleFileName = 0;
extern "C" void mySetModuleFileNameA(const char * moduleFileName)
{
	char  *ptr =  new char[strlen(moduleFileName)+1];
        strcpy(ptr,moduleFileName);
	char * p = ptr;
	while (*p) {
		if (*p == '/') *p = '\\';
		p++;
	}
	myModuleFileName = ptr;
	TRACEN((printf("mySetModuleFileNameA(%s) &myModuleFileName=%p\n",myModuleFileName,&myModuleFileName)))
}

void mySetModuleFileName_resolve_link(const char * moduleName)
{
	char new_path[2048];

	std::string filename = moduleName;
	ssize_t len = 0;
	int max_try = 50;
	while ((len != -1) && (max_try != 0))
	{
		len = readlink(filename.c_str(),new_path,sizeof(new_path)-1);
		if (len != -1) {
			new_path[len] = '\0';
			// printf("new_path='%s'\n",new_path);
			filename = new_path;
			max_try--;
		} /* else {
			printf("len = %d (errno=%d,%s)\n",(int)len,errno,strerror(errno));
		} */
	}

	mySetModuleFileNameA(filename.c_str());
}

DWORD GetModuleFileNameA( HMODULE hModule, LPSTR lpFilename, DWORD nSize)
{
	TRACEN((printf("GetModuleFileNameA(%p) &myModuleFileName=%p\n",(void *)hModule,&myModuleFileName)))
	if (hModule != 0) throw "GetModuleFileNameA not implemented when hModule !=0";

	if ((nSize>=1) && (myModuleFileName))
	{
			strncpy(lpFilename,myModuleFileName,nSize);
			lpFilename[nSize-1] = 0;
			TRACEN((printf("GetModuleFileNameA(%p) lpFilename='%s'\n",(void *)hModule,lpFilename)))
			return strlen(lpFilename);
	}
	return 0;
}
