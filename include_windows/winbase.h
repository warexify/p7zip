#ifndef _WINBASE_H
#define _WINBASE_H

#define STD_INPUT_HANDLE (DWORD)(0xfffffff6)
#define STD_OUTPUT_HANDLE (DWORD)(0xfffffff5)
#define STD_ERROR_HANDLE (DWORD)(0xfffffff4)
#define INVALID_HANDLE_VALUE (HANDLE)(-1)

#define FILE_BEGIN	0
#define FILE_CURRENT	1
#define FILE_END	2
#define INVALID_SET_FILE_POINTER	((DWORD)-1)

#define INVALID_FILE_SIZE 0xFFFFFFFF

#define WAIT_OBJECT_0 0
#define INFINITE	0xFFFFFFFF

typedef void * LPOVERLAPPED;

typedef FILETIME *LPFILETIME;

typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME,*LPSYSTEMTIME;

typedef struct _WIN32_FIND_DATAA {
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD dwReserved0;
	DWORD dwReserved1;
	CHAR cFileName[MAX_PATH];
	CHAR cAlternateFileName[14];
} WIN32_FIND_DATAA,*PWIN32_FIND_DATAA,*LPWIN32_FIND_DATAA;
typedef struct _WIN32_FIND_DATAW {
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD dwReserved0;
	DWORD dwReserved1;
	WCHAR cFileName[MAX_PATH];
	WCHAR cAlternateFileName[14];
} WIN32_FIND_DATAW,*PWIN32_FIND_DATAW,*LPWIN32_FIND_DATAW;

#ifdef __cplusplus
extern "C" {
#endif

LPWSTR WINAPI GetCommandLineW(VOID);

typedef void * LPSECURITY_ATTRIBUTES;

/* HANDLE WINAPI GetStdHandle(DWORD); */

typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID);
HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES,DWORD,LPTHREAD_START_ROUTINE,PVOID,DWORD,PDWORD);
DWORD WINAPI ResumeThread(HANDLE);
DWORD WINAPI SuspendThread(HANDLE);
BOOL WINAPI TerminateThread(HANDLE,DWORD);

BOOL WINAPI DosDateTimeToFileTime(WORD,WORD,FILETIME *);
BOOL WINAPI FileTimeToDosDateTime(CONST FILETIME *,LPWORD,LPWORD);
BOOL WINAPI FileTimeToLocalFileTime(CONST FILETIME *,FILETIME *);
BOOL WINAPI FileTimeToSystemTime(CONST FILETIME *,LPSYSTEMTIME);
BOOL WINAPI LocalFileTimeToFileTime(CONST FILETIME *,FILETIME *);
VOID WINAPI GetSystemTime(LPSYSTEMTIME);
BOOL WINAPI SystemTimeToFileTime(const SYSTEMTIME*,LPFILETIME);

DWORD WINAPI GetShortPathNameA(LPCSTR,LPSTR,DWORD);
DWORD WINAPI GetShortPathNameW(LPCWSTR,LPWSTR,DWORD);

HANDLE WINAPI FindFirstFileA(LPCSTR,LPWIN32_FIND_DATAA);
HANDLE WINAPI FindFirstFileW(LPCWSTR,LPWIN32_FIND_DATAW);

BOOL WINAPI FindNextFileA(HANDLE,LPWIN32_FIND_DATAA);
BOOL WINAPI FindNextFileW(HANDLE,LPWIN32_FIND_DATAW);

BOOL WINAPI FindClose(HANDLE);

BOOL WINAPI SetFileAttributesA(LPCSTR,DWORD);
BOOL WINAPI SetFileAttributesW(LPCWSTR,DWORD);

BOOL WINAPI MoveFileA(LPCSTR,LPCSTR);
BOOL WINAPI MoveFileW(LPCWSTR,LPCWSTR);

BOOL WINAPI RemoveDirectoryA(LPCSTR);
BOOL WINAPI RemoveDirectoryW(LPCWSTR);

DWORD WINAPI GetCompressedFileSizeA(LPCSTR,PDWORD);
DWORD WINAPI GetCompressedFileSizeW(LPCWSTR,PDWORD);

BOOL WINAPI SetCurrentDirectoryA(LPCSTR);
BOOL WINAPI SetCurrentDirectoryW(LPCWSTR);

BOOL WINAPI AreFileApisANSI(void);

/* FIXED LONG WINAPI CompareFileTime(CONST FILETIME*,CONST FILETIME*); */

UINT WINAPI GetWindowsDirectoryA(LPSTR,UINT);
UINT WINAPI GetWindowsDirectoryW(LPWSTR,UINT);
UINT WINAPI GetSystemDirectoryA(LPSTR,UINT);
UINT WINAPI GetSystemDirectoryW(LPWSTR,UINT);
UINT WINAPI GetTempFileNameA(LPCSTR,LPCSTR,UINT,LPSTR);
UINT WINAPI GetTempFileNameW(LPCWSTR,LPCWSTR,UINT,LPWSTR);
DWORD WINAPI GetTempPathA(DWORD,LPSTR);
DWORD WINAPI GetTempPathW(DWORD,LPWSTR);
DWORD WINAPI GetFullPathNameA(LPCSTR,DWORD,LPSTR,LPSTR*);
DWORD WINAPI GetFullPathNameW(LPCWSTR,DWORD,LPWSTR,LPWSTR*);
DWORD WINAPI GetCurrentDirectoryA(DWORD,LPSTR);
DWORD WINAPI GetCurrentDirectoryW(DWORD,LPWSTR);
DWORD WINAPI GetLogicalDriveStringsA(DWORD,LPSTR);
DWORD WINAPI GetLogicalDriveStringsW(DWORD,LPWSTR);

