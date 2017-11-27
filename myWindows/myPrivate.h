
#define MAX_PATHNAME_LEN   1024

/*
#ifdef __cplusplus
extern "C" {
#endif
*/

void nameWindowToUnixA(LPCSTR lpFileName,char name[MAX_PATHNAME_LEN]);
void WINAPI RtlSecondsSince1970ToTime( DWORD Seconds, LARGE_INTEGER *Time );

/*
#ifdef __cplusplus
}
#endif
*/

