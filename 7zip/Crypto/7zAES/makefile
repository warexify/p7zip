PROG=../../../bin/Codecs/7zAES.dll

LOCAL_FLAGS=

MY_WINDOWS=$(MY_HOME)/wine_variant.o \
	$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/myModuleFileName.o \
	$(MY_HOME)/myDirectoryAndPath.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myEvents.o

LOCAL_SHARED=-shared

OBJS = \
	DllExports.o \
	StringConvert.o \
	Vector.o \
	StreamObjects.o \
	DLL.o \
	Synchronization.o \
	7zAES.o \
	SHA256.o

include ../../../makefile.glb

