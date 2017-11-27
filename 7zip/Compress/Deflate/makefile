PROG=../../../bin/Codecs/Deflate.dll

LOCAL_FLAGS=

MY_WINDOWS= $(MY_HOME)/wine_variant.o $(MY_HOME)/wine_BSTR.o

LOCAL_SHARED=-shared

OBJS = \
	DllExports.o \
	HuffmanEncoder.o \
	InBuffer.o \
	LSBFDecoder.o \
	LSBFEncoder.o \
	OutBuffer.o \
	CRC.o \
	LZInWindow.o \
	LZOutWindow.o \
	DeflateDecoder.o \
	DeflateEncoder.o

include ../../../makefile.glb

