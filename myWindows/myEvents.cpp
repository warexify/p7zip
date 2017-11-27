#include "StdAfx.h"

#include "Windows/Synchronization.h"

//#define TRACEN(u) u;
#define TRACEN(u)  /* */

static NWindows::NSynchronization::CCriticalSection gbl_criticalSection;

#define myEnter() gbl_criticalSection.Enter()
#define myLeave() gbl_criticalSection.Leave()

static void myYield() {
  myLeave();
#ifdef __CYGWIN__
  usleep(10);
#else
  int ret = pthread_yield();
  if (ret != 0) {
    printf("ERROR : pthread_yield()=%d\n",ret);
    exit(EXIT_FAILURE);
  }
#endif
  myEnter();
}

#define MAX_HANDLE 32

#define TYPE_UNKNOWN 0
/* #define TYPE_THREAD  1 */
#define TYPE_EVENT   2
/* #define TYPE_FILE    3 */

static struct {
  HANDLE handle;
  int    type;

  // si EVENT
  BOOL manual_reset;
  BOOL state;

}
listOfHandle[MAX_HANDLE] = { { 0, 0 } };

static int findHandle(HANDLE hHandle) {
  for(int i = 0; i<MAX_HANDLE; i++) {
    if (hHandle == listOfHandle[i].handle)
      return i;
  }
  return -1;
}

static void addHandle(HANDLE hHandle,int type,BOOL manual_reset = FALSE,BOOL initial_state = FALSE) {
  myEnter();
  if (hHandle == INVALID_HANDLE_VALUE) {
    printf("addHandle : INVALID_HANDLE_VALUE\n");
    myLeave();
    return ;
  }
  for(int i = 0; i<MAX_HANDLE; i++) {
    if (listOfHandle[i].handle == 0) {
      listOfHandle[i].handle = hHandle;
      listOfHandle[i].type = type;
      listOfHandle[i].manual_reset = manual_reset;
      listOfHandle[i].state = initial_state;
      myLeave();
      return ;
    }
  }
  printf("addHandle : out of handles\n");
  myLeave();
  exit(EXIT_FAILURE);
}

static void delHandle(HANDLE hHandle) {
  myEnter();
  for(int i = 0; i<MAX_HANDLE; i++) {
    if (listOfHandle[i].handle == hHandle) {
      listOfHandle[i].handle = 0;
      listOfHandle[i].type = 0;
      myLeave();
      return ;
    }
  }
  myLeave();
  printf("WARINING delHandle : %p not found\n",hHandle);
}



/************************* WAITFOR ***************************/


DWORD WINAPI myInfiniteWaitForSingleEvent(HANDLE hHandle) {
  myEnter();
  int indice = findHandle(hHandle);
  if (indice == -1) {
    printf("myWaitForSingleEvent : %p is not a handle\n",hHandle);
    exit(EXIT_FAILURE);
  }

  if (listOfHandle[indice].type != TYPE_EVENT) {
    printf("myWaitForSingleEvent : %p a not an event (type %d)\n",hHandle,listOfHandle[indice].type);
    exit(EXIT_FAILURE);
  }

  while(true) {
    if (listOfHandle[indice].state == TRUE) {
      if (listOfHandle[indice].manual_reset == FALSE)
        listOfHandle[indice].state = FALSE;
      myLeave();
      return WAIT_OBJECT_0;
    }
    myYield();
  }
}

DWORD WINAPI myWaitForMultipleEvents( DWORD count, const HANDLE *handles,
                                      BOOL wait_all, DWORD timeout ) {
  if (timeout != INFINITE) {
    printf("myWaitForMultipleEvents : timeout != INFINITE\n");
    exit(EXIT_FAILURE);
  }

  myEnter();
  for(DWORD i=0;i<count;i++) {
    int indice = findHandle(handles[i]);
    if (indice == -1) {
      printf("myWaitForMultipleEvents[%d] : %p is not a handle\n",i,handles[i]);
      exit(EXIT_FAILURE);
    }
    if (listOfHandle[indice].type != TYPE_EVENT) {
      printf("myWaitForMultipleEvents[%d] : %p is not an event (type %d)\n",i,handles[i],listOfHandle[indice].type);
      exit(EXIT_FAILURE);
    }
  }
  if (wait_all) {
    while(true) {
      bool tout_trouve = true;
      for(DWORD i=0;i<count;i++) {
        int indice = findHandle(handles[i]);

        if (listOfHandle[indice].state == FALSE) {
          tout_trouve = false;
          break;
        }
      }
      if (tout_trouve) {
        for(DWORD i=0;i<count;i++) {
          int indice = findHandle(handles[i]);

          if (listOfHandle[indice].manual_reset == FALSE)
            listOfHandle[indice].state = FALSE;
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
        int indice = findHandle(handles[i]);

        if (listOfHandle[indice].state == TRUE) {
          if (listOfHandle[indice].manual_reset == FALSE)
            listOfHandle[indice].state = FALSE;
          myLeave();
          return WAIT_OBJECT_0+i;
        }
      }
      myYield();
    }
  }
}

/*************** EVENT *******************/

static int count_event = 0x1234000;

HANDLE WINAPI myCreateEvent(BOOL manual_reset,BOOL initial_state) {
  myEnter();
  HANDLE ret = (HANDLE)(count_event++);
  myLeave();
  addHandle(ret,TYPE_EVENT,manual_reset,initial_state);
  return ret;
}

BOOL myChangeStateEvent(HANDLE hEvent , BOOL newState) {
  myEnter();
  int indice = findHandle(hEvent);
  if (indice == -1) {
    printf("myChangeStateEvent : %p is not a handle\n",hEvent);
    exit(EXIT_FAILURE);
  }

  if (listOfHandle[indice].type != TYPE_EVENT) {
    printf("myChangeStateEvent : %p is not an event (type %d)\n",hEvent,listOfHandle[indice].type);
    exit(EXIT_FAILURE);
  }
  listOfHandle[indice].state = newState;
  myLeave();

  return TRUE;
}

BOOL WINAPI mySetEvent(HANDLE hEvent)   {
  return ::myChangeStateEvent(hEvent,TRUE);
}
BOOL WINAPI myResetEvent(HANDLE hEvent) {
  return ::myChangeStateEvent(hEvent,FALSE);
}
BOOL WINAPI myCloseEvent(HANDLE hFile) {
  delHandle(hFile);
  return TRUE;
}

