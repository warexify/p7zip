// Windows/Synchronization.cpp

#include "StdAfx.h"

#include "Synchronization.h"

namespace NWindows {
namespace NSynchronization {

CEvent::CEvent(bool manualReset, bool initiallyOwn)
{
  if (!Create(manualReset, initiallyOwn))
    throw "CreateEvent error";
}

}}
