PROG=../../../bin/Formats/cab.so

LOCAL_FLAGS=

MY_WINDOWS=$(MY_HOME)/wine_date_and_time.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)
LIBS=$(LOCAL_LIBS)

OBJS = \
../../../Common/MyWindows.o \
../../../Common/Alloc.o\
../../../Common/UTFConvert.o\
../../../Common/StringConvert.o\
../../../Common/Vector.o\
../../../Common/String.o\
../../../Common/IntToString.o\
DllExports.o\
PropVariant.o\
CabCopyDecoder.o\
CabHandler.o\
CabHeader.o\
CabIn.o\
CabInBuffer.o\
LZXDecoder.o\
LZXi86Converter.o\
MSZipDecoder.o\
InBuffer.o\
LSBFDecoder.o\
OutBuffer.o\
ProgressUtils.o\
LZOutWindow.o

include ../../../makefile.glb

