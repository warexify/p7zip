PROG=../../../bin/Formats/arj.dll

LOCAL_FLAGS=

MY_WINDOWS=$(MY_HOME)/myLastError.o \
	   $(MY_HOME)/wine_date_and_time.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)
LIBS=$(LOCAL_LIBS)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/Vector.o\
../../../BUILD/Common/StringConvert.o\
../../../BUILD/Common/String.o\
../../../BUILD/Common/CRC.o\
DllExports.o\
PropVariant.o\
ArjHandler.o\
ArjIn.o\
Decoder1.o\
Decoder2.o\
LZOutWindow.o\
CopyCoder.o\
InBuffer.o\
LimitedStreams.o\
ProgressUtils.o\
ItemNameUtils.o\
OutStreamWithCRC.o

include ../../../makefile.glb

