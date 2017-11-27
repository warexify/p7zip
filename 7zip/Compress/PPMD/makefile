PROG=../../../bin/Codecs/PPMD.dll

LOCAL_FLAGS=

MY_WINDOWS=

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)
LIBS=$(LOCAL_LIBS)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o \
DllExports.o\
PPMDDecoder.o\
PPMDEncoder.o\
InBuffer.o\
OutBuffer.o

include ../../../makefile.glb

