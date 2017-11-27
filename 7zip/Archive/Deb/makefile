PROG=../../../bin/Formats/deb.dll

LOCAL_FLAGS=

MY_WINDOWS=\
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/wine_date_and_time.o 

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/Vector.o\
../../../BUILD/Common/StringConvert.o\
../../../BUILD/Common/String.o\
DllExports.o\
PropVariant.o\
CopyCoder.o\
DebHandler.o\
DebHeader.o\
DebIn.o\
ItemNameUtils.o\
LimitedStreams.o\
ProgressUtils.o

include ../../../makefile.glb

