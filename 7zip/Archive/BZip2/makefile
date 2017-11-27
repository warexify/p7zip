PROG=../../../bin/Formats/bz2.dll

LOCAL_FLAGS=

MY_WINDOWS=$(MY_HOME)/wine_variant.o \
	$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myModuleFileName.o

LOCAL_SHARED=-shared

OBJS = \
	DllExports.o \
	StringConvert.o \
	DLL.o \
	PropVariant.o \
	CopyCoder.o \
	CodecsPath.o \
	DummyOutStream.o \
	BZip2Handler.o \
	BZip2HandlerOut.o \
	BZip2Update.o \
	ProgressUtils.o 

include ../../../makefile.glb

