PROG=../../../bin/Formats/split.dll

LOCAL_FLAGS=

MY_WINDOWS= \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/myLastError.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)

OBJS = \
../../../BUILD/Common/Alloc.o \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Vector.o \
../../../BUILD/Common/StringConvert.o \
../../../BUILD/Common/String.o \
DllExports.o \
PropVariant.o \
CopyCoder.o \
ProgressUtils.o \
SplitHandler.o \
SplitHanlerOut.o \
MultiStream.o 

include ../../../makefile.glb

