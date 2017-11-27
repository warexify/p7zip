
#define MAX_PATHNAME_LEN   1024

void nameWindowToUnixA(LPCSTR lpFileName,char name[MAX_PATHNAME_LEN]);
void WINAPI RtlSecondsSince1970ToTime( DWORD Seconds, LARGE_INTEGER *Time );
