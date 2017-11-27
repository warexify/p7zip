PROG=../../../bin/Codecs/BZip2.dll

LOCAL_FLAGS=

MY_WINDOWS=

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)
LIBS=$(LOCAL_LIBS)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o\
DllExports.o\
BZip2Decoder.o\
BZip2Encoder.o\
BZip2Error.o\
blocksort.o\
bzlib.o\
compress.o\
crctable.o\
decompress.o\
huffman.o\
randtable.o

include ../../../makefile.glb

