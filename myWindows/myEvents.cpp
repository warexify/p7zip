#include "StdAfx.h"

#include "Windows/Synchronization.h"
#ifdef DEBUG
#include <assert.h>
#endif

static NWindows::NSynchronization::CCriticalSection gbl_criticalSection;

#define myEnter() gbl_criticalSection.Enter()
#define myLeave() gbl_criticalSection.Leave()
#define myYield() gbl_criticalSection.WaitCond()

typedef struct {
#ifdef DEBUG
#define TYPE_UNKNOWN 0
#define TYPE_EVENT   0x78CAFEDE 
  int    type;
#endif
  BOOL manual_reset;
  BOOL state;
} EventItem;

/************************* WAITFOR ***************************/


DWORD WINAPI myInfiniteWaitForSingleEvent(HANDLE hHandle) {
  EventItem* hitem = (EventItem *)hHandle;
#ifdef DEBUG
  assert(hitem);
  assert(hitem->type == TYPE_EVENT);
#endif
  myEnter();
  while(true) {
    if (hitem->state == TRUE) {
      if (hitem->manual_reset == FALSE) {
        hitem->state = FALSE;
      }
      myLeave();
      return WAIT_OBJECT_0;
    }
    myYield();
  }
}

DWORD WINAPI WaitForMultipleObjects( DWORD count, const HANDLE *handles, BOOL wait_all, DWORD timeout )
{
#ifdef DEBUG
  assert(timeout == INFINITE);
#endif

  myEnter();
  if (wait_all) {
    while(true) {
      bool found_all = true;
      for(DWORD i=0;i<count;i++) {
        EventItem* hitem = (EventItem*)handles[i];
#ifdef DEBUG
        assert(hitem);
        assert(hitem->type == TYPE_EVENT);
#endif
        if (hitem->state == FALSE) {
          found_all = false;
          break;
        }
      }
      if (found_all) {
        for(DWORD i=0;i<count;i++) {
          EventItem* hitem = (EventItem*)handles[i];

          if (hitem->manual_reset == FALSE) {
            hitem->state = FALSE;
          }
        }
        myLeave();
        return WAIT_OBJECT_0;
      } else {
        myYield();
      }
    }
  } else {
    while(true) {
      for(DWORD i=0;i<count;i++) {
        EventItem* hitem = (EventItem*)handles[i];
#ifdef DEBUG
        assert(hitem);
        assert(hitem->type == TYPE_EVENT);
#endif
        if (hitem->state == TRUE) {
          if (hitem->manual_reset == FALSE) {
            hitem->state = FALSE;
          }
          myLeave();
          return WAIT_OBJECT_0+i;
        }
      }
      myYield();
    }
  }
}

/*************** EVENT *******************/

HANDLE WINAPI myCreateEvent(BOOL manual_reset,BOOL initial_state) {
  EventItem * handle = (EventItem *)malloc(sizeof(*handle));
  if (handle)
  {
#ifdef DEBUG
    handle->type   = TYPE_EVENT;
#endif
    handle->manual_reset = manual_reset;
    handle->state = initial_state;

  }
  return (HANDLE)handle;
}

BOOL WINAPI mySetEvent(HANDLE hEvent)   {
  EventItem* hitem = (EventItem *)hEvent;
#ifdef DEBUG
  assert(hitem);
  assert(hitem->type == TYPE_EVENT);
#endif
  myEnter();
  hitem->state = TRUE;
  myLeave();
  gbl_criticalSection.SignalCond();
  return TRUE;
}
BOOL WINAPI myResetEvent(HANDLE hEvent) {
  EventItem* hitem = (EventItem *)hEvent;
#ifdef DEBUG
  assert(hitem);
  assert(hitem->type == TYPE_EVENT);
#endif
  myEnter();
  hitem->state = FALSE;
  myLeave();
  gbl_criticalSection.SignalCond();
  return TRUE;
}

BOOL WINAPI myCloseEvent(HANDLE hEvent) {
#ifdef DEBUG
  assert(hitem);
  assert(((EventItem*)hEvent)->type == TYPE_EVENT);
  ((EventItem*)hEvent)->type = TYPE_UNKNOWN;
#endif
  free(hEvent);
  return TRUE;
}

