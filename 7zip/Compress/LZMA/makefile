PROG=../../../bin/Codecs/LZMA.dll

LOCAL_FLAGS=-DCOMPRESS_MF_BT -DCOMPRESS_MF_PAT -DCOMPRESS_MF_HC -DCOMPRESS_MF_MT

MY_WINDOWS= $(MY_HOME)/myEvents.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/CRC.o\
../../../BUILD/Common/AlignedBuffer.o\
DllExports.o\
InBuffer.o\
OutBuffer.o\
RangeCoderBit.o\
MT.o\
LZInWindow.o\
LZOutWindow.o\
Synchronization.o\
LZMADecoder.o\
LZMAEncoder.o

include ../../../makefile.glb

