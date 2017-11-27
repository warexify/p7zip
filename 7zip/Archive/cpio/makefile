PROG=../../../bin/Formats/cpio.dll

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
	CopyCoder.o \
	CpioHandler.o \
	CpioHeader.o \
	CpioIn.o \
	PropVariant.o \
	ItemNameUtils.o \
	LimitedStreams.o \
	ProgressUtils.o

include ../../../makefile.glb

