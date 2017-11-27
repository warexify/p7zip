PROG=../../../bin/Formats/deb.dll

LOCAL_FLAGS=

LOCAL_SHARED=-shared

MY_WINDOWS=$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/wine_variant.o

OBJS = \
	DllExports.o \
	StringConvert.o \
	Vector.o \
	PropVariant.o \
	CopyCoder.o \
	DebHandler.o \
	DebHeader.o \
	DebIn.o \
	ItemNameUtils.o \
	LimitedStreams.o \
	ProgressUtils.o

include ../../../makefile.glb

