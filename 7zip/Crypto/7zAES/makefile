PROG=../../../bin/Codecs/7zAES.dll

LOCAL_FLAGS=

MY_WINDOWS= \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/myModuleFileName.o \
	$(MY_HOME)/myDirectoryAndPath.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myEvents.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/StringConvert.o\
../../../BUILD/Common/Vector.o\
DllExports.o\
StreamObjects.o\
DLL.o\
Synchronization.o\
7zAES.o\
SHA256.o

include ../../../makefile.glb

