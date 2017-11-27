PROG=../../../bin/Formats/cab.dll

LOCAL_FLAGS=

LOCAL_SHARED=-shared

MY_WINDOWS=$(MY_HOME)/wine_BSTR.o \
	   $(MY_HOME)/myLastError.o $(MY_HOME)/my_itow.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/wine_date_and_time.o\
	$(MY_HOME)/wine_variant.o

OBJS = \
	DllExports.o \
	String.o \
	StringConvert.o \
	UTFConvert.o \
	Vector.o \
	PropVariant.o \
	CabCopyDecoder.o \
	CabHandler.o \
	CabHeader.o \
	CabIn.o \
	CabInBuffer.o \
	LZXDecoder.o \
	LZXi86Converter.o \
	MSZipDecoder.o \
	InBuffer.o \
	LSBFDecoder.o \
	OutBuffer.o \
	ProgressUtils.o \
	LZOutWindow.o

include ../../../makefile.glb

