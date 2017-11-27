PROG=../../../bin/Codecs/LZMA.dll

LOCAL_FLAGS=-DCOMPRESS_MF_BT -DCOMPRESS_MF_PAT -DCOMPRESS_MF_HC -DCOMPRESS_MF_MT

MY_WINDOWS= $(MY_HOME)/myEvents.o $(MY_HOME)/wine_BSTR.o

LOCAL_SHARED=-shared

OBJS = \
	DllExports.o \
	InBuffer.o \
	OutBuffer.o \
	RangeCoderBit.o \
	MT.o \
	LZInWindow.o \
	LZOutWindow.o \
	AlignedBuffer.o \
	CRC.o \
	Synchronization.o \
	LZMADecoder.o \
	LZMAEncoder.o \
	LZMALen.o \
	LZMALiteral.o

#NewHandler.o

include ../../../makefile.glb

