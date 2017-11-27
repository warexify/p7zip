PROG=../../../bin/Formats/gz.dll

LOCAL_FLAGS=

MY_WINDOWS=$(MY_HOME)/wine_variant.o \
	$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myModuleFileName.o

LOCAL_SHARED=-shared

OBJS = \
	DllExports.o \
	CRC.o \
	String.o \
	StringConvert.o \
	StringToInt.o \
	DLL.o \
	PropVariant.o \
	CopyCoder.o \
	GZipHandler.o \
	GZipHandlerOut.o \
	GZipHeader.o \
	GZipIn.o \
	GZipOut.o \
	GZipUpdate.o \
	ProgressUtils.o \
	CodecsPath.o \
	InStreamWithCRC.o \
	OutStreamWithCRC.o

include ../../../makefile.glb

