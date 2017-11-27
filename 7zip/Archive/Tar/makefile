PROG=../../../bin/Formats/Tar.dll

LOCAL_FLAGS=

MY_WINDOWS= \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/myLastError.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)
LIBS=$(LOCAL_LIBS)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/Vector.o\
../../../BUILD/Common/StringConvert.o\
../../../BUILD/Common/String.o\
../../../BUILD/Common/IntToString.o\
DllExports.o\
PropVariant.o\
CopyCoder.o\
TarHandler.o\
TarHandlerOut.o\
TarHeader.o\
TarIn.o\
TarOut.o\
TarUpdate.o\
ItemNameUtils.o\
LimitedStreams.o\
ProgressUtils.o

include ../../../makefile.glb

