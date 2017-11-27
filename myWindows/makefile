PROG=test_emul

LOCAL_FLAGS=-DENV_UNIX -I. -I.. -I../include_windows

include ../makefile.machine

OBJS=myEvents.o myFiles.o myGetTickCount.o myFindFile.o myDirectoryAndPath.o \
	myLastError.o myModuleFileName.o my_itow.o \
	wine_date_and_time.o wine_strings.o \
	test_emul.o Vector.o MyWindows.o \
	stuff_for_cygwin.o

include ../makefile.glb

