PROG=../../../../bin/Codecs/Rar29.so

LOCAL_FLAGS=

MY_WINDOWS=

include ../../../../makefile.crc32
include ../../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)
LIBS=$(LOCAL_LIBS)

OBJS = \
../../../Common/MyWindows.o \
../../../Common/CRC.o\
../../../Common/Vector.o\
CodecExports.o \
DllExports.o \
Rar1Decoder.o \
Rar2Decoder.o \
Rar3Decoder.o \
Rar3Vm.o \
RarCodecsRegister.o \
InBuffer.o \
OutBuffer.o \
StreamUtils.o \
LZOutWindow.o \
$(OBJ_CRC32) \
Alloc.o

include ../../../../makefile.glb

