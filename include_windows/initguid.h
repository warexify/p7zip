#ifndef _INITGUID_H
#define _INITGUID_H

#ifndef DEFINE_GUID
#include "Common/MyWindows.h"
#endif
#undef DEFINE_GUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
      MY_EXTERN_C const GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

#endif
