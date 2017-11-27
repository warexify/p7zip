PROG=../../../bin/Formats/Tar.dll

LOCAL_FLAGS=

MY_WINDOWS=$(MY_HOME)/wine_variant.o \
	$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/myLastError.o

LOCAL_SHARED=-shared

OBJS = \
	DllExports.o \
	String.o \
	StringConvert.o \
	Vector.o \
	PropVariant.o \
	CopyCoder.o \
	TarHandler.o \
	TarHandlerOut.o \
	TarHeader.o \
	TarIn.o \
	TarOut.o \
	TarUpdate.o \
	ItemNameUtils.o \
	LimitedStreams.o \
	ProgressUtils.o

include ../../../makefile.glb

