PROG=test_emul

LOCAL_FLAGS=-DENV_UNIX -I. -I.. -I../include_windows

include ../makefile.machine

OBJS=myEvents.o myFiles.o myGetTickCount.o myFindFile.o myDirectoryAndPath.o \
	myLastError.o myModuleFileName.o my_ui64toa.o \
	wine_date_and_time.o wine_strings.o \
	test_emul.o \
	../BUILD/Common/Vector.o \
	../BUILD/Common/MyWindows.o

include ../makefile.glb

