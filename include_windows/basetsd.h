#ifndef _BASETSD_H
#define _BASETSD_H

#ifdef __GNUC__
#ifndef __int64
#define __int64 long long
#endif
#endif
typedef int INT32, *PINT32;
typedef unsigned int UINT32, *PUINT32;
typedef unsigned __int64 UINT64,  *PUINT64;
typedef __int64 INT64,  *PINT64;
typedef  unsigned int UINT_PTR, *PUINT_PTR;

#endif /* _BASETSD_H */
