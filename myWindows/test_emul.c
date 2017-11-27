#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include <wchar.h>
#include <windows.h>

#include "myPrivate.h"


int main()
{
	char pathname[MAX_PATHNAME_LEN];
	char unix_pathname[MAX_PATHNAME_LEN];
	char *lastpart;
	const char *path;
	UINT ret;

	ret = GetCurrentDirectoryA(MAX_PATHNAME_LEN,pathname);
	nameWindowToUnixA(pathname,unix_pathname);
	printf("GetCurrentDirectoryA(%s)=%u => '%s'\n",pathname,ret,unix_pathname);
	
	ret = GetTempPathA(MAX_PATHNAME_LEN,pathname);
	nameWindowToUnixA(pathname,unix_pathname);
	printf("GetTempPathA(%s)=%u => '%s'\n",pathname,ret,unix_pathname);
	
	ret = GetWindowsDirectoryA(pathname,sizeof(pathname));
	nameWindowToUnixA(pathname,unix_pathname);
	printf("GetWindowsDirectoryA(%s)=%u => '%s'\n",pathname,ret,unix_pathname);


	path = "File";
	ret = GetFullPathNameA( path, MAX_PATHNAME_LEN,pathname , &lastpart );
	nameWindowToUnixA(pathname,unix_pathname);
	printf("GetFullPathNameA(%s,%s,%s)=%u => '%s'\n",path,pathname,lastpart,ret,unix_pathname);

	path = "c:\\path1\\path2\\file";
	ret = GetFullPathNameA( path, MAX_PATHNAME_LEN,pathname , &lastpart );
	nameWindowToUnixA(pathname,unix_pathname);
	printf("GetFullPathNameA(%s,%s,%s)=%u => '%s'\n",path,pathname,lastpart,ret,unix_pathname);

	path = "\\path3\\path4\\file2";
	ret = GetFullPathNameA( path, MAX_PATHNAME_LEN,pathname , &lastpart );
	nameWindowToUnixA(pathname,unix_pathname);
	printf("GetFullPathNameA(%s,%s,%s)=%u => '%s'\n",path,pathname,lastpart,ret,unix_pathname);


	return 0;
}