BOOL WINAPI CreateDirectoryA(LPCSTR,LPSECURITY_ATTRIBUTES);
BOOL WINAPI CreateDirectoryW(LPCWSTR,LPSECURITY_ATTRIBUTES);
BOOL WINAPI DeleteFileA(LPCSTR);
BOOL WINAPI DeleteFileW(LPCWSTR);
DWORD WINAPI SearchPathA(LPCSTR,LPCSTR,LPCSTR,DWORD,LPSTR,LPSTR*);
DWORD WINAPI SearchPathW(LPCWSTR,LPCWSTR,LPCWSTR,DWORD,LPWSTR,LPWSTR*);

int WINAPI lstrlenA(LPCSTR);
int WINAPI lstrlenW(LPCWSTR);
/* LPSTR WINAPI lstrcatA(LPSTR,LPCSTR); */
#define lstrcatA strcat /* OK for MBS */

BOOL WINAPI FindNextChangeNotification(HANDLE);
BOOL WINAPI CloseHandle(HANDLE);

DWORD WINAPI WaitForMultipleObjects(DWORD,const HANDLE*,BOOL,DWORD);
DWORD WINAPI WaitForMultipleObjectsEx(DWORD,const HANDLE*,BOOL,DWORD,BOOL);
DWORD WINAPI WaitForSingleObject(HANDLE,DWORD);
DWORD WINAPI WaitForSingleObjectEx(HANDLE,DWORD,BOOL);

HANDLE WINAPI CreateEventA(LPSECURITY_ATTRIBUTES,BOOL,BOOL,LPCSTR);
HANDLE WINAPI CreateEventW(LPSECURITY_ATTRIBUTES,BOOL,BOOL,LPCWSTR);

HANDLE WINAPI OpenEventA(DWORD,BOOL,LPCSTR);
HANDLE WINAPI OpenEventW(DWORD,BOOL,LPCWSTR);
BOOL WINAPI SetEvent(HANDLE);
BOOL WINAPI PulseEvent(HANDLE);
BOOL WINAPI ResetEvent(HANDLE);

#define MoveMemory memmove

DWORD WINAPI GetTickCount(VOID);


HANDLE WINAPI CreateFileA(LPCSTR,DWORD,DWORD,LPSECURITY_ATTRIBUTES,DWORD,DWORD,HANDLE);
HANDLE WINAPI CreateFileW(LPCWSTR,DWORD,DWORD,LPSECURITY_ATTRIBUTES,DWORD,DWORD,HANDLE);
DWORD WINAPI GetFileSize(HANDLE,PDWORD);

#ifdef UNICODE
typedef WIN32_FIND_DATAW WIN32_FIND_DATA,*LPWIN32_FIND_DATA;
#define FindFirstFile FindFirstFileW
#define FindNextFile FindNextFileW
#define SearchPath SearchPathW
#define GetShortPathName GetShortPathNameW
#define GetLogicalDriveStrings GetLogicalDriveStringsW
#define GetCurrentDirectory GetCurrentDirectoryW
#define SetFileAttributes SetFileAttributesW
#define MoveFile MoveFileW
#define RemoveDirectory RemoveDirectoryW
#define CreateFile CreateFileW
#define GetCompressedFileSize GetCompressedFileSizeW
#define SetCurrentDirectory SetCurrentDirectoryW
#define GetWindowsDirectory GetWindowsDirectoryW
#define GetSystemDirectory GetSystemDirectoryW
#define GetTempFileName GetTempFileNameW
#define GetTempPath GetTempPathW
#define CreateDirectory CreateDirectoryW
#define DeleteFile DeleteFileW
#define GetFullPathName GetFullPathNameW
#define lstrlen lstrlenW
#define CreateEvent CreateEventW
#define OpenEvent OpenEventW
#else
typedef WIN32_FIND_DATAA WIN32_FIND_DATA,*LPWIN32_FIND_DATA;
#define FindFirstFile FindFirstFileA
#define FindNextFile FindNextFileA
#define SearchPath SearchPathA
#define GetShortPathName GetShortPathNameA
#define GetLogicalDriveStrings GetLogicalDriveStringsA
#define GetCurrentDirectory GetCurrentDirectoryA
#define SetFileAttributes SetFileAttributesA
#define MoveFile MoveFileA
#define CreateFile CreateFileA
#define RemoveDirectory RemoveDirectoryA
#define GetCompressedFileSize GetCompressedFileSizeA
#define SetCurrentDirectory SetCurrentDirectoryA
#define GetWindowsDirectory GetWindowsDirectoryA
#define GetSystemDirectory GetSystemDirectoryA
#define GetTempFileName GetTempFileNameA
#define GetTempPath GetTempPathA
#define CreateDirectory CreateDirectoryA
#define DeleteFile DeleteFileA
#define GetFullPathName GetFullPathNameA
/* #define lstrlen lstrlenA */
#define lstrlen strlen  /* OK for MBS */
#define lstrlenA strlen  /* OK for MBS */
#define CreateEvent CreateEventA
#define OpenEvent OpenEventA
#endif

#ifdef __cplusplus
}
#endif

#endif /* _WINBASE_H */
