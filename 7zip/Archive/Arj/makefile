PROG=../../../bin/Formats/arj.dll

LOCAL_FLAGS=

LOCAL_SHARED=-shared

MY_WINDOWS=\
	$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/wine_variant.o

OBJS = \
	DllExports.o \
	CRC.o \
	String.o \
	StringConvert.o \
	Vector.o \
	PropVariant.o \
	ArjHandler.o \
	ArjIn.o \
	Decoder1.o \
	Decoder2.o \
	LZOutWindow.o \
	CopyCoder.o \
	InBuffer.o \
	LimitedStreams.o \
	ProgressUtils.o \
	ItemNameUtils.o \
	OutStreamWithCRC.o

include ../../../makefile.glb

