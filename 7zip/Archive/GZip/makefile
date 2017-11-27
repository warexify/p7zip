PROG=../../../bin/Formats/gz.dll

LOCAL_FLAGS=

MY_WINDOWS= \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myModuleFileName.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/StringConvert.o\
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/String.o\
../../../BUILD/Common/CRC.o\
../../../BUILD/Common/StringToInt.o\
DllExports.o\
DLL.o\
PropVariant.o\
CopyCoder.o\
GZipHandler.o\
GZipHandlerOut.o\
GZipHeader.o\
GZipIn.o\
GZipOut.o\
GZipUpdate.o\
ProgressUtils.o\
CodecsPath.o\
InStreamWithCRC.o\
OutStreamWithCRC.o

include ../../../makefile.glb

