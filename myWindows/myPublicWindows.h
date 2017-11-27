

extern "C" void mySetModuleFileNameA(const char * moduleFileName);

/************************* FILES *************************/

#define FILE_HANDLE_INVALID 0
class CFileHandlerInternal;
typedef CFileHandlerInternal * t_file_handle;

t_file_handle WINAPI myCreateFile(
  LPCTSTR lpFileName,
  DWORD dwDesiredAccess,
  DWORD dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD dwCreationDisposition,
  DWORD dwFlagsAndAttributes,
  HANDLE hTemplateFile
);

BOOL WINAPI myCloseFile(t_file_handle hFile);

#define FILE_SHARE_READ	1
#define GENERIC_READ	0x80000000
#define GENERIC_WRITE	0x40000000

#define CREATE_NEW	1
#define CREATE_ALWAYS	2
#define OPEN_EXISTING	3
#define OPEN_ALWAYS	4
#define TRUNCATE_EXISTING	5

t_file_handle WINAPI myCreateFileA(LPCSTR,DWORD,DWORD,LPSECURITY_ATTRIBUTES,DWORD,DWORD);
t_file_handle WINAPI myCreateFileW(LPCWSTR,DWORD,DWORD,LPSECURITY_ATTRIBUTES,DWORD,DWORD);
bool myGetFileLength( t_file_handle hFile,UINT64 &length);

bool myFileSeek( t_file_handle hFile, INT64 distanceToMove, DWORD moveMethod, UINT64 &newPosition);

BOOL WINAPI ReadFile(t_file_handle,PVOID,DWORD,PDWORD,LPOVERLAPPED);
BOOL WINAPI WriteFile(t_file_handle ,PCVOID,DWORD,PDWORD,LPOVERLAPPED);
BOOL WINAPI SetEndOfFile(t_file_handle);
BOOL WINAPI SetFileTime(t_file_handle,const FILETIME*,const FILETIME*,const FILETIME*);

#define myCreateFile myCreateFileA

/************************* EVENTS *************************/

DWORD WINAPI myInfiniteWaitForSingleEvent(HANDLE hHandle);
DWORD WINAPI WaitForMultipleObjects( DWORD count, const HANDLE *handles, BOOL wait_all, DWORD timeout );
HANDLE WINAPI myCreateEvent(BOOL manual_reset,BOOL initial_state);
BOOL WINAPI mySetEvent(HANDLE hEvent);
BOOL WINAPI myResetEvent(HANDLE hEvent);
BOOL WINAPI myCloseEvent(HANDLE hFile);

/************************* OTHERS *************************/
extern int global_use_utf16_conversion;
const char *my_getlocale(void);

