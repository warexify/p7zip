PROG=../../../bin/Codecs/BZip2.dll

LOCAL_FLAGS=

MY_WINDOWS= $(MY_HOME)/wine_variant.o $(MY_HOME)/wine_BSTR.o

LOCAL_SHARED=-shared

VPATH=Original

OBJS = \
	DllExports.o \
	BZip2Decoder.o \
	BZip2Encoder.o \
	BZip2Error.o \
	blocksort.o bzlib.o compress.o crctable.o decompress.o huffman.o \
	randtable.o

include ../../../makefile.glb

