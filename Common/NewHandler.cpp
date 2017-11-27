// NewHandler.cpp
 
#include "StdAfx.h"

#include "NewHandler.h"

void * __cdecl operator new(size_t size)
{
  void *p = ::malloc(size);
  if (p == 0)
    throw CNewException();
  return p;
}

void __cdecl operator delete(void *p)
{
  ::free(p);
}
