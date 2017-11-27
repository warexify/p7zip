PROG=../../../bin/Formats/cab.dll

LOCAL_FLAGS=

MY_WINDOWS=$(MY_HOME)/myLastError.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/wine_date_and_time.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)
LIBS=$(LOCAL_LIBS)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/UTFConvert.o\
../../../BUILD/Common/StringConvert.o\
../../../BUILD/Common/Vector.o\
../../../BUILD/Common/String.o\
../../../BUILD/Common/IntToString.o\
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

