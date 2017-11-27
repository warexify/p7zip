PROG=test_emul

LOCAL_FLAGS=-DENV_UNIX -I. -I.. -I../include_windows

include ../makefile.machine

LIBS=$(LOCAL_LIBS)

OBJS=myEvents.o myFiles.o myGetTickCount.o myFindFile.o myDirectoryAndPath.o \
	myLastError.o myModuleFileName.o \
	wine_date_and_time.o wine_strings.o \
	mySplitCommandLine.o \
	test_emul.o \
	../BUILD/Common/Vector.o \
	../BUILD/Common/MyWindows.o

include ../makefile.glb

