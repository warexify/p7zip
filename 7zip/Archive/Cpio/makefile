PROG=../../../bin/Formats/cpio.dll

LOCAL_FLAGS=

MY_WINDOWS=\
	   $(MY_HOME)/myLastError.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/wine_date_and_time.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)
LIBS=$(LOCAL_LIBS)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/Vector.o\
../../../BUILD/Common/StringConvert.o\
DllExports.o\
CopyCoder.o\
CpioHandler.o\
CpioHeader.o\
CpioIn.o\
PropVariant.o\
ItemNameUtils.o\
LimitedStreams.o\
ProgressUtils.o

include ../../../makefile.glb

