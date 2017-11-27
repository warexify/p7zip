// Windows/Thread.h

#pragma once

#ifndef __WINDOWS_THREAD_H
#define __WINDOWS_THREAD_H

#include "Handle.h"
#include "Defs.h"

namespace NWindows {

class CThread
{
	pthread_t _tid;
	bool _created;
public:
   CThread() : _created(false) {}
  ~CThread() { Close(); }

  void Wait()
  {
	if (_created) 
	{
		void *thread_return;
		pthread_join(_tid,&thread_return);
		_created = false;
	}
  }
  void WaitAndClose()
  {
	Wait();
	Close();
  }

  bool Close()
  {
    if (!_created) return true;
    
/*
    if (!::CloseHandle(_handle))
      return false;
*/
    pthread_detach(_tid);
    _tid = 0;
    _created = false;
    return true;
  }

  bool Create(DWORD (*startAddress)(void *), LPVOID parameter)
  {
	pthread_attr_t attr;
	pthread_t tid;
	int ret;

	_created = false;

	ret = pthread_attr_init(&attr);
	if (ret) return false;

	ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	if (ret) return false;

	ret = pthread_create(&_tid, &attr, (void * (*)(void *))startAddress, parameter);

	/* ret2 = */ pthread_attr_destroy(&attr);

	if (ret) return false;
	
	_created = true;

	return _created;
  }
};

}

#endif
