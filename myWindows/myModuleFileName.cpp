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


void my_windows_split_path(const std::string &p_path, std::string &dir , std::string &base)
{
	size_t pos = p_path.find_last_of("/");
	if (pos == std::string::npos) {
		// no separator
		dir  = ".";
		if (p_path.empty()) base = ".";
		else              base = p_path;
	} else if ((pos+1) < p_path.size()) {
		// true separator
		base = p_path.substr(pos+1);
		while ((pos >= 1) && (p_path[pos-1] == '/')) pos--;
		if (pos == 0) dir = "/";
               	else          dir = p_path.substr(0,pos);
	} else {
		// separator at the end of the path
		pos = p_path.find_last_not_of("/");
		if (pos == std::string::npos) {
			base = "/";
                	dir = "/";
		} else {
			my_windows_split_path(p_path.substr(0,pos+1),dir,base);
		}
	}
}

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

#if 0 // not needed any more
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
#endif

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


static DWORD mySearchPathA( LPCSTR path, LPCSTR name, LPCSTR ext,
                          DWORD buflen, LPSTR buffer, LPSTR *lastpart )
{
	if (path != 0) {
		printf("NOT EXPECTED : SearchPathA : path != NULL\n");
		exit(EXIT_FAILURE);
	}

	if (ext != 0) {
		printf("NOT EXPECTED : SearchPathA : ext != NULL\n");
		exit(EXIT_FAILURE);
	}

	if (myModuleFileName)
	{
		FILE *file;
		file = fopen(name,"r");
		if (file)
		{
			DWORD ret = (DWORD)strlen(name);
			fclose(file);
			if (ret >= buflen) {
				SetLastError(ERROR_FILENAME_EXCED_RANGE);
				return 0;
			}
			strcpy(buffer,name);
			if (lastpart) *lastpart = buffer;
			
			return ret;
		}
		std::string module_path(myModuleFileName);
		std::string dir,name2,dir_path;
		int ind = 0;
		while (module_path[ind]) {
			if (module_path[ind] == '\\') module_path[ind]='/';
			ind++;
		}
		my_windows_split_path(module_path,dir,name2);
		dir_path = dir;
		dir_path += "/";
		dir_path += name;

		file = fopen(dir_path.c_str(),"r");
		if (file)
		{
			DWORD ret = strlen(dir_path.c_str());
			fclose(file);
			if (ret >= buflen) {
				SetLastError(ERROR_FILENAME_EXCED_RANGE);
				return 0;
			}
			strcpy(buffer,dir_path.c_str());
			if (lastpart) *lastpart = buffer + (strlen(dir.c_str()) + 1);
			
			return ret;
		}

	}
					
	return 0;
}

DWORD SearchPathA( LPCSTR path, LPCSTR name, LPCSTR ext,
                          DWORD buflen, LPSTR buffer, LPSTR *lastpart )
{
	*buffer=0;
	DWORD ret = mySearchPathA(path,name,ext,buflen,buffer,lastpart);

	TRACEN((printf("SearchPathA(%s,%s,%s,%d,%s,%p)=%d\n",
					(path ? path : "<NULL>"),
					(name ? name : "<NULL>"),
					(ext ? ext : "<NULL>"),
					(int)buflen,
					buffer,lastpart,(int)ret)));
	return ret;
}

