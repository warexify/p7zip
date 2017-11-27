PROG=../../../bin/Formats/bz2.dll

LOCAL_FLAGS=

MY_WINDOWS= \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myModuleFileName.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)
LIBS=$(LOCAL_LIBS_DLL)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/StringConvert.o\
DllExports.o\
DLL.o\
PropVariant.o\
CopyCoder.o\
CodecsPath.o\
DummyOutStream.o\
BZip2Handler.o\
BZip2HandlerOut.o\
BZip2Update.o\
ProgressUtils.o

include ../../../makefile.glb

