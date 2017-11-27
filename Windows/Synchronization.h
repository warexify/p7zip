// Windows/Synchronization.h

// #pragma once

#ifndef __WINDOWS_SYNCHRONIZATION_H
#define __WINDOWS_SYNCHRONIZATION_H

#include "Defs.h"
#include "Handle.h"

namespace NWindows {
namespace NSynchronization {

class CBaseEvent
{
	HANDLE _handle;

public:
	CBaseEvent() : _handle(0) {} 
	 ~CBaseEvent() { Close(); }

 operator HANDLE() { return _handle; }

  bool Create(bool manualReset, bool initiallyOwn)
  {
    _handle = ::myCreateEvent(BoolToBOOL(manualReset),BoolToBOOL(initiallyOwn));
    return (_handle != 0);
  }

  bool Set() { return BOOLToBool(::mySetEvent(_handle)); }
  bool Reset() { return BOOLToBool(::myResetEvent(_handle)); }

  bool Lock()
    { return (::myInfiniteWaitForSingleEvent(_handle) == WAIT_OBJECT_0); }
  
  bool Close()
  {
    if (_handle == NULL)
      return true;
    if (!::myCloseEvent(_handle))
      return false;
    _handle = NULL;
    return true;
  }

};

class CEvent: public CBaseEvent
{
public:
  CEvent() {};
  CEvent(bool manualReset, bool initiallyOwn);
};

class CManualResetEvent: public CEvent
{
public:
  CManualResetEvent(bool initiallyOwn = false):
    CEvent(true, initiallyOwn) {};
};

class CAutoResetEvent: public CEvent
{
public:
  CAutoResetEvent(bool initiallyOwn = false):
    CEvent(false, initiallyOwn) {};
};

class CCriticalSection
{
  pthread_mutex_t _object;
public:
  CCriticalSection() { ::pthread_mutex_init(&_object,0); }
  ~CCriticalSection() { ::pthread_mutex_destroy(&_object); }
  void Enter() { ::pthread_mutex_lock(&_object); }
  void Leave() { ::pthread_mutex_unlock(&_object); }
};

class CCriticalSectionLock
{
  CCriticalSection &_object;
  void Unlock()  { _object.Leave(); }
public:
  CCriticalSectionLock(CCriticalSection &object): _object(object) 
    {_object.Enter(); } 
  ~CCriticalSectionLock() { Unlock(); }
};

}}

#endif
